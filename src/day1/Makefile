OBJS=\
	main.o

CFLGS=-c -mwindows -O2 -I ..\..\libdave64

LIBS=

day1.exe : $(OBJS) $(INCS)
	g++ -o day1.exe -mwindows $(OBJS) $(LIBS) ..\..\libdave64\libdave.a

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

clean :
	rm *.o
