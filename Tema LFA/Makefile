#Grameni Stere-Alexandru 333CC

all: build compile

build: temaFlex.l
	flex temaFlex.l

compile: lex.yy.c
	gcc lex.yy.c

clear:
	rm lex.yy.c
	rm a.out
