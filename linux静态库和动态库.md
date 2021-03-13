文章摘自：[作者：爱编程的大丙](https://subingwen.cn/linux/library/)



## 1. 静态库

在 Linux 中静态库由程序 `ar` 生成，现在静态库已经不像之前那么普遍了，这主要是由于程序都在使用动态库。关于静态库的命名规则如下:

- 在 Linux 中静态库以 `lib` 作为前缀，以`.a` 作为后缀，中间是库的名字自己指定即可，即: `libxxx.a`
- 在 Windows 中静态库一般以 `lib` 作为前缀，以 `lib` 作为后缀，中间是库的名字需要自己指定，即: `libxxx.lib`



### 1.1 生成静态链接库

生成静态库，需要先对源文件进行汇编操作 (使用参数` -c`) 得到二进制格式的目标文件 (`.o` 格式), 然后在通过 `ar` 工具将目标文件打包就可以得到静态库文件了 (`libxxx.a`)。

使用` ar` 工具创建静态库的时候需要三个参数：

- 参数c：创建一个库，不管库是否存在，都将创建。
- 参数s：创建目标文件索引，这在创建较大的库时能加快时间。
- 参数r：在库中插入模块 (替换)。默认新的成员添加在库的结尾处，如果模块名已经在库中存在，则替换同名的模块。



![2.png](https://github.com/katoluo/basic_knowledge/raw/master/images/2.png)



生成静态链接库的具体步骤如下:

1. 需要将源文件进行汇编，得到 .o 文件，需要使用参数 -c
2. 将得到的 .o 进行打包，得到静态库

```bash
$ ar crs libxxx.a *.o
```

3. 发布静态库

```bash
# 发布静态库
	1. 提供头文件 **.h
	2. 提供制作出来的静态库 libxxx.a
```



## 2. 动态库

动态链接库是程序运行时加载的库，当动态链接库正确部署之后，运行的多个程序可以使用同一个加载到内存中的动态库，因此在 Linux 中动态链接库也可称之为共享库。

动态链接库是目标文件的集合，目标文件在动态链接库中的组织方式是按照特殊方式形成的。库中函数和变量的地址使用的是相对地址（静态库中使用的是绝对地址），其真实地址是在应用程序加载动态库时形成的。

关于动态库的命名规则如下:

- 在 Linux 中动态库以 `lib` 作为前缀，以`.so` 作为后缀，中间是库的名字自己指定即可，即: `libxxx.so`

- 在 Windows 中动态库一般以 `lib` 作为前缀，以 `dll `作为后缀，中间是库的名字需要自己指定，即: `libxxx.dll`




### 2.1 生成动态链接库

生成动态链接库是直接使用 `gcc` 命令并且需要添加 `-fPIC（-fpic`） 以及` -shared` 参数。

- -fPIC 或 -fpic 参数的作用是使得 gcc 生成的代码是与位置无关的，也就是使用相对位置。
- -shared参数的作用是告诉编译器生成一个动态链接库。



![3.png](https://github.com/katoluo/basic_knowledge/raw/master/images/3.png)



生成动态链接库的具体步骤如下:

1. 将源文件进行汇编操作，需要使用参数 `-c`, 还需要添加额外参数 `-fpic /-fPIC`

```bash
# 得到若干个 .o文件
$ gcc 源文件(*.c) -c -fpic
```

2. 将得到的.o 文件打包成动态库，还是使用 gcc, 使用参数 -shared 指定生成动态库 (位置没有要求)

```bash
$ gcc -shared 与位置无关的目标文件(*.o) -o 动态库(libxxx.so)
```

3. 发布动态库和头文件

```bash
# 发布
 	1. 提供头文件: xxx.h
 	2. 提供动态库: libxxx.so
```



### 2.2 动态库制作举例

在此还是以上面制作静态库使用的实例代码为例来制作动态库，代码目录如下:

```bash
# 举例, 示例目录如下:
# 目录结构 add.c div.c mult.c sub.c -> 算法的源文件, 函数声明在头文件 head.h
# main.c中是对接口的测试程序, 制作库的时候不需要将 main.c 算进去
.
├── add.c
├── div.c
├── include
│   └── head.h
├── main.c
├── mult.c
└── sub.c
```

第一步：使用` gcc` 将源文件进行汇编 (参数`-c`), 生成与位置无关的目标文件，需要使用参数 `-fpic`或者`-fPIC`

```bash
# 1. 将.c汇编得到.o, 需要额外的参数 -fpic/-fPIC
$ gcc add.c div.c mult.c sub.c -c -fpic -I ./include/

# 查看目录文件信息, 检查是否生成了目标文件
$ tree
.
├── add.c
├── add.o                # 生成的目标文件
├── div.c
├── div.o                # 生成的目标文件
├── include
│   └── head.h
├── main.c
├── mult.c
├── mult.o               # 生成的目标文件
├── sub.c
└── sub.o                # 生成的目标文件
```

第二步：使用 `gcc` 将得到的目标文件打包生成动态库，需要使用参数` -shared`

```bash
# 2. 将得到 .o 打包成动态库, 使用gcc , 参数 -shared
$ gcc -shared add.o div.o mult.o sub.o -o libcalc.so  

# 检查目录中是否生成了动态库
$ tree
.
├── add.c
├── add.o
├── div.c
├── div.o
├── include
│   └── `head.h   ===> 和动态库一起发布
├── `libcalc.so   ===> 生成的动态库
├── main.c
├── mult.c
├── mult.o
├── sub.c
└── sub.o
```

第三步：发布生成的动态库和相关的头文件

```bash
# 3. 发布库文件和头文件
	1. head.h
	2. libcalc.so
```



### 2.3 动态库的使用

当我们得到了一个可用的动态库之后，需要将其放到一个目录中，然后根据得到的头文件编写测试代码，对动态库中的函数进行调用。

```bash
# 1. 拿到发布的动态库
	`head.h   libcalc.so
# 2. 基于头文件编写测试程序, 测试动态库中提供的接口是否可用
	`main.c`
# 示例目录:
.
├── head.h          ==> 函数声明
├── libcalc.so      ==> 函数定义
└── main.c          ==> 函数测试
```

编译测试程序

```bash
# 3. 编译测试程序
$ gcc main.c -o app
/tmp/ccwlUpVy.o: In function `main':
main.c:(.text+0x38): undefined reference to `add'
main.c:(.text+0x58): undefined reference to `subtract'
main.c:(.text+0x78): undefined reference to `multiply'
main.c:(.text+0x98): undefined reference to `divide'
collect2: error: ld returned 1 exit status
```

**错误原因:**

- 和使用静态库一样，在编译的时候需要指定库相关的信息: **库的路径 -L 和 库的名字 -l**

添加库信息相关参数，重新编译测试代码:

```bash
# 在编译的时候指定动态库相关的信息: 库的路径 -L, 库的名字 -l
$ gcc main.c -o app -L./ -lcalc

# 查看是否生成了可执行程序
$ tree
.
├── app 			# 生成的可执行程序
├── head.h
├── libcalc.so
└── main.c

# 执行生成的可执行程序, 错误提示 ==> 可执行程序执行的时候找不到动态库
$ ./app 
./app: error while loading shared libraries: libcalc.so: cannot open shared object file: No such file or directory
```

**关于整个操作过程的报告：**

- gcc 通过指定的动态库信息生成了可执行程序，但是可执行程序运行却提示无法加载到动态库。

**具体办法：**查看原文



## 3. 优缺点

### 3.1 静态库

- 优点：

  - 静态库被打包到应用程序中加载速度快
  - 发布程序无需提供静态库，移植方便

- 缺点：

  - 相同的库文件数据可能在内存中被加载多份，消耗系统资源，浪费内存

  - 库文件更新需要重新编译项目文件，生成新的可执行程序，浪费时间



### 3.2 动态库

- 优点：
  - 可实现不同进程间的资源共享
  - 动态库升级简单，只需要替换库文件，无需重新编译应用程序
  - 程序猿可以控制何时加载动态库，不调用库函数动态库不会被加载
- 缺点：
  - 加载速度比静态库慢，以现在计算机的性能可以忽略
  - 发布程序需要提供依赖的动态库



