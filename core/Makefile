include ../Makefile.inc

LOCALINCLUDES= -I../logging/include 

default: gamemanager.o scriptmanager.o

shared: gamemanaer.o scriptmanager.o
	$(CC) -shared  gamemanager.o scriptmanager.o core.so

gamemanager.o: gamemanager.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) $(LOCALINCLUDES) $(LIBS) gamemanager.cpp
scriptmanager.o: scriptmanager.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) $(LOCALINCLUDES) $(LIBS) scriptmanager.cpp 

clean:
	$(RM) core.so scriptmanager.o gamemanager.o