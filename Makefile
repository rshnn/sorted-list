
COMPILER = gcc
CCFLAGS  = -Wall -g


ifeq ($(DEBUG), TRUE)
CCFLAGS += -g
endif


sl: 	main.o libsl.a
	$(COMPILER) $(CCFLAGS) -o sl main.o libsl.a



main.o: 		main.c
	$(COMPILER) $(CCFLAGS) -c main.c
	

libsl.a:		sorted-list.o
	ar rv libsl.a sorted-list.o


sorted-list.o: 	sorted-list.c
	$(COMPILER) $(CCFLAGS) -c sorted-list.c	


debug:
	make DEBUG = TRUE;
	
clean: 
	rm -f sl
	rm -f *o 
	rm -f libsl.a

