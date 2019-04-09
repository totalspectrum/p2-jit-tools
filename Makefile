FASTSPIN=/home/ersmith/Parallax/spin2cpp/build/fastspin


COMMON=sample.spin2 util_serial.spin2 timing.bytecode

default: plain.binary xbyte.binary jit.binary optjit.binary

xbyte.binary: $(COMMON) sample_xbyte.spin2
	$(FASTSPIN) -2 -o xbyte.binary -DUSE_XBYTE sample.spin2

plain.binary: $(COMMON) sample_plain.spin2
	$(FASTSPIN) -2 -o plain.binary -DUSE_PLAIN sample.spin2

jit.binary: $(COMMON) sample_jit.spin2 jit_engine.spinh
	$(FASTSPIN) -l -2 -o jit.binary -DUSE_JIT sample.spin2

optjit.binary: $(COMMON) sample_optjit.spin2 jit_engine.spinh stack_cache.spinh
	$(FASTSPIN) -l -2 -o optjit.binary -DUSE_OPT_JIT sample.spin2

clean:
	rm -f *.binary
