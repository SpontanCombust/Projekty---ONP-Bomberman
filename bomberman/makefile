# Makefile for Allegro5 programs
####################


PROGRAM_NAME=bomberman
SOURCES=-I./headers -I./src -I./libs \
\
./libs/matrix.h ./libs/matrix/matrix.c \
\
./headers/_game_rules.h \
./headers/_game_state.h \
./headers/_game.h \
./headers/actor.h \
./headers/ai.h \
./headers/block_type.h \
./headers/bomb.h \
./headers/camera.h \
./headers/direction.h \
./headers/level_map.h \
./headers/level_tile_matrix_tools.h \
./headers/level.h \
./headers/logic.h \
./headers/menus.h \
./headers/player_input.h \
./headers/rendering.h \
./headers/sfx.h \
./headers/sprite_properties.h \
\
./src/_game/game_functions.c ./src/_game/game_state_functions.c \
./src/actor/actor_essentials.c \
./src/ai/ai_essentials.c ./src/ai/ai_module_handler.c ./src/ai/path_array_creator.c \
./src/bomb/bomb_action.c ./src/bomb/bomb_container_manager.c ./src/bomb/bomb_essentials.c ./src/bomb/bomb_placing.c \
./src/camera/camera_essentials.c ./src/camera/camera_handler.c \
./src/level/level_creator.c ./src/level/level_essentials.c \
./src/level_map/level_map_essentials.c ./src/level_map/level_map_rendering.c \
./src/logic/collision_handler.c ./src/logic/movement_handler.c \
./src/menus/menu_essentials.c ./src/menus/menu_handler.c ./src/menus/menu_rendering.c ./src/menus/menu_templates.c \
./src/player_input/input_handler.c \
./src/rendering/rendering.c \
./src/sfx/sfx_essentials.c ./src/sfx/sfx_container_manager.c \
./src/level_tile_matrix_tools/coordinate_translator.c ./src/level_tile_matrix_tools/level_tile_matrix_creator.c \
\
main.c 


####################
OUTPUT_DIR=bin
LINUX_GCC=gcc
LINUX_CFLAGS=-O2 -Wall 
WINDOWS_GCC=i686-w64-mingw32-gcc
WINDOWS_CFLAGS=-O2 -Wall
MATH=-lm -ldl
ALLEGRO5_LINUX=`pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_image-5 allegro_color-5 allegro_font-5 allegro_ttf-5`
ALLEGRO5_WINDOWS=`pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_image-5 allegro_color-5 allegro_font-5 allegro_ttf-5`
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
	$(LINUX_GCC) $(LINUX_CFLAGS) -o $(OUTPUT_DIR)/linux/$(PROGRAM_NAME) $(SOURCES) $(ALLEGRO5_LINUX) $(MATH)

debug:
	mkdir -p $(OUTPUT_DIR)/linux/
	$(LINUX_GCC) $(LINUX_CFLAGS) -g -o $(OUTPUT_DIR)/linux/$(PROGRAM_NAME) $(SOURCES) $(ALLEGRO5_LINUX) $(MATH)

windows:
	mkdir -p $(OUTPUT_DIR)/windows/
	$(WINDOWS_GCC) $(WINDOWS_CFLAGS) -o $(OUTPUT_DIR)/windows/$(PROGRAM_NAME).exe $(SOURCES) $(ALLEGRO5_WINDOWS) $(MATH)

run:
	$(OUTPUT_DIR)/linux/$(PROGRAM_NAME)

clean:
	rm -rf $(OUTPUT_DIR)