#include <stdio.h>

int _foo(int n, int n3, int n2, int n1, int n0) {
  if (n == 0) {
    return n3;
  }
  if (n == 1) {
    return n2;
  }
  if (n == 2) {
    return n1;
  }

  if (n == 3) {
    return n0;
  } else {

    return _foo(n - 1, n2, n1, n0, n0 + n1 + n2 - n3 + 1);
  }
}

int foo(int n) {
  return _foo(n, 3, 6, 2, 7);
}

int main() {
  int n;
  printf("Enter a value for n: ");
  scanf("%d", &n);
  printf("Foo(%d) = %d\n", n, foo(n));
  return 0;
}