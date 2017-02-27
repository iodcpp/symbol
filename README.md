
iod::symbol
=================================

This tiny library (45 lines) implements the basics of symbol based
programming. Symbols is a new C++ paradigm that allow you to simply
implement introspection, serialization, named parameters, and other
things that are very hard / impossible to build in classic C++.

A symbol is defined with:

```c++
IOD_SYMBOL(my_symbol)
``` 

And provides 4 operators :

```c++
// Named Variable declaration.
auto v = s::make_variable(s::_my_symbol, 42);
assert(v.my_symbol == 42);

// Introspection
assert(!strcmp(s::symbol_string(v), "my_symbol"));

// Member access.
assert(s::symbol_member_access(v, s::_my_symbol) == 42);  

// Method call
struct {
  int my_symbol(int a) { return x + a; }
  int x;
} obj{40};

assert(s::symbol_method_call(obj, s::_my_symbol, 2) == 42);
```
