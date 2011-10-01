include ../Makefile.inc



default: log_system.o	log_provider_file.o  log_provider_stdout.o

shared: log_system.o log_provider_file.o  log_provider_stdout.o
	$(CC) -shared  log_provider_file.o log_provider_stdout.o log_system.o  -o log_system.so

log_system.o: log_system.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) $(LIBS) log_system.cpp
log_provider_file.o: log_provider_file.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) $(LIBS) log_provider_file.cpp
log_provider_stdout.o: log_provider_stdout.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) $(LIBS) log_provider_stdout.cpp 

clean:
	$(RM) log_system.so log_system.o log_provider_file.o  log_provider_stdout.o
