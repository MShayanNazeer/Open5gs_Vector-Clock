#include "vector_clock.h"

static node_clock_map_t *node_clock_map = NULL;

const char *nf_typeArray[] =  { "NULL", "NRF", "UDM", "AMF", "SMF", "AUSF", "NEF", "PCF", "NSSF", "UDR", "LMF", "SEPP", "UPF", "N3IWF", "AF", "UDSF", "BSF", "CHF", "NWDAF", "PCSCF", "HSS", "UCMF", "MME", "SCP"};

static int get_node_id(const char *node_name) {
    for (int i = 0; i < NUM_NODES; i++) {
        if (strcmp(node_name, nf_typeArray[i]) == 0) {
            return i;
        }
    }
    return 0; // Return 0 if the node name is unknown
}

vector_clock_t *vector_clock_create() {
    vector_clock_t *vc = (vector_clock_t *)malloc(sizeof(vector_clock_t));
    memset(vc->clocks, 0, sizeof(vc->clocks));
    return vc;
}

void vector_clock_destroy(vector_clock_t *vc) {
    free(vc);
}

node_clock_map_t *get_node_clock(const char *node_name) {
    node_clock_map_t *s;
    HASH_FIND_STR(node_clock_map, node_name, s);
    if (s == NULL) {
        s = (node_clock_map_t *)malloc(sizeof(node_clock_map_t));
        strncpy(s->node_name, node_name, sizeof(s->node_name) - 1);
        s->node_name[sizeof(s->node_name) - 1] = '\0';
        s->node_id = get_node_id(node_name);
        s->vector_clock = *vector_clock_create();
        HASH_ADD_STR(node_clock_map, node_name, s);
    }
    return s;
}

void vector_clock_update(const char *sender, const char *receiver) {

    printf("Sender is: %s", sender);
    printf("Reciever is: %s", receiver);
    node_clock_map_t *sender_clock = get_node_clock(sender);
    node_clock_map_t *receiver_clock = get_node_clock(receiver);

    sender_clock->vector_clock.clocks[sender_clock->node_id]++;
    receiver_clock->vector_clock.clocks[receiver_clock->node_id]++;    

    int i;
    for (i = 0; i < MAX_NODES; i++) {
        if (sender_clock->vector_clock.clocks[i] < receiver_clock->vector_clock.clocks[i]) {
            sender_clock->vector_clock.clocks[i] = receiver_clock->vector_clock.clocks[i];
        }
    }


    printf("Vector Clock for node %d:\n", sender_clock->node_name);
    int j;
    for (j = 0; j < NUM_NODES; j++) {
        printf("%d ", sender_clock->vector_clock.clocks[j]);
    }
    printf("\n");

}
