#ifndef NUMPP_DIFFERENTIATION_SYMBOLIC_ARITHMETIC_SIMPLIFIER_HPP_
#define NUMPP_DIFFERENTIATION_SYMBOLIC_ARITHMETIC_SIMPLIFIER_HPP_

#include"types.hpp"

namespace numpp::differentiation::symbolic{
  template<typename Left, typename Right> class multiply;
  template<typename T> class minus;
  template<typename Left, typename Right> class subtract;

  template<typename Left, typename Right> class add;
  template<typename Left, typename Right> class divide;

  namespace impl{
    //MAIN CLASS
    template<typename Left, typename Right> class simplify_multiplication{
      public:
      using type = multiply<Left, Right>;
    };

    //MULTIPLY SIMPLIFICATION
    //MULTIPLICATION TIMES ONE
    template<typename Left>
      class simplify_multiplication<Left, constant<1>>{
        public:
        using type = Left;
      };

    template<typename Right>
      class simplify_multiplication<constant<1>, Right>{
        public:
        using type = Right;
      };

    //MULTIPLICATION TIMES ZERO
    template<typename Left>
      class simplify_multiplication<Left, constant<0>>{
        public:
        using type = constant<0>;
      };

    template<typename Left>
      class simplify_multiplication<Left, minus<constant<0>>>{
        public:
        using type = constant<0>;
      };

    template<typename Right>
      class simplify_multiplication<constant<0>, Right>{
        public:
        using type = constant<0>;
      };

    template<typename Right>
      class simplify_multiplication<minus<constant<0>>, Right>{
        public:
        using type = constant<0>;
      };

    //VALUE TIMES VALUE MULTIPLICATION
    template<int left_value, int right_value>
      class simplify_multiplication<constant<left_value>, constant<right_value>>{
        public:
        using type = constant<left_value*right_value>;
      };

    //VALUE OUTSIDE OF FUNCTIONS
    template<typename T, int left_value, int right_value>
      class simplify_multiplication<
        multiply<T, constant<left_value>>,
        constant<right_value>
      >{
        public:
        using type = multiply<T, constant<left_value*right_value>>;
      };

    template<typename T, int left_value, int right_value>
      class simplify_multiplication<
        constant<left_value>,
        multiply<T, constant<right_value>>
      >{
        public:
        using type = multiply<T, constant<left_value*right_value>>;
      };

    //DIVISION WITH MULTIPLICATION
    template<typename First, typename Second>
      class simplify_multiplication<
        First,
        divide<constant<1>, Second>
      >{
        public:
        using type = divide<First, Second>;
      };

    //MINUS MULTIPLICATION
    template<typename First, typename Second>
      class simplify_multiplication<minus<First>, minus<Second>>{
        public:
          using type = multiply<First, Second>;

      };

  }

  template<typename Left, typename Right>
    using simplify_multiplication = typename impl::simplify_multiplication<Left, Right>::type;

  //ADDITION SIMPLIFICATION

  namespace impl{
    template<typename Left, typename Right>
      class simplify_addition{
        public:
        using type = add<Left, Right>;
      };

    template<typename Left>
      class simplify_addition<Left, constant<0>>{
        public:
        using type = Left;
      };

    template<typename Right>
      class simplify_addition<constant<0>, Right>{
        public:
        using type = Right;
      };

    //ADDITION OF MINUS
    template<typename Left, typename Right>
      class simplify_addition<Left, minus<Right>>{
        public:
        using type = subtract<Left, Right>;
      };

    //OUTSIDE OF REALM SIMPLIFICATION
    template<typename Left, int left_value, int right_value>
      class simplify_addition<
        constant<left_value>,
        add<Left, constant<right_value>>
      >{
        public:
        using type = add<Left, constant<left_value+right_value>>;
      };

    template<typename Left, int left_value, int right_value>
      class simplify_addition<
        add<Left, constant<left_value>>,
        constant<right_value>
      >{
        public:
        using type = add<Left, constant<left_value+right_value>>;
      };

    template<typename Right, int left_value, int right_value>
      class simplify_addition<
        constant<left_value>,
        add<constant<right_value>, Right>
      >{
        public:
        using type = add<Right, constant<left_value+right_value>>;
      };

    template<typename Right, int left_value, int right_value>
      class simplify_addition<
        add<constant<left_value>, Right>,
        constant<right_value>
      >{
        public:
        using type = add<Right, constant<left_value+right_value>>;
      };

  }

  template<typename Left, typename Right>
    using simplify_addition = typename impl::simplify_addition<Left, Right>::type;

  //SIMPLIFY MINUS

  namespace impl{
    template<typename T>
      class simplify_minus{
        public:
        using type = minus<T>;
      };

    template<>
    class simplify_minus<minus<constant<0>>>{
      public:
      using type = constant<0>;
    };

    template<typename T>
      class simplify_minus<minus<T>>{
        public:
        using type = T;
      };

    template<typename Left, typename Right>
      class simplify_minus<minus<subtract<Left, Right>>>{
        public:
        using type = subtract<Right, Left>;
      };

  }

  template<typename T>
    using simplify_minus = typename impl::simplify_minus<T>::type;

  //SIMPLIFY SUBTRACTION

  namespace impl{
    template<typename Left, typename Right>
      class simplify_subtraction{
        public:
        using type = subtract<Left, Right>;
      };

    template<typename Left, typename Right>
      class simplify_subtraction<Left, minus<Right>>{
        public:
        using type = add<Left, Right>;
      };
  }

  template<typename Left, typename Right>
    using simplify_subtraction = typename impl::simplify_subtraction<Left, Right>::type;

  //SIMPLIFY DIVISION
  namespace impl{
    template<typename Upper, typename Lower>
      class simplify_division{
        public:
        using type = divide<Upper, Lower>;
      };

    template<typename First, typename Second>
      class simplify_division<multiply<First, Second>, Second>{
        public:
        using type = First;
      };

    template<typename First, typename Second>
      class simplify_division<First, multiply<First, Second>>{
        public:
        using type = divide<constant<1>, Second>;
      };

    template<typename First, typename Second, typename Third>
      class simplify_division<multiply<First, Second>, multiply<Second, Third>>{
        public:
        using type = divide<First, Third>;
      };

    template<typename T>
      class simplify_division<T, T>{
        public:
        using type = constant<1>;
      };

    template<typename T>
      class simplify_division<T, constant<1>>{
        public:
        using type = T;
      };

    template<typename T>
      class simplify_division<constant<0>, T>{
        public:
        using type = constant<0>;
      };

    template<typename First, typename Second>
      class simplify_division<constant<1>, divide<First, Second>>{
        public:
        using type = divide<Second, First>;
      };

  }

  template<typename Left, typename Right>
    using simplify_division = typename impl::simplify_division<Left, Right>::type;
}

#endif
