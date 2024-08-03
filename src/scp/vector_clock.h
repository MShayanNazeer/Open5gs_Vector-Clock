#ifndef VECTOR_CLOCK_H
#define VECTOR_CLOCK_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NUM_NODES   // Adjust this to the number of network functions

typedef struct {
    int clocks[NUM_NODES];
} vector_clock_t;

typedef struct {
    char node_name[50];
    int node_id;
    vector_clock_t vector_clock;
} node_clock_map_t;

vector_clock_t *vector_clock_create();
void vector_clock_destroy(vector_clock_t *vc);
static int get_node_id(const char *node_name);
node_clock_map_t *get_node_clock(const char *node_name);
void vector_clock_update(const char *sender, const char *receiver);

#endif // VECTOR_CLOCK_H
