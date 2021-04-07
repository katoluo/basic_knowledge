#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

struct msg {
  int num;
  struct msg *next;
};

struct msg *head = NULL, *mp = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;

void *productor(void *arg) {

  while (1) {
    mp = (struct msg*)malloc(sizeof(struct msg));
    mp->num = rand() % 100 + 1;
    printf("--------producted------%d\n", mp->num);

    pthread_mutex_lock(&mutex);
    mp->next = head;
    head = mp;
    pthread_mutex_unlock(&mutex);

    pthread_cond_signal(&has_product);
  }

  return NULL;
}

void *consumer(void *arg) {

  while (1) {
    pthread_mutex_lock(&mutex);
    while (head == NULL) {
      pthread_cond_wait(&has_product, &mutex);
    }
    mp = head;
    head = head->next;
    pthread_mutex_unlock(&mutex);

    printf("---------------consumer-------%d\n", mp->num);
    free(mp);
    mp = NULL;
    sleep(rand() % 3);
  }

  return NULL;
}

int main(void)
{
  srand(time(NULL));

  pthread_t ptid, ctid;

  pthread_create(&ptid, NULL, productor, NULL);
  pthread_create(&ctid, NULL, consumer, NULL);

  pthread_join(ptid, NULL);
  pthread_join(ctid, NULL);

  return 0;
}

