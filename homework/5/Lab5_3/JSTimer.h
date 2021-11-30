#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 100

struct timeval* start[SIZE], *end[SIZE];
double *res;
int size;

void JSTimer_init(int count){
	if(count > SIZE) return;
	size = count;
	for(int i = 0; i < size; i++){
		start[i] = malloc(sizeof(struct timeval));
		end[i] = malloc(sizeof(struct timeval));
	}
	res = (double *)malloc(sizeof(double) * count);
	return;
}
void JSTimer_on(int id){
	gettimeofday(start[id], NULL);
}
void JSTimer_off(int id){
	gettimeofday(end[id], NULL);
	res[id] += (end[id]->tv_usec - start[id]->tv_usec) / 1000.0;
	res[id] += (end[id]->tv_sec - start[id]->tv_sec) * 1000;
}
void JSTimer_print(){
	for(int i = 0; i < size; i++){
		printf("Timer %d : %.2f ms\n", i, res[i]);
	}
}
void JSTimer_finalize(){
	for(int i = 0; i < size; i++){
		free(start[i]);
		free(end[i]);
	}
	free(res);
}

