CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -g -O2 -I include -DKSCRIPT_VENDOR=\"KrabbaTek\" -MMD -MP

SRC_DIR := src
OBJ_DIR := obj
TARGET  := kscript

SRCS    := $(shell find $(SRC_DIR) -name "*.c")
OBJS    := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS    := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "     LD $@"
	@$(CC) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "     CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJ_DIR) $(TARGET) build

install:
	@echo "Installing..."
	@cp kscript /usr/local/bin/kscript

format:
	@echo "Formatting code..."
	@clang-format -i $(SRCS)

.PHONY: all clean install format

-include $(DEPS)