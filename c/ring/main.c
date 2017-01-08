/* -*- c-basic-offset: 4 -*- */

#include "ring.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

Ring ring;

void show_info()
{
    printf("empty=%d, full=%d, size=%d\n",
	   ring_empty(&ring),
	   ring_full(&ring),
	   ring_size(&ring));
}

void random_test(Ring* ring, int count)
{
    uint16_t next_write = 1, next_read = 1;
    int i, n;

    while (count--) {
	
	n = rand() % RING_CAPACITY;
	for (i = 0; i < n; i++) {
	    if (ring_full(ring)) break;
	    ring_write(ring, next_write++);
	}

	n = rand() % RING_CAPACITY;
	for (i = 0; i < n; i++) {
	    if (ring_empty(ring)) break;
	    uint16_t value = ring_read(ring);
	    assert(value == next_read);
	    next_read++;
	}
    }
}

int main()
{
    ring_init(&ring);
    show_info();

    ring_write(&ring, 10);
    ring_write(&ring, 20);
    ring_write(&ring, 30);
    ring_write(&ring, 40);
    ring_write(&ring, 50);

    show_info();

    while (!ring_empty(&ring)) {
	printf("%d\n", (int)ring_read(&ring));
    }

    show_info();

    srand(time(0));
    random_test(&ring, 1000000);
    
    show_info();
    return 0;
}
