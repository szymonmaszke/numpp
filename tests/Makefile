# -*- MakeFile -*-
#  NEEDS FIXING WITH .cpp FILES RECOMPILATION, TEMP WORKAROUND, I'M SLEEPY...

all: clean tests_matrix_normal_structure \
	tests_vector_structure \
	tests_differentiation_forward \
	tests_differentiation_backward \
	tests_differentiation_central \
	tests_root_finding_bisection

#Flags
CXXFLAGS = -std=c++1z

tests_root_finding_bisection: tests_main.o
	$(CXX) tests_main.o $(CXXFLAGS) ./root_finding/bisection.cpp \
		-o tests_root_finding_bisection\
		&& ./tests_root_finding_bisection -r compact

tests_differentiation_central: tests_main.o
	$(CXX) tests_main.o $(CXXFLAGS) ./differentiation/central_tests.cpp \
		-o tests_differentiation_central\
		&& ./tests_differentiation_central -r compact

tests_differentiation_backward: tests_main.o
	$(CXX) tests_main.o $(CXXFLAGS) ./differentiation/backward_tests.cpp \
		-o tests_differentiation_backward \
		&& ./tests_differentiation_backward -r compact

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
									 tests_differentiation_forward \
									 tests_differentiation_backward \
									 tests_differentiation_central \
									 tests_root_finding_bisection
