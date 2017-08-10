#ifndef NUMPP_STRUCTURES_VECTOR_STRUCTURE_HPP_
#define NUMPP_STRUCTURES_VECTOR_STRUCTURE_HPP_

#include<array>
#include<type_traits>

namespace numpp{
/**
\ingroup numpp_structures_vector

\class vector

\tparam T arithmetic type contained in vector class
\tparam Size size of the vector
\tparam Transposition bool indicating whether the vector is transposed

\code
#include"numpp/structures/vector.hpp"
\endcode

*/
		template<typename T, std::size_t Size, bool Transposition=false>
			class vector{
			public:
				using value_type = T;
				using size_type = std::size_t;
				using difference_type = std::ptrdiff_t;
				using reference = typename std::array<T,Size>::reference;
				using const_reference = typename std::array<T,Size>::const_reference;
				using pointer = value_type*;
				using const_pointer = const value_type*;

				using iterator = typename std::array<T,Size>::iterator;
				using const_iterator = typename std::array<T,Size>::const_iterator;
				using reverse_iterator = typename std::array<T,Size>::reverse_iterator;
				using const_reverse_iterator = typename std::array<T,Size>::const_reverse_iterator;

				//CTORS
				constexpr vector()=default;
				constexpr vector(const vector&)=default;
				constexpr vector(vector&&)=default;
				constexpr vector& operator=(const vector&)=default;
				constexpr vector& operator=(vector&&)=default;


				template<
					typename... U,
					typename = std::enable_if_t<
						std::is_same<T, std::common_type_t<T, U...>>::value
					>
				>
					constexpr vector(U&&... args):
        /**
          \brief constructor acting exactly like std::initializer_list one with type checking
        */
						vector_{std::forward<T>(args)...}
				{}
				//COPY/MOVE WHEN VECTOR HAS DIFFERENT TRANSPOSITION
				explicit constexpr vector(const vector<T,Size, !Transposition>& transposed):
        /**
          \brief copy constructor for vector with different transposition

          Cannot be used in implict casting, you have to cast it explicitly
        */
					vector_{transposed.vector_}
				{}

				explicit constexpr vector(vector<T,Size, !Transposition>&& transposed):
        /**
          \brief move constructor for vector with different transposition

          Cannot be used in implict casting, you have to cast it explicitly
        */
					vector_{std::move(transposed.vector_)}
				{}

				//UTILITY FUNCTIONS

				constexpr bool transposed()const {
          /**
            \brief returns whether the vector is transposed.
            \returns true for transposed, false otherwise
          */
					return Transposition;
				}

				constexpr std::size_t size()const {
					return Size;
				}

				constexpr std::size_t max_size()const {
					return Size;
				}
				constexpr bool operator==(const vector& x)const {
					return x.vector_ == vector_;
				}

				constexpr bool operator!=(const vector& x)const {
					return !(x==*this);
				}

				constexpr bool operator==(const vector<T, Size, !Transposition>& x)const {
					return x.vector_ == vector_;
				}

				constexpr bool operator!=(const vector<T, Size, !Transposition>& x)const {
					return !(x==*this);
				}

				constexpr reference operator()(size_type pos){
					return vector_[pos];
				}

				constexpr const_reference operator()(size_type pos)const{
					return vector_[pos];
				}

				constexpr iterator begin() {
					return vector_.begin();
				}
				constexpr const_iterator begin()const {
					return vector_.begin();
				}
				constexpr const_iterator cbegin()const {
					return vector_.cbegin();
				}
				constexpr iterator end(){
					return vector_.end();
				}
				constexpr const_iterator end()const {
					return vector_.end();
				}
				constexpr const_iterator cend()const {
					return vector_.cend();
				}
				constexpr reverse_iterator rbegin(){
					return vector_.rbegin();
				}
				constexpr const_reverse_iterator rbegin()const {
					return vector_.rbegin();
				}
				constexpr const_reverse_iterator crbegin()const {
					return vector_.crbegin();
				}
				constexpr reverse_iterator rend(){
					return vector_.rend();
				}
				constexpr const_reverse_iterator rend()const {
					return vector_.rend();
				}
				constexpr const_reverse_iterator crend()const {
					return vector_.crend();
				}

				std::array<T, Size> vector_;
	};
}

#endif
