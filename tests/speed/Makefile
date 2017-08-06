# -*- MakeFile -*-

all: \
	finite_differentiation_central_gsl \
	finite_differentiation_forward_gsl \
	finite_differentiation_backward_gsl \
	matrix_multiplication_eigen \
	symbolic_differentiatiation_symengine

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
EIGEN_MATRIX_CASES = 100
NUMPP_MATRIX_CASES = 100

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
DIFFERENTIATION_FINITE_CASES = 15

#INTEGER VALUE: HOW MANY EXPRESSIONS IN EACH TEST (DON'T SET TOO HIGH VALUE)
DIFFERENTIATION_FINITE_EXPRESSIONS = 5

#PATH: DIFFERENTIATION LOGS LOCALIZATION
DIFFERENTIATION_FINITE_FORWARD_LOG_RUNTIME  = ./differentiation/logs/forward/runtime
DIFFERENTIATION_FINITE_BACKWARD_LOG_RUNTIME = ./differentiation/logs/backward/runtime
DIFFERENTIATION_FINITE_CENTRAL_LOG_RUNTIME = ./differentiation/logs/central/runtime

#HOW MANY SPEED TESTS MAY FAIL IN PERCENT? E.G. 0.01 FOR ONE PERCENT, USUALLY FAILS 0.005
DIFFERENTIATION_PASSED_TESTS_RATIO = 0.01

#
#SYMBOLIC DIFFERENTIATION SPECIFIC PARAMETERS
#

#RANDOMLY GENERATED ARGUMENTS TO DERIVATIVES
#LOWEST POSSIBLE VALUE IS ZERO, SYMENG CRASHES OTHERWISE (?)
SYMENGINE_LOW = 0
SYMENGINE_HIGH = 200

SYMENGINE_CASES = 100000

#
#TARGETS
#

catch_tests: ../utilities/tests_main.cpp ../utilities/catch.hpp
	$(CXX) $(CXXFLAGS) ../utilities/tests_main.cpp -c -o ../utilities/tests_main.o

matrix_multiplication_eigen: setup_tests
	python3 ./structures/matrices/normal/generate_speed_test.py \
					-c $(EIGEN_MATRIX_CASES) -s $(SIZE) \
					-t ./structures/matrices/normal/test_templates/eigen_template \
					-al $(LOW) -ah $(HIGH) -l $(EIGEN_MATRIX_MULTIPLICATION_COMPILATION_LOG) \
					>> $(EIGEN_MATRIX_MULTIPLICATION_RUNTIME_LOG)
	python3 ./structures/matrices/normal/generate_speed_test.py \
					-c $(NUMPP_MATRIX_CASES) -s $(SIZE) \
					-t ./structures/matrices/normal/test_templates/numpp_template \
					-al $(LOW) -ah $(HIGH) -l $(NUMPP_MATRIX_MULTIPLICATION_COMPILATION_LOG) \
					>> $(NUMPP_MATRIX_MULTIPLICATION_RUNTIME_LOG)
	python3 ./utilities/average_time.py \
					$(NUMPP_MATRIX_MULTIPLICATION_COMPILATION_LOG) \
					$(EIGEN_MATRIX_MULTIPLICATION_COMPILATION_LOG) \
					-m Compilation
	python3 ./utilities/average_time.py \
					$(NUMPP_MATRIX_MULTIPLICATION_RUNTIME_LOG) \
					$(EIGEN_MATRIX_MULTIPLICATION_RUNTIME_LOG) \
					-m Runtime

finite_differentiation_forward_gsl: catch_tests setup_tests
	python3 ./differentiation/forward_test.py \
					-t ./differentiation/test_templates/test_template \
					-c $(DIFFERENTIATION_FINITE_CASES) \
					-e $(DIFFERENTIATION_FINITE_EXPRESSIONS) \
					-nl $(GENERATOR_LOW) -nh $(GENERATOR_HIGH) -al $(LOW) -ah $(HIGH) \
					>> $(DIFFERENTIATION_FINITE_FORWARD_LOG_RUNTIME) \
					2> /dev/null
	python3 ./utilities/test_differentiation_success.py \
					$(DIFFERENTIATION_PASSED_TESTS_RATIO) \
					-l $(DIFFERENTIATION_FINITE_FORWARD_LOG_RUNTIME) \
					-m "Forward finite differentiation"

finite_differentiation_backward_gsl: catch_tests setup_tests
	python3 ./differentiation/backward_test.py \
					-t ./differentiation/test_templates/test_template \
					-c $(DIFFERENTIATION_FINITE_CASES) \
					-e $(DIFFERENTIATION_FINITE_EXPRESSIONS) \
					-nl $(GENERATOR_LOW) -nh $(GENERATOR_HIGH) -al $(LOW) -ah $(HIGH) \
					>> $(DIFFERENTIATION_FINITE_BACKWARD_LOG_RUNTIME) \
					2> /dev/null
	python3 ./utilities/test_differentiation_success.py \
					$(DIFFERENTIATION_PASSED_TESTS_RATIO) \
					-l $(DIFFERENTIATION_FINITE_BACKWARD_LOG_RUNTIME) \
					-m "Backward finite differentiation"

finite_differentiation_central_gsl: catch_tests setup_tests
	python3 ./differentiation/central_test.py \
					-t ./differentiation/test_templates/test_template \
					-c $(DIFFERENTIATION_FINITE_CASES) \
					-e $(DIFFERENTIATION_FINITE_EXPRESSIONS) \
					-nl $(GENERATOR_LOW) -nh $(GENERATOR_HIGH) -al $(LOW) -ah $(HIGH) \
					>> $(DIFFERENTIATION_FINITE_CENTRAL_LOG_RUNTIME) \
					2> /dev/null
	python3 ./utilities/test_differentiation_success.py \
					$(DIFFERENTIATION_PASSED_TESTS_RATIO) \
					-l $(DIFFERENTIATION_FINITE_CENTRAL_LOG_RUNTIME) \
					-m "Central finite differentiation"

symbolic_differentiatiation_symengine:
	make -C ./differentiation/symbolic \
					SYMENGINE_LOW=$(SYMENGINE_LOW) SYMENGINE_HIGH=$(SYMENGINE_HIGH) \
					SYMENGINE_CASES=$(SYMENGINE_CASES)

setup_tests:
	./utilities/setup_tests.sh

.PHONY: clean
clean:
	./utilities/clean_tests.sh
