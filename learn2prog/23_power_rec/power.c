unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;  // Base case
  }
  if (y % 2 == 0) {
    unsigned halfPower = power(x, y / 2);
    return halfPower * halfPower;  // Square for even powers
  } else {
    return x * power(x, y - 1);  // Multiply by x for odd powers
  }
}
