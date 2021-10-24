#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int calculateSum(int K, int N);

int main(int argc, char *argv[])
{
    int x,y,z, pid, pid1, pid2;
    int n = 15;
    uint wtime, rtime;
    // int K = 5000;
    // int N = 100,M=1000, L=10000;
    int K, L, M, N;
    if (argc < 2){
        printf("Please enter valid number of arguments.\n");
        exit(1);
    }

    K = atoi(argv[1]);
    L = atoi(argv[2]);
    M = atoi(argv[3]);
    N = atoi(argv[4]);
    /*
        Calculate for N
    */
    // N
    for(x = 0; x< n; x++){
        int sum = 0;
        pid = fork();
        if ( pid <  0 ){
            printf("Fork error.\n");
            break;
        }
        else if(pid == 0){
            sum += calculateSum(K, N);
            exit(0);
        }
    }

    int N_TA_TIME_SUM = 0, N_R_TIME_SUM = 0;
    printf("\n================Group N================\n");
    while(waitstat(0, &wtime, &rtime) != -1){
        N_TA_TIME_SUM += wtime;
        N_R_TIME_SUM += rtime;
        printf("Child exited. Wait time: %d Run time: %d \n", wtime, rtime);
    }
    printf("Sum of Turn around time: %d, Sum of Total Run time: %d\n", N_TA_TIME_SUM, N_R_TIME_SUM);

    /*
    Calculate for M
    */
    // M
    for(y = 0; y< n; y++){
        int sum2 = 0;
        pid1 = fork();
        if ( pid1<  0 ){
            printf("Fork error.\n");
            break;
        }
        else if(pid1 == 0){
            sum2 += calculateSum(K, M);
            exit(0);
        }
    }

    int M_TA_TIME_SUM = 0, M_R_TIME_SUM = 0;
    printf("\n================Group M================\n");
    while(waitstat(0, &wtime, &rtime) != -1){
        M_TA_TIME_SUM += wtime;
        M_R_TIME_SUM += rtime;
        printf("Child exited. Wait time: %d Run time: %d \n", wtime, rtime);
    }
    printf("Sum of Turn around time: %d, Sum of Total Run time: %d\n", M_TA_TIME_SUM, M_R_TIME_SUM);

    /*
    Calculate for L
    */
    // L
    for(z = 0; z< n; z++){
        int sum3 = 0;
        pid2 = fork();
        if ( pid2 <  0 ){
            printf("Fork error.\n");
            break;
        }
        else if(pid2 == 0){
            sum3 += calculateSum(K, L);
            exit(0);
        }
    }

    int L_TA_TIME_SUM = 0, L_R_TIME_SUM = 0;
    printf("\n================Group L================\n");
    while(waitstat(0, &wtime, &rtime) != -1){
        L_TA_TIME_SUM += wtime;
        L_R_TIME_SUM += rtime;
        printf("Child exited. Wait time: %d Run time: %d \n", wtime, rtime);
    }
    printf("Sum of Turn around time: %d, Sum of Total Run time: %d\n", L_TA_TIME_SUM, L_R_TIME_SUM);

    exit(0);
}


int calculateSum(int K, int N){
    int i,j;
    int sum = 0;
    for(i=0;i<K;i++){
        for(j=0;j<N; j++){
            sum += i-j;
        }
    }
    return sum;
}