#ifndef UTILITY_DETAIL_MEMORY_VIEW_REPRESENTATION_HPP
#define UTILITY_DETAIL_MEMORY_VIEW_REPRESENTATION_HPP
namespace utility {
namespace detail {
namespace memory_view {

/// Used to determine output representation in a Memory_view object.
enum Representation { Binary, Decimal, Hex, Octal };

}  // namespace memory_view
}  // namespace detail
}  // namespace utility
#endif  // UTILITY_DETAIL_MEMORY_VIEW_REPRESENTATION_HPP
