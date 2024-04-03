CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
GCCFLAGS = -Wall -O1 -ffreestanding -nostdinc -nostdlib -nostartfiles
GCCPATH ?= aarch64-linux-gnu

all: clean kernel8.img

boot.o: boot.S
	$(GCCPATH)-gcc $(GCCFLAGS) -c boot.S -o boot.o

%.o: %.c
	$(GCCPATH)-gcc $(GCCFLAGS) -c $< -o $@


kernel8.img: boot.o $(OFILES)
	$(GCCPATH)-ld -nostdlib boot.o $(OFILES) -T linker.ld -o kernel8.elf
	$(GCCPATH)-objcopy -O binary kernel8.elf kernel8.img

clean:
	/bin/rm kernel8.elf *.o *.img > /dev/null 2> /dev/null || true