OBJDIR=$(PREFIX)/objs
CFLAGS=-g -Wall
LIBS=
CC=gcc

OBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend
