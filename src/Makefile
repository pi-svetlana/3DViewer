CLANGFILES = */*.cc */*.h

.PHONY: tests build

all: install

build:
	cmake -S ../ -B build -DCMAKE_BUILD_TYPE=Release $(coverage_build_flag)
	cmake --build build

run:
	open build/src/view.app

rebuild: uninstall clean build

install: build

uninstall:
	rm -rf build/*

tests: build
	cd build/src/tests/ && ./viewer_tests

dist: uninstall clean
	tar -czf 3D_Viewer_v2.tar.gz ./*

clang-check:
	clang-format -n --style=Google -verbose $(CLANGFILES)

clang-format:
	clang-format -i --style=Google -verbose $(CLANGFILES)

leaks:
ifeq ($(shell uname -s), Linux)
	cd build/src/tests/ && valgrind --tool=memcheck --leak-check=yes --track-origins=yes --quiet ./viewer_tests
else
	cd build/src/tests/ && CK_FORK=no leaks --atExit -- ./viewer_tests
endif

clean:
	rm -rf *user gcov* report *.tar.gz guide/html guide/latex ../*user ../.idea build

gcov_report: coverage_build_flag= -DCMAKE_CXX_FLAGS_RELEASE="-g -fprofile-arcs -ftest-coverage"
gcov_report: tests
	mkdir -p report
	gcovr -r . --html-details -o ./report/gcov_report.html -f model/converter.cc -f model/obj_parser.cc
	open ./report/gcov_report.html
