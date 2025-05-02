#include<stdio.h>
#include<string.h>
#include"../include/ordonnanceur.h"

void ord_prio(process* p_list, int nproc, int inter) {
    gantt_event gantt[100];
    int gantt_idx = 0;

    for (int i = 0; i < nproc - 1; i++) {
        for (int j = 0; j < nproc - i - 1; j++) {
            if (p_list[j].at > p_list[j+1].at ||
                (p_list[j].at == p_list[j+1].at && p_list[j].priority > p_list[j+1].priority))
                permuter(&p_list[j], &p_list[j+1]);
        }
    }
    int waiting_time[nproc], turnaround_time[nproc];
    int start_time = 0;
    printf("\n\t===== ordonnancement avec priority =====\n");
    printf("+---------+------------+-------+----------+------------+----------+\n");
    printf("| process | arrival    | burst | priority | waiting    | turnaround|\n");
    printf("+---------+------------+-------+----------+------------+----------+\n");
    for (int i = 0; i < nproc; i++) {
        if (start_time < p_list[i].at)
            start_time = p_list[i].at;
        waiting_time[i] = start_time - p_list[i].at;
        turnaround_time[i] = waiting_time[i] + p_list[i].bt;
        gantt[gantt_idx].start_time = start_time;
        gantt[gantt_idx].end_time = start_time + p_list[i].bt;
        strcpy(gantt[gantt_idx].name, p_list[i].name);
        gantt_idx++;
        start_time += p_list[i].bt;
        printf("| %-7s | %-10d | %-5d | %-8d | %-10d | %-10d |\n",
               p_list[i].name, p_list[i].at, p_list[i].bt, p_list[i].priority,
               waiting_time[i], turnaround_time[i]);
    }
    printf("+---------+------------+-------+----------+------------+----------+\n\n");
    printf("+======================================================+\n\n");
    gantt_graph(gantt, gantt_idx, inter);
}
