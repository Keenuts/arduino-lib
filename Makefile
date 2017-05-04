CC=avr-gcc
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega328p -Wall -Werror -Wextra

bin=led

main: $(bin)

export:
	avr-objcopy -O ihex -R .eeprom led led.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b57600 \
	-D -U flash:w:led.hex

clean:
	$(RM) $(bin) $(bin:=.hex)
	
