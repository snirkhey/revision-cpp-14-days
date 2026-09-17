CXX ?= g++
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic -Iinclude
DAYS = day01_references_const day02_const_pointers_members day03_raii \
       day04_rule_of_three day05_unique_ptr day06_move_part1 day07_move_part2 \
       day08_shared_ptr day09_weak_ptr day10_enable_shared_from_this \
       day11_lambdas_part1 day12_lambdas_part2 day13_std_function \
       day14_deferred_queue

.PHONY: all clean

all: $(DAYS)

$(DAYS): %: days/%.cpp include/check.hpp
	$(CXX) $(CXXFLAGS) -o $@ days/$*.cpp

clean:
	rm -f $(DAYS)
