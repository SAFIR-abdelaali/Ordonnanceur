#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ordonnanceur.h"

#define MAX_TIME 100
#define MAX_PROCESSES 10

process* create(int taille) {
    process* p = (process*)malloc(taille * sizeof(process));
    if (!p) {
        printf("memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

int readfile(FILE* fread, process* p_list) {
    char line[100];
    int i = 0;
    while (fgets(line, sizeof(line), fread)) {
        if (line[0] == '\n' || line[0] == '\t' || (line[0] == '/' && line[1] == '/'))
            continue;
        if (sscanf(line, "%s %d %d %d", p_list[i].name, &p_list[i].at, &p_list[i].bt, &p_list[i].priority) == 4)
            i++;
    }
    return i;
}

void permuter(process* p1, process* p2) {
    process tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void gantt_graph(gantt_event* gantt, int n, int inter) {
    char process_names[MAX_PROCESSES][10];
    int num_processes = 0;
    int max_time = 0;
    int grid[MAX_PROCESSES][MAX_TIME] = {0};
    if(inter){
        printf("\n\t\t=========IHM de gantt=========\n");
        for (int i = 0; i < n; i++) {
            printf("Process %s: [%d -> %d]\n", gantt[i].name, gantt[i].start_time, gantt[i].end_time);
            printf("cliquer sur 'n' pour continuer...\n");
            while (getchar() != 'n');
        }
    }else{
        for (int i = 0; i < n; i++) {
            int found = -1;
            for (int j = 0; j < num_processes; j++) {
                if (strcmp(process_names[j], gantt[i].name) == 0) {
                    found = j;
                    break;
                }
            }
            if (found == -1) {
                strcpy(process_names[num_processes], gantt[i].name);
                num_processes++;
            }
        }
        for (int i = 0; i < n; i++) {
            int row = -1;
            for (int j = 0; j < num_processes; j++) {
                if (strcmp(process_names[j], gantt[i].name) == 0) {
                    row = j;
                    break;
                }
            }
            for (int t = gantt[i].start_time; t < gantt[i].end_time; t++) {
                grid[row][t] = 1;
            }
            if (gantt[i].end_time > max_time)
                max_time = gantt[i].end_time;
        }
        printf("\n\t\t=== graph de gantt ===\n\n");
        for (int i = 0; i < num_processes; i++) {
            printf("%-5s |", process_names[i]);
            for (int t = 0; t < max_time; t++) {
                if (grid[i][t] == 1)
                    printf("## ");
                else
                    printf("   ");
            }
            printf("\n");
        }
        printf("      "); 
        for (int t = 0; t < max_time+1; t++) {
            printf("---");
        }
        printf("\n");
        printf("      ");
        for (int t = 0; t < max_time+1; t++) {
            if (t < 10)
                printf("%d  ", t);  
            else
                printf("%d ", t); 
        }
        printf("\n\n");
    }
    
}



