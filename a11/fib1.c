#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...
//       n: 0  1  2  3  4  5  6   7   8  ...

int numThreads = 0;

void *compute_fib( void *ptr )
{	
	int index = (int) ptr;
	
	
	numThreads++;

	if(index == 0) {
		return (void *) 0;
	}
	else if(index == 1) {
		return (void *) 1;
	}
	else {
    		pthread_t threads[2];
		//create 2 threads to do computation
		index--;
		pthread_create(&threads[0], NULL, compute_fib, (void *) index);
		index--;
		pthread_create(&threads[1], NULL, compute_fib, (void *) index);
		//get the results and combine
		void *result1, *result2;
		pthread_join(threads[0], &result1);
		pthread_join(threads[1], &result2);
		int final = (int)result1 + (int)result2;
		//return the result
		return (void *)final;
	}
}

int main(int argc, char *argv[])
{
     	pthread_t thread1;

	int n = atoi(argv[1]); 

    	/* Create independent threads each of which will execute function */

     	if (pthread_create(&thread1, NULL, &compute_fib, (void *) n) != 0) {// (void *) n) != 0) {
	 	puts("Cannot create threads.");
		exit(1);
	 }

	     /* Wait till threads are complete before main continues. Unless we  */
	     /* wait we run the risk of executing an exit which will terminate   */
	     /* the process and all threads before the threads have completed.   */
	
	void *rp;
	pthread_join(thread1, &rp);
     	printf("\nResult: %d\n", (int)rp);
     	printf("\n# of threads: %d\n", numThreads);

     	exit(0);
}

