
MFILE = $(FILE).cpp
GCC = g++-14
GCCFLAGS = -Wall -Wextra -Werror -Wpedantic -Wnull-dereference  -Wshadow -mavx2 -Wconversion -Wduplicated-branches -Wlogical-op -O3  -Wformat=2   -pthread 
C23 = -std=c++23
INCLUDES = -I includes -I src 
COMPILE.c = $(GCC) $(GCCFLAGS) $(INCLUDES) $(C23)
COMPILEASM.o = nasm -f elf64 -g 
COMPILEYASM.o = yasm -g dwarf2 -felf64
vpath %.c src 
vpath %.cc src 
vpath %.cpp src 
vpath %.h includes 

run : $(MFILE) $(HARGS)
	$(COMPILE.c) $<  -o ./bin/$(FILE) && ./bin/$(FILE)  

create: 
	touch src/$(MFILE)
push : 
	git add  . && git commit -m "update x86 sim DDD" && git push origin main
