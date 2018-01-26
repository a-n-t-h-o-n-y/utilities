#ifndef UTILITY_SIGNED_INTEGER_HPP
#define UTILITY_SIGNED_INTEGER_HPP
#include <bitset>
#include <cstdint>

// #include "detail/signed_helper.hpp"

namespace utility {

template <std::size_t N>
class Signed_integer {
   public:
   private:
    std::bitset<N> data_;
};

}  // namespace utility
#endif  // UTILITY_SIGNED_INTEGER_HPP
