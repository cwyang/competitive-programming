int snoob (int x) {
  int y = x + (x & -x);
  x = x & ~y;
  while ((x & 1) == 0) x  = x >> 1;
  x = x >> 1;
  return y | x;
}
