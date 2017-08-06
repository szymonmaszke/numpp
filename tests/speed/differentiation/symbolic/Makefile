all: symengine_comparison

SYMPY_COMPILATION=`cmake --find-package -DNAME=SymEngine -DCOMPILER_ID=GNU -DLANGUAGE=CXX -DMODE=COMPILE`
SYMPY_LINKING=`cmake --find-package -DNAME=SymEngine -DCOMPILER_ID=GNU -DLANGUAGE=CXX -DMODE=LINK`

CXXFLAGS = -std=c++17 -Wall -Werror -Weffc++ -O3 -march=native -fopenmp -fopenmp-simd

SYMENGINE_CASES=100
SYMENGINE_LOW=10
SYMENGINE_HIGH=20

symengine_comparison:
	g++ $(SYMPY_COMPILATION) $(CXXFLAGS) ./symengine_comparison.cpp $(SYMPY_LINKING) -o temp \
		&& ./temp $(SYMENGINE_CASES) $(SYMENGINE_LOW) $(SYMENGINE_HIGH)
