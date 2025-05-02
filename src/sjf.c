#include <stdio.h>
#include<string.h>
#include "../include/ordonnanceur.h"

void ord_sjf(process* p_list, int nproc, int inter) {
    gantt_event gantt[100];
    int gantt_idx = 0;
    for (int i = 0; i < nproc - 1; i++) {
        for (int j = 0; j < nproc - i - 1; j++) {
            if (p_list[j].at > p_list[j+1].at)
                permuter(&p_list[j], &p_list[j+1]);
        }
    }
    int completed = 0, current_time = 0;
    int waiting_time[nproc], turnaround_time[nproc];
    int is_completed[nproc];
    for (int i = 0; i < nproc; i++) is_completed[i] = 0;
    printf("\n\t===== ordonnancement sjf =====\n");
    printf("+---------+------------+-------+----------+------------+\n");
    printf("| process | arrival    | burst | waiting  | turnaround |\n");
    printf("+---------+------------+-------+----------+------------+\n");
    while (completed < nproc) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < nproc; i++) {
            if (p_list[i].at <= current_time && !is_completed[i] && p_list[i].bt < min_bt) {
                min_bt = p_list[i].bt;
                idx = i;
            }
        }
        if (idx != -1) {
            gantt[gantt_idx].start_time = current_time;
            gantt[gantt_idx].end_time = current_time + p_list[idx].bt;
            strcpy(gantt[gantt_idx].name, p_list[idx].name);
            gantt_idx++;
            waiting_time[idx] = current_time - p_list[idx].at;
            turnaround_time[idx] = waiting_time[idx] + p_list[idx].bt;
            current_time += p_list[idx].bt;
            is_completed[idx] = 1;
            completed++;
            printf("| %-7s | %-10d | %-5d | %-8d | %-10d |\n", p_list[idx].name, p_list[idx].at, p_list[idx].bt, waiting_time[idx], turnaround_time[idx]);
        } else {
            current_time++;
        }
    }
    printf("+---------+------------+-------+----------+------------+\n\n");
    printf("+======================================================+\n\n");
    gantt_graph(gantt, gantt_idx, inter);
}
