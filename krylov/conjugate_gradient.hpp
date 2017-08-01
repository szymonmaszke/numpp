#ifndef CONJUGATE_GRADIENT_HPP
#define CONJUGATE_GRADIENT_HPP

#include"../structures/matrix_vector_operations.hpp"

namespace numpp::krylov{
  template<typename T, typename U, std::size_t Size>
    constexpr auto conjugate_gradient(
        const matrix::normal<T, Size, Size>& A,
        const vector<U, Size>& x,
        const vector<U, Size>& b,
        std::size_t iterations = Size*Size*Size
        ){

      auto residual = b - (A*x);
      auto direction{residual};

      auto temp{x};
      for(std::size_t i = 0; i<iterations; ++i){
        const auto alpha {sum(residual)/(sum(direction, A*direction))};


        temp = temp + (alpha * direction);
        auto residual_next = residual - alpha * (A * direction);
        //SPRAWDZENIE ROZMIARU RESIDUAL
        auto beta = sum(residual_next)/sum(residual);

        direction = residual_next + beta*direction;
        residual = std::move(residual_next);
      }

      return temp;

    }

  template<typename T, typename U, std::size_t Size>
    constexpr auto conjugate_gradient(
        const matrix::normal<T, Size, Size>& A,
        const vector<U, Size>& b,
        vector<U, Size>& x,
        const matrix::normal<T, Size, Size>& preconditioner_matrix,
        std::size_t iterations = Size*Size*Size
        ){
      auto residual = b - (A*x);
      auto preconditioner = preconditioner_matrix * residual;
      auto direction{preconditioner};

      for(int i=0; i<iterations; ++i){
        auto alpha =
          (transpose(residual) * preconditioner)/
          (transpose(direction) * (A * direction));

        x += alpha * direction;
        auto residual_next = residual - alpha * (A * direction);
        auto preconditioner_next = preconditioner_matrix * residual_next;

        auto beta =
          (transpose(preconditioner_next) * residual_next)/
          (transpode(preconditioner) * residual);

        direction = preconditioner_next + beta*direction;
        residual = std::move(residual_next);
        preconditioner = std::move(preconditioner_next);
      }

      return x;

    }
}

#endif
