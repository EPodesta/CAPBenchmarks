#
# Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
#

# Source files.
SRC = $(wildcard *.c)

# Executable file.
EXEC = lu

# Builds kernel.
all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(BINDIR)/$(EXEC) $(LIBS)
	
# Cleans compilation files.
clean:
	rm -f $(BINDIR)/$(EXEC)
