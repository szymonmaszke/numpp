# -*- MakeFile -*-

all: \
	matrix_multiplication \
	differentiation_forward \
	differentiation_backward \
	differentiation_central \

#Flags
CXXFLAGS = -std=c++17 -O3 -march=native

matrix_multiplication: setup_tests
	python ./structures/matrices/normal/generate_speed_test.py -c 1000 -s 100 -t ./structures/matrices/normal/test_templates/eigen_template -al -100 -ah 100 -l ./structures/matrices/normal/logs/eigen_compilation >> ./structures/matrices/normal/logs/eigen_runtime
	python ./structures/matrices/normal/generate_speed_test.py -c 1000 -s 100 -t ./structures/matrices/normal/test_templates/numpp_template -al -100 -ah 100 -l ./structures/matrices/normal/logs/numpp_compilation >> ./structures/matrices/normal/logs/numpp_runtime
	python ./utilities/average_compile_time.py ./structures/matrices/normal/logs/numpp_compilation ./structures/matrices/normal/logs/eigen_compilation
	python ./utilities/average_runtime.py ./structures/matrices/normal/logs/numpp_runtime ./structures/matrices/normal/logs/eigen_runtime

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
