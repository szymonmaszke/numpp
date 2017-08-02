#ifndef CONJUGATE_GRADIENT_HPP
#define CONJUGATE_GRADIENT_HPP

#include"../structures/matrix_vector_operations.hpp"

#if defined  __GNUC__ && !defined __clang__
  #define CONSTEXPR constexpr
#elif
  #define CONSTEXPR
#endif

namespace numpp::krylov{
  template<typename T, std::size_t Size>
    CONSTEXPR auto conjugate_gradient(
        const matrix::normal<T, Size, Size>& A,
        const vector<T, Size>& x,
        const vector<T, Size>& b,
        const double threshold = 0.01
        ){

      auto residual = b - (A*x);
      auto direction{residual};

      auto temp{x};
      for(std::size_t i = 0; i<b.size(); ++i){
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
        const matrix::normal<T, Size, Size>& A,
        const vector<T, Size>& b,
        const vector<T, Size>& x,
        const matrix::normal<T, Size, Size>& preconditioner_matrix,
        const double threshold = 0.01
        ){
      auto residual = b - (A*x);
      auto preconditioner = preconditioner_matrix * residual;
      auto direction{preconditioner};

      auto temp{x};

      for(int i=0; i<b.size(); ++i){
        const auto alpha {sum(residual)/(sum(direction, A*direction))};

        temp += alpha * direction;
        auto residual_next = residual - alpha * (A * direction);
        if(norm::euclidean(residual_next) < threshold)
          break;

        auto preconditioner_next = preconditioner_matrix * residual_next;

        auto beta = sum(preconditioner_next, residual_next)/sum(preconditioner, residual);

        direction = preconditioner_next + beta*direction;
        residual = std::move(residual_next);
        preconditioner = std::move(preconditioner_next);
      }

      return temp;

    }
}

#endif
