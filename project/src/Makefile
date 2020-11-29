COMMON_OBJECTS  = 
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#internal rules
CC		= msp430-elf-gcc
AS		= msp430-elf-as

all: toy.elf

toy.elf: ${COMMON_OBJECTS} driver.o led.o buzzer.o switches.o stateMachines.o wdInterruptHandler.o p2_IH.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: toy.elf
	msp430loader.sh toy.elf

clean: 
	rm -f *.o *~ *# *.elf

reset:
	mspdebug rf2500 erase "all"

stateMachines.o: led.h switches.h
