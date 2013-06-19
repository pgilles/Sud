sudmain	:	sudmain.cpp sud.h sud.o
	g++ -o sudmain sudmain.cpp sud.o

sud.o	:	sud.cpp sud.h
	g++ -c sud.cpp

clean	:
	rm -rf *.o sudmain
