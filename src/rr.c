#include <stdio.h>
#include <stdbool.h>
#include<string.h>
#include "../include/ordonnanceur.h"

void ord_rr(process* p_list, int nproc, int quantum, int inter) {
    gantt_event gantt[100];
    int gantt_idx = 0;
    for (int i = 0; i < nproc; i++) {
        p_list[i].remaining_time = p_list[i].bt;
    }
    int current_time = 0, completed = 0;
    bool done;
    int waiting_time[nproc], turnaround_time[nproc];
    printf("\n\t===== ordonnancement round robin avec (quantum= %d) =====\n", quantum);
    printf("+---------+------------+-------+----------+------------+\n");
    printf("| process | arrival    | burst | waiting  | turnaround |\n");
    printf("+---------+------------+-------+----------+------------+\n");
    while (completed < nproc) {
        done = true;
        for (int i = 0; i < nproc; i++) {
            if (p_list[i].remaining_time > 0 && p_list[i].at <= current_time) {
                done = false;
                gantt[gantt_idx].start_time = current_time;
                if (p_list[i].remaining_time > quantum) {
                    current_time += quantum;
                    p_list[i].remaining_time -= quantum;
                    gantt[gantt_idx].end_time = current_time;
                } else {
                    current_time += p_list[i].remaining_time;
                    gantt[gantt_idx].end_time = current_time;
                    waiting_time[i] = current_time - p_list[i].at - p_list[i].bt;
                    turnaround_time[i] = waiting_time[i] + p_list[i].bt;
                    p_list[i].remaining_time = 0;
                    completed++;
                    printf("| %-7s | %-10d | %-5d | %-8d | %-10d |\n", p_list[i].name, p_list[i].at, p_list[i].bt, waiting_time[i], turnaround_time[i]);
                }
                strcpy(gantt[gantt_idx].name, p_list[i].name);
                gantt_idx++;
            }
        }
        if (done) current_time++;
    }
    printf("+---------+------------+-------+----------+------------+\n\n");
    printf("+======================================================+\n\n");
    gantt_graph(gantt, gantt_idx, inter);
}
