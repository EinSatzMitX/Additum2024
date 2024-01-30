Additum 2023/2024
==================

In meinem Additum für diese Jahr habe ich mich dafür entschieden verschiedene Projekte mit meinem Raspberry Pi 4B (kurz: RPi) zu behandeln.
Allerdings hat mich ein bestimmtes Projekt besonders fasziniert: Ein eigenen Kernel für das Betriebssystem meines RPi‘s schreiben.

Dafür benötigte Hardware:
-----
- RPi (logischerweise) & SDHC-Karte
- PC, auf dem der Code für den Kernel geschrieben wird (Dev-Machine)
- Sowohl MicroHDMI-HDMI-Kabel & Bildschirm, als auch USB-SerialTTL-Kabel, um den RPi mit der Dev Machine zu verbinden und via UART darauf zu schreiben

Dafür Benötigte Software:
----
- Code-Editor(en) (ich habe mich für VSCode & Vim entschieden)
- "AArch64 ELF bare-metal target“ (Cross-Compiler, um den C-Code auf der Dev-Machine, die auf einem x86_64 Processor läuft für den RPi, der auf einem ARM-Processor läuft zu Compilen)
- PuTTY (Programm, um die Dev-Machine mittels UART-Protocol mit dem Rpi zu verbinden und sich somit das Leben um einiges zu erleichtern)

Vorgehen & Funktionsweise
----
Da ich das komplette Vorgehen auf keinen Fall unter 30 Seiten protokollieren kann, werde ich hier die gröbsten Vorgehensweisen für mein Projekt auflisten.
Nachdem die Benötigte


Hilfreiche Ressourcen:
[Github](https://github.com/babbleberry/rpi4-osdev)
[test image](https://1.bp.blogspot.com/-X1N_xwpDxmw/V7M1eIzPuUI/AAAAAAAABC0/vktEVckQDKAdN0o305OrHEDzH2TmCkLgQCPcB/s200/PowerShell.JPG)