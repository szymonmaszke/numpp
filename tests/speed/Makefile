# -*- MakeFile -*-

all: \
	matrix_multiplication \
	differentiation_forward \
	differentiation_backward \
	differentiation_central \

#Flags
CXXFLAGS = -std=c++17 -Wall -Werror -pedantic -Weffc++ -O3 -march=native -fopenmp -fopenmp-simd

#
#PARAMETERS AFFECTING ALL OF THE TESTS
#

#LOW AND HIGH ARGUMENTS TO FUNCTIONS
LOW  = -100
HIGH =  100

#LOW AND HIGH ARGUMENT TO RANDOM GENERATORS
GENERATOR_LOW = -100
GENERATOR_HIGH = 100

#
# MATRIX MULTIPLICATION SPECIFIC PARAMETERS
#

#HOW MANY TESTS MATRIX MULTIPLICATION
EIGEN_MATRIX_CASES = 20
NUMPP_MATRIX_CASES = 20

#SIZE OF MATRICES (number of elements, sqrt(SIZE) has to be int)
SIZE = 100

#PATH TO LOGS
EIGEN_MATRIX_MULTIPLICATION_COMPILATION_LOG = ./structures/matrices/normal/logs/eigen_compilation
EIGEN_MATRIX_MULTIPLICATION_RUNTIME_LOG 		= ./structures/matrices/normal/logs/eigen_runtime

NUMPP_MATRIX_MULTIPLICATION_COMPILATION_LOG = ./structures/matrices/normal/logs/numpp_compilation
NUMPP_MATRIX_MULTIPLICATION_RUNTIME_LOG 		= ./structures/matrices/normal/logs/numpp_runtime

#
#FINITE DIFFERENCE DIFFERENTIATION PARAMETERS
#

#INTEGER VALUE: HOW MANY TESTS FOR FINITE DIFFERENTIATION TESTS
DIFFERENTIATION_FINITE_CASES = 100

#INTEGER VALUE: HOW MANY EXPRESSIONS IN EACH TEST (DON'T SET TOO HIGH VALUE)
DIFFERENTIATION_FINITE_EXPRESSIONS = 15

#PATH: DIFFERENTIATION LOGS LOCALIZATION
DIFFERENTIATION_FORWARD_LOG  = ./differentiation/logs/forward/runtime
DIFFERENTIATION_BACKWARD_LOG = ./differentiation/logs/backward/runtime
DIFFERENTIATION_CENTRAL_LOG = ./differentiation/logs/central/runtime

#HOW MANY SPEED TESTS MAY FAIL IN PERCENT? E.G. 0.01 FOR ONE PERCENT, USUALLY FAILS 0.005
DIFFERENTIATION_FAILURE_CASES = 0.01



catch_tests: ../utilities/tests_main.cpp ../utilities/catch.hpp
	$(CXX) $(CXXFLAGS) ../utilities/tests_main.cpp -c -o ../utilities/tests_main.o

matrix_multiplication: setup_tests
	python ./structures/matrices/normal/generate_speed_test.py -c $(EIGEN_MATRIX_CASES) -s $(SIZE) -t ./structures/matrices/normal/test_templates/eigen_template -al $(LOW) -ah $(HIGH) -l $(EIGEN_MATRIX_MULTIPLICATION_COMPILATION_LOG) >> $(EIGEN_MATRIX_MULTIPLICATION_RUNTIME_LOG)
	python ./structures/matrices/normal/generate_speed_test.py -c $(NUMPP_MATRIX_CASES) -s $(SIZE) -t ./structures/matrices/normal/test_templates/numpp_template -al $(LOW) -ah $(HIGH) -l $(NUMPP_MATRIX_MULTIPLICATION_COMPILATION_LOG) >> $(NUMPP_MATRIX_MULTIPLICATION_RUNTIME_LOG)
	python ./utilities/average_compile_time.py $(NUMPP_MATRIX_MULTIPLICATION_COMPILATION_LOG) $(EIGEN_MATRIX_MULTIPLICATION_COMPILATION_LOG)
	python ./utilities/average_runtime.py $(NUMPP_MATRIX_MULTIPLICATION_RUNTIME_LOG) $(EIGEN_MATRIX_MULTIPLICATION_RUNTIME_LOG)

differentiation_forward: catch_tests setup_tests
	python ./differentiation/forward_test.py -t ./differentiation/test_templates/test_template -c $(DIFFERENTIATION_FINITE_CASES) -e $(DIFFERENTIATION_FINITE_EXPRESSIONS) -nl $(GENERATOR_LOW) -nh $(GENERATOR_HIGH) -al $(LOW) -ah $(HIGH) >> $(DIFFERENTIATION_FORWARD_LOG)
	./utilities/test_success.sh $(DIFFERENTIATION_FORWARD_LOG) $(DIFFERENTIATION_FAILURE_CASES)

differentiation_backward: catch_tests setup_tests
	python ./differentiation/backward_test.py -t ./differentiation/test_templates/test_template -c $(DIFFERENTIATION_FINITE_CASES) -e $(DIFFERENTIATION_FINITE_EXPRESSIONS) -nl $(GENERATOR_LOW) -nh $(GENERATOR_HIGH) -al $(LOW) -ah $(HIGH) >> $(DIFFERENTIATION_BACKWARD_LOG)
	./utilities/test_success.sh $(DIFFERENTIATION_BACKWARD_LOG) $(DIFFERENTIATION_FAILURE_CASES)

differentiation_central: catch_tests setup_tests
	python ./differentiation/central_test.py -t ./differentiation/test_templates/test_template -c $(DIFFERENTIATION_FINITE_CASES) -e $(DIFFERENTIATION_FINITE_EXPRESSIONS) -nl $(GENERATOR_LOW) -nh $(GENERATOR_HIGH) -al $(LOW) -ah $(HIGH) >> $(DIFFERENTIATION_CENTRAL_LOG)
	./utilities/test_success.sh $(DIFFERENTIATION_CENTRAL_LOG) $(DIFFERENTIATION_FAILURE_CASES)

setup_tests:
	./utilities/setup_tests.sh

.PHONY: clean
clean:
	./utilities/clean_tests.sh
