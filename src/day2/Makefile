OBJS=\
	main.o

CFLGS=-c -mwindows -O2 -I ..\..\libdave64

LIBS=

day2.exe : $(OBJS) $(INCS)
	g++ -o day2.exe -mwindows $(OBJS) $(LIBS) ..\..\libdave64\libdave.a

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

clean :
	rm *.o
