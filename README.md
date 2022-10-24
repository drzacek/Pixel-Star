# Pixel-Star
PCB star with RGB LEDs, xmas decoration


With this project you can make a simple yet nice star-shaped PCB with a bunch of addressable LEDs.

It has STM32 microcontroller on board and this project provides software for it to drive the LEDs.

In order to make it:

1. Download KiCAD 6, STM32CubeIDE, clone/download this project
2. Generate Gerber files according to your manufarcturer rules (for example [JLCPCB](https://support.jlcpcb.com/article/194-how-to-generate-gerber-and-drill-files-in-kicad-6))
3. Order the PCB
4. Order the parts (Kicad project contains links to all parts on lcsc)
5. Solder everything
6. Compile the STM32 project
7. Flash the firmware using ST-Link
