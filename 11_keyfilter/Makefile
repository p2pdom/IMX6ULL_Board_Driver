CROSS_COMPILE ?= arm-linux-gnueabihf-
TARGET        ?= keyfilter

CC            := $(CROSS_COMPILE)gcc
LD            := $(CROSS_COMPILE)ld
OBJCOPY       := $(CROSS_COMPILE)objcopy
OBJDUMP       := $(CROSS_COMPILE)objdump

INCUDIRS      := project \
                 imx6u \
				 bsp/delay \
				 bsp/clk \
				 bsp/led \
				 bsp/beep \
				 bsp/key \
				 bsp/uart \
				 bsp/int \
				 bsp/gpio \
				 bsp/epit
				 

SRCDIRS       := project \
                 imx6u \
				 bsp/delay \
				 bsp/clk \
				 bsp/led \
				 bsp/beep \
				 bsp/key \
				 bsp/uart \
				 bsp/int \
				 bsp/gpio \
				 bsp/epit
                  			
INCLUDE       := $(patsubst %, -I %, $(INCUDIRS))

SFILES        := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
CFILES        := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILENODIR    := $(notdir $(SFILES))
CFILENODIR    := $(notdir $(CFILES))
SOBJS         := $(patsubst %, obj/%, $(SFILENODIR:.S=.o))
COBJS         := $(patsubst %, obj/%, $(CFILENODIR:.c=.o))

OBJS          := $(SOBJS) $(COBJS)

VPATH         := $(SRCDIRS)


$(TARGET).bin : $(OBJS)
	$(LD) -Timx6u.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS) : obj/%.o : %.S
	$(CC) -Wall -nostdlib -O2  $(INCLUDE) -c -o $@ $<

$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -nostdlib -O2  $(INCLUDE) -c -o $@ $<
	

.PHONY : clean
clean  :
	-rm -rf $(OBJS) $(TARGET).bin $(TARGET).elf $(TARGET).dis
	-rm -rf *.bin *.elf *.dis load.imx