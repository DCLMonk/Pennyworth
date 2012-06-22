OBJDIR=$(PREFIX)/objs
CFLAGS=-g -Wall
LIBS=
CC=g++

OBJS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(patsubst %.c,$(OBJDIR)/%.o,$(SRCS)))

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend
