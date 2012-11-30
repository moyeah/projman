SOURCES = main.c \
          mainwindow.c \
          exitdialog.c \
          menubar.c \
          buttonmenu.c \
          newprojectdialog.c \
          newprojectgda.c
OBJS    = ${SOURCES:.c=.o}
CFLAGS  = `pkg-config gtk+-3.0 libgda-4.0 --cflags`
LDADD   = `pkg-config gtk+-3.0 libgda-4.0 --libs`
CC      = gcc
DEBUG   = -g
PACKAGE = projman

all: ${OBJS}
	${CC} ${DEBUG} -o ${PACKAGE} ${OBJS} ${LDADD}

.c.o:
	${CC} ${DEBUG} ${CFLAGS} -c $<

clean:
	rm -f *~ *.o ${PACKAGE}
