OBJS=\
	main.o

CFLGS=-c -mwindows -O2 -I ..\..\libdave64

LIBS=

day3.exe : $(OBJS) $(INCS)
	g++ -o day3.exe -mwindows $(OBJS) $(LIBS) ..\..\libdave64\libdave.a

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

clean :
	rm *.o
