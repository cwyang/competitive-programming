unsigned gcd (unsigned n1, unsigned n2) {
  return (n2 == 0) ? n1 : gcd (n2, n1 % n2);
}
