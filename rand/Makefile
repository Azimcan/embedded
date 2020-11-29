
TARGETS = hello.elf

all: $(TARGETS) 

CROSS_PREFIX ?= riscv64-unknown-elf
CC           := $(CROSS_PREFIX)-gcc
LD           := $(CROSS_PREFIX)-gcc
OBJCOPY      := $(CROSS_PREFIX)-objcopy
SIZE         := $(CROSS_PREFIX)-size
GDB          := $(CROSS_PREFIX)-gdb

GDBFLAGS := -ex 'set remotetimeout 10' -ex 'target remote :3333' -ex load -ex 'break main'

RISCV_ARCHFLAGS := \
	-march=rv32im \
	-mabi=ilp32 \
	-mcmodel=medany

LINKERSCRIPT := hal/pqvexriscvsim.ld

ifeq ($(DEBUG),1)
CFLAGS := \
	-Og -g3
else
CFLAGS := \
	-O3 -g3
endif

CFLAGS += \
	$(RISCV_ARCHFLAGS) \
	-Wall -Wextra -Wshadow \
	-MMD \
	-fno-common \
	-ffunction-sections \
	-fdata-sections \
	-fstrict-volatile-bitfields \
	-I./hal \
	--specs=nano.specs


LDFLAGS := \
	$(RISCV_ARCHFLAGS) \
	--specs=nosys.specs \
	-nostartfiles \
	-ffreestanding \
	-Wl,--gc-sections \
	-Wl,-T$(notdir $(LINKERSCRIPT)) \
	-L./hal

OBJ := 

LIBHAL_SRC := \
	hal/hal-vexriscv.c \
	hal/init.c \
	hal/start.S

LIBHAL_OBJ := \
	hal/hal-vexriscv.o \
	hal/init.o \
	hal/start.o

OBJ += $(LIBHAL_OBJ)
OBJ += hello.o rand.o

$(LIBHAL_OBJ): CFLAGS += -DVEXRISCV_RWMTVEC

debug: all
	$(GDB) $(GDBFLAGS) $(TARGETS)


%.elf: $(LINKERSCRIPT) $(OBJ) 
	$(LD) -o $@ $(LDFLAGS) $(OBJ)

%.bin: %.elf
	$(OBJCOPY) -Obinary $^ $@

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $<

%.o: %.S
	$(CC) -c -o $@ $(CFLAGS) $<

clean:
	rm -f *.o *.d hal/*.o hal/*.d *.elf *.bin .platform.mk

