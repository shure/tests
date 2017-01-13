
#include <stdio.h>

void print_bits(unsigned int val)
{
  printf("0x%02x: ", val);
  while (val) {
    int bit = __builtin_ffs(val) - 1;
    printf("%d ", bit);
    val &= ~(1 << bit);
  }
  printf("\n");
}


int main()
{
  int i;
  for (i = 0; i < 64; i++) {
    print_bits(i);
  }
}
