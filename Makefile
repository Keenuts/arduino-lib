CC=avr-gcc
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega328p -Wall -Werror -Wextra

OBJ=digital.o lcd.o led.o
BIN=led


all: export

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) ${OBJ} -o $(BIN)

export: main
	avr-objcopy -O ihex -R .eeprom $(BIN) $(BIN).hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b57600 \
	-D -U flash:w:$(BIN).hex

clean:
	$(RM) $(BIN) $(BIN).hex $(OBJ)
	
