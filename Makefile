CC = g++
OBJS = main.o bmp_reader.o

all: ${OBJS}
	${CC} ${OBJS} -o test
	
%.o: %.cpp
	${CC} -c $*.cpp
	
clean:
	-rm -rf *.o
	-rm test
