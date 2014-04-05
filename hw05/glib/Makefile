CC=gcc
SRC=wordfreq.c
OBJ=wordfreq
CFLAG=`pkg-config --cflags --libs glib-2.0`

wordfreq:
	$(CC) $(CFLAG) $(SRC) -o $(OBJ)
clean:
	rm -rf $(OBJ)
