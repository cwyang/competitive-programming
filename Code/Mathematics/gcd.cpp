#include <cstdio>
#include <cassert>

unsigned gcd (unsigned n1, unsigned n2) {
  return (n2 == 0) ? n1 : gcd (n2, n1 % n2);
}

int main() {
  assert( gcd(2, 1) == 1 );
  assert( gcd(2001, 25001) == 23 );
  assert( gcd(96, 42) == gcd(42,96) );
  assert( gcd(2*2*3*3*7, 2*2*2*3*5) ==  2*2*3 );
}