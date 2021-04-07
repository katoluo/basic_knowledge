#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char *argv[])
{
  // 1. 创建/打开共享内存，大小为4k
  int shmid = shmget(1000, 0, 0);
  if (shmid == -1) {
    perror("shmget error");
    return -1;
  }

  // 2. 当前进程和共享内存关联
  void *ptr = shmat(shmid, NULL, 0);
  if (ptr == (void*)-1) {
    perror("shmat error");
    return -1;
  }

  // 3. 读共享内存
  printf("共享内存数据：%s\n", (char*)ptr);

  // 阻塞程序
  printf("按任意键继续，删除共享内存\n");
  getchar();

  // 解除关联
  shmctl(shmid, IPC_RMID, NULL);
  printf("共享内存已经被删除...\n");

  return 0;
}

