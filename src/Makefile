CPP = g++
CPPFLAGS = -Wall -Wextra -Wextra -std=c++17

all: clean install

install:
	@mkdir -p build
	@cd build && qmake .. && make
	@-cd build && make clean && rm -f Makefile
	@mv build ~
uninstall:
	@rm -rf ~/build

dvi:
#texi2dvi 3D_Viewer_manual.texi
#xdvi 3D_Viewer_manual.dvi
	@open ./3D_Viewer_manual.html

dist: 
	@tar -czf s21_3D_Viewer.tar ~/build/3D_Viewer

tests:
	@$(CPP) test/test.cc ModelOperations.cc ReadMethods.cc -o tst --coverage -lgtest $(CPPFLAGS) -g
	@./tst


gcov_report: tests
	@lcov -t "gcov_report" -o gcov_report.info -c -d ./
	@genhtml -o report gcov_report.info
	@rm -f *.gcda *.gcno *.gcov *.info
	@open report/index.html

gcov_report1: tests
	@mkdir -p report
	@gcovr -r . --html --html-details -o report/index.html
	@rm -rf *.gcda *.gcno
	@open report/index.html

check_style:
	@cp ../materials/linters/.clang-format ./
	@clang-format -n *.cc *.h *.cpp headers/* test/test.cc
	@rm .clang-format

valgrind:
	@valgrind -s --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./tst

rebuild: all

clean:
	@rm -rf *.gcda *.gcno *.out *.dSYM *.o *.a report s21_3D_Viewer.tar *.log *.toc *.aux *.dvi *.pdf tst
