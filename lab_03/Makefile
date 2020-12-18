CFLAGS := -Wall -Werror -std=gnu99 -Wvla -Wfloat-equal -Wfloat-conversion -pedantic -lm -lrt
OBJS := ./out/io.o ./out/matrix_utils.o ./out/memory_manager.o
UTOBJS := ./out/check_io.o ./out/check_sc.o ./out/check_utils.o
CC := gcc
LINKER := -o


ifeq ($(mode), debug)
	CFLAGS += -ggdb3
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0 -O2
endif

ifeq ($(os), linux)
	LINKER := -lpthread -lrt -lsubunit -lm -o
endif

app.exe: ./out/main.o $(OBJS)
	$(CC) $^ $(LINKER) $@

./out/main.o: ./src/main.c ./inc/*.h
	mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@

./out/io.o: ./src/io.c ./inc/*.h
	$(CC) $(CFLAGS) -c $< -o $@

./out/matrix_utils.o: ./src/matrix_utils.c ./inc/*.h
	$(CC) $(CFLAGS) -c $< -o $@

./out/memory_manager.o: ./src/memory_manager.c ./inc/*.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.exe ./out/*.o