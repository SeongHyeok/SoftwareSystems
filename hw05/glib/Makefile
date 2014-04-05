CC=gcc
SRC=wordfreq.c
OBJ=wordfreq
CFLAG=`pkg-config --cflags --libs glib-2.0`
CFLAG+=`pkg-config --cflags --libs gio-2.0`
CFLAG+=`pkg-config --cflags --libs gtk+-2.0`

wordfreq:
	$(CC) $(SRC) -o $(OBJ) $(CFLAG)
clean:
	rm -rf $(OBJ)
