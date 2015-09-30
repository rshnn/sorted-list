
COMPILER = gcc
CCFLAGS  = -Wall -g


ifeq ($(DEBUG), TRUE)
CCFLAGS += -g
endif

make: main.c sorted-list.c
	$(COMPILER) $(CCFLAGS) -o sorted-list main.c sorted-list.c
	
debug:
	make DEBUG = TRUE;
	
clean: 
	rm -f sorted-list
	rm -f *o 