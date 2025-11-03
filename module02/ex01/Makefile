MC = atmega328p
CC = avr-gcc
DF_CPU = 16000000UL
SRC = main.c
OBJ = $(SRC:.c=)

all: hex flash

hex:
	@${CC} -Wall -mmcu=${MC} -DF_CPU=${DF_CPU} -Os -o ${OBJ}.bin ${OBJ}.c
	@avr-objcopy -O ihex ${OBJ}.bin ${OBJ}.hex
	@if [ ! -d obj ]; then mkdir obj; fi
	@mv ${OBJ}.bin ${OBJ}.hex obj/

flash:
	@avrdude -c arduino -p ${MC} -P /dev/ttyUSB0 -b 115200 -U flash:w:obj/${OBJ}.hex

clean:
	@rm -rf  obj

.PHONY : all hex flash clean