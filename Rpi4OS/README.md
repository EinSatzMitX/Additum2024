Additum 2023/2024
===

In meinem Additum für diese Jahr habe ich mich dafür entschieden verschiedene Projekte mit meinem Raspberry Pi 4B (kurz: RPi) zu behandeln.
Allerdings hat mich ein bestimmtes Projekt besonders fasziniert: Ein eigenen Kernel für das Betriebssystem (auch genannt: OS) meines RPi‘s schreiben.

Dafür benötigte Hardware:
---

- RPi (logischerweise) & SDHC-Karte
- PC, auf dem der Code für den Kernel geschrieben wird (Dev-Machine)
- Sowohl MicroHDMI-HDMI-Kabel & Bildschirm, als auch [USB-SerialTTL-Kabel](https://www.amazon.de/Hailege-PL2303TA-RS232-Download-Windows/dp/B07Z7PPT6Y/ref=sr_1_3?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=1I8QYDEBL9B02&keywords=2+Pack+Debug+Cable+for+Raspberry+Pi+USB+Programming+USB+to+TTL+Serial+Cable%2C+Windows+XP%2FVISTA%2F+7%2F8%2F+8.1+Supported&qid=1706455641&sprefix=2+pack+debug+cable+for+raspberry+pi+usb+programming+usb+to+ttl+serial+cable+windows+xp%2Fvista%2F+7%2F8%2F+8.1+supported%2Caps%2C75&sr=8-3), um den RPi mit der Dev Machine zu verbinden und via UART darauf zu arbeiten

Dafür Benötigte Software:
---

- Code-Editor(en) (ich habe mich für VSCode & Vim entschieden)
- ["AArch64 ELF bare-metal target“](https://developer.arm.com/-/media/Files/downloads/gnu-a/10.2-2020.11/binrel/gcc-arm-10.2-2020.11-aarch64-aarch64-none-elf.tar.xz) (Cross-Compiler,um den C-Code auf der Dev-Machine, die auf einem x86_64 Processor läuft für den RPi, der auf einem ARM-Processor läuft zu Compilen)
- ["Gnu Make"](https://www.gnu.org/software/make/) (wird später im Detail erläutert)
- [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) (Programm, um die Dev-Machine mittels UART-Protocol mit dem Rpi zu verbinden und sich somit das Leben um einiges zu erleichtern)
- [Driver für das USB-SerialTTL-Kabel](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)

Vorgehen & Funktionsweise:
---

Da ich das komplette Vorgehen auf keinen Fall unter 15 Seiten protokollieren kann, werde ich hier die gröbsten Vorgehensweisen für mein Projekt auflisten.
Nachdem die Benötigte Software installiert wurde, kann ich nun endlich das Fundament für den sogenannten „kernel“ zu schreiben.
Der Kernel ist praktisch das Herzstück eines jeden OS‘ .  Auf ihm basiert das ganz OS, dazu zählen alle Programme, Shells und noch vieles mehr.

![Kernel schematic](https://1.bp.blogspot.com/-X1N_xwpDxmw/V7M1eIzPuUI/AAAAAAAABC0/vktEVckQDKAdN0o305OrHEDzH2TmCkLgQCPcB/s200/PowerShell.JPG)

Zu Beginn meines Projekts habe ich lediglich einen Kernel in [C](https://en.wikipedia.org/wiki/C_(programming_language)) geschrieben, der darauf wartet, dass der User eine Taste drückt und dann den entsprechenden Buchstaben wiedergibt.
Diesen C-Code kann ich allerdings nicht einfach auf meine SD-Karte laden und hoffen, dass alles klappt, das wäre ja viel zu einfach. Zu erst muss dieser Code in eine .img-Datei kompiliert werden, d.h. er muss von einem sogenannten Compiler gelesen, in Objekt-Dateien umgewandelt und schließlich von einer .elf-Datei zu einer .img Datei gemacht werden.
Zusätzlich muss man allerdings beachten, dass diese .img-Datei dann später auch an erster Stelle (Also an der Addresse: 0x80000) der SD-Karte stehen muss, da das [BIOS](https://de.wikipedia.org/wiki/BIOS) (Basic Input/Output System) dort beim Starten des Computers nach einer solchen Datei sucht und diese anfängt auszuführen. Nun kommt ein sogenanntes [Linkscript](https://www.gnu.org/software/binutils/) ins Spiel, dessen Job es ist, genau das in die Tat umzusetzen.
Da ich Programmierer bin, und meine Aufgabe es ist, solche Dinge zu automatisieren, habe ich das natürlich getan. Wie habe ich das getan? - Mit einem *Makefile*

```
ARMGNU ?= aarch64-linux-gnu

COPS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

ASMOPS = -Iinclude

BUILD_DIR = build
SRC_DIR = src

all : kernel8.img

clean :
	rm -rf $(BUILD_DIR) *.img 
	/bin/rm kernel8.elf *.o *.img > /dev/null 2> /dev/null || true

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	@echo "Building for RPI $(value RPI_VERSION)"
	@echo ""
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img
```

Keine Sorge! Sie müssen diesen Code nicht verstehen, denn alles was er tut, ist die .img-Datei mit zwei simplen Befehlen zu erstellen, bzw. zu löschen

```
make

make clean
```

Bin ich jetzt endlich fertig? - Ja, fast. Nun muss man nur noch die .img-Datei auf die SD-Karte spielen, den Raspberry Pi über die verschiedenen Pins verbinden, Strom anlegen und es funktioniert! In dem PuTTY-Fenster auf der Dev-Machine kann man nun Dinge in die Konsole eingeben! 

![cabled RPi](/Rpi4OS/documenttion/cabled-pins.jpg)




Hilfreiche Ressourcen:
---
[Github](https://github.com/babbleberry/rpi4-osdev)
[test image](https://1.bp.blogspot.com/-X1N_xwpDxmw/V7M1eIzPuUI/AAAAAAAABC0/vktEVckQDKAdN0o305OrHEDzH2TmCkLgQCPcB/s200/PowerShell.JPG)