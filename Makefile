CC := gcc
CFLAGS := -Wall -Wextra -Werror -Iinclude
LDFLAGS := -Llib
LDLIBS := -lraylib -lGl -lm -lpthread -ldl -lrt -lX11


TARGET := main

all:
	$(CC) main.c -o $(TARGET) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
next: all
	./main


#source $(HOME)/Programy/emsdk/emsdk_env.sh

#web-proper: web-start
#	emcc main.c -o main.html \
	-Os -Wall \
	-Iinclude \
	-Llib -lraylib \
	-s USE_GLFW=2 \
	-s ASYNCIFY \
	-DPLATFORM_WEB
	##--shell-file path-to/shell.html \  na razie nie 
