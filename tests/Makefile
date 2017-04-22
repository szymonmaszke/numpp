# -*- MakeFile -*-

all: \
		matrix_normal_operations \
		root_finding_bisection \
		vector_structure \
		matrix_normal_structure \

#Flags
CXXFLAGS = -std=c++17

matrix_multiplication_speed: setup_tests
	python ./structures/matrix/normal/generate_speed_test.py -c 50 -s 100 -t ./structures/matrix/normal/test_templates/eigen_template -al -100 -ah 100 -l ./structures/matrix/normal/log/eigen_compilation >> ./structures/matrix/normal/log/eigen_runtime
	python ./structures/matrix/normal/generate_speed_test.py -c 50 -s 100 -t ./structures/matrix/normal/test_templates/numpp_template -al -100 -ah 100 -l ./structures/matrix/normal/log/numpp_compilation >> ./structures/matrix/normal/log/numpp_runtime
	python ./test_utilities/average_compile_time.py ./structures/matrix/normal/log/numpp_compilation ./structures/matrix/normal/log/eigen_compilation
	python ./test_utilities/average_runtime.py ./structures/matrix/normal/log/numpp_runtime ./structures/matrix/normal/log/eigen_runtime

# matrix_multiply_eigen_speed: setup_tests
# 	python ./structures/matrix/normal/generate_speed_test.py -c 1000 -s 100 -t ./structures/matrix/normal/test_templates/eigen_template -al -100 -ah 100 -l ./structures/matrix/normal/log/eigen_compilation >> ./structures/matrix/normal/log/eigen_runtime

# matrix_multiply_numpp_speed: setup_tests
# 	python ./structures/matrix/normal/generate_speed_test.py -c 1000 -s 100 -t ./structures/matrix/normal/test_templates/numpp_template -al -100 -ah 100 -l ./structures/matrix/normal/log/numpp_compilation >> ./structures/matrix/normal/log/numpp_runtime

differentiation_forward: catch_tests setup_tests
	python ./differentiation/forward_test.py -t ./differentiation/test_templates/test_template -c 10000 -e 15 -nl -100 -nh 100 -al -100 -ah 100 >> ./differentiation/log/forward/test.log
	./test_utilities/test_success.sh ./differentiation/log/forward/test.log 0.01

differentiation_backward: catch_tests setup_tests
	python ./differentiation/backward_test.py -t ./differentiation/test_templates/test_template -c 10000 -e 15 -nl -100 -nh 100 -al -100 -ah 100 1> ./differentiation/log/backward/test.log
	./test_utilities/test_success.sh ./differentiation/log/backward/test.log 0.01

differentiation_central: catch_tests setup_tests
	python ./differentiation/central_test.py -t ./differentiation/test_templates/test_template -c 10000 -e 15 -nl -100 -nh 100 -al -100 -ah 100 1> ./differentiation/log/central/test.log
	./test_utilities/test_success.sh ./differentiation/log/central/test.log 0.01

matrix_normal_operations: catch_tests
	$(CXX) ./test_utilities/tests_main.o $(CXXFLAGS) ./structures/matrix/normal/operations_tests.cpp \
		-o temp_matrix_normal_operations \
		&& ./temp_matrix_normal_operations -r compact

root_finding_bisection: catch_tests
	$(CXX) ./test_utilities/tests_main.o $(CXXFLAGS) ./root_finding/bisection.cpp \
		-o temp_root_finding_bisection\
		&& ./temp_root_finding_bisection -r compact

vector_structure: catch_tests
	$(CXX) ./test_utilities/tests_main.o $(CXXFLAGS) ./structures/vector/vector_tests.cpp \
		-o temp_vector_structure \
		&& ./temp_vector_structure -r compact

matrix_normal_structure: catch_tests
	$(CXX) ./test_utilities/tests_main.o  $(CXXFLAGS) ./structures/matrix/normal/structure_tests.cpp \
 		-o temp_matrix_normal_structure \
 		&& ./temp_matrix_normal_structure -r compact


catch_tests: test_utilities/tests_main.cpp test_utilities/catch.hpp
	$(CXX) $(CXXFLAGS) test_utilities/tests_main.cpp -c -o test_utilities/tests_main.o

setup_tests:
	./test_utilities/setup_tests.sh

.PHONY: clean
clean:
	./test_utilities/clean_tests.sh
