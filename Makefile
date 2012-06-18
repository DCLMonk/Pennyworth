TARGET=dev-server
SRCS=Main.cpp \

OBJDIR=objs
OBJS1=$(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))
OBJS=$(patsubst %.cu,$(OBJDIR)/%CU.o,$(OBJS1))
BUILDDIR=objs
CFLAGS=-g -Wall
LIBS=-lpthread -lrt
CC=g++

.PHONY:all clean
all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJS) $(LIBS)

$(OBJDIR)/%.o : %.cpp
	$(CC) -c -o $@ $(CFLAGS) $<

$(OBJDIR)/%.o : %.c
	$(CC) -c -o $@ $(CFLAGS) $<

$(OBJDIR)/%CU.o : %.cu
	$(CC) -c -o $@ $(CFLAGS) $<

clean:
	rm -rf $(OBJDIR)/* core* $(TARGET)
	mkdir $(BUILDDIR)
