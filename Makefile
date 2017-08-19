DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

LIBS    := -lpthread -lrt
DEFINES :=

SRC = $(wildcard ${DIR_SRC}/*.c)  
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = main

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc
CFLAGS = -g -Wall $(DEFINES) -I${DIR_INC}

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ) $(LIBS) -o $@
    
${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c  $< -o $@
.PHONY:clean
clean:
	find $(DIR_OBJ) -name *.o -exec rm -rf {} \;
