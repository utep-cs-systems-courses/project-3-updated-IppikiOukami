COMMON_OBJECTS  = 
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include

#internal rules
CC		= msp430-elf-gcc
AS		= msp430-elf-gcc -mmcu=${CPU} -c

all: toy.elf

toy.elf: ${COMMON_OBJECTS} driver.o led.o buzzer.o switches.o stateMachines.o wdt_handler.o p2_IH.o state_advance.s
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: toy.elf
	msp430loader.sh $^

clean: 
	rm -f *.o *~ *# *.elf

reset:
	mspdebug rf2500 erase "all"
