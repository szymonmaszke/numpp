# -*- MakeFile -*-

all: root_finding_bisection \
		vector_structure \
		matrix_normal_structure \
		differentiation_forward \
		differentiation_backward \
		differentiation_central
# all: clean tests_matrix_normal_structure \
# 	tests_vector_structure \
# 	tests_differentiation_forward \
# 	tests_differentiation_backward \
# 	tests_differentiation_central \
# 	tests_root_finding_bisection

#Flags
CXXFLAGS = -std=c++1z

differentiation_forward: catch_tests setup_tests
	python ./differentiation/forward_test.py -t ./differentiation/test_templates/test_template -c 100 -e 15 -nl -100 -nh 100 -al -100 -ah 100 >> ./differentiation/log/forward/test.log
	./test_utilities/test_success.sh ./differentiation/log/forward/test.log 0.01

differentiation_backward: catch_tests setup_tests
	python ./differentiation/backward_test.py -t ./differentiation/test_templates/test_template -c 100 -e 15 -nl -100 -nh 100 -al -100 -ah 100 1> ./differentiation/log/backward/test.log
	./test_utilities/test_success.sh ./differentiation/log/backward/test.log 0.01

differentiation_central: catch_tests setup_tests
	python ./differentiation/central_test.py -t ./differentiation/test_templates/test_template -c 100 -e 15 -nl -100 -nh 100 -al -100 -ah 100 1> ./differentiation/log/central/test.log
	./test_utilities/test_success.sh ./differentiation/log/central/test.log 0.01

root_finding_bisection: catch_tests
	$(CXX) ./test_utilities/tests_main.o $(CXXFLAGS) ./root_finding/bisection.cpp \
		-o temp_root_finding_bisection\
		&& ./temp_root_finding_bisection -r compact

vector_structure: catch_tests
	$(CXX) ./test_utilities/tests_main.o $(CXXFLAGS) ./structures/vector/vector_tests.cpp \
		-o temp_vector_structure \
		&& ./temp_vector_structure -r compact

matrix_normal_structure: catch_tests
	$(CXX) ./test_utilities/tests_main.o  $(CXXFLAGS) ./structures/matrix/normal/tests_structure.cpp \
 		-o temp_matrix_normal_structure \
 		&& ./temp_matrix_normal_structure -r compact


catch_tests: test_utilities/tests_main.cpp test_utilities/catch.hpp
	$(CXX) $(CXXFLAGS) test_utilities/tests_main.cpp -c -o test_utilities/tests_main.o

setup_tests:
	./test_utilities/setup_tests.sh

.PHONY: clean
clean:
	./test_utilities/clean_tests.sh
