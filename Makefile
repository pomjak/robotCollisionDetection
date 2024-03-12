# Makefile for a Qt-based C++ project

# Qt configuration
QMAKE = /bin/qmake

# Target naem
TARGET = icp24
TARGET_DEBUG = icp24_debug

# Source files
SRC_PATH = src
INC_PATH = include
FOR_PATH = forms

SOURCES = $(SRC_PATH)/*.cpp
HEADERS = $(INC_PATH)/*.h
FORMS   = $(FOR_PATH)/*.ui
PROJ    = $(TARGET).pro
OBJECTS = $(SOURCES:.cpp=.o) # mby useless idk

BUILD_DIR = build

# Default target
all: build
	cd build && $(QMAKE) && $(MAKE) && cp $(TARGET) $(TARGET_DEBUG) ../

build: clean
	mkdir $(BUILD_DIR)
	cp $(SOURCES) $(HEADERS) $(PROJ) $(FORMS) $(BUILD_DIR)/

run: all
	./$(TARGET)

debug: all
	./$(TARGET_DEBUG)

doxygen: cleandoc
	doxygen doc/Doxyfile

cleandoc:
	rm -rf doc/html doc/latex

clean: 
	rm -rf $(BUILD_DIR)/
	rm -rf $(TARGET)
	rm -rf $(TARGET_DEBUG)

.PHONY: run clean
