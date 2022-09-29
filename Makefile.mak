EXECS = assembler
OBJS = assembler.o

CC = g++
CCFLAGS = -std=c++17 -Wall

all: clean $(EXECS)

assembler: $(OBJS)
	$(OBJS) -o $@

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)