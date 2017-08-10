#ifndef CONJUGATE_GRADIENT_HPP
#define CONJUGATE_GRADIENT_HPP

#include"../structures/vector/matrix_vector_operations.hpp"

#if defined  __GNUC__ && !defined __clang__
  #define CONSTEXPR constexpr
#elif
  #define CONSTEXPR
#endif

namespace numpp::krylov{
  template<typename T, std::size_t Size>
    CONSTEXPR auto conjugate_gradient(
        const matrix::dense<T, Size, Size>& A,
        const vector<T, Size>& x,
        const vector<T, Size>& b,
        const double threshold = 0.01,
        const std::size_t iterations= Size > 20 ? Size : 20
        ){
  /**
    \ingroup numpp_krylov

    \brief Calculates solution to linear equation \f$ Ax = b \f$ via conjugate gradient

    \tparam T Argument type of the matrix (e.g. double)
    \tparam Size size of matrix row and column (have to be equal)

    \param A matrix A of the method
    <b>\warning Matrix A HAS TO be symmetric, it's not enforced in anyway in this method</b>
    \param x Vector containing an initial guess of the solution (solution won't be placed here!).
    <b>\warning If you are unsure about this parameter go with vector filled with 1's.</b>
    \param b Solution vector of the linear equations

    \param threshold Tolerance of the algorithm. If the error (as an euclidean norm of residual)\n
    is smaller than this value, the algorithm will stop

    \param iterations Maximum number of iterations performed by the algorithm

    Conjugate gradient is one of the algorithms from the krylov subspace method.

    It may allow us to solve linear equations of the form \f$Ax = b\f$ in a more efficient manner\n
    than popular direct methods like LU, Cholesky or similiar.

    For exact use cases consult the professional literature.

    \returns vector of type identical to x filled with an answer
    @{
  */

      auto residual = b - (A*x);
      auto direction{residual};

      auto temp{x};
      for(std::size_t i = 0; i<iterations; ++i){
        const auto alpha {sum(residual)/(sum(direction, A*direction))};


        temp = temp + (alpha * direction);
        auto residual_next = residual - alpha * (A * direction);
        if(norm::euclidean(residual_next) < threshold)
          break;
        auto beta = sum(residual_next)/sum(residual);

        direction = residual_next + beta*direction;
        residual = std::move(residual_next);
      }

      return temp;

    }

  template<typename T, std::size_t Size>
    CONSTEXPR auto conjugate_gradient(
        const matrix::dense<T, Size, Size>& A,
        const vector<T, Size>& b,
        const vector<T, Size>& x,
        const matrix::dense<T, Size, Size>& preconditioner,
        const double threshold = 0.01,
        const std::size_t iterations= Size > 20 ? Size : 20
        ){
  /**
    \overload
    \param preconditioner matrix being a preconditioner to the method. \n
    If used correctly it can speed up algorithm convergence.
    \warning If you are unsure about this parameter use the version without it!

  */
      auto residual = b - (A*x);
      auto precondition = preconditioner * residual;
      auto direction{precondition};

      auto temp{x};

      for(int i=0; i<iterations; ++i){
        const auto alpha {sum(residual)/(sum(direction, A*direction))};

        temp += alpha * direction;
        auto residual_next = residual - alpha * (A * direction);
        if(norm::euclidean(residual_next) < threshold)
          break;

        auto preconditioner_next = preconditioner * residual_next;

        auto beta = sum(preconditioner_next, residual_next)/sum(precondition, residual);

        direction = preconditioner_next + beta*direction;
        residual = std::move(residual_next);
        precondition = std::move(preconditioner_next);
      }

      return temp;

    }
}

#endif
