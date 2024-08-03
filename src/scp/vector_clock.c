#include "vector_clock.h"

static node_clock_map_t *node_clock_map = NULL;

const char *nf_typeArray[] =  { 
    "NULL", "NRF", "UDM", "AMF", "SMF", "AUSF", "NEF", "PCF", "NSSF", 
    "UDR", "LMF", "SEPP", "UPF", "N3IWF", "AF", "UDSF", "BSF", "CHF", 
    "NWDAF", "PCSCF", "HSS", "UCMF", "MME", "SCP"
};

static int get_node_id(const char *node_name) {
    
    int i;
    for (i = 0; i < NUM_NODES; i++) {
        if (strcmp(node_name, nf_typeArray[i]) == 0) {
            return i;
        }
    }
    return 0; // Return 0 if the node name is unknown
}

vector_clock_t *vector_clock_create(void) {
    vector_clock_t *vc = (vector_clock_t *)malloc(sizeof(vector_clock_t));
    memset(vc->clocks, 0, sizeof(vc->clocks));
    return vc;
}

void vector_clock_destroy(vector_clock_t *vc) {
    free(vc);
}

node_clock_map_t *get_node_clock(const char *node_name) {
    node_clock_map_t *current = node_clock_map;
    while (current != NULL) {
        if (strcmp(current->node_name, node_name) == 0) {
            return current;
        }
        current = current->next;
    }

    // If node clock not found, create a new one
    node_clock_map_t *new_node = (node_clock_map_t *)malloc(sizeof(node_clock_map_t));
    strncpy(new_node->node_name, node_name, sizeof(new_node->node_name) - 1);
    new_node->node_name[sizeof(new_node->node_name) - 1] = '\0';
    new_node->node_id = get_node_id(node_name);
    new_node->vector_clock = *vector_clock_create();
    new_node->next = node_clock_map;
    node_clock_map = new_node;

    return new_node;
}

void vector_clock_update(const char *sender, const char *receiver) {
    printf("Sender is: %s\n", sender);
    printf("Receiver is: %s\n", receiver);
    
    node_clock_map_t *sender_clock = get_node_clock(sender);
    node_clock_map_t *receiver_clock = get_node_clock(receiver);

    sender_clock->vector_clock.clocks[sender_clock->node_id]++;
    receiver_clock->vector_clock.clocks[receiver_clock->node_id]++;    

    int i;
    for (i = 0; i < NUM_NODES; i++) {
        if (sender_clock->vector_clock.clocks[i] < receiver_clock->vector_clock.clocks[i]) {
            sender_clock->vector_clock.clocks[i] = receiver_clock->vector_clock.clocks[i];
        }
    }
}

void vector_clock_merge(int *clock1, int *clock2) {
    
    int i;
    for (i = 0; i < NUM_NODES; i++) {
        if (clock1[i] < clock2[i]) {
            clock1[i] = clock2[i];
        }
    }
}

void print_vector_clock(const char *node_name) {
    node_clock_map_t *node_clock = get_node_clock(node_name);
    if (node_clock) {
        printf("Vector Clock for node %s:\n", node_clock->node_name);
        
        int j;
        for (j = 0; j < NUM_NODES; j++) {
            printf("%d ", node_clock->vector_clock.clocks[j]);
        }
        printf("\n");
    } else {
        printf("Node %s not found.\n", node_name);
    }
}

