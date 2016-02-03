WORKROOT=../
CC=g++
LIBPATH=$(WORKROOT)lib

INCLUDES= -I$(WORKROOT)include -I../../../corelib/output/include
CFLAGS = -fsigned-char -Wall -W -pipe -Wno-unused-parameter -g -D__XDEBUG__ -D__YDEBUG__

LDFLAGS=  -L$(LIBPATH) \
	  -L../../../corelib/output/lib \
  	-lminicore -lminiserver -lpthread -lm
OBJS=test_net.o
TARGET=test_net 

all : $(TARGET) $(LIB)
	rm -f $(OBJS) 

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)



test_net: test_net.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(INCLUDES)

$(LIB) : $(OBJS)
	rm -f $@
	ar cr $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
