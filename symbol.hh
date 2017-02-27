#include <utility>

namespace iod
{
  template <typename S>
  class symbol {};
}

#define IOD_SYMBOL(NAME)                                                \
namespace s {                                                           \
  struct _##NAME##_t : iod::symbol<_##NAME##_t> {                       \
    inline constexpr bool operator==(_##NAME##_t) { return true; }      \
    template <typename T>                                               \
    inline constexpr bool operator==(T) { return false; }               \
  };                                                                    \
  static constexpr _##NAME##_t _##NAME;                                 \
}                                                                       \
namespace iod {                                                         \
  template <typename V>                                                 \
  static decltype(auto) make_variable_reference(s::_##NAME##_t k, V&& v) \
  {                                                                     \
    struct {                                                            \
      typedef s::_##NAME##_t _iod_symbol_type;                             \
      typedef V _iod_value_type;                                        \
      V NAME;                                                           \
    } res{std::forward<V>(v)};                                          \
                                                                        \
    return res;                                                         \
  }                                                                     \
  template <typename V>                                                 \
  static decltype(auto) make_variable(s::_##NAME##_t k, V v)               \
  {                                                                     \
    struct {                                                            \
      typedef s::_##NAME##_t _iod_symbol_type;                             \
      typedef V _iod_value_type;                                        \
      std::remove_const_t<std::remove_reference_t<V>> NAME;             \
    } res{std::forward<V>(v)};                                          \
                                                                        \
    return res;                                                         \
  }                                                                     \
                                                                        \
  template <typename T, typename... A>                                  \
  static inline auto symbol_method_call(T&& o, s::_##NAME##_t, A... args) { return o.NAME(args...); } \
  template <typename T, typename... A>                                  \
  static inline auto symbol_member_access(T&& o, s::_##NAME##_t) { return o.NAME; } \
                                                                        \
  static inline auto symbol_string(s::_##NAME##_t)                         \
  {                                                                     \
    return #NAME;                                                       \
  }                                                                     \
                                                                        \
}                                                                       

namespace iod
{
  template <typename V>
  auto symbol_string(V v)
  {
    return symbol_string(typename V::_iod_symbol_type());
  }
}
