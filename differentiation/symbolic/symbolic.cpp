#ifndef NUMPP_SYMBOLIC_HPP_
#define NUMPP_SYMBOLIC_HPP_

#include<cmath>
#include<iostream>
#include<typeinfo>
#include<type_traits>

/* 'Abandon All Hope, Ye Who Enter Here' ~XTerm README */

namespace numpp::differentiation::symbolic{
  template<typename T> class value;
  template<typename T> class cos;
  /* template<typename T, typename V=value<T>> class sin; */

  template<typename... Dummy> class minus;
  template<typename T> class minus<T>;
  template<typename T, typename U> class minus<T, U>;

  template<typename Left, typename Right> class plus;
  template<typename Left, typename Right> class multiply;
  template<typename Left, typename Right> class divide;

  //ADD TYPE SAFETY WITH ENABLE IF ?
  template<typename T>
    class value{
      public:
        using active = std::true_type;
        using derivative = value<T>;
        using type = T;

        constexpr T operator()(T value)const{
          return value;
        }
    };

  template<typename T>
    class constant{
      public:
        using active = std::false_type;
        using derivative = constant<T>;
        using type = T;

        constexpr T operator()(T value)const{
          return value;
        }
    };

  class none{
    template<typename U>
      constexpr U operator()(U dummy...){
        return 0;
      }
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
}

namespace nds = numpp::differentiation::symbolic;

int main(){
  /* constexpr auto value = nds::sin<nds::value<double>>::derivative{}; */
  /* constexpr auto value = nds::plus<nds::cos<nds::value<double>>, nds::sin<nds::constant<double>>>::derivative{}; */
  /* constexpr auto value = nds::cos<nds::sin<nds::constant<double>>>::derivative{}; */
  /* constexpr auto value = nds::cos<nds::sin<nds::value<double>>>::derivative{}; */
  /* constexpr auto value = nds::sin<nds::sin<nds::value<double>>>::derivative{}; */
  /* constexpr auto value = nds::sin< */
  /*   nds::plus< */
  /*     nds::cos<nds::constant<double>>, */
  /*     nds::sin<nds::value<double>> */
  /*   >>::derivative{}; */
  //OK

  /* std::cout << typeid(value).name() << std::endl; */
  /* std::cout << value(0.4) << std::endl; */

}

#endif
