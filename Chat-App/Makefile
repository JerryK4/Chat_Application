.PHONY:all clean my_objs my_shared install

my_objs:
	gcc -c ./main.c -o ./objs/main.o -I ./inc
	gcc -c -fPIC ./src/menu.c -o ./objs/menu.o -I ./inc 
	gcc -c -fPIC ./src/socket.c -o ./objs/socket.o -I ./inc
my_shared:
	gcc -shared ./objs/menu.o ./objs/socket.o -o ./libs/shared/libmd.so 
install:
	cp -f ./libs/shared/libmd.so /usr/lib 
all:my_objs my_shared install
	gcc ./objs/main.o -L./libs/shared -lmd -o ./chat -pthread
clean:
	rm -rf ./objs/*
	rm -rf ./libs/shared/libmd.so
	rm -rf ./chat
