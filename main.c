#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 9
#define M 3
int numbers[N];

int sumByIndex(int i1, int i2){
    int sum = 0;
    for(int k = i1; k <= i2; k++){
        sum += numbers[k];
    }
    return sum;
}

void* sumPart(void* arg){
    int *res = malloc(sizeof(int));
    int loop = *(int *)arg;
    switch (loop) {
        case 0:
            *res = sumByIndex(0,(N/3)-1);
            break;
        case 1:
            *res = sumByIndex(N/3,2*(N/3)-1);
            break;
        case 2:
            *res = sumByIndex(2*(N/3), N-1);
            break;
    }
    printf("thread#%d\n", *res);
    pthread_exit((void*) res);
}

int main(){
    int creator, i, sumResult = 0;
    int arr[M];
    int* part;
    pthread_t threads[M];
    for(i = 0; i < N; i++){
        scanf("%d",numbers+i);
    }
    for(i = 0; i < N; i++){
        printf("%d ",numbers[i]);
    }
    printf("\n");
    for(i = 0; i < M; i++){
        arr[i] = i;
        creator = pthread_create(threads+i,NULL,sumPart,(void*)(arr+i));
        if(creator != 0){
            fputs("pthread creating failed", stderr);
            exit(EXIT_FAILURE);
        }
    }
    for(i = 0; i < M; i++){
        pthread_join(threads[i], (void**)&part);
        sumResult += *(part);
        free(part);
    }
    printf("result: %d\n",sumResult);
    return 0;
}