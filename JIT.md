# A generic JIT engine for P2

Support routines for producing Just-in-time (JIT) compilers
for the Parallax Propeller 2 chip.
   
Copyright 2019 Total Spectrum Software Inc.
TERMS OF USE: MIT License

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


## Introduction

These are routines for maintaining a cache of basic blocks / traces
in HUB memory for a bytecode based interpreter. The idea is that
as the interpreter encounters bytecode instructions, it compiles them
to P2 instructions and they are saved in a "trace cache" in HUB memory.
A trace ends when a bytecode branch is encountered, or when the cache
runs out of room; that point the interpreter inserts a P2 branch at the
end of the cache and then jumps to the start of the compiled trace.

We use LUT to maintain a mapping from virtual machine PCs to compiled
traces. If there is a cache hit we can skip compiling the trace and just
jump directly to the cached P2 code.

Note that the cache is additive; we never evict anything from cache
until the cache fills up, at which time we flush it and re-initialize.
The benefit of this is that it means that whenever we have a jump
in cache that goes directly to another point in cache, we can replace it
with a direct P2 jump instruction, rather than having to go through the
LUT table lookup to figure out where the cached code is. This is a
significant performance improvement.

Also note that traces end with any branch, and no branch can jump into
the middle of a trace (only to the beginning). This means that the JIT
compiler may optimize bytecode instruction sequences without needing
to worry about state changes in between the bytecodes. That is, given
a bytecode sequence like:
```
  L1:
     pushimm 2
  L2:
     push  varA
     add
     pop varA
```
if we start compiling at L1 we may emit:
```
   add varA, #2
```
because if the VM ever branches to L2 it will start a completely new
trace.
     
## Usage

### Compile time

The JIT engine needs some memory for a cache. You can do this in one of
two ways. For a HUB cache (the default) create symbols CACHE_START and
CACHE_END pointing to the start and end of the cache. For best
performance make sure these are long aligned.

For example:

```
    orgh   ' must be in HUB after $800
    alignl
CACHE_START
    byte 0[4096]   ' 4K cache
CACHE_END
```

Alternatively, you can keep the cache entirely in LUT. This makes for
a relatively small cache (only 1.5K) but for small programs may
improve performance. To do this, define the symbol USE_LUT_CACHE
before including `jit_engine.spinh`.

### Runtime

As part of your VM initialization, make sure to call `jit_init_cache`.

After your interpreter has done its setup, it should set `ptrb` to the
P2 address of the bytecode to interpret and then jump to `jit_set_pc`.
This will look in the cache, find it empty (because jit_init_cache set it
up entry) and then as part of the cache miss code it will loop
calling `compile_bytecode` with `ptrb` still pointing at the bytecode
to compile. This will continue either until the cache is full or
the VM interpreter calls `jit_emit_direct_branch` or
`jit_emit_indirect_branch`, at which point we will close out the cache
line and then jump to it,

The `compile_bytecode` routine that you provide should read one VM
bytecode instruction and convert it to a sequence of P2 instructions.
It's OK if a VM instruction needs several bytes; just make sure to
leave `ptrb` pointing after the whole instruction.

To generate some P2 instructions, set the variable `jit_instrptr`
to point to the P2 instructions (in COG memory), set `pb` to the
number of instructions, and then call `jit_emit`. For example, to
generate 3 instructions starting at `my_add_pattern`, do:
```
   mov    jit_instrptr, #my_add_pattern
   callpb #3, #jit_emit
```
This will place the P2 instructions into the cache.

Note that the P2 instructions generated with `jit_emit` should *not*
change the control flow of the VM code; for those we need
`jit_emit_direct_branch` and `jit_emit_iindirect_branch`. It is OK
for the P2 instructions to contain a subroutine call to some runtime
support code, but that support code should return to its original place
(or abort the program entirely).

For a branch instruction, there are `jit_emit_direct_branch` and
`jit_emit_indirect_branch`. These will close out a trace and return
directly to `jit_set_pc`, so the compiler should call these last. For
`jit_emit_direct_branch`, set `ptrb` to the value we want to branch to
(this must be a P2 HUB address). For `jit_emit_indirect_branch`, emit
code to set `ptrb` to the value you want, and then call
`jit_emit_indirect_branch`. In both cases you should set the variable
`condition` to a P2 condition code to be applied to the branch. For
unconditional branches this should be `$f`. For conditional branches
it should be a different non-zero value, e.g.  `$a` for `if_z`.
See the P2 instruction set manual for details. If a `0` is passed in
`condition` to one of the emit_branch functions, it will close out the
cache line but not emit any branch (implicitly it will produce
a branch to the next PC in `ptrb`).

## API

### jit_init

Initialize the JIT engine.

### jit_emit

Emit generated instructions from COG memory. `jit_instrptr` points at
the instructions to emit, and `pb` gives the number of instructions to
emit. Use this only for non-branch instructions.

### jit_emit_direct_branch

Emit a conditional branch instruction. `jit_condition` is a 4 bit
value giving the P2 condition (except that condition 0 means "never",
just as in P1). `jit_instrptr` gives the branch destination.

This function will not return, so it must be the last one called when
generating code for a VM branch instruction.

### jit_emit_indirect_branch

Emits an indirect branch instruction. `jit_condition` is a 4 bit value
giving the P2 condition (0 means "never"). Code to put the new PC into
the `ptrb` register must have been generated prior to this call.

This function will not return, so it must be the last one called when
generating code for a VM branch instruction.
