Additum 2023/2024
===

In meinem Additum für dieses Jahr habe ich mich dafür entschieden verschiedene Projekte mit meinem Raspberry Pi 4B (kurz: RPi) zu behandeln.
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
- ["Gnu binutils"](https://www.gnu.org/software/binutils/)
- [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) (Programm, um die Dev-Machine mittels UART-Protocol mit dem Rpi zu verbinden und sich somit das Leben um einiges zu erleichtern)
- [Driver für das USB-SerialTTL-Kabel](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)

Vorgehen & Funktionsweise:
---

Da ich das komplette Vorgehen auf keinen Fall unter 15 Seiten protokollieren kann, werde ich hier die gröbsten Vorgehensweisen für mein Projekt auflisten.
Nachdem die Benötigte Software installiert wurde, kann ich nun endlich das Fundament für den sogenannten „Kernel“ zu schreiben.
Der Kernel ist praktisch das Herzstück eines jeden OS‘ .  Auf ihm basiert das ganz OS, dazu zählen alle Programme, Shells und noch vieles mehr.

![Kernel schematic](https://1.bp.blogspot.com/-X1N_xwpDxmw/V7M1eIzPuUI/AAAAAAAABC0/vktEVckQDKAdN0o305OrHEDzH2TmCkLgQCPcB/s200/PowerShell.JPG)

Zu Beginn meines Projekts habe ich lediglich einen Kernel in [C](https://en.wikipedia.org/wiki/C_(programming_language)) geschrieben, der darauf wartet, dass der User eine Taste drückt und dann den entsprechenden Buchstaben wiedergibt.
Das ist jedoch einfacher gesagt, als getan, denn ich muss meinem Kernel zuerst einmal beibringen, was "UART" ist, d.h. Ich muss einen sogenannten ["Driver"](https://de.wikipedia.org/wiki/Gerätetreiber) schreiben, der dem RPi sagt, wie er Signale empfangen, interpretieren und senden kann. Wenn dies nun nach harter Arbeit und (und wirklich, wirklich vieler) Recherche gelingt, bin ich schon einen ganzen Schritt weiter. 
Den geschriebenen C-Code kann ich allerdings nicht einfach auf meine SD-Karte laden und hoffen, dass alles klappt, das wäre ja viel zu einfach. Zu erst muss dieser Code in eine .img-Datei kompiliert werden, d.h. er muss von einem sogenannten Compiler gelesen, in Objekt-Dateien (Dateinendung: *.o) umgewandelt und schließlich von einer .elf-Datei zu einer .img Datei gemacht werden.
Zusätzlich muss man allerdings beachten, dass diese .img-Datei dann später auch an erster Stelle (Also an der Addresse: 0x80000) der SD-Karte stehen muss, da das [BIOS](https://de.wikipedia.org/wiki/BIOS) (Basic Input/Output System) dort beim Starten des Computers nach einer solchen Datei sucht und diese anfängt auszuführen. Nun kommt ein sogenanntes [Linkscript](https://www.gnu.org/software/binutils/) ins Spiel, dessen Job es ist, genau das in die Tat umzusetzen.
Da ich Programmierer bin, und meine Aufgabe es ist, solche Dinge zu automatisieren, habe ich das natürlich getan. Wie habe ich das getan? - Mit einem *Makefile*

```
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
```

Keine Sorge! Sie müssen diesen 'Code' nicht verstehen, denn alles was er tut, ist die .img-Datei mit zwei simplen Befehlen zu erstellen, bzw. zu löschen

```
make

make clean
```

Bin ich jetzt endlich fertig? - Naja, fast. Nun muss man nur noch die kernel8.img-Datei auf die SD-Karte spielen, den Raspberry Pi über die verschiedenen Pins verbinden, Strom anlegen und es funktioniert! In dem PuTTY-Fenster auf der Dev-Machine kann man nun Dinge in die Konsole eingeben! 

Das wäre allerdings ein ziemlich langweiliges Projekt und schon fast zu wenig Aufwand, daher habe ich mich direkt dazu entschieden C zu lernen und das Spiel "breakout" zu programmieren. Auch wenn das Original im Jahr 1976 entstanden ist, ist es noch lange nicht veraltet und eine gute Übungsaufgabe, um meine neu erworbenen C-Kenntnisse anzuwenden. Zudem muss ich mich mit der HDMI-Übertragung des RPis auseinandersetzen und einen eigenen framebuffer schreiben.


![cabled RPi](/Rpi4OS/documenttion/cabled-pins.jpg)




Hilfreiche Ressourcen:
---
[Raspberry Pi datasheets](https://datasheets.raspberrypi.com)
