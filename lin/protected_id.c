
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

static uint8_t lin_protect_id(uint8_t id)
{
    uint8_t x = id, p0 = 0, p1 = 0, b;
    /* bit 0 */ b = x & 1; x >>= 1; p0 ^= b;
    /* bit 1 */ b = x & 1; x >>= 1; p0 ^= b; p1 ^= b;
    /* bit 2 */ b = x & 1; x >>= 1; p0 ^= b;
    /* bit 3 */ b = x & 1; x >>= 1; p1 ^= b;
    /* bit 4 */ b = x & 1; x >>= 1; p0 ^= b; p1 ^= b;
    /* bit 5 */ b = x & 1; x >>= 1; p1 ^= b;
    return id | (p0 << 6) | ((!p1) << 7);
}

static void test(uint8_t id)
{
  printf("id=0x%x, protected_id=0x%x\n", id, lin_protect_id(id));
}

int main()
{
  int id;
  for (id = 0; id <= 63; id++) {
    test(id);
  }
}
