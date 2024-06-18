Additum 2023/2024
===

In meinem Additum für dieses Jahr habe ich mich dafür entschieden verschiedene Projekte mit meinem Raspberry Pi 4B (kurz: RPi) zu behandeln.
Allerdings hat mich ein bestimmtes Projekt besonders fasziniert: Ein eigenescBetriebssystem (auch genannt: OS) für meinen RPi zu schreiben.

Dafür benötigte Hardware:
---

- RPi (logischerweise) & SDHC-Karte
- PC, auf dem der Code für den Kernel geschrieben wird (Dev-Machine)
- Sowohl MicroHDMI-HDMI-Kabel & Bildschirm, als auch [USB-SerialTTL-Kabel](https://www.amazon.de/Hailege-PL2303TA-RS232-Download-Windows/dp/B07Z7PPT6Y/ref=sr_1_3?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=1I8QYDEBL9B02&keywords=2+Pack+Debug+Cable+for+Raspberry+Pi+USB+Programming+USB+to+TTL+Serial+Cable%2C+Windows+XP%2FVISTA%2F+7%2F8%2F+8.1+Supported&qid=1706455641&sprefix=2+pack+debug+cable+for+raspberry+pi+usb+programming+usb+to+ttl+serial+cable+windows+xp%2Fvista%2F+7%2F8%2F+8.1+supported%2Caps%2C75&sr=8-3), um den RPi mit der Dev Machine zu verbinden und via [UART](https://de.wikipedia.org/wiki/Universal_Asynchronous_Receiver_Transmitter) darauf zu arbeiten

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
Zusätzlich muss man allerdings beachten, dass diese .img-Datei dann später auch an der Adresse 0x80000 im Arbeitsspeicher stehen muss, da die Firmware des RPi (ähnlich wie das [BIOS](https://de.wikipedia.org/wiki/BIOS) (Basic Input/Output System) oder das modernere [UEFI](https://www.computerweekly.com/de/definition/UEFI-Unified-Extensible-Firmware-Interface#:~:text=Unified%20Extensible%20Firmware%20Interface%20(UEFI)%20ist%20ein%20Softwareprogramm%2C%20das,seinem%20Betriebssystem%20(OS)%20verbindet.) (Unified Extensible Firmware Interface) auf anderen Computern) dort beim Starten des Computers versucht den Programmcode zu laden. Nun kommt ein sogenanntes [Linkscript](https://www.gnu.org/software/binutils/) ins Spiel, dessen Job es ist, genau das in die Tat umzusetzen.
Da ich Programmierer bin, und meine Aufgabe es ist, solche Dinge zu automatisieren, habe ich das natürlich getan. Wie habe ich das getan? - Mit einem *[Makefile](https://www.sis.pitt.edu/mbsclass/tutorial/advanced/makefile/whatis.htm)*

```
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
```

Keine Sorge! Sie müssen diesen 'Code' nicht verstehen, denn alles was er tut, ist die .img-Datei mit zwei simplen Befehlen zu erstellen, bzw. zu löschen

```
make

make clean
```

Bin ich jetzt endlich fertig? - Naja, fast. Nun muss man nur noch die kernel8.img-Datei auf die SD-Karte spielen, den Raspberry Pi über die verschiedenen Pins verbinden, Strom anlegen und es funktioniert! In dem PuTTY-Fenster auf der Dev-Machine kann man nun Dinge in die Konsole eingeben! 

Das wäre allerdings ein ziemlich langweiliges Projekt und schon fast zu wenig Aufwand, daher habe ich mich direkt dazu entschieden C zu lernen und das Spiel "breakout" zu programmieren. Auch wenn das Original von Steve Wozniak im Jahre 1976 entstanden ist, ist es noch lange nicht veraltet und eine gute Übungsaufgabe, um meine neu erworbenen C-Kenntnisse anzuwenden. Zudem muss ich mich mit der HDMI-Übertragung des RPis auseinandersetzen und einen eigenen framebuffer schreiben.
Wenn nun auch das getan ist, kann ich nun erneut die .img-Datei auf meine SD-Karte übertragen, meinen RPi an den Bildschirm, meinen PC und das Netzteil andschließen und es läuft! Ein funktionierendes Spiel, das mit Hilfe der Tasten 'h' und 'l' gesteuert werden kann!


![cabled RPi](/Rpi4OS/documentation/cabled_pins.jpg)
![breakout Game](/Rpi4OS/documentation/breakout_Game.jpg)

Was ich bisher erreicht habe
---

- Eine Mailbox geschrieben, die Dateien auf den Bildschirm 'zeichnen' kann
	- Dazu noch eine I/O-System, das Dateien über UART versenden kann
	- Ebenso der Framebuffer, der ganze Bilder, nicht nur einzelne Pixel beschreiben kann
- Mit den gegebenen Ressourcen ein HelloWorld-Programm und schließlich auch ein ganzes Spiel erstellt
- Von PuTTY auf einen Arduino umgestiegen, sodass ich kein anderes Gerät (außer eine Tastatur) brauche


Was ich dieses Jahr gelernt habe
===

- _*Viel zu viel*_ um das alles aufzuschreiben, aber im gröbsten:
	- Was Firmware ist und wie man sie benutzen kann
	- Wie ein Computer aufgebaut ist und welche Bauteile für was zuständig sind
	- Dass es verschiedene Assembly-Typen für verschiedene CPUs gibt 
	- Wie verschiedene Datenübertragungsprotokolle es gibt und wie diese aufgebaut sind (zwei Kabel für die Stromversorgung (Ground, 5V/3V3 Power supply), ein bis zwei Kabel zur DatenÜbertragung, bei den meisten Protokollen gibt es auch ein Clock-Kabel,... )
	- Was MSB, LSB, Big- und Little-endian sind
	- Wie man richtig in C programmiert
	- und noch Vieles, vieles mehr


Würde ich diese Additum weiterempfehlen?
===
- ABSOLUT! Es gibt nichts das mehr Spaß macht, als sein eigenes OS von Grund auf aufzubauen 

Hilfreiche Ressourcen:
---
[Raspberry Pi datasheets](https://datasheets.raspberrypi.com)
