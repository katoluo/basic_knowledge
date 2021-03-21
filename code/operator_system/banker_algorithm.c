#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FALSE         0
#define TRUE          1
#define MAX_PROCESS   10    // 最大进程数
#define MAX_RESOURCE  10    // 最大资源类数

static int process_num;     // 进程数
static int resource_num;    // 资源数目
static int process_id;      // 进程ID号

static int Max[MAX_PROCESS][MAX_RESOURCE];      // 最大需求矩阵
static int Allocate[MAX_PROCESS][MAX_RESOURCE]; // 已分配矩阵
static int Need[MAX_PROCESS][MAX_RESOURCE];     // 最多还需要的矩阵

static int Available[MAX_RESOURCE];             // 资源总数
static int Request[MAX_RESOURCE];               // 请求资源
static int Work[MAX_RESOURCE];                  // 工作向量
static int Finish[MAX_PROCESS];                 // 进程完成标志

static int work_allocation[MAX_PROCESS][MAX_RESOURCE];

static void Init_system();
static void Print_info();
static int Try_allocate();
static void Return_back();
static int Is_safe();

static int flag = FALSE;
static int safe[MAX_PROCESS];


int main(int argc, char *argv[])
{
  int ret = FALSE;
  int choice;
  
  while(1) {
    printf("欢迎使用模拟避免进程死锁算法，请选择你要进行的操作:\n");
    printf("\t**1、初始化系统\n");
    printf("\t**2、请求分配资源\n");
    printf("\t**3、查看系统分配结果\n");	
    printf("\t**4、撤销分配\n");
    printf("\t**5、当前状态安全性检查\n");
    printf("\t**0、退出系统\n");
    scanf("%d",&choice);
    if ( choice == 1 )
      Init_system();
    else if (choice == 2) {
      if ( Try_allocate() == TRUE ) {
        flag = Is_safe();
        if ( flag == FALSE ) {
          printf("系统不安全，不能予以分配！\n");
          Return_back();
        }
        else {
          printf("系统安全！分配成功！\n");
          Print_info();
        }
      }
      else {
        printf("分配失败！\n");
        Return_back();
      }
    }
    else if ( choice == 3 )
      Print_info();
    else if ( choice == 0 )
      break;
    else if ( choice == 4 )
      Return_back();
    else if ( choice == 5 ) {
      if ( ( flag == Is_safe() ) == FALSE )
        printf("当前状态不安全！\n");
      else 
        printf("当前状态安全！\n");
    }
    else 
      printf("输入不合法！重新输入！\n");
  }


  return EXIT_SUCCESS;
}


static void Init_system()
{
  int i, j, temp;
  char ch;

  printf("请输入进程数目：");
  scanf("%d", &process_num);
  printf("请输入资源种数：");
  scanf("%d", &resource_num);

  printf("请输入各类资源总数：");
  for (i = 0; i != resource_num; ++i)
    scanf("%d", &Available[i]);

  printf("输入各进程对各资源的最大需求：");
  for (i = 0; i != process_num; ++i) {
    printf("进程P%d：", i);
    for (j = 0; j != resource_num; ++j)
      scanf("%d", &Max[i][j]);
  }

  ch = getchar();

  printf("是否输入分配矩阵？（y/n）\n");
  while (scanf("%c", &ch)) {
    if ( ch == 'n' || ch == 'N' ) {
      bzero(Allocate, sizeof(Allocate));
      bzero(work_allocation, sizeof(work_allocation));
      break;
    }
    else if ( ch == 'y' || ch == 'Y' ) {
      printf("请输入T时刻资源的分配矩阵：\n");
      for ( i = 0; i != process_num; ++i ) {
        printf("进程P%d：", i);
        for ( j = 0; j != resource_num; ++j )
          scanf("%d", &Allocate[i][j]);
      }
      break;
    }
    else 
      printf("请重新输入：");
  }

  bzero(Request, sizeof(Request));
  bzero(Work, sizeof(Work));
  bzero(Finish, sizeof(Finish));

  // 初始时刻 Need
  for ( i = 0; i != process_num; ++i )
    for ( j = 0; j != resource_num; ++j ) {
      Need[i][j]            = Max[i][j]       -   Allocate[i][j];
      work_allocation[i][j] = Allocate[i][j]  +   Work[j];
    }
}


