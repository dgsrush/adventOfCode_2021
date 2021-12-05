OBJS=\
	main.o

CFLGS=-c -mconsole -I ..\..\libdave64

LIBS=

day5.exe : $(OBJS) $(INCS)
	g++ -o day5.exe -mconsole $(OBJS) $(LIBS) ..\..\libdave64\libdave.a

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

clean :
	rm *.o
