
SRCDIR=./src

all: lex.yy.c y.tab.c lib_imageprocessing.o util.o
	gcc -omain lex.yy.c y.tab.c lib_imageprocessing.o util.o -ll -lm -lfreeimage -I$(SRCDIR)

lex.yy.c:$(SRCDIR)/imageprocessing.l
	lex $(SRCDIR)/imageprocessing.l

y.tab.c:$(SRCDIR)/imageprocessing.y $(SRCDIR)/imageprocessing.l
	bison -dy $(SRCDIR)/imageprocessing.y -Wconflicts-rr

lib_imageprocessing.o:$(SRCDIR)/lib_imageprocessing.c
	gcc -c $(SRCDIR)/lib_imageprocessing.c -lm

util.o:$(SRCDIR)/util.c
	gcc -c $(SRCDIR)/util.c -lm

clean:
	rm *.h lex.yy.c y.tab.c *.o main
