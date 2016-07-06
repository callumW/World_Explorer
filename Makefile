#Comment the line below for debugging
#NDEBUG=1

CC=g++
SYSTEM := $(shell uname)

FLAGS= -std=c++14
#Check the environment
ifeq ($(SYSTEM),MINGW32_NT-6.2)
	INCS=-IF:\libs\Irrlicht\include
	LINK=-LF:\libs\Irrlicht\lib\Win32-gcc
	SUF=.exe
	MKDIR=mkdir
	RM=rm -r -f
endif
ifeq ($(SYSTEM),Linux)
	SUF=.out
	MKDIR=mkdir -p
	LINKS=
	INCS= -I/usr/include/irrlicht
	RM=rm -r -f
endif


ifndef NDEBUG
FLAGS +=-g -Wall
else
FLAGS +=-DNDEBUG
endif

LINK += -lIrrlicht
TARGET=world_explorer$(SUF)
SRC=$(wildcard src/*.cpp)
OBS=$(SRC:.cpp=.o)


all: | notify $(OBS)
	$(info Building application: $(TARGET))
	$(info )
	$(CC) $(OBS) -o $(TARGET) $(LINK)

.cpp.o: $(SRC)
	$(info --- Building object file: $@ ---)
	$(info )
	$(CC) $(FLAGS) $(INCS) -c $< -o $@

notify:
	$(info --- Building for: $(SYSTEM) ---)
	$(info )

clean:
	$(warning cleaning...)
	$(RM) src/*.o $(TARGET)
