# strcpy和memcpy的区别？



```c
#include <string.h>
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
```

```c
#include <string.h>
void *memcpy(void *dest, const void *src, size_t n);
```



- **复制的内容不同：** strcpy只能复制字符串，而memcpy可以复制任意类型的内容。strcpy只用于字符串复制，并且还会复制字符串的结束符。memcpy对于复制的内容没有限制，用途更广。
- **复制的方法不同：** strcpy不需要指定长度，遇到结束符’\0’才会结束，所以容易溢出。memcpy则是根据第三个参数决定复制的长度。
- **用途不同：** 通常在复制字符串时用strcpy，在复制其他类型数据时一般用memcpy。