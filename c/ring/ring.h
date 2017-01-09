/* -*- c-basic-offset: 4 -*- */

#include <stdint.h>
#include <stdbool.h>

typedef struct Ring Ring;

#define RING_CAPACITY 32

struct Ring {
    uint16_t begin[RING_CAPACITY];
    uint16_t *end, *write, *read;
};

static inline void ring_init(Ring* ring) {
    ring->write = ring->read = ring->begin;
    ring->end = ring->begin + RING_CAPACITY;
}

static inline bool ring_empty(Ring* ring) {
    return ring->write == ring->read;
}

static inline bool ring_full(Ring* ring) {
    uint16_t* next = ring->write + 1;
    if (next == ring->end)
	next = ring->begin;
    return next == ring->read;
}

static inline void ring_write(Ring* ring, uint16_t value) {
    *ring->write++ = value;
    if (ring->write == ring->end)
	ring->write = ring->begin;
}

static inline uint16_t ring_read(Ring* ring) {
    uint16_t value = *ring->read++;
    if (ring->read == ring->end)
	ring->read = ring->begin;
    return value;
}

static inline uint16_t ring_peek(Ring* ring) {
    return *ring->read;
}

static inline unsigned int ring_size(Ring* ring) {
    if (ring->write >= ring->read)
	return ring->write - ring->read;
    else
	return RING_CAPACITY - (ring->read - ring->write);
}
