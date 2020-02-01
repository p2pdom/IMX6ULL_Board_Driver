CROSS_COMPILE ?= arm-linux-gnueabihf-
TARGET        ?= lcd

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
				 bsp/epit \
				 bsp/gpt \
				 bsp/lcd
				 

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
				 bsp/epit \
				 bsp/gpt \
				 bsp/lcd
                  			
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
	$(LD) -Timx6u.lds -o $(TARGET).elf $^ -lgcc -L/home/wangwei/i_mxDevelopment/tool/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4
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