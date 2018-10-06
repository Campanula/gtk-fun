SRC_DIR := src
VPATH := $(SRC_DIR)
TARGET := grid_buttom gtkbuilder_xml

.PHONY: all clean

all: $(TARGET)

$(TARGET): %: %.c
	$(CC) `pkg-config --cflags gtk+-3.0` -o $@ $< `pkg-config --libs gtk+-3.0`

clean:
	-rm -f $(TARGET)
