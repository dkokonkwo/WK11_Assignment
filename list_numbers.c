#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MIN_THREADS 10

/**
 * ThreadData - struct for thread data
 * @start: starting integer
 * @end: ending integer
 */

typedef struct
{
long start;
long end;
} ThreadData;

void *print_range(void *arg)
{
long i;
ThreadData *data = (ThreadData *) arg;
for (i = data->start; i <= data->end; i++)
{
printf("%ld, ", i);
}
free(data);
return NULL;
}

int main(void)
{
pthread_t threads[MIN_THREADS];
long n, range, start, end;
int i;
printf("Enter input number (minimun 1000000): \n");
scanf("%ld", &n);

if (n < 1000000)
{
printf("Number must be at least 1000000\n");
return (1);
}

range = n / 1000000;
start = 0;
end = range;

for (i = 0; i < MIN_THREADS; i++)
{
ThreadData *data = (ThreadData *) malloc(sizeof(ThreadData));
data->start = start;
data->end = (i == MIN_THREADS - 1) ? n : end;

pthread_create(&threads[i], NULL, print_range, (void *) data);

start = end + 1;
end += range;
}

for (i = 0; i < MIN_THREADS; i++)
{
pthread_join(threads[i], NULL);
}

return (0);
}
