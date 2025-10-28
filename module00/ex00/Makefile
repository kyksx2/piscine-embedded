NAME = setup
MC = atmega328p
CC = avr-gcc
DF_CPU = 16000000UL
SRC = main.c
OBJ = $(SRC:.c=)

all: hex flash

hex: ${OBJ}
	@${CC} -mmcu=${MC} -DF_CPU=${DF_CPU} -Os -o ${OBJ}.bin ${OBJ}.c
	@avr-objcopy -O ihex ${OBJ}.bin ${OBJ}.hex

flash:
	@avrdude -c arduino -p ${MC} -P /dev/ttyUSB0 -b 115200 -U flash:w:${OBJ}.hex

clean:
	rm -rf ${OBJ} ${OBJ}.hex ${OBJ}.bin

.PHONY : all hex flash clean