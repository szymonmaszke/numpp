#ifndef NUMPP_SYMBOLIC_HPP_
#define NUMPP_SYMBOLIC_HPP_

#include<cmath>
#include<type_traits>

#include"types.hpp"

/* 'Abandon All Hope, Ye Who Enter Here' ~XTerm README */

namespace numpp::differentiation::symbolic{
  template<typename... Dummy> class minus;
  template<typename T> class minus<T>;
  template<typename T, typename U> class minus<T, U>;

  template<typename Left, typename Right> class plus;
  template<typename Left, typename Right> class multiply;
  template<typename Left, typename Right> class divide;

  template<typename Left, typename Right>
    class divide{
      public:
        using derivative = std::conditional_t<
          typename Left::active{},
          std::conditional_t<
            typename Right::active{},
              divide<
                minus<multiply<typename Left::derivative, Right>, multiply<Left, typename Right::derivative>>,
                multiply<Right, Right>
              >,
              divide<typename Left::derivative, Right>
          >,
          std::conditional_t<
            typename Right::active{},
              divide<Left, typename Right::derivative>,
              divide<Left, Right>
            >
          >;

        using active = std::conditional_t<
          typename Left::active{} || typename Right::active{},
          std::true_type,
          std::false_type
        >;

        using type = std::conditional_t<
          std::is_arithmetic<typename Left::type>::value,
          typename Right::type,
          typename Left::type
        >;

        template<typename U>
          constexpr U operator()(U value)const{
            return left(value)/right(value);
          }
      private:
        const Left left{};
        const Right right{};
    };

  template<typename Left, typename Right>
    class multiply{
      public:
        using derivative = std::conditional_t<
          typename Left::active{},
          std::conditional_t<
            typename Right::active{},
              plus<multiply<typename Left::derivative, Right>, multiply<Left, typename Right::derivative>>,
              multiply<Right, typename Left::derivative>
          >,
          std::conditional_t<
            typename Right::active{},
              multiply<Left, typename Right::derivative>,
              multiply<Left, Right>
          >
        >;


        using active = std::conditional_t<
          typename Left::active{} || typename Right::active{},
          std::true_type,
          std::false_type
        >;

        using type = std::conditional_t<
          std::is_arithmetic<typename Left::type>::value,
          typename Right::type,
          typename Left::type
        >;

        template<typename U>
          constexpr U operator()(U value)const{
            return left(value)*right(value);
          }

        template<typename U>
          constexpr U operator()(U left_value, U right_value)const{
            return left(left_value)*right(right_value);
          }

      private:
        const Left left{};
        const Right right{};
    };


  template<typename Left, typename Right>
    class plus{
      public:
        using active = std::conditional_t<
          typename Left::active{} || typename Right::active{},
          std::true_type,
          std::false_type
        >;
        using type = std::conditional_t<
          std::is_arithmetic<typename Left::type>::value,
          typename Right::type,
          typename Left::type
        >;
        using derivative = std::conditional_t<
                        typename Left::active{},
                          std::conditional_t<
                            typename Right::active{},
                              plus<typename Left::derivative, typename Right::derivative>,
                              typename Left::derivative
                          >,
                          std::conditional_t<
                            typename Right::active{},
                              typename Right::derivative,
                              none
                          >
                        >;

        template<typename U>
          constexpr U operator()(U value)const{
            return left(value) + right(value);
          }

        template<typename U>
          constexpr U operator()(U left_value, U right_value)const{
            return left(left_value) + right(right_value);
          }

      private:
        const Left left{};
        const Right right{};
    };

  template<typename Left, typename Right>
    class minus<Left,Right>{
      public:
        //ACTIVE ALWAYS TRUE?
        using active = std::conditional_t<
          typename Left::active{} || typename Right::active{},
          std::true_type,
          std::false_type
        >;
        using type = std::conditional_t<
          std::is_arithmetic<typename Left::type>::value,
          typename Right::type,
          typename Left::type
        >;
        using derivative = std::conditional_t<
                        typename Left::active{},
                          std::conditional_t<
                            typename Right::active{},
                              minus<typename Left::derivative, typename Right::derivative>,
                              typename Left::derivative
                          >,
                          std::conditional_t<
                            typename Right::active{},
                              minus<typename Right::derivative>,
                              none
                          >
                        >;

        template<typename U>
          constexpr U operator()(U value)const{
            return left(value) - right(value);
          }

        template<typename U>
          constexpr U operator()(U left_value, U right_value)const{
            return left(left_value) - right(right_value);
          }

      private:
        const Left left{};
        const Right right{};
    };

  template<typename T>
    class minus<T>{
      public:
        using derivative = minus<typename T::derivative>;
        using active = typename T::active;
        using type = T;

        template<typename U>
          constexpr U operator()(U value)const{
            return - inner(value);
          }

      private:
        const T inner{};
    };

}

#endif
