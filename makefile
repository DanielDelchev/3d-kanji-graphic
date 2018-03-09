CC=mingw32-g++
CFLAGS=-Wall -std=c++11 -O2 -static

SOURCE_DIR=source
DEPEND_DIR=.\Dependencies
INCLUDE_DIR=.\include
OUTPUT_DIR=build

Files= ${SOURCE_DIR}\kanji.cpp
libs=-lglfw -lopengl32 -lglu32 -lgdi32
INCLUDE_DIRS=-I${DEPEND_DIR}\glfw-2.7.bin.WIN32\include -I${INCLUDE_DIR}
LINK_DIRS=-L${DEPEND_DIR}\glfw-2.7.bin.WIN32\lib

all:
	${CC} ${Files} -o ${OUTPUT_DIR}\kanji ${CFLAGS} ${INCLUDE_DIRS} ${LINK_DIRS} ${libs}