#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void example_task(void *arg) {
  if (arg == NULL) {
    return;
  }
  int num = *((int *)arg);
  printf("Processing taks %d\n", num);
  sleep(1); // Simulate work
  free(arg);
}

int main(int argc, char *argv[]) {
  threadpool_t pool;
  threadpool_init(&pool);
  int task_count = 50;

  for (int i = 0; i < task_count; i++) {
    int *task_num = malloc(sizeof(int));
    *task_num = i;
    threadpool_add_task(&pool, example_task, task_num);
  }

  sleep(task_count / THREADS + 2); // Wait for tasks to complete
  threadpool_destroy(&pool);

  return EXIT_SUCCESS;
}
