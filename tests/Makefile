# -*- MakeFile -*-
#  NEEDS FIXING WITH .cpp FILES RECOMPILATION, TEMP WORKAROUND, I'M SLEEPY...

all: clean tests_matrix_normal_structure \
	tests_vector_structure \
	tests_differentiation_forward

#Flags
CXXFLAGS = -std=c++14

tests_differentiation_forward: tests_main.o
	$(CXX) tests_main.o $(CXXFLAGS) ./differentiation/forward_tests.cpp \
		-o tests_differentiation_forward \
		&& ./tests_differentiation_forward -r compact

tests_vector_structure: tests_main.o
	$(CXX) tests_main.o $(CXXFLAGS) ./structures/vector/vector_tests.cpp \
		-o tests_vector_structure \
		&& ./tests_vector_structure -r compact

tests_matrix_normal_structure: tests_main.o
	$(CXX) tests_main.o $(CXXFLAGS) ./structures/matrix/normal/tests_structure.cpp \
		-o tests_matrix_normal_structure \
		&& ./tests_matrix_normal_structure -r compact

tests_main.o: tests_main.cpp catch.hpp
	$(CXX) tests_main.cpp -c

clean:
	rm -rf *.o *.gch tests_matrix_normal_structure \
									 tests_vector_structure \
									 tests_differentiation_forward
