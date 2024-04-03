CFILES = $(wildcard *.c src/*.c games/*.c)
SFILES = $(wildcard boot/*.S)
OFILES = $(CFILES:.c=.o) $(SFILES:.S=.o)
LLDPATH ?= ld.lld
CLANGPATH ?= clang
GCCPATH ?= aarch64-linux-gnu
CLANGFLAGS = -Wall -O1 -ffreestanding -nostdlib -mcpu=cortex-a72+nosimd


all: clean kernel8.img

%.o: %.c
	$(CLANGPATH) --target=aarch64-elf $(CLANGFLAGS) -c $< -o $@

%.o: %.S
	$(CLANGPATH)  --target=aarch64-elf $(CLANGFLAGS) -c $< -o $@

kernel8.img: $(OFILES)
	$(LLDPATH) -m aarch64elf -nostdlib $(OFILES) -T boot/linker.ld -o kernel8.elf
	$(GCCPATH)-objcopy -O binary kernel8.elf kernel8.img

clean:
	/bin/rm kernel8.elf */*.o *.img > /dev/null 2> /dev/null || true