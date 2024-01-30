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
- [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) (Programm, um die Dev-Machine mittels UART-Protocol mit dem Rpi zu verbinden und sich somit das Leben um einiges zu erleichtern)
- [Driver für das USB-SerialTTL-Kabel](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)

Vorgehen & Funktionsweise:
---

Da ich das komplette Vorgehen auf keinen Fall unter 15 Seiten protokollieren kann, werde ich hier die gröbsten Vorgehensweisen für mein Projekt auflisten.
Nachdem die Benötigte Software installiert wurde, kann ich nun endlich das Fundament für den sogenannten „kernel“ zu schreiben.
Der Kernel ist praktisch das Herzstück eines jeden OS‘ .  Auf ihm basiert das ganz OS, dazu zählen alle Programme, Shells und noch vieles mehr.
![Kernel schematic](https://1.bp.blogspot.com/-X1N_xwpDxmw/V7M1eIzPuUI/AAAAAAAABC0/vktEVckQDKAdN0o305OrHEDzH2TmCkLgQCPcB/s200/PowerShell.JPG)


Hilfreiche Ressourcen:
---
[Github](https://github.com/babbleberry/rpi4-osdev)
[test image](https://1.bp.blogspot.com/-X1N_xwpDxmw/V7M1eIzPuUI/AAAAAAAABC0/vktEVckQDKAdN0o305OrHEDzH2TmCkLgQCPcB/s200/PowerShell.JPG)