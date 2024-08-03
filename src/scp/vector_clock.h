#ifndef VECTOR_CLOCK_H
#define VECTOR_CLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_NODES 24 // Adjust this based on the number of nodes in nf_typeArray

typedef struct {
    int clocks[NUM_NODES];
} vector_clock_t;

typedef struct node_clock_map {
    char node_name[50];
    int node_id;
    vector_clock_t vector_clock;
    struct node_clock_map *next;
} node_clock_map_t;

vector_clock_t *vector_clock_create(void);
void vector_clock_destroy(vector_clock_t *vc);
node_clock_map_t *get_node_clock(const char *node_name);
void vector_clock_update(const char *sender, const char *receiver);
void vector_clock_merge(int *clock1, int *clock2);
void print_vector_clock(const char *node_name);

#endif // VECTOR_CLOCK_H
