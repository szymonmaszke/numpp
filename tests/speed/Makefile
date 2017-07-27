# -*- MakeFile -*-

all: \
	matrix_multiplication \
	differentiation_forward \
	differentiation_backward \
	differentiation_central \

#Flags
CXXFLAGS = -std=c++17 -Wall -Werror -pedantic -Weffc++ -O3 -march=native -fopenmp -fopenmp-simd -fconstexpr-detph=4294967296 -fconstexpr-loop-limit=4294967296

#How many tests
EIGEN_CASES = 1000
NUMPP_CASES = 1000

#Size of matrices (number of elements, sqrt(SIZE) has to be int)
SIZE = 100

#Low and high arguments for random generators
LOW  = -100
HIGH =  100

#Path to log folders
EIGEN_COMPILATION = ./structures/matrices/normal/logs/eigen_compilation
EIGEN_RUNTIME 		= ./structures/matrices/normal/logs/eigen_runtime

NUMPP_COMPILATION = ./structures/matrices/normal/logs/numpp_compilation
NUMPP_RUNTIME 		= ./structures/matrices/normal/logs/numpp_runtime


matrix_multiplication: setup_tests
	python ./structures/matrices/normal/generate_speed_test.py -c $(EIGEN_CASES) -s $(SIZE) -t ./structures/matrices/normal/test_templates/eigen_template -al $(LOW) -ah $(HIGH) -l $(EIGEN_COMPILATION) >> $(EIGEN_RUNTIME)
	python ./structures/matrices/normal/generate_speed_test.py -c $(NUMPP_CASES) -s $(SIZE) -t ./structures/matrices/normal/test_templates/numpp_template -al $(LOW) -ah $(HIGH) -l $(NUMPP_COMPILATION) >> $(NUMPP_RUNTIME)
	python ./utilities/average_compile_time.py $(NUMPP_COMPILATION) $(EIGEN_COMPILATION)
	python ./utilities/average_runtime.py $(NUMPP_RUNTIME) $(EIGEN_RUNTIME)

differentiation_forward: catch_tests setup_tests
	python ./differentiation/forward_test.py -t ./differentiation/test_templates/test_template -c 10000 -e 15 -nl -100 -nh 100 -al -100 -ah 100 >> ./differentiation/logs/forward/runtime 2>/dev/null
	./utilities/test_success.sh ./differentiation/logs/forward/runtime 0.01

differentiation_backward: catch_tests setup_tests
	python ./differentiation/backward_test.py -t ./differentiation/test_templates/test_template -c 10000 -e 15 -nl -100 -nh 100 -al -100 -ah 100 >> ./differentiation/logs/backward/runtime 2>/dev/null
	./utilities/test_success.sh ./differentiation/logs/backward/runtime 0.01

differentiation_central: catch_tests setup_tests
	python ./differentiation/central_test.py -t ./differentiation/test_templates/test_template -c 10000 -e 15 -nl -100 -nh 100 -al -100 -ah 100 >> ./differentiation/logs/central/runtime 2>/dev/null
	./utilities/test_success.sh ./differentiation/logs/central/runtime 0.01

catch_tests: ../utilities/tests_main.cpp ../utilities/catch.hpp
	$(CXX) $(CXXFLAGS) ../utilities/tests_main.cpp -c -o ../utilities/tests_main.o

setup_tests:
	./utilities/setup_tests.sh

.PHONY: clean
clean:
	./utilities/clean_tests.sh
