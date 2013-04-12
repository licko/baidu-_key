# Project: DABaiDuMarkAnalyse 
# Editor : lsz 
# Time   : 2013-04-11


EXEC = /home/SecDR_F118/solib/Other/DABaiDuMarkAnalyse.so
SOURCE = src/DABaiDuMarkAnalyse.c
CFLAGS = -I include -I src -I ../include -I /home/SecDR_F118/include
CFLAGS += -Wall -O2
CFLAGS += -shared -rdynamic
 CFLAGS += -lmysqlclient -L/usr/lib/mysql
CC = gcc

all:
	${CC} -o ${EXEC} ${SOURCE} ${CFLAGS}


clean:
	rm -f ${EXEC}


