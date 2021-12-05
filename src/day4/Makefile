OBJS=\
	main.o

CFLGS=-c -mconsole -O2 -I ..\..\libdave64

LIBS=

day4.exe : $(OBJS) $(INCS)
	g++ -o day4.exe -mconsole $(OBJS) $(LIBS) ..\..\libdave64\libdave.a

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

clean :
	rm *.o
