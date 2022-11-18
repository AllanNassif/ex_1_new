CC = gcc
OBJS = main.o AsciiArtTool.o RLEList.o 
EXEC = AsciiArtTool
DEBUG_FLAG = -DNDEBUG
COMP_FLAG = -std=c99 -Wall -Werror -pedantic-errors -Itool -I/home/mtm/public/2223a/ex1 $(DEBUG_FLAG)

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

AsciiArtTool.o: AsciiArtTool.c AsciiArtTool.h RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
main.o: main.c AsciiArtTool.h RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
RLEList.o: RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
clean:
	rm -f $(OBJS) $(EXEC)