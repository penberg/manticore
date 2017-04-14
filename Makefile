ARCH ?= $(shell uname -m)

include arch/$(ARCH)/Makefile
include lib/libc/Makefile

includes += -include include/kernel/kernel.h -Iinclude

objs += kernel/init.o
objs += kernel/panic.o
objs += kernel/printf.o
objs += kernel/thread.o
objs += mm/kmem.o

rust_src += kernel/panic.rs
rust_src += kernel/print.rs
rust_src += kernel/lib.rs
rust_src += kernel/memory.rs

WARNINGS = -Wall -Wextra -Wno-unused-parameter
CFLAGS += -O3 -g $(WARNINGS) -ffreestanding $(includes)
ASFLAGS += -D__ASSEMBLY__ $(includes)
LDFLAGS += --gc-sections

LIBKERNEL=target/$(ARCH)-unknown-none/release/libkernel.a

DEPS=.deps
$(objs): | $(DEPS)
$(DEPS):
	mkdir -p $(DEPS)

kernel.elf: $(objs) $(LIBKERNEL)
	$(CROSS_PREFIX)ld $(LDFLAGS) -Tarch/$(ARCH)/kernel.ld $^ -o $@ -Ltarget/$(ARCH)-unknown-none/release -lkernel

$(LIBKERNEL): $(rust_src)
	CC=$(CROSS_PREFIX)gcc RUST_TARGET_PATH=$(PWD) xargo build --release --target $(ARCH)-unknown-none

%.o: %.c
	$(CROSS_PREFIX)gcc $(CFLAGS) -MD -c -o $@ $< -MF $(DEPS)/$(notdir $*).d

%.o: %.S
	$(CROSS_PREFIX)gcc $(ASFLAGS) -MD -c $< -o $@ -MF $(DEPS)/$(notdir $*).d

clean:
	rm -f kernel.elf $(objs)
	rm -rf target
	rm -rf $(DEPS)

.PHONY: all clean

-include $(DEPS)/*.d
