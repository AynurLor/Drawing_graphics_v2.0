CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17
TESTFLAGS=-lgtest

.PHONY: all

all: install


install:
	@make clean
	@mkdir build
	@cd View && qmake && make -j6 && make clean && rm Makefile && cd ../ && mv View/View.app build
	@echo ==Install finished==
	@echo ==To open application write 'make open'==

uninstall:
	@rm -rf build/
	@echo ==Uninstall finished==


test:
	@$(CC) $(CFLAGS) $(TESTFLAGS) --coverage test.cc FileReader/objectfilereader.cc -o test
	@./test

gcov_report:
	@$(CC) $(CFLAGS) $(TESTFLAGS) --coverage test.cc FileReader/objectfilereader.cc -o gcov_report
	@chmod +x *
	@./gcov_report
	@lcov -t "gcov_report" -o gcov_report.info --no-external -c -d .
	@genhtml -o report/ gcov_report.info
	@open ./report/index.html


dvi:
	@open info.html

dist:
	@rm -rf Archive_3DViewer_v2.0/
	@mkdir Archive_3DViewer_v2.0/
	@mkdir Archive_3DViewer_v2.0/src
	@mv ./build/View.app Archive_3DViewer_v2.0/src/
	@tar cvzf Archive_3DViewer_v2.0.tgz Archive_3DViewer_v2.0/
	@rm -rf Archive_3DViewer_v2.0/
	@echo ==Archive was created==

bist:
	@rm -rf Archive_3DViewer_v2.0.tgz
	@echo ==Archive was removed==

open:
	@open ./build/View.app

check:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -i FacadeController/*.hpp
	@clang-format -i FacadeModel/*.hpp
	@clang-format -i FileReader/*.hpp FileReader/*.cc
	@clang-format -i NormalizationParameters/*.hpp
	@clang-format -i ObjectDataModel/*.hpp
	@clang-format -i TransformModel/*.hpp
	@clang-format -i RecordModel/*.hpp RecordModel/*.cc
	@clang-format -i Scene/*.hpp Scene/*.cc
	@clang-format -i View/*.h View/*.cpp
	@clang-format -i test.cc

	@clang-format -n FacadeController/*.hpp
	@clang-format -n FacadeModel/*.hpp
	@clang-format -n FileReader/*.hpp FileReader/*.cc
	@clang-format -n NormalizationParameters/*.hpp
	@clang-format -n ObjectDataModel/*.hpp
	@clang-format -n TransformModel/*.hpp
	@clang-format -n RecordModel/*.hpp RecordModel/*.cc
	@clang-format -n Scene/*.hpp Scene/*.cc
	@clang-format -n View/*.h View/*.cpp
	@clang-format -n test.cc	

	@rm .clang-format
	@echo ==No style errors==


clean:
	@rm -rf *.{a,o,dSYM,out}
	@rm -rf $(EXECUTABLE)
	@rm -rf gcov_report
	@rm -rf report
	@rm -rf CPPLINT.cppfg
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf test
	@rm -rf Archive_3DViewer_v2.0 
	@rm -rf *tgz
	@rm -rf build
	@rm -rf gcov_test
	@echo ==Clean was finished==


