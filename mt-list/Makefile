
ifeq ($(OSTYPE), solaris2.7)
PURIFY=purify
CC=$(PURIFY) cc
OS_OPTS=-mt
OS_LIB=-lnsl -lsocket -lresolv -lpthread
else
CC=gcc
#CC=clang
#OS_OPTS=-Wall
OS_LIB=-pthread
endif

INC=-I.
CFLAGS=$(OS_OPTS) -g $(INC)
LDLIBS=$(OS_LIB)

SRCS=list.c item.c main.c
OBJS=$(SRCS:%.c=%.o)
PROG=list

all: $(PROG)

$(PROG): $(OBJS)

clean:
	$(RM) *.o *core *~ $(PROG)
