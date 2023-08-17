OUT = bin/spaso.exe
CC = x86_64-w64-mingw32-gcc.exe
SRC = src/*.c src/*/*.c src/*/*/*.c src/*/*/*/*.c lib/*.c
LIB = -Llib -lglfw3dll -lopengl32 -lWs2_32 -lole32 -lcomctl32 -lgdi32 -lcomdlg32 -luuid
CFLAGS = $(LIB) -g

$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC) $(CFLAGS)

run: $(OUT)
	./$(OUT)