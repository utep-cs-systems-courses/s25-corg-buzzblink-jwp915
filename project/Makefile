#CPU and flags
CPU         = msp430g2553
CFLAGS      = -mmcu=$(CPU) -I../h
LDFLAGS     = -L/opt/ti/msp430_gcc/include

#Toolchain
CC          = msp430-elf-gcc
AS          = msp430-elf-as
AR          = msp430-elf-ar

#Objects
COMMON_OBJECTS =
LIB_OBJECTS     = clocksTimer.o sr.o
APP_OBJECTS     = main.o p1_interrupt_handler.o
LIB_NAME        = libTimer.a
ELF_NAME        = led.elf

#Default target
all: $(LIB_NAME) $(ELF_NAME)

#Build static library
$(LIB_NAME): $(LIB_OBJECTS)
	$(AR) crs $@ $^

#Build the final application
$(ELF_NAME): $(COMMON_OBJECTS) $(APP_OBJECTS) ../lib/$(LIB_NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

#Install static library and headers
install: $(LIB_NAME)
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

#Load ELF to device
load: $(ELF_NAME)
	msp430loader.sh $(ELF_NAME)

#Clean build artifacts
clean:
	rm -f *.o *.elf *.a
