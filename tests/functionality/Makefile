# -*- MakeFile -*-

all: \
		matrix_normal_operations \
		matrix_normal_functions \
		root_finding_bisection \
		vector \
		matrix_normal_structure \
		matrix_vector_operations

#Flags
# ‑mveclibabi=svml
CXXFLAGS = -std=c++17 -Wall -Werror -pedantic -Weffc++ -O3 -march=native -fopenmp -fopenmp-simd

matrix_vector_operations: catch_tests
	$(CXX) ../utilities/tests_main.o $(CXXFLAGS) ./structures/vector_matrix_tests.cpp \
		-o temp_matrix_vector_operations\
		&& ./temp_matrix_vector_operations -r compact

matrix_normal_operations: catch_tests
	$(CXX) ../utilities/tests_main.o $(CXXFLAGS) ./structures/matrices/normal/operations_tests.cpp \
		-o temp_matrix_normal_operations \
		&& ./temp_matrix_normal_operations -r compact

matrix_normal_functions: catch_tests
	$(CXX) ../utilities/tests_main.o $(CXXFLAGS) ./structures/matrices/normal/functions_tests.cpp \
		-o temp_matrix_normal_functions \
		&& ./temp_matrix_normal_functions -r compact

root_finding_bisection: catch_tests
	$(CXX) ../utilities/tests_main.o $(CXXFLAGS) ./root_finding/bisection.cpp \
		-o temp_root_finding_bisection\
		&& ./temp_root_finding_bisection -r compact

vector: catch_tests
	$(CXX) ../utilities/tests_main.o $(CXXFLAGS) ./structures/vector/vector_tests.cpp \
		-o temp_vector \
		&& ./temp_vector -r compact

matrix_normal_structure: catch_tests
	$(CXX) ../utilities/tests_main.o  $(CXXFLAGS) ./structures/matrices/normal/structure_tests.cpp \
 		-o temp_matrix_normal_structure \
 		&& ./temp_matrix_normal_structure -r compact

catch_tests: ../utilities/tests_main.cpp ../utilities/catch.hpp
	$(CXX) $(CXXFLAGS) ../utilities/tests_main.cpp -c -o ../utilities/tests_main.o

.PHONY: clean
clean:
	./utilities/clean_tests.sh
