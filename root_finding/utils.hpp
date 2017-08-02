#ifndef NUMPP_ROOTS_UTILS_HPP_
#define NUMPP_ROOTS_UTILS_HPP_

namespace numpp::roots{
  namespace impl{
    constexpr auto abs(auto value){
      return value < 0 ? -value : value;
    }

  }
}

#endif
