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
	INCS=-I/usr/include/irrlicht
	RM=rm -r -f
endif


ifndef NDEBUG
FLAGS +=-g -Wall
else
FLAGS +=-DNDEBUG
endif

LINK += -lIrrlicht
TARGET=world_explorer
SRC=$(wildcard src/*.cpp)
OBS=$(SRC:.cpp=.o)


all:
	$(warning Building $(TARGET))
	$(warning sources: $(SRC))
	$(CC) $(FLAGS) $(INCS) $(SRC) -o $(TARGET)$(SUF) $(LINK)

clean:
	$(warning cleaning...)
	$(RM) *.o $(TARGET)$(SUF)
