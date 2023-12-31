#include <stdio.h>
#include <stdlib.h> // for the function: int atoi(char*);

struct Process {
    int id;
    int priority;
    int numQuanta;
    int numScheduled;
    float meter;
} typedef Process;

struct Node {
    Process* data;
    struct Node* next;
} typedef Node ;

/*
 * Compare two processes, p1 and p2, to see if p1 should be scheduled 
 * first. I wanted to overload the '>' operator, but C doesn't have
 * operator overloading. Comparison is based on:
 * 1) lowest meter
 * 2) if p1->meter == p2->meter, then highest priority
 * 3) if p1->priority == p2->priority, then smallest process id
 *
 * Returns: 0 or 1
 *   1 if p1 should be scheduled before p2
 *   0 if p1 should not be scheduled before p2
 */
int proc_compare_gt(Process* p1, Process* p2) {
    if (p1->meter > p2->meter)
        return 0;
    if (p1->meter < p2->meter)
        return 1;
    if (p1->meter == p2->meter) {
        if (p1->priority > p2->priority)
            return 1;
        if (p1->priority == p2->priority && p1->id < p2->id)
            return 1;
    }
    return 0;
}

/*
 * Insert process into priorty queue based on proc_compare_gt().
 */
void enqueue(Node** queue, Node* process) {
    if (*queue == NULL) {
        *queue = process;
    }
    else {
        int first_pass = 1;
        Node* curr = *queue;
        Node* prev = *queue;

        // Walk queue to find insertion position.
        while (curr != NULL && !proc_compare_gt(process->data, curr->data)) {
            if (first_pass) {
                first_pass = 0;
            }
            else {
                prev = prev->next;
            }
            curr = curr->next; 
        }

        // insert at beginning
        if (curr == *queue) {
            process->next = *queue; 
            *queue = process;
        }
        // insert after prev before curr
        else {
            process->next = curr; 
            prev->next = process;
        }
    }
}

/*
 * Remove and return highest priority process from priorty queue.
 */
Node* dequeue(Node** queue) {
    Node* temp = *queue;
    if (temp == NULL) {
        return NULL;
    }
    *queue = (*queue)->next;
    return temp;
}

/*
 * Free all nodes in queue. (not used in code)
 */
void free_queue(Node** queue) {
    Node* temp;
    while (*queue != NULL) {
        temp = *queue;
        *queue = (*queue)->next;
        free(temp);
    }
}

/*
 * Pretty print all elements of queue.
 */
void print_queue(Node** queue) {
    printf("{\n");
    for(Node *curr=*queue; curr != NULL; curr=curr->next) {
        printf("  {\n    id=%d,\n    priorty=%d,\n    numQuanta=%d,\n    numScheduled=%d,\n    meter=%f\n  },\n",
                curr->data->id,
                curr->data->priority,
                curr->data->numQuanta,
                curr->data->numScheduled,
                curr->data->meter);
    }
    printf("}\n");
}

/*
 * Execute highest priority process in queue and re-enqueue the process
 * until it has been scheduled numQuanta times, in which the process
 * node will be freed.
 */
void stride_schedule_processes(Node** queue) {
    Node* curr = dequeue(queue);
    while (curr != NULL) {
        printf("%d\n", curr->data->id);
        curr->data->meter += 1.0/curr->data->priority;
        if (++curr->data->numScheduled == curr->data->numQuanta) {
            free(curr);
        }
        else {
            enqueue(queue, curr);
        }
        curr = dequeue(queue);
    }
}

int main(int argc, char** argv) {
    char* progName = argv[0];

    // Validate command line args, accounting for argv containing progName. 
    // All processes must have a priority and numQuanta.
    if (argc == 1 || argc % 2 == 0) {
        printf("Error! Usage: %s <priority_1> <numQuanta_1> ... <priority_n> <numQuanta_n>\n", progName);
        return 1;
    }

    Node* queue = NULL;
    int num_processes = (argc-1)/2;

    // Initialze process structs and create priority queue.
    Process processes[num_processes];
    for (int i=0; i < num_processes; i++) {
        int p_id = i + 1;
        int priority = atoi(argv[(2*i) + 1]);
        int numQuanta = atoi(argv[(2*i) + 2]);
        int numScheduled = 0;
        float meter = 1.0/priority;
        processes[i] = (Process) {p_id, priority, numQuanta, numScheduled, meter};
        Node *node = (Node*) malloc(sizeof(Node));
        node->data = &processes[i];
        node->next = NULL;
        enqueue(&queue, node);
    }

    //print_queue(&queue);
    stride_schedule_processes(&queue);

    return 0;
}
