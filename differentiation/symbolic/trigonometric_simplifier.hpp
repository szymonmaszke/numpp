#ifndef NUMPP_DIFFERENTIATION_SYMBOLIC_TRIGONOMETRIC_SIMPLIFIER_HPP_
#define NUMPP_DIFFERENTIATION_SYMBOLIC_TRIGONOMETRIC_SIMPLIFIER_HPP_

#include"types.hpp"
#include<type_traits>

namespace numpp::differentiation::symbolic{
  template<typename T> class cosinus;
  template<typename T> class sinus;
  template<typename T> class minus;

  namespace impl{
    template<typename T>
      class simplify_cosinus{
        public:
        using type = cosinus<T>;
      };

    template<int Number>
      class simplify_cosinus<constant<Number>>{
        public:
        using type = std::conditional_t<
                      Number%2 == 0,
                      constant<1>,
                      constant<0>
                     >;
      };

    template<int Number>
      class simplify_cosinus<minus<constant<Number>>>{
        public:
        using type = std::conditional_t<
                      Number%2 == 0,
                      minus<constant<1>>,
                      constant<0>
                     >;
      };
  }

  template<typename T>
    using simplify_cosinus = typename impl::simplify_cosinus<T>::type;

  namespace impl{
    template<typename T>
      class simplify_sinus{
        public:
        using type = sinus<T>;
      };
    template<int Number>
      class simplify_sinus<constant<Number>>{
        public:
        using type = std::conditional_t<
                      Number%2 == 0,
                      constant<0>,
                      constant<1>
                     >;
      };

    template<int Number>
      class simplify_sinus<minus<constant<Number>>>{
        using type = std::conditional_t<
                      Number%2 == 0,
                      constant<0>,
                      minus<constant<1>>
                     >;
      };
  }

  template<typename T>
    using simplify_sinus = typename impl::simplify_sinus<T>::type;
}

#endif
