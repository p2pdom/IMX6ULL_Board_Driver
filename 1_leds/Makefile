target:
	arm-linux-gnueabihf-gcc  -c  leds.s -o leds.o
	arm-linux-gnueabihf-ld -Ttext 0x87800000 leds.o -o leds.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g leds.elf leds.bin
	arm-linux-gnueabihf-objdump -D leds.elf > leds.dis

clean:
	rm leds.o leds.elf leds.bin leds.dis load.imx