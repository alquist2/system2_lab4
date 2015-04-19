#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]){
int n=2400;
int m=2000;
int p=500;
//int a[n][m]={0};
//int b[m][p]={0};
//int c[n][p]={0};
int i=0;
int j=0;
int k=0;

int threadNumber;
int startColumn;
int endColumn;

	//get threadNumber from commandline arg
	threadNumber=atoi(argv[1]);

	//run without threads

		//start timer
		i=0;
		printf("%d\n", threadNumber);
		int difference=n/threadNumber;
		for(i=0; i<threadNumber; i++){
			startColumn=difference*i;
			endColumn=startColumn+difference-1;
			printf("Start: %d End: %d \n", startColumn, endColumn);
			//create thread
			//pass arrays and start/end numbers
			//destroy thread

		}
		//end timer
		//print results

}
