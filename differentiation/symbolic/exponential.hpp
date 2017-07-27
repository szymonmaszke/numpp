#ifndef NUMPP_DIFFERENTIATION_SYMBOLIC_EXPONENTIAL_HPP_
#define NUMPP_DIFFERENTIATION_SYMBOLIC_EXPONENTIAL_HPP_

#include<type_traits>
#include<cmath>
#include"types.hpp"
#include"arithmetic.hpp"

namespace numpp::differentiation::symbolic{
  template<typename T>
    class log{
      public:
        using active = typename T::active;
        using type = log<T>;

        using derivative = std::conditional_t<
          typename T::active{},
            std::conditional_t<
              std::is_arithmetic<typename T::type>::value,
                divide<constant<1>, T>,
                multiply<divide<constant<1>, T>, typename T::derivative>
            >,
            log<T>
        >;
        template<typename U>
          constexpr U operator()(U value)const{
            return std::log(inner(value));
          }

      private:
        const T inner{};
    };

  template<typename T>
    class exp{
      public:
        using active = typename T::active;
        using type = exp<T>;

        using derivative = std::conditional_t<
              std::is_arithmetic<typename T::type>::value,
                exp<T>,
                multiply<exp<T>, typename T::derivative>
        >;
        template<typename U>
          constexpr U operator()(U value)const{
            return std::exp(inner(value));
          }

      private:
        const T inner{};
    };

}

#endif
