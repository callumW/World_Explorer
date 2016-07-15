#Comment the line below for debugging
#NDEBUG=1
STATIC=1

CC=g++
SYSTEM := $(shell uname)

FLAGS= -std=c++14
#Check the environment
ifeq ($(SYSTEM),MINGW32_NT-6.2)

INCS= -IF:\libs\Irrlicht\include

ifndef STATIC
	FLAGS +=
	LINK= -LF:\libs\Irrlicht\lib\Win32-gcc -lIrrlicht
else
	FLAGS += -D_IRR_STATIC_LIB_
	LINK= -LF:\libs\Irrlicht\lib\Win32-gcc\static -static -lIrrlicht \
		-lglu32 -lopengl32 "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3d9.lib" "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dx9.lib" "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/DxErr.lib" "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/dxguid.lib" "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/dinput8.lib" -lwinmm -lgdi32 -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32
endif

	SUF=.exe
	MKDIR=mkdir
	RM=rm -r -f
endif
ifeq ($(SYSTEM),Linux)
	SUF=.out
	MKDIR=mkdir -p
	LINK= -lIrrlicht
	INCS= -I/usr/include/irrlicht
	RM=rm -r -f
endif


ifndef NDEBUG
FLAGS +=-g -Wall
else
FLAGS +=-DNDEBUG
endif

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
