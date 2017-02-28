#include <iod/symbol/symbol.hh>
#include <cassert>
#include <cstring>

IOD_SYMBOL(my_symbol)

int main()
{
  // Simple variable.
  auto v = iod::make_variable(_my_symbol, 42);
  assert(v.my_symbol == 42);
  assert(!strcmp(iod::symbol_string(v), "my_symbol"));

  // Member access.
  assert(iod::symbol_member_access(v, _my_symbol) == 42);  


  // Ref
  int x = 23;
  auto v2 = iod::make_variable_reference(_my_symbol, x);
  x++;
  assert(v2.my_symbol == 24);

  // Not ref
  int y = 23;
  auto v3 = iod::make_variable<int>(_my_symbol, y);
  y++;
  assert(v3.my_symbol == 23);


  // Method call
  struct {
    int my_symbol(int a) { return x + a; }
    int x;
  } obj{40};

  assert(iod::symbol_method_call(obj, _my_symbol, 2) == 42);
}
