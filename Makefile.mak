# Makefile for Unit Converter (C)
# Author: Mobin Yousefi (GitHub: https://github.com/mobinyousefi-cs)

CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -Iinclude
LDFLAGS =
TARGET  = unit_converter

SRC_DIR = src
OBJ_DIR = obj

SRCS    = $(SRC_DIR)/main.c \
          $(SRC_DIR)/converter.c \
          $(SRC_DIR)/ui.c

OBJS    = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
