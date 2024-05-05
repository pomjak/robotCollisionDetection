# Makefile for a Qt-based C++ project
# Authors: Pomsar Jakub (xpomsa00), Cagala Simon (xcagal00)
XLOGINS = xpomsa00-xcagal00

# Qt configuration
QMAKE = qmake

# Target naem
TARGET = icp24

# Source files
SRC_PATH = src
INC_PATH = include
FOR_PATH = forms

# misc files needed for submission
MISC = examples/ doc/Doxyfile README.md Makefile class-dia.pdf

SOURCES = $(SRC_PATH)/*.cpp
HEADERS = $(INC_PATH)/*.h
FORMS   = $(FOR_PATH)/*.ui
PROJ    = $(TARGET).pro
OBJECTS = $(SOURCES:.cpp=.o) # mby useless idk
TRASH 	= vgcore.*

BUILD_DIR = build

# Default target
all: build
	cd build && $(QMAKE) && $(MAKE) && cp $(TARGET) ../

build: clean
	mkdir $(BUILD_DIR)
	cp $(SOURCES) $(HEADERS) $(PROJ) $(FORMS) $(BUILD_DIR)/

run: all
	./$(TARGET)

debug: all
	./$(TARGET_DEBUG)
	rm -rf $(BUILD_DIR)/

doxygen: cleandoc
	doxygen doc/Doxyfile

cleandoc:
	rm -rf doc/html doc/latex

celan: clean

clean: cleandoc
	rm -rf $(BUILD_DIR)/
	rm -rf $(TARGET)
	rm -rf $(TARGET_DEBUG)
	rm -rf $(TRASH)

pack:
	zip $(XLOGINS).zip -r $(SRC_PATH)/ $(INC_PATH)/ $(FOR_PATH)/ $(TARGET).pro  $(MISC)

zip: pack

.PHONY: run clean zip
