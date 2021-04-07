#include <stdio.h>

#include <pthread.h>

#define THREAD_NUMBER  3
#define TRUE  1
#define FALSE 0

// 子线程的互斥量和条件变量
pthread_mutex_t thread_mutex[THREAD_NUMBER];
pthread_cond_t thread_cond[THREAD_NUMBER];

// 子线程是否正在等待
int thread_wait_flag[THREAD_NUMBER];

// 标识轮到那个子线程输出其ID
pthread_mutex_t mutex;
int thread_turn;

void *thread_func(void *arg);

int main(void)
{
  pthread_t tids[THREAD_NUMBER];
  int i;

  for (i = 0; i != THREAD_NUMBER; ++i) {
    pthread_mutex_init(&thread_mutex[i], NULL);
    pthread_cond_init(&thread_cond[i], NULL);
  }

  for (i = 0; i != THREAD_NUMBER; ++i) {
    pthread_create(&tids[i], NULL, thread_func, (void*)i);
  }

  for (i = 0; i != THREAD_NUMBER; ++i) {
    pthread_join(tids[i], NULL);
  }

  printf("\n");
  return 0;
}


void *thread_func(void *arg)
{
  int id = (int)arg;
  char ch = 'A' + id;
  int count = 0;

  while (1) {
    if (id == thread_turn) // 若轮到当前子线程，输出ID，发送信号
    {
      printf("%c", ch);
      ++count;
      // 若是第3个子线程，输出ID后
      if (id == THREAD_NUMBER - 1 && count == 10)
        break;
      pthread_mutex_lock(&mutex);
      ++thread_turn;
      thread_turn %= THREAD_NUMBER;  // 0 1 2
      pthread_mutex_unlock(&mutex);

      while (1) {
        pthread_mutex_lock(&thread_mutex[thread_turn]);
        if (thread_wait_flag[thread_turn] == TRUE)
        {
          pthread_cond_signal(&thread_cond[thread_turn]);
          pthread_mutex_unlock(&thread_mutex[thread_turn]);
          break;
        }
        pthread_mutex_unlock(&thread_mutex[thread_turn]);
      }
      if (count == 10)
        break;
    } else {
      pthread_mutex_lock(&thread_mutex[id]);
      thread_wait_flag[id] = TRUE;
      pthread_cond_wait(&thread_cond[id], &thread_mutex[id]);
      thread_wait_flag[id] = FALSE;
      pthread_mutex_unlock(&thread_mutex[id]);
    }
  }
  return (void*)0;
}
