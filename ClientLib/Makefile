TARGET=
SRCS=$(wildcard *.c)
PREFIX=../ClientSocket

all: depend OBJS

include $(PREFIX)/common.mk

OBJS : $(OBJS)

$(OBJDIR)/%.o : %.cpp
	$(CC) -c -o $@ $(CFLAGS) $<

$(OBJDIR)/%.o : %.c
	$(CC) -c -o $@ $(CFLAGS) $<
