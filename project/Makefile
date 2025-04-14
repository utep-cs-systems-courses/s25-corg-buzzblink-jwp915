#Target CPU and flags
CPU     = msp430g2553
CFLAGS  = -mmcu=$(CPU)

#Toolchain definitions
CC      = msp430-elf-gcc
AS      = msp430-elf-as
AR      = msp430-elf-ar

#Default target
all: libTimer.a

#Archive the object files into a static library
libTimer.a: clocksTimer.o sr.o
	$(AR) crs $@ $^

#Install headers and library to parent directories
install: libTimer.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

#Clean build artifacts
clean:
	rm -f libTimer.a *.o
