SRC_DIR := src
VPATH := $(SRC_DIR)

.PHONY: ALL

ALL: grid_buttom

grid_buttom: grid_buttom.c
	gcc `pkg-config --cflags gtk+-3.0` -o $@ $^ `pkg-config --libs gtk+-3.0`
