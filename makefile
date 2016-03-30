all:	bin/PF.o	bin/RM.o	bin/SM.o	bin/parser.o	bin/CREATE	bin/DROP 	bin/SHOW	bin/TEST_pf		bin/test  bin/query.o  lex.yy.c yacc.tab.o lex.yy.o yacc.tab.h yacc.tab.c lex.yy.o interp.o parser.o bin/main

LEX=flex
YACC=bison
CC=g++
OBJECT=bin/main			#生成的目标文件


bin/main:  bin/PF.o bin/RM.o bin/query.o bin/SM.o  use.cpp lex.yy.o  yacc.tab.o parser.o interp.o
	$(CC)  bin/PF.o bin/RM.o bin/query.o bin/SM.o use.cpp lex.yy.o yacc.tab.o parser.o interp.o -o bin/main -std=c++11
	#@./bin/main	#编译后立刻运行

parser.o: tree.cpp parser_internal.h main.h
	$(CC) -c tree.cpp  -o parser.o -std=c++11

interp.o: interp.cpp parser_internal.h main.h
	$(CC) -c interp.cpp -o interp.o -std=c++11

lex.yy.o: lex.yy.c  yacc.tab.h  main.h
	$(CC) -c lex.yy.c -std=c++11

yacc.tab.o: yacc.tab.c  main.h
	$(CC) -c yacc.tab.c -std=c++11

yacc.tab.c  yacc.tab.h: yacc.y
#	bison使用-d参数编译.y文件
	$(YACC)  --debug --verbose -d yacc.y

lex.yy.c: lex.l lexhelper.cpp yacc.tab.h
	$(LEX) lex.l 

bin/test: bin/PF.o bin/RM.o bin/query.o bin/SM.o  test.cpp
	g++ bin/PF.o bin/RM.o bin/query.o bin/SM.o test.cpp -o bin/test -std=c++11
bin/query.o: query.h query.cpp parser.h
	g++ -c query.cpp -o bin/query.o -std=c++11
bin/TEST_rm:	bin/PF.o	bin/RM.o	test_record_manager.cpp
	g++ bin/PF.o bin/RM.o test_record_manager.cpp -o bin/TEST_rm -std=c++11

bin/TEST_pf: test_pages_file.cpp bin/PF.o
	g++ bin/PF.o test_pages_file.cpp -o bin/TEST_pf -std=c++11

bin/CREATE:	CREATE.cpp	bin/RM.o	bin/PF.o
	g++ bin/PF.o bin/SM.o bin/RM.o CREATE.cpp -o bin/CREATE -std=c++11

bin/DROP:	DROP.cpp	bin/RM.o	bin/PF.o
	g++ bin/PF.o bin/RM.o DROP.cpp -o bin/DROP -std=c++11

bin/SHOW:	SHOW.cpp	bin/RM.o	bin/PF.o
	g++ bin/PF.o bin/RM.o SHOW.cpp -o bin/SHOW -std=c++11

bin/parser.o:	parser.h	parser.cpp	system_manage.h
	g++ -c parser.cpp -o bin/parser.o -std=c++11

bin/SM.o:	system_manage.h	system_manage.cpp
	g++ -c system_manage.cpp -o bin/SM.o -std=c++11

bin/RM.o: pages_file.h record_manager.h record_manager.cpp pf_defines.h
	g++ -c record_manager.cpp -o bin/RM.o -std=c++11

bin/PF.o: pages_file.h pages_file.cpp pf_defines.h
	g++ -c pages_file.cpp -o bin/PF.o -std=c++11

clean:
	rm -r bin/*
	rm *~
