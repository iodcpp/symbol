#include "symbol.hh"
#include <cassert>
#include <cstring>

IOD_SYMBOL(my_symbol)

int main()
{
  // Simple variable.
  auto v = s::make_variable(s::_my_symbol, 42);
  assert(v.my_symbol == 42);
  assert(!strcmp(s::symbol_string(v), "my_symbol"));

  // Member access.
  assert(s::symbol_member_access(v, s::_my_symbol) == 42);  


  // Ref
  int x = 23;
  auto v2 = s::make_variable_reference(s::_my_symbol, x);
  x++;
  assert(v2.my_symbol == 24);

  // Not ref
  int y = 23;
  auto v3 = s::make_variable<int>(s::_my_symbol, y);
  y++;
  assert(v3.my_symbol == 23);


  // Method call
  struct {
    int my_symbol(int a) { return x + a; }
    int x;
  } obj{40};

  assert(s::symbol_method_call(obj, s::_my_symbol, 2) == 42);
}
