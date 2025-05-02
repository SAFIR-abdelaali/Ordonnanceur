#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ordonnanceur.h"

int main(int argc, char *argv[]) {
    type_ord lequel;
    FILE* filetoread;
    int nproc;
    int quantum = 0;
    int choice;
    int sortir=0;
    if (argc != 2) {
        printf("vous avez faire une erreur d'execution, regarde l'example pour comprendre !\n");
        printf("\t\texample: ./ordonnanceur config.txt\n");
        return EXIT_FAILURE;
    }
    filetoread = fopen(argv[1], "r");
    if (!filetoread) {
        printf("impossible d'ouvrir le fichier %s !\n", argv[1]);
        return EXIT_FAILURE;
    }
    process *p_list = create(100);
    nproc = readfile(filetoread, p_list);
    fclose(filetoread);
    int inter = 0;
    char v_choice;
    while(!sortir){
        printf("==========choisir votre type d'ordonnancement:============\n");
        printf("\t1- fcfs (first come first served)\n");
        printf("\t2- sjf (shortest job first)\n");
        printf("\t3- rr (round robin)\n");
        printf("\t4- priorite\n");
        printf("\t5- sortir\n");
        printf("donner votre choix: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                lequel = FCFS;
                break;
            case 2:
                lequel = SJF;
                break;
            case 3:
                lequel = RR;
                break;
            case 4:
                lequel = PRIO;
                break;
            case 5:
                sortir=1;
                continue;
            default:
                printf("invalid choice, valide choices are between(1-5)!\n");
                continue;
        }
        printf("ihm ? (y/n): ");
        scanf(" %c", &v_choice);
        if (v_choice == 'y' || v_choice == 'Y'){
            inter = 1;
        }else if(v_choice=='n' || v_choice=='N'){
            inter = 0;
        }else{
            printf("invalid choice! please retry");
        }
                
        if (lequel == RR) {
            printf("quantum? : ");
            scanf("%d", &quantum);
        }
        if (lequel == SJF)
            ord_sjf(p_list, nproc, inter);
        else if (lequel == FCFS)
            ord_fcfs(p_list, nproc, inter);
        else if (lequel == RR)
            ord_rr(p_list, nproc, quantum, inter);
        else if (lequel == PRIO)
            ord_prio(p_list, nproc, inter);
    }
    free(p_list);
    return 0;
}