CC      = clang
CFLAGS  = -Wall -Wextra -O0

SRCDIR	= src/
OBJDIR  = obj/
LIBDIR  = lib/

${LIBDIR}gen_tables : ${SRCDIR}gen_tables.c
	${CC} ${CFLAGS} -o $@ $<

${OBJDIR}crcx.o : ${SRCDIR}crcx.c ${SRCDIR}crcx.h
	${CC} ${CFLAGS} -c -o $@ $<

${LIBDIR}libcrcx.a : ${OBJDIR}crcx.o
	ar rcs $@ $<
	rm ${OBJDIR}*
	./${LIBDIR}gen_tables ${LIBDIR}tables

all:\
	${LIBDIR}gen_tables\
	${OBJDIR}crcx.o\
	${LIBDIR}libcrcx.a

.PHONY: install
install:
	cp ${SRCDIR}crcx.h /usr/include