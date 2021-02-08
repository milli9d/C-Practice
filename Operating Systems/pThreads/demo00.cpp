#include <pthread.h>
#include <iostream>
#include <vector>
#include <unistd.h>

void *myTurn(void *arg)
{
	int *i = (int *)arg;
	for (*i = 0; *i < 100000; (*i)++)
	{
		usleep(1);
		printf("%d My Turn\n", *i);
	}
	return NULL;
}

void *yourTurn(void *arg)
{
	for (int i = 0; i < 100000; i++)
	{

		usleep(1);
		printf("Your Turn\n");
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t mythread;
	pthread_t yourThread;

	int v = 0;

	pthread_create(&mythread, NULL, myTurn, &v);
	pthread_create(&mythread, NULL, myTurn, &v);
	pthread_create(&mythread, NULL, myTurn, &v);
	pthread_create(&yourThread, NULL, yourTurn, NULL);

	pthread_join(mythread,NULL);
	pthread_join(yourThread,NULL);

	std::cout << v << std::endl;
	return 0;
}
