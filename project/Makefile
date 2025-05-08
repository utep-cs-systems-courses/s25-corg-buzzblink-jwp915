# === Makefile Configuration ===
CPU            = msp430g2553
CC             = msp430-elf-gcc
AR             = msp430-elf-ar
AS             = msp430-elf-as

CFLAGS         = -mmcu=$(CPU) -I. -I./timerLib -I../h
LDFLAGS        = -L/opt/ti/msp430_gcc/include

COMMON_OBJECTS =
OBJECTS        = buzzer.o incrementing.o p1_interrupt_handler.o led.o switches.o buttonMain.o
TIMERLIB_OBJS  = timerLib/clocksTimer.o timerLib/sr.o
TARGET         = button.elf
LIBS           = timerLib/libTimer.a

# === Default Target ===
all: $(TARGET)

# === Build libTimer.a from object files ===
$(LIBS): $(TIMERLIB_OBJS)
	$(AR) rcs $@ $^

# === Compile TimerLib Sources ===
timerLib/clocksTimer.o: timerLib/clocksTimer.c timerLib/clocksTimer.h
	$(CC) $(CFLAGS) -c -o $@ $<

timerLib/sr.o: timerLib/sr.s timerLib/sr.h
	$(AS) -o $@ $<

# === Link the Target ELF ===
$(TARGET): $(COMMON_OBJECTS) $(OBJECTS) $(LIBS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# === Load the Program onto the MSP430 ===
load: $(TARGET)
	msp430loader.sh $(TARGET)

# === Clean Build Artifacts ===
clean:
	rm -f *.o *.elf timerLib/*.o timerLib/*.a
