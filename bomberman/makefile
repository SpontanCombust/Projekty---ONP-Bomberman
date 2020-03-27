# Makefile for Allegro5 programs
####################


PROGRAM_NAME=bomberman
SOURCES=-I./headers -I./src \
./headers/direction.h ./headers/entity.h ./headers/level_utilities.h ./headers/logic_handlers.h ./headers/sprite_properties.h\
./src/collision_handler.c ./src/coordinate_translator.c ./src/entity_init.c ./src/level_map_manager.c ./src/movement_handler.c\
main.c 


####################
OUTPUT_DIR=bin
LINUX_GCC=gcc
LINUX_CFLAGS=-O2 -Wall
WINDOWS_GCC=x86_64-w64-mingw32-gcc
WINDOWS_CFLAGS=-O2 -Wall
ALLEGRO5_LINUX=`pkg-config --cflags --libs allegro-5 allegro_ttf-5 allegro_primitives-5 allegro_physfs-5 allegro_memfile-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_dialog-5 allegro_color-5 allegro_audio-5 allegro_acodec-5`
ALLEGRO5_WINDOWS=`pkg-config --cflags --libs allegro-5 allegro_ttf-5 allegro_primitives-5 allegro_physfs-5 allegro_memfile-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_dialog-5 allegro_color-5 allegro_audio-5 allegro_acodec-5`
export PKG_CONFIG_PATH=/usr/x86_64-w64-mingw32/lib/pkgconfig/
####################

.PHONY: all run clean help linux debug windows

all: linux

help:
	@echo "##### HELP #####"
	@echo "make all - build for linux and windows"
	@echo "make clean - clean up"
	@echo "make linux - build for linux only"
	@echo "make debug - build debug version for linux"
	@echo "make windows - build for windows only"
	@echo "make help - print this help"
	@echo "################"

linux:
	mkdir -p $(OUTPUT_DIR)/linux/
	$(LINUX_GCC) $(LINUX_CFLAGS) -o $(OUTPUT_DIR)/linux/$(PROGRAM_NAME) $(SOURCES) $(ALLEGRO5_LINUX)

debug:
	mkdir -p $(OUTPUT_DIR)/linux/
	$(LINUX_GCC) $(LINUX_CFLAGS) -g -o $(OUTPUT_DIR)/linux/$(PROGRAM_NAME) $(SOURCES) $(ALLEGRO5_LINUX)

windows:
	mkdir -p $(OUTPUT_DIR)/windows/
	$(WINDOWS_GCC) $(WINDOWS_CFLAGS) -o $(OUTPUT_DIR)/windows/$(PROGRAM_NAME).exe $(SOURCES) $(ALLEGRO5_WINDOWS)

run:
	$(OUTPUT_DIR)/linux/$(PROGRAM_NAME)

clean:
	rm -rf $(OUTPUT_DIR)