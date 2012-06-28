OBJDIR=$(PREFIX)/objs
INCLUDES=-I $(PREFIX)/Comm -I $(PREFIX)/DevicePackets -I $(PREFIX)/ClientPackets -I $(PREFIX)/Device -I $(PREFIX)/User -I $(PREFIX)/CComm -I $(PREFIX)/Device/Field -I $(PREFIX)/
CFLAGS=-g -Wall $(INCLUDES)
LIBS=-lreadline
CC=g++

OBJS=$(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ >> ./.depend;

include .depend
