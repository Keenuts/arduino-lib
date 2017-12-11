DEPS=sdl
BIN=lib4k.so

CC=avr-gcc
CFLAGS=-O3 -DF_CPU=16000000UL -mmcu=atmega2560 -Wall -Werror -Wextra

vpath %.c src
vpath %.h include
vpath %.h src

C_FILES=$(wildcard **/*.c)
O_FILES=$(foreach f,$(C_FILES:.c=.o),build/$(subst /,_,$(f)))

BIN=core

build/src_%.o: %.c
	@echo $(subst build/,,$@)
	@$(CC) -c $(CFLAGS) -o build/$(subst build/,,$@) $<

all: main

main: $(O_FILES)
	@echo $(O_FILES)
	@$(CC) $(CFLAGS) ${O_FILES} -o $(BIN)

export: main
	avr-objcopy -O ihex -R .eeprom $(BIN) $(BIN).hex
	avrdude -F -V -c wiring -p atmega2560 -P /dev/ttyUSB0 -b115200 \
	-D -U flash:w:$(BIN).hex
#	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b57600 \
#	-D -U flash:w:$(BIN).hex

proper:
	$(RM) $(O_FILES)

clean:proper
	$(RM) $(BIN) $(BIN).hex
	
