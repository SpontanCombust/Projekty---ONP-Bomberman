##############################
##       RPN MAKEFILE		##
## @author Cedro Przemysław ##
##############################

#######################################################

PROGRAM_NAME=RPN
OUTPUT_DIR=bin
INCLUDES=-I./stack -I./rpn -I./gui_ncurses
SOURCES=main.c \
./stack/stack.hpp ./stack/stack.cpp \
./rpn/rpn.hpp ./rpn/rpn_counter.cpp ./rpn/rpn_parser.cpp \
./gui_ncurses/app.hpp ./gui_ncurses/app.cpp

#######################################################

LINUX_COMPILER=g++
CFLAGS=-lncurses

#######################################################

.PHONY: build run clean help 

help:
	@echo "############# HELP #############"
	@echo "make build - compile the project"
	@echo "make run   - run the program"
	@echo "make clean - clean up"
	@echo "make help  - display help"
	@echo "################################"

build:
	mkdir -p $(OUTPUT_DIR)/linux/
	$(LINUX_COMPILER) -o $(OUTPUT_DIR)/linux/$(PROGRAM_NAME) $(INCLUDES) $(SOURCES) $(CFLAGS)

run:
	$(OUTPUT_DIR)/linux/$(PROGRAM_NAME)

clean:
	rm -rf $(OUTPUT_DIR)	
