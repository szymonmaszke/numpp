all: nigga_fag_work

SYMPY_COMPILATION=`cmake --find-package -DNAME=SymEngine -DCOMPILER_ID=GNU -DLANGUAGE=CXX -DMODE=COMPILE`
SYMPY_LINKING=`cmake --find-package -DNAME=SymEngine -DCOMPILER_ID=GNU -DLANGUAGE=CXX -DMODE=LINK`

CXXFLAGS = -std=c++17 -Wall -Werror -Weffc++ -O3 -march=native -fopenmp -fopenmp-simd

nigga_fag_work:
	g++ $(SYMPY_COMPILATION) $(CXXFLAGS) ./symengine.cpp $(SYMPY_LINKING)
