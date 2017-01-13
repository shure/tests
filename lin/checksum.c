
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

static uint8_t lin_checksum(uint8_t* begin, uint8_t* end)
{
    uint16_t sum = 0;
    uint8_t* ptr;
    for (ptr = begin; ptr != end; ptr++) {
	sum += *ptr;
	if (sum >= 256) sum -= 255;
    }
    return 0xff - sum;
}

static void test(uint8_t* begin, uint8_t* end)
{
  uint8_t* ptr;
  for (ptr = begin; ptr != end; ++ptr) {
    printf("0x%02x ", *ptr);
  }
  printf("\t 0x%02x\n", lin_checksum(begin, end));
}

int main()
{
  uint8_t data1[] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
  test(data1, data1 + 8);

  uint8_t data2[] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8};
  test(data2, data2 + 8);
}
