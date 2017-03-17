/* Group Members: Vivek Jadon
		  Jeme John
*/

#include "threads.h"

int a[3];

void func1() {
		printf("Thread:1\n");
		a[0]++;
		sleep(1);
		yield();
		printf("Back in Thread:1\n");
}

void func2() {
	
		printf("Thread:2\n");
		a[1]++;
		sleep(1);
		yield();
		printf("Back in Thread:2\n");
}

void func3() {
	
		printf("Thread:3\n");
		a[2]++;
		sleep(1);
		yield();
		printf("Back in Thread:3\n");

}

int main() {
	// Initialize the queue pointer
	init();
	int i=0;
	for(i=0;i<3;i++)
		a[i]=0;
	// Create user threads and prepare the RunQ
	while(1)
	{
	start_thread(&(func1));
	start_thread(&(func2));
	start_thread(&(func3));
	// Initiate context switiching
	run();
	for(i=0;i<3;i++)
		printf("%d ",a[i]);
	}
	return 0;
}
