#include "../inc/threadpool.h"

void *threadpool_worker(void *arg) {
  threadpool_t *pool = (threadpool_t *)arg;

  while (1) {
    pthread_mutex_lock(&pool->lock);

    while (pool->queued == 0 && !pool->stop) {
      pthread_cond_wait(&pool->notify, &pool->lock);
    }

    if (pool->stop) {
      pthread_mutex_unlock(&pool->lock);
      break;
    }

    task_t task = pool->task_queue[pool->queue_front];
    pool->queue_front = (pool->queue_front + 1) % QUEUE_SIZE;
    pool->queued--;

    pthread_mutex_unlock(&pool->lock);

    task.fn(task.arg);
  }

  return NULL;
}

void threadpool_init(threadpool_t *pool) {
  pthread_mutex_init(&pool->lock, NULL);
  pthread_cond_init(&pool->notify, NULL);
  pool->queued = 0;
  pool->queue_front = 0;
  pool->queue_back = 0;
  pool->stop = 0;

  for (int i = 0; i < THREADS; i++) {
    pthread_create(&pool->threads[i], NULL, threadpool_worker, pool);
  }
}
