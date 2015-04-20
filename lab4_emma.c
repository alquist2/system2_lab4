#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define M 2400
#define P 2000
#define N 500

typedef struct {

	int a[M][P];
	int b[P][N];
	int c[M][N];
	int start_row;
	int increment;

}args;

typedef struct {
	long sec;
	suseconds_t micro;
}timeval;


//Multiplies section of array according to the number of threads
void *section_array(void *param){

	int i, j, k;

	//Initialize arguments into thread
	args *info;
	info = (args *) param;

	//Calculate section of array based on number of threads
	//Loop rows of resulting array
	for (i = info->start_row; i < info->start_row + info->increment; i++){

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
//int a[N][M]={0};
//int b[M][P]={0};
//int c[N][P]={0};
int i=0;
int j=0;
int k=0;

long start, diff;  //use clock() function
timeval *time = (timeval *) malloc(sizeof(timeval));
args *info = (args *) malloc(sizeof(args));

int threadNumber;
int startColumn;
int endColumn;

	//get threadNumber from commandline arg
	threadNumber=atoi(argv[1]);

	//Initialize a and b
	for (j = 0; j < M; j++){
		for (k = 0; k < P; k++){
			info->a[j][k] = k - j + 2;
		}
	}
	for (j = 0; j < P; j++){
		for (k = 0; k < N; k++){
			info->b[j][k] = j - k + 1;
		}
	}

	printf("Arrays initialized\n");
	
	//run without threads

		//start timer
		i=0;
		printf("%d\n", threadNumber);
		int difference=n/threadNumber;
for(i=0; i<threadNumber; i++){
printf("%d\n",i);
		for(j=0; j<i; j++){
			startColumn=difference*j;
			endColumn=startColumn+difference-1;
			printf("Start: %d End: %d \n", startColumn, endColumn);
			//create thread
			//pass arrays and start/end numbers
			//destroy thread

		}
}
		//end timer
		//print results

}
