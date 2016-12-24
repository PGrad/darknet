CC=gcc
CFLAGS= -Wall -fPIC -shared
RM= rm -f
.PHONY: all clean

NAME= HelloJni

SRC= $(NAME).c

INCLUDES= -I/usr/lib/jvm/default-java/include -I/usr/lib/jvm/default-java/include/linux

all: lib$(NAME).so
clean:
	$(RM) lib$(NAME).so

lib$(NAME).so: $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $@