static int Try_allocate()
{
  int i, j, temp;
  int ret = TRUE;

  for ( i = 0; i != process_num; ++i )
    for ( j = 0; j != resource_num; ++j )
      work_allocation[i][j] = Allocate[i][j] + Work[j];

  printf("请输入请求进程号：");
  while (scanf("%d", &process_id)) {
    if ( process_id < 0 || process_id > process_num )
      printf("进程不存在，重新输入！\n");
    else 
      break;
  }

  printf("请输入请求资源数：");
  for (i = 0; i != resource_num; ++i)
    scanf("%d", &Request[i]);

  printf("开始为进程P%d分配资源：\n", process_id);
  for ( i = 0; i != resource_num; ++i ) {
    if ( Request[i] > Need[process_id][i] ) {
      printf("进程请求的资源数大于所需资源数，不予分配！\n");
      ret = FALSE;
    }
    else if ( Request[i] > Available[i] ) {
      printf("进程请求资源数大于可用资源数，无法分配！\n");
      ret = FALSE;
    }
    Available[i] -= Request[i];
    Allocate[process_num][i] += Request[i];
    Need[process_num][i] -= Request[i];
  }

  return ret;
}


static void Print_info()
{
  int i, j, k;
  
  printf("\t Work       Need        Allocation    Work + Allocation   Finish\n");
  for ( j = 0; j != 4; ++j ) {
    printf("\t  ");
    for ( i = 0; i != resource_num; ++i )
      printf("%c  ", (char)('A' + i));
  }

  printf("\n********************************************************************\n");
  for ( k = 0; k != process_num; ++k ) {

    if ( flag == TRUE ) i = safe[k];
    else                i = k;

    printf("P%d\t", i);
    for ( j = 0; j != resource_num; ++j )
      printf("%3d", work_allocation[i][j] - Allocate[i][j]);

    printf("\t");
    for ( j = 0; j != resource_num; ++j )
      printf("%3d", Need[i][j]);

    printf("\t");
    for ( j = 0; j != resource_num; ++j )
      printf("%3d", Allocate[i][j]);

    printf("\t");
    for ( j = 0; j != resource_num; ++j )
      printf("%3d", work_allocation[i][j]);

    printf("\t");
    if ( Finish[i] == FALSE )
      printf("false\n");
    else
      printf("true\n");
  }
}


static void Return_back()
{
  int i, j;
  bzero(Finish, sizeof(Finish));
  for ( i = 0; i != resource_num; ++i ) {
    Available[i]            += Request[i];
    Allocate[process_id][i] -= Request[i];
    Need[process_id][i]     += Request[i];
  }

  bzero(work_allocation, sizeof(work_allocation));
  for ( i = 0; i != process_num; ++i )
    for ( j = 0; j != resource_num; ++j )
      work_allocation[i][j] = Allocate[i][j];
}


static int Is_safe()
{
  int i, j, count = 0;
  bzero(work_allocation, sizeof(work_allocation));

  printf("*****************Work向量********************\n");
  for ( i = 0; i != resource_num; ++i ) {
    Work[i]               = Available[i];
    work_allocation[0][i] = Work[i];
  }

  for ( i = 0; i != process_num; ++i )
    Finish[i] = FALSE;

  for ( i = 0; i != process_num; ++i ) {
    if ( Finish[i] == FALSE ) {
      for ( j = 0; j != resource_num; ++j ) {
        if ( Need[i][j] > Work[j] )
          break;
      }
      if ( j == resource_num ) {
        printf("P%d\t", i);
        safe[count++] = i;
        for ( j = 0; j != resource_num; ++j ) {
          Work[j]               += Allocate[i][j];
          work_allocation[i][j] = Work[j];
          printf("%d\t", Work[j]);
        }
        printf("\n");
        Finish[i] = TRUE;
        if ( i == process_num - 1 )
          i = -1;
      }
    }
  }
  printf("\n");
  for ( i = 0; i != process_num; ++i ) {
    if ( Finish[i] == FALSE ) {
      printf("进程P%d不能顺利完成！\n", i);
      return FALSE;
    }
  }
  printf("存在如下安全序列：\n");
  for ( i = 0; i != process_num; ++i )
    printf("P%d", safe[i]);
  printf("\n");
  return TRUE;
}

