#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(void)
{
  // 1. 创建共享内存
  int shmid = shmget(1000, 4096, IPC_CREAT | 0664);
  if (shmid == -1) {
    perror("shmget error");
    return -1;
  }

  // 2. 关联共享内存
  void *ptr = shmat(shmid, NULL, 0);
  if (ptr == (void*)-1) {
    perror("shmat error");
    return -1;
  }

  // 3. 写
  const char *p = "Hello world, 共享内存真香...";
  memcpy(ptr, p, strlen(p) + 1);

  // 阻塞进程
  printf("按任意键继续，删除共享内存\n");
  getchar();

  shmdt(ptr);

  shmctl(shmid, IPC_RMID, NULL);
  printf("共享内存已经被删除...\n");


  return 0;
}
