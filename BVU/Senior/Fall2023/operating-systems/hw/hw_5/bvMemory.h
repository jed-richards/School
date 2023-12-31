#include <stdint.h> // uint8_t
#include <stdlib.h> // malloc


#define SLAB_SIZE 1000


struct DataNode {
    struct DataNode *next;
    uint8_t *start;
    uint8_t *end;
} typedef DataNode;


// "virtual memory" region
uint8_t *slab = NULL;

// linked list head
DataNode *data_head = NULL;


// creates a DataNode representing [size] many bytes and inserts into 
// linked list based on [prev] DataNode
DataNode *constructDataNode(int size, DataNode *prev) {
    DataNode *new_node = (DataNode *) malloc(sizeof(DataNode));

    // prepend new node
    if (prev == NULL) {
        new_node->next = data_head;
        new_node->start = slab;
        new_node->end = new_node->start + size;
        data_head = new_node;
    } 
    else {
        new_node->next = prev->next;
        new_node->start = prev->end;
        new_node->end = new_node->start + size;
        prev->next = new_node;
    }

    return new_node;
}


// if size bytes fits in slab return best fit address else return NULL
uint8_t *get_bestfit(int size) {

    // if no allocations
    if (data_head == NULL) {
        if (size <= 1000) {
            return constructDataNode(size, data_head)->start;
        } 
        else {
            return NULL;
        }
    } 
    else {
        int smallest = 9999; // set to number bigger than slab
        DataNode *best_prev;

        // check between data_head and start of slab
        if (data_head->start - slab >= size) { 
            smallest = data_head->start - slab;
            best_prev = NULL; // prepend to linked list
        }

        DataNode *curr = data_head;
        int curr_size;

        while (curr != NULL) {
            // at end of list so empty chunk size = (slab+1000) - curr->end
            if (curr->next == NULL) {
                curr_size = (slab + 1000) - curr->end;
            }
            else {
                curr_size = curr->next->start - curr->end;
            }

            // update smallest and best_prev if a better spot is found
            if (curr_size < smallest && curr_size >= size) {
                smallest = curr_size;
                best_prev = curr;
            }

            curr = curr->next;
        }

        // make sure we actually found a place that fits
        if (smallest >= size) {
            return constructDataNode(size, best_prev)->start;
        }
    }
    
    // if here then data does not fit, so return NULL
    return NULL;
}


// if size bytes fits in slab return first fit address else return NULL
uint8_t *get_firstfit(int size) {

    // no allocations
    if (data_head == NULL) {
        if (size <= 1000) {
            return constructDataNode(size, data_head)->start;
        } 
        else {
            return NULL;
        }
    } 
    else if (data_head->start - slab >= size) {
        // insert between data head and start of slab
        return constructDataNode(size, NULL)->start;
    }
    else {
        // walk through list looking at in between for insertion spot
        DataNode *curr;
        int curr_size;
        for (curr = data_head; curr != NULL; curr = curr->next) {
            // at end of list so empty chunk size = (slab+1000) - curr->end
            if (curr->next == NULL) {
                curr_size = (slab + 1000) - curr->end;
            } 
            else {
                curr_size = curr->next->start - curr->end;
            }

            if (curr_size >= size) {
                return constructDataNode(size, curr)->start;
            }
        }
    }

    // if here then data does not fit, so return NULL
    return NULL;
}


// return address to start of malloc'd data or NULL if data doesn't fit
void *bvMalloc(int size, int bestFit) {
    if (slab == NULL) {
        slab = (uint8_t *) malloc(SLAB_SIZE);
    }

    if (bestFit) {
        return get_bestfit(size);
    } 
    else {
        return get_firstfit(size);
    }
}


void bvFree(void *address) {
    DataNode *temp;

    // free first DataNode
    if (data_head->start == address) {
        temp = data_head;
        data_head = data_head->next;
        free(temp);
        return;
    }

    // walk through linked list until address is found
    DataNode *curr = data_head;
    while (curr->next->start != address) {
        curr = curr->next;
    }

    // remove DataNode from linked list and free
    temp = curr->next;
    curr->next = temp->next;
    free(temp);
}
