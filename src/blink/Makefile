PROJECT = blink
BUILD_DIR = bin

CFILES = blink.c

DEVICE=stm32g030j6m6
OOCD_FILE=../stm32g0.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

debug:		$(PROJECT).debug
%.debug:	%.elf
	$(PREFIX)gdb $(PROJECT).elf -x gdbinit.gdb
.PHONY:	debug
# $(PREFIX)gdb $(PROJECT).elf -x gdbinit.gdb

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
