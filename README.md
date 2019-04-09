# Simple Interpreter Framework

This is a simple interpreter framework for P2. It's mainly focused
on producing JIT (just in time) interpreters, but there are examples
of a plain interpreter and an xbyte based one.

There's a sample interpreter here for a very simple bytecode based
virtual machine (documented in vm.txt), and two different bytecode
programs. `blink.bytecode` is a program to blink an LED on pin 56
five times, then print elapsed cycles. This is to verify that things
are working properly. `timing.bytecode` toggles pin 0 one million
times and then prints elapsed cycles. This is to check timing.

## Usage

Edit the Makefile to give the proper path to fastspin. In theory this
code could be compiled with other P2 assemblers, but I've used
`#include` and `#define` in a lot of places, so you'd have
to manually make those substitutions.

Just running `make` will produce 4 binaries: plain.binary, jit.binary,
optjit.binary, and xbyte.binary. `make clean` will remove these. I'm
not sure all the dependencies are correct, so you may need to `make
clean` after bytecode changes.

The bytecode program to use is given with a `#include` in sample.spin2.
Change this if you want to try out a different program.

## Files

  * Makefile:           used to build the 3 interpreters
  * jit_engine.spinh:   the JIT engine, see JIT.md for details
  * sample.spin2:       common top level for sample program
  * sample_jit.spin2:   JIT version of sample code
  * sample_optjit.spin2:  optimizing  JIT version of sample code
  * sample_plain.spin2: regular interpreter
  * sample_xbyte.spin2: xbyte based interpreter
  * util_serial.spin2:  some serial utilities
  * timing.bytecode:    timing program
  * blink,bytecode:     blink program
  * vm.txt:             description of VM

