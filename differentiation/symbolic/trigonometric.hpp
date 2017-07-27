#ifndef NUMPP_SYMBOLIC_TRIGONOMETRIC_HPP_
#define NUMPP_SYMBOLIC_TRIGONOMETRIC_HPP_

#include<type_traits>
#include<cmath>

#include"arithmetic.hpp"

namespace numpp::differentiation::symbolic{
  template<typename T> class cos;
  template<typename T>
    class sin{
      public:
        using active = typename T::active;
        using type = sin<T>;

        using derivative = std::conditional_t<
          //ARE WE DIFFERENTIATING BY THIS VALUE?
          typename T::active{},
            //YES
            std::conditional_t<
              //IS THE TYPE INSIDE AN ARITHMETIC ONE? IF YES, THAN IT'S A SIMPLE DERIVATIVE
              std::is_arithmetic<typename T::type>::value,
                //IS NOT FUNCTION, SIMPLE DERIVATIVE
                cos<T>,
                //IS FUNCTION, NESTED DERIVATIVE
                multiply<cos<T>, typename T::derivative>
            >,
            //NOT DIFFERENTIATING BY THIS VALUE, RETURN AS IS
            sin<T>
        >;

        template<typename U>
          constexpr U operator()(U value)const{
            return std::sin(inner(value));
          }

      private:
        const T inner{};
    };

  template<typename T>
    class cos{
      public:
        using active = typename T::active;
        using type = cos<T>;

        using derivative = std::conditional_t<
          typename T::active{},
            std::conditional_t<
              std::is_arithmetic<typename T::type>::value,
                minus<sin<T>>,
                multiply<minus<sin<T>>, typename T::derivative>
            >,
            cos<T>
        >;
        template<typename U>
          constexpr U operator()(U value)const{
            return std::cos(inner(value));
          }

      private:
        const T inner{};
    };

  //TO DO
  template<typename T>
    class tan{
      public:
        using active = typename T::active;
        using type = cos<T>;

        using derivative = std::conditional_t<
          typename T::active{},
            std::conditional_t<
              std::is_arithmetic<typename T::type>::value,
                minus<sin<T>>,
                multiply<minus<sin<T>>, typename T::derivative>
            >,
            cos<T>
        >;
        template<typename U>
          constexpr U operator()(U value)const{
            return std::cos(inner(value));
          }

      private:
        const T inner{};
    };
}
#endif
