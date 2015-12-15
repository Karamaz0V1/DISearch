CC	=	g++

EXEC=test
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) `pkg-config --libs opencv` -o $@ $^

%.o: %.cpp
	$(CC) `pkg-config --cflags opencv` -o $@ -c $<

clean:
	rm -rf $(EXEC) *.o
