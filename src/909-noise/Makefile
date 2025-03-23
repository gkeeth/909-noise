PROJECT = noise
BUILD_DIR = bin

CFILES = noise.c lfsr.c

DEVICE=stm32g030j6m6
OOCD_FILE=../stm32g0.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

TEST_DIR = test
TEST_BUILD_DIR = $(TEST_DIR)/$(BUILD_DIR)
TEST_TARGET = $(TEST_BUILD_DIR)/test
TEST_INCLUDES = -I$(TEST_DIR) -I.
TEST_CFILES = lfsr.c
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_CFILE_OBJS := $(patsubst %.c,$(TEST_BUILD_DIR)/%.o,$(TEST_CFILES))
TEST_OBJS := $(patsubst %.c,$(TEST_BUILD_DIR)/%.o,$(notdir $(TEST_SRC)))
TEST_DEPS = $(TEST_OBJS) $(TEST_CFILE_OBJS)

debug:		$(PROJECT).debug
%.debug:	%.elf
	$(PREFIX)gdb $(PROJECT).elf -x gdbinit.gdb

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@printf "  CC\t$<\n"
	@mkdir -p $(dir $@)
	gcc $(TEST_CFLAGS) $(TEST_CPPFLAGS) $(TEST_INCLUDES) -o $@ -c $<

$(TEST_BUILD_DIR)/%.o: %.c
	@printf "  CC\t$<\n"
	@mkdir -p $(dir $@)
	gcc $(TEST_CFLAGS) $(TEST_CPPFLAGS) $(TEST_INCLUDES) -o $@ -c $<

$(TEST_TARGET): $(TEST_DEPS)
	@printf "  CC\t$<\n"
	gcc -o $@ $^

test: $(TEST_TARGET)
	./$(TEST_TARGET) -v | $(TEST_DIR)/greenest

.PHONY:	debug test

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk

GENERATED_BINS += $(TEST_BUILD_DIR)
