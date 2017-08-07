# -*- MakeFile -*-

all: \
		dense_operations \
		dense_functions \
		dense_structure \
		vector \
		dense_vector \
		roots_bisection \
		roots_newton \
		krylov_conjugate_gradient

#Flags
# ‑mveclibabi=svml
LIB_PATH = /usr/include
CXXFLAGS = -std=c++17 -Wall -Werror -pedantic -Weffc++ -O3 -march=native -fopenmp -fopenmp-simd

#TEST FRAMEWORK INITIALIZATION
catch_tests: ../utilities/tests_main.cpp ../utilities/catch.hpp
	$(CXX) $(CXXFLAGS) ../utilities/tests_main.cpp -c -o ../utilities/catch.o

#DENSE MATRIX TESTS
dense_operations: catch_tests $(LIB_PATH)/numpp/structures/matrices/dense/operations.hpp
	$(CXX) ../utilities/catch.o $(CXXFLAGS) ./structures/matrices/dense/operations.cpp \
		-o dense_operations.out \
		&& ./dense_operations.out -r compact

dense_functions: catch_tests $(LIB_PATH)/numpp/structures/matrices/dense/functions.hpp
	$(CXX) ../utilities/catch.o $(CXXFLAGS) ./structures/matrices/dense/functions.cpp \
		-o dense_functions.out \
		&& ./dense_functions.out -r compact

dense_structure: catch_tests $(LIB_PATH)/numpp/structures/matrices/dense/structure.hpp
	$(CXX) ../utilities/catch.o  $(CXXFLAGS) ./structures/matrices/dense/structure.cpp \
 		-o dense_structure.out \
 		&& ./dense_structure.out -r compact

#VECTOR TESTS

vector: catch_tests $(LIB_PATH)/numpp/structures/vector/structure.hpp
	$(CXX) ../utilities/catch.o $(CXXFLAGS) ./structures/vector/overall.cpp \
		-o overall.out \
		&& ./overall.out -r compact

dense_vector: catch_tests $(LIB_PATH)/numpp/structures/vector/matrix_vector_operations.hpp
	$(CXX) ../utilities/catch.o $(CXXFLAGS) ./structures/vector/vector_matrix_tests.cpp \
		-o dense_vector.out \
		&& ./dense_vector.out -r compact

#ROOTS TESTS
roots_bisection: catch_tests $(LIB_PATH)/numpp/roots/bisection.hpp
	$(CXX) ../utilities/catch.o $(CXXFLAGS) ./roots/bisection.cpp \
		-o roots_bisection.out \
		&& ./roots_bisection.out -r compact

roots_newton: catch_tests $(LIB_PATH)/numpp/roots/newton.hpp
	$(CXX) ../utilities/catch.o $(CXXFLAGS) ./roots/newton.cpp \
		-o roots_newton.out \
		&& ./roots_newton.out -r compact

#KRYLOV TESTS
krylov_conjugate_gradient: catch_tests $(LIB_PATH)/numpp/krylov/conjugate_gradient.hpp
	$(CXX) ../utilities/catch.o $(CXXFLAGS) ./krylov/conjugate_gradient.cpp \
		-o krylov_conjugate_gradient.out \
		&& ./krylov_conjugate_gradient.out -r compact

.PHONY: clean
clean:
	./utilities/clean_tests.sh
