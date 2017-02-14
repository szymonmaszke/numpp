# -*- MakeFile -*-

all: tests_matrix_normal_structure

tests_matrix_normal_structure: tests_main.o
	$(CXX) tests_main.o ./structures/matrix/normal/tests_structure.cpp \
		-o tests_matrix_normal_structure \
		&& ./tests_matrix_normal_structure -r compact

tests_main.o: tests_main.cpp catch.hpp
	$(CXX) tests_main.cpp -c

clean:
	rm -rf *.o *.gch tests_matrix_normal_structure
