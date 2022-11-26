CC = gcc
EXEC = AsciiArtTool
OBJS = tool/main.o tool/AsciiArtTool.o RLEList.o 
DEBUG_FLAG = -DNDEBUG
COMP_FLAG = -std=c99 -Wall -Werror -pedantic-errors -Itool -I/home/mtm/public/2223a/ex1

$(EXEC) : $(OBJS)
	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) $(OBJS) -o $@

tool/AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $@
tool/main.o: tool/main.c tool/AsciiArtTool.h 
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $@
RLEList.o: RLEList.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
clean:
	rm -f $(OBJS) $(EXEC)