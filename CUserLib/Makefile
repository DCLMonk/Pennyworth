TARGET=cuser-lib
SRCS=$(wildcard *.cpp) 

BUILDDIR=objs
PREFIX=.

.PHONY:all clean
all:$(TARGET)

include common.mk

DIRS:
	+$(MAKE) -C ClientPackets
	+$(MAKE) -C CComm
	+$(MAKE) -C User
	+$(MAKE) -C Device

$(TARGET): DIRS $(OBJS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJDIR)/*.o $(LIBS)

$(OBJDIR)/%.o : %.cpp
	$(CC) -c -o $@ $(CFLAGS) $<

$(OBJDIR)/%.o : %.c
	$(CC) -c -o $@ $(CFLAGS) $<

clean:
	rm -rf $(OBJDIR)/* core* $(TARGET)
	mkdir -p $(BUILDDIR)
