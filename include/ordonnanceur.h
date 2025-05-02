#ifndef ORDONNANCEUR_H
#define ORDONNANCEUR_H

typedef struct {
    char name[10];
    int at;              
    int bt;               
    int remaining_time;  
    int priority; 
} process;

typedef enum {
    FCFS,
    RR,
    SJF,
    PRIO
} type_ord;

typedef struct {
    char name[10];
    int start_time;
    int end_time;
} gantt_event;

process* create(int taille);
int readfile(FILE* fread, process* p_list);
void permuter(process* p1, process* p2);
void ord_fcfs(process* p_list, int nproc, int inter);
void ord_sjf(process* p_list, int nproc, int inter);
void ord_rr(process* p_list, int nproc, int quantum, int inter);
void ord_prio(process* p_list, int nproc, int inter);
void gantt_graph(gantt_event* gantt, int n, int inter);

#endif
