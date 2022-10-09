CC = g++
FLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic
TSTFLAGS = -g -pthread -lgtest_main -lgtest
OS = $(shell uname -s)

all: test

test_stack: test_stack.cc
	$(CC) $(FLAGS) $(TSTFLAGS) $^
	-./a.out

test_set: test_set.cc
	$(CC) $(FLAGS) $(TSTFLAGS) $^
	-./a.out

test_map: test_map.cc
	$(CC) $(FLAGS) $(TSTFLAGS) $^
	-./a.out

test_queue: test_queue.cc
	$(CC) $(FLAGS) $(TSTFLAGS) $^
	-./a.out

test_vector: test_vector.cc
	$(CC) $(FLAGS) $(TSTFLAGS) $^
	-./a.out

test_list: test_list.cc
	$(CC) $(FLAGS) $(TSTFLAGS) $^
	-./a.out

test_array: test_array.cc
	$(CC) $(FLAGS) $(TSTFLAGS) $^
	-./a.out

test_multiset: test_multiset.cc
	$(CC) $(FLAGS) $(TSTFLAGS) $^
	-./a.out
	
test: test_stack.cc test_set.cc test_queue.cc test_vector.cc test_list.cc test_array.cc test_multiset.cc test_map.cc
	$(CC) $(FLAGS) $(TSTFLAGS) $^
	-./a.out

clean:
	rm -rf *.o *.a *.gch *.gcda *.gcno *.info *.out report

gcov_report: test_stack.cc test_set.cc test_queue.cc test_vector.cc test_list.cc test_array.cc test_multiset.cc test_map.cc
	$(CC) $(TSTFLAGS) -fprofile-arcs -ftest-coverage $^
	-./a.out
	lcov -t "test" --no-external -o test.info -c -d .
	genhtml -o report test.info
ifeq ($(OS), Darwin)
	-open report/index.html
else
	-xdg-open report/index.html
endif

check:
	clang-format -n ./*.cc ./*.h

leaks: test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind --leak-check=full --show-leak-kinds=all \
        --track-origins=yes --verbose --quiet -s ./a.out 
endif

leaks_stack: test_stack
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind --leak-check=full --show-leak-kinds=all \
        --track-origins=yes --verbose --quiet -s ./a.out 
endif

leaks_queue: test_queue
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind --leak-check=full --show-leak-kinds=all \
        --track-origins=yes --verbose --quiet -s ./a.out 
endif

leaks_set: test_set
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind --leak-check=full --show-leak-kinds=all \
        --track-origins=yes --verbose --quiet -s ./a.out 
endif

leaks_vector: test_vector
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind --leak-check=full --show-leak-kinds=all \
        --track-origins=yes --verbose --quiet -s ./a.out 
endif

leaks_list: test_list
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind --leak-check=full --show-leak-kinds=all \
        --track-origins=yes --verbose --quiet -s ./a.out 
endif

leaks_array: test_array
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind --leak-check=full --show-leak-kinds=all \
        --track-origins=yes --verbose --quiet -s ./a.out 
endif

leaks_multiset: test_multiset
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind --leak-check=full --show-leak-kinds=all \
        --track-origins=yes --verbose --quiet -s ./a.out 
endif
