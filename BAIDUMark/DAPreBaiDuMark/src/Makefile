# Project: DAPre360Marktest 
# Editor : xsk 
# Time   : 2013-03-04


EXEC = test
SOURCE = test.c
CFLAGS = -I ../include -I ../src -I /home/SecDR_F118/include 
CFLAGS += -I ../../include
CFLAGS += -Wall -O2
#CFLAGS += -shared -rdynamic
#CFLAGS += -lmysqlclient -L/usr/lib/mysql
#CFLAGS += -g
CC = gcc

all:
	${CC} -o ${EXEC} ${SOURCE} ${CFLAGS}


clean:
	rm -f ${EXEC}
