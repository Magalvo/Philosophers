#include "../include/philosophers.h"

void	*eat()
{
	printf("Eating...\n ID: %d\n\n", getpid());
	return NULL;
}

void	*think()
{
	printf("Thinking...\n ID: %d\n\n", getpid());
	return NULL;
}


void	*sleeping()
{
	printf("Sleeping...\n ID: %d\n\n", getpid());
	return NULL;
}

void	*routine()
{
	printf("Sleeping...\n ID: %d\n\n", getpid());
	return NULL;
}

int 	main(int argc, char *argv[])
{
	pthread_t t1, t2;

	(void)argv;
	if (argc > 6)
		printf("Too many args");
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0) 
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	return (0);
}