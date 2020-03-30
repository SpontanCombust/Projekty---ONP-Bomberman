# Makefile for Allegro5 programs
####################


PROGRAM_NAME=bomberman
SOURCES=-I./headers -I./src \
\
./headers/_game.h ./headers/actor.h ./headers/block_type.h ./headers/bomb.h ./headers/direction.h ./headers/level_map.h ./headers/logic.h ./headers/sfx.h ./headers/sprite_properties.h ./headers/tile_matrix_tools.h \
\
./src/game.c \
./src/actor/actor_essentials.c \
./src/bomb/bomb_action.c ./src/bomb/bomb_essentials.c ./src/bomb/bomb_placing.c \
./src/level_map/level_map_essentials.c ./src/level_map/level_map_gfx.c \
./src/logic/collision_handler.c ./src/logic/movement_handler.c \
./src/sfx/sfx_essentials.c ./src/sfx/sfx_manager.c \
./src/tile_matrix_tools/coordinate_translator.c ./src/tile_matrix_tools/tile_matrix_creator.c ./src/tile_matrix_tools/tile_matrix_handler.c \
\
main.c 


####################
OUTPUT_DIR=bin
LINUX_GCC=gcc
LINUX_CFLAGS=-O2 -Wall
WINDOWS_GCC=x86_64-w64-mingw32-gcc
WINDOWS_CFLAGS=-O2 -Wall
ALLEGRO5_LINUX=`pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_image-5 allegro_color-5`
ALLEGRO5_WINDOWS=`pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_image-5 allegro_color-5`
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