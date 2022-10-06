EXECS = assemble

all: clean $(EXECS)

assemble: assembler.cpp
	g++ -o assemble assembler.cpp

clean:
	/bin/rm -f a.out $(EXECS)