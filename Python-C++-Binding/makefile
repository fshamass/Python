CC=g++
INCLUDE_DIR := -I inc
SRC := src

CFLAGS := -std=c++11 -g
LIB_OUTPUT := libwaterpouring.so
EXE_OUTPUT:= water_pouring
shared: $(LIB_OUTPUT)
exec: $(EXE_OUTPUT)

$(LIB_OUTPUT) : obj lib WaterPouring.o Wrapper.o
	$(CC) $(CFLAGS) -shared -o lib/$(LIB_OUTPUT) obj/*.o

$(EXE_OUTPUT) : obj WaterPouring.o Wrapper.o main.o
	$(CC) $(CFLAGS) -o $(EXE_OUTPUT) obj/*.o

obj:
	if [ ! -d "obj" ]; then mkdir obj; fi

lib:
	if [ ! -d "lib" ]; then mkdir lib; fi

WaterPouring.o : $(SRC)/WaterPouring.cpp
	$(CC) -c $(CFLAGS) $(SRC)/WaterPouring.cpp -o obj/WaterPouring.o $(INCLUDE_DIR)

Wrapper.o : $(SRC)/Wrapper.cpp
	$(CC) -c $(CFLAGS) $(SRC)/Wrapper.cpp -o obj/Wrapper.o $(INCLUDE_DIR)

main.o : $(SRC)/main.cpp
	$(CC) -c $(CFLAGS) $(SRC)/main.cpp -o obj/main.o $(INCLUDE_DIR)

clean :
	rm -rf obj lib water_pouring