SOURCES = main.c mainwindow.c menubar.c buttonmenu.c
OBJS    = ${SOURCES:.c=.o}
CFLAGS  = `pkg-config gtk+-3.0 --cflags`
LDADD   = `pkg-config gtk+-3.0 --libs`
CC      = gcc
PACKAGE = projman

all: ${OBJS}
	${CC} -o ${PACKAGE} ${OBJS} ${LDADD}

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f *~ *.o ${PACKAGE}
