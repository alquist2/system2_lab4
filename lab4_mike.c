#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

#define M 2400
#define P 2000
#define N 500

typedef struct {

	long a[M][P];
	long b[P][N];
	long c[M][N];
	int start_row;
	int end_row;

}args;

typedef struct {
	long sec;
	long micro;
}timeval;

//Multiplies section of array according to the number of threads
void *section_array(void *param){

	int i, j, k;

	//Initialize arguments into thread
	args *info;
	info = (args *) param;

	//Calculate section of array based on number of threads
	//Loop rows of resulting array
	for (i = info->start_row; i < info->end_row; i++){

		//Calulates each column of the row
		for (j = 0; j < N; j++){

			info->c[i][j] = 0;

			//Array multiplication
			for (k = 0; k < P; k++){

				info->c[i][j] += info->a[i][k] * info->b[k][j];

			}

		}

	}
}

int main(int argc, char *argv[]){
	
	int thread_count = 1, i, j, k; 
	int max_threads = argv[1][0] - '0';
	int increment;
	long comp[M][N];
	double diff;
	timeval *start = (timeval *)malloc(sizeof(timeval));
	timeval *finish = (timeval *)malloc(sizeof(timeval));
	args *info = (args *) malloc(sizeof(args));

	//Initialize a and b
	for (j = 0; j < M; j++){
		for (k = 0; k < P; k++){
			info->a[j][k] = (long)(k - j + 2);
		}
	}
	for (j = 0; j < P; j++){
		for (k = 0; k < N; k++){
			info->b[j][k] = (long)(j - k + 1);
		}
	}

	pthread_t thread[6];
	pthread_attr_t attr_thread[6];
	pthread_attr_init(&attr_thread[0]);

	info->start_row = 0;
	info->end_row = 2400;
	
	gettimeofday(start, NULL);
	//start = time->micro;

	printf("Threads\t\tSeconds\n");

	//Run array multiplication with one thread
	pthread_create(&thread[0], &attr_thread[0], section_array, (void *) info);
	pthread_join(thread[0], NULL);
	gettimeofday(finish, NULL);
	diff = (finish->sec - start->sec) + ((finish->micro - start->micro)/1000000.0);
	printf("%d\t\t%f\n", thread_count, diff);
	thread_count++;

	//Save 1-thread array into global variable
	for (j = 0; j < M; j++){
		for (k = 0; k < N; k++){
			comp[j][k] = info->c[j][k];
		}
	}

	/*for (j = 2380; j < 2400; j++){
		printf("%lu ", info->c[j][498]);
	}*/
	
	//Run array multiplication starting with 2 threads, then up to x threads (6 max)
	while (thread_count <= max_threads){
		int boolean = 0;
		info->start_row = 0;
		increment = 2400 / thread_count;	

		pthread_attr_init(&attr_thread[thread_count - 1]);
		gettimeofday(start, NULL);
		for (i = 0; i < thread_count; i++){
			info->end_row = info->start_row + increment;
			pthread_create(&thread[i], &attr_thread[i], section_array, (void *) info);
			info->start_row = info->end_row;
		}
		for (i = 0; i < thread_count; i++){
			pthread_join(thread[i], NULL);
		}
		gettimeofday(finish, NULL);
		diff = (finish->sec - start->sec) + ((finish->micro - start->micro)/1000000.0);
		
		printf("%d\t\t%f\t", thread_count, diff);
		thread_count++;

		/*for (j = 2380; j < 2400; j++){
			printf("%lu ", info->c[j][498]);
		}*/

		//Compare results to global array
		for (j = 0; j < M; j++){
			for (k = 0; k < N; k++){
				if (comp[j][k] != info->c[j][k]){
					boolean = 1;
					break;
				}
			}
		}

		if (boolean == 0){
			printf("No error\n");
		} else {
			printf("Error\n");
		}

	}

	return 0;
}
