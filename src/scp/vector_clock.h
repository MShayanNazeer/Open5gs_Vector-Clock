#ifndef VECTOR_CLOCK_H
#define VECTOR_CLOCK_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NUM_NODES 10  // Adjust this to the number of network functions

typedef struct vector_clock {
    int clocks[NUM_NODES];
} vector_clock_t;

vector_clock_t* vector_clock_create(void);
void vector_clock_destroy(vector_clock_t *vc);
void vector_clock_update(vector_clock_t *vc, int node_id, int *other_clock);
void vector_clock_print(const vector_clock_t *vc, int node_id);
void vector_clock_merge(int *vc1, int *vc2);

#endif // VECTOR_CLOCK_H
