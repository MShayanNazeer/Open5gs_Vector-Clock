#include "vector_clock.h"

vector_clock_t* vector_clock_create(void) {
    vector_clock_t *vc = (vector_clock_t *)malloc(sizeof(vector_clock_t));
    memset(vc->clocks, 0, sizeof(vc->clocks));
    return vc;
}

void vector_clock_destroy(vector_clock_t *vc) {
    free(vc);
}

void vector_clock_update(vector_clock_t *vc, int node_id, int *other_clock) {
    vc->clocks[node_id]++;
    if (other_clock) {
        vector_clock_merge(vc->clocks, other_clock);
    }
}

void vector_clock_print(const vector_clock_t *vc, int node_id) {
    printf("Vector Clock for node %d:\n", node_id);
    int i;
    for (i = 0; i < NUM_NODES; i++) {
        printf("%d ", vc->clocks[i]);
    }
    printf("\n");
}

void vector_clock_merge(int *vc1, int *vc2) {
    int i;
    for (i = 0; i < NUM_NODES; i++) {
        if (vc2[i] > vc1[i]) {
            vc1[i] = vc2[i];
        }
    }
}
