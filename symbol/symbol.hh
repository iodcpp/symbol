#include <utility>
#include "ast.hh"

namespace iod
{
  template <typename S>
  class symbol : public assignable<S>,
                 public array_subscriptable<S>,
                 public callable<S>,
                 public Exp<S>
  {};
}

#define IOD_SYMBOL(NAME)                                                \
struct _##NAME##_t : iod::symbol<_##NAME##_t> {                         \
                                                                        \
using assignable<_##NAME##_t>::operator=;                               \
                                                                        \
inline constexpr bool operator==(_##NAME##_t) { return true; }          \
  template <typename T>                                                 \
  inline constexpr bool operator==(T) { return false; }                 \
                                                                        \
template <typename V>                                                   \
  struct variable_t {                                                   \
    typedef _##NAME##_t _iod_symbol_type;                            \
    typedef V _iod_value_type;                                          \
    V NAME;                                                             \
  };                                                                   \
                                                                        \
  template <typename T, typename... A>                                  \
  static inline decltype(auto) symbol_method_call(T&& o, A... args) { return o.NAME(args...); } \
  template <typename T, typename... A>                                  \
  static inline decltype(auto) symbol_member_access(T&& o) { return o.NAME; } \
  template <typename T>                                                 \
  static constexpr auto has_member(T&& o) -> decltype(o.NAME, std::true_type{}) { return {}; } \
  static constexpr std::false_type has_member(...) { return {}; }              \
                                                                        \
  static inline auto symbol_string()                                    \
  {                                                                     \
    return #NAME;                                                       \
  }                                                                     \
                                                                        \
};                                                                      \
static constexpr _##NAME##_t _##NAME;


namespace iod
{

  template <typename V, typename S>
  inline decltype(auto) make_variable(S s, V v)
  {
    typedef typename S::template variable_t<std::remove_const_t<std::remove_reference_t<V>>> ret;
    return ret{v};
  }

  template <typename K, typename V>
  inline decltype(auto) make_variable_reference(K s, V&& v)
  {
    typedef typename K::template variable_t<V> ret;
    return ret{v};
  }

  template <typename T, typename S, typename... A>
  static inline decltype(auto) symbol_method_call(T&& o, S, A... args)
  {
    return S::symbol_method_call(o, std::forward<A>(args)...);
  }

  template <typename T, typename S>
  static inline decltype(auto) symbol_member_access(T&& o, S)
  {
    return S::symbol_member_access(o);
  }
  
  template <typename T, typename S>
  constexpr auto has_member(T&& o, S)
  {
    return decltype(S::has_member(o)){};
  }

  template <typename S>
  auto symbol_string(symbol<S> v)
  {
    return typename S::symbol_string();
  }

  template <typename V>
  auto symbol_string(V v)
  {
    return V::_iod_symbol_type::symbol_string();
  }
}
