OBJS=\
	ReadFile.o\
	main.o

CFLGS=-c -mconsole -O2

LIBS=

day8.exe : $(OBJS) $(INCS)
	g++ -o day8.exe -mconsole $(OBJS) $(LIBS)

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

ReadFile.o : ReadFile.cpp $(INCS)
	g++ $(CFLGS) ReadFile.cpp

clean :
	rm *.o
