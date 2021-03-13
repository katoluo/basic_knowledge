# Makefile



`make `是一个命令工具，是一个解释 `makefile` 中指令的命令工具，一般来说，大多数的 IDE 都有这个命令，比如：Visual C++ 的 `nmake`，QtCreator 的 `qmake` 等。

make 工具在构造项目的时候需要加载一个叫做 makefile 的文件，makefile 关系到了整个工程的编译规则。一个工程中的源文件不计数，其按类型、功能、模块分别放在若干个目录中，makefile 定义了一系列的规则来指定哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至于进行更复杂的功能操作，因为 makefile 就像一个 Shell 脚本一样，其中也可以执行操作系统的命令。

**makefile 带来的好处就是 ——“自动化编译”，一旦写好，只需要一个 make 命令，整个工程完全自动编译，极大的提高了软件开发的效率。**



## 1. 规则

Makefile 的框架是由规则构成的。make 命令执行时先在 Makefile 文件中查找各种规则，对各种规则进行解析后运行规则。规则的基本格式为：

```makefile
# 每条规则的语法格式:
target1,target2...: depend1, depend2, ...
	command
	......
	......

```

- 命令(command): 当前这条规则的动作，一般情况下这个动作就是一个 shell 命令
  - 例如：通过某个命令编译文件、生成库文件、进入目录等。
  - 动作可以是多个，每个命令前必须有一个Tab缩进并且独占占一行。
- 依赖(depend): 规则所必需的依赖条件，在规则的命令中可以使用这些依赖。
  - 例如：生成可执行文件的目标文件（*.o）可以作为依赖使用
  - 如果规则的命令中不需要任何依赖，那么规则的依赖可以为空
  - 当前规则中的依赖可以是其他规则中的某个目标，这样就形成了规则之间的嵌套
  - 依赖可以根据要执行的命令的实际需求，指定很多个
- 目标(target)： 规则中的目标，这个目标和规则中的命令是对应的
  - 通过执行规则中的命令，可以生成一个和目标同名的文件
  - 规则中可以有多个命令，因此可以通过这多条命令来生成多个目标，所有目标也可以有很多个
  - 通过执行规则中的命令，可以只执行一个动作，不生成任何文件，这样的目标被称为伪目标



## 2. 工作原理

### 2.1 规则的执行

### 2.2 文件的时间戳

### 2.3 自动推导



## 3. 变量

使用 Makefile 进行规则定义的时候，为了写起来更加灵活，我们可以在里边使用变量。makefile 中的变量分为三种：**自定义变量**，**预定义变量**和**自动变量**。



### 3.1 自定义变量

用 Makefile 进行规则定义的时候，用户可以定义自己的变量，称为用户自定义变量。makefile 中的变量是没有类型的，直接创建变量然后给其赋值就可以了。

```makefile
# 错误, 只创建了变量名, 没有赋值
变量名 
# 正确, 创建一个变量名并且给其赋值
变量名=变量值
```

在给 makefile 中的变量赋值之后，如何在需要的时候将变量值取出来呢？

```makefile
# 如果将变量的值取出?
$(变量的名字)

# 举例 add.o  div.o  main.o  mult.o  sub.o
# 定义变量并赋值
obj=add.o  div.o  main.o  mult.o  sub.o
# 取变量的值
$(obj)
```

自定义变量使用举例：

```makefile
# 这是一个规则，普通写法
calc:add.o  div.o  main.o  mult.o  sub.o
        gcc  add.o  div.o  main.o  mult.o  sub.o -o calc
        
# 这是一个规则，里边使用了自定义变量
obj=add.o  div.o  main.o  mult.o  sub.o
target=calc
$(target):$(obj)
        gcc  $(obj) -o $(target)
```



### 3.2 预定义变量

在 Makefile 中有一些已经定义的变量，用户可以直接使用这些变量，不用进行定义。在进行编译的时候，某些条件下 Makefile 会使用这些预定义变量的值进行编译。这些预定义变量的名字一般都是大写的，经常采用的预定义变量如下表所示：

|  变量名  |             含义             |  默认值  |
| :------: | :--------------------------: | :------: |
|    AR    |  生成静态库库文件的程序名称  |    ar    |
|    AS    |       汇编编译器的名称       |    as    |
|    CC    |      C 语言编译器的名称      |    cc    |
|   CPP    |     C 语言预编译器的名称     | $(CC) -E |
|   CXX    |     C++ 语言编译器的名称     |   g++    |
|    FC    |   FORTRAN 语言编译器的名称   |   f77    |
|    RM    |      删除文件程序的名称      |  rm -f   |
| ARFLAGS  |  生成静态库库文件程序的选项  | 无默认值 |
| ASFLAGS  |   汇编语言编译器的编译选项   | 无默认值 |
|  CFLAGS  |    C 语言编译器的编译选项    | 无默认值 |
| CPPFLAGS |    C 语言预编译的编译选项    | 无默认值 |
| CXXFLAGS |   C++ 语言编译器的编译选项   | 无默认值 |
|  FFLAGS  | FORTRAN 语言编译器的编译选项 | 无默认值 |



```makefile
# 这是一个规则，普通写法
calc:add.o  div.o  main.o  mult.o  sub.o
        gcc  add.o  div.o  main.o  mult.o  sub.o -o calc
        
# 这是一个规则，里边使用了自定义变量和预定义变量
obj=add.o  div.o  main.o  mult.o  sub.o
target=calc
CFLAGS=-O3 # 代码优化
$(target):$(obj)
        $(CC)  $(obj) -o $(target) $(CFLAGS)
```



### 3.3 自动变量

Makefile 中的变量除了用户自定义变量和预定义变量外，还有一类自动变量。Makefile 中的规则语句中经常会出现目标文件和依赖文件，自动变量用来代表这些规则中的目标文件和依赖文件，并且它们只能在规则的命令中使用。

下表中是一些常见的自动变量。

| 变量 |                             含义                             |
| :--: | :----------------------------------------------------------: |
|  $*  |          表示目标文件的名称，不包含目标文件的扩展名          |
|  $+  | 表示所有的依赖文件，这些依赖文件之间以空格分开，按照出现的先后为顺序，其中可能 包含重复的依赖文件 |
|  $<  |               表示依赖项中第一个依赖文件的名称               |
|  $?  | 依赖项中，所有比目标文件时间戳晚的依赖文件，依赖文件之间以空格分开 |
|  $@  |              表示目标文件的名称，包含文件扩展名              |
|  $^  |    依赖项中，所有不重复的依赖文件，这些文件之间以空格分开    |

下面几个例子，演示一下自动变量如何使用。

```makefile
# 这是一个规则，普通写法
calc:add.o  div.o  main.o  mult.o  sub.o
        gcc  add.o  div.o  main.o  mult.o  sub.o -o calc
        
# 这是一个规则，里边使用了自定义变量
# 使用自动变量, 替换相关的内容
calc:add.o  div.o  main.o  mult.o  sub.o
	gcc $^ -o $@ 			# 自动变量只能在规则的命令中使用
```



## 4. 模式匹配

在介绍概念之前，先读一下下面的这个 makefile 文件:

```makefile
calc:add.o  div.o  main.o  mult.o  sub.o
        gcc  add.o  div.o  main.o  mult.o  sub.o -o calc
# 语法格式重复的规则, 将 .c -> .o, 使用的命令都是一样的 gcc *.c -c
add.o:add.c
        gcc add.c -c

div.o:div.c
        gcc div.c -c

main.o:main.c
        gcc main.c -c

sub.o:sub.c
        gcc sub.c -c

mult.o:mult.c
        gcc mult.c -c
```



在阅读过程中能够发现从第二个规则开始到第六个规则做的是相同的事情，但是由于文件名不同不得不在文件中写出多个规则，这就让 makefile 文件看起来非常的冗余，我们可以将这一系列的相同操作整理成一个模板，所有类似的操作都通过模板去匹配 makefile 会因此而精简不少，只是可读性会有所下降。

这个规则模板可以写成下边的样子，这种操作就称之为模式匹配。

```makefile
# 模式匹配 -> 通过一个公式, 代表若干个满足条件的规则
# 依赖有一个, 后缀为.c, 生成的目标是一个 .o 的文件, % 是一个通配符, 匹配的是文件名
%.o:%.c
	gcc $< -c
```



## 5. 函数

makefile 中有很多函数并且所有的函数都是有返回值的。makefile 中函数的格式和 C/C++ 中函数也不同，其写法是这样的： $(函数名 参数1, 参数2, 参数3, ...)，主要目的是让我们能够快速方便的得到函数的返回值。

这里为大家介绍两个 makefile 中使用频率比较高的函数：`wildcard` 和 `patsubst`。



### 5.1 wildcard

这个函数的主要作用是获取指定目录下指定类型的文件名，其返回值是以空格分割的、指定目录下的所有符合条件的文件名列表。函数原型如下：

```makefile
# 该函数的参数只有一个, 但是这个参数可以分成若干个部分, 通过空格间隔
$(wildcard PATTERN...)
	参数:	指定某个目录, 搜索这个路径下指定类型的文件，比如： *.c
```

- 参数功能:
  - PATTERN 指的是某个或多个目录下的对应的某种类型的文件，比如当前目录下的.c 文件可以写成 *.c
  - 可以指定多个目录，每个路径之间使用空格间隔
- 返回值：
  - 得到的若干个文件的文件列表， 文件名之间使用空格间隔
  - 示例：`$(wildcard *.c ./sub/*.c)`
    - 返回值格式: a.c b.c c.c d.c e.c f.c ./sub/aa.c ./sub/bb.c



函数使用举例:

```makefile
# 使用举例: 分别搜索三个不同目录下的 .c 格式的源文件
src = $(wildcard /home/robin/a/*.c /home/robin/b/*.c *.c)  # *.c == ./*.c
# 返回值: 得到一个大的字符串, 里边有若干个满足条件的文件名, 文件名之间使用空格间隔
/home/robin/a/a.c /home/robin/a/b.c /home/robin/b/c.c /home/robin/b/d.c e.c f.c
```



### 5.2 patsubst

这个函数的功能是按照指定的模式替换指定的文件名的后缀，函数原型如下:

```makefile
# 有三个参数, 参数之间使用 逗号间隔
$(patsubst <pattern>,<replacement>,<text>)
```

- 参数功能：
  - pattern: 这是一个模式字符串，需要指定出要被替换的文件名中的后缀是什么
    - 文件名和路径不需要关心，因此使用 % 表示即可 [通配符是 %]
    - 在通配符后边指定出要被替换的后缀，比如: %.c, 意味着 .c 的后缀要被替换掉
  - replacement: 这是一个模式字符串，指定参数 pattern 中的后缀最终要被替换为什么
    - 还是使用 % 来表示参数 pattern 中文件的路径和名字
    - 在通配符 % 后边指定出新的后缀名，比如: %.o 这表示原来的后缀被替换为 .o
  - text: 该参数中存储这要被替换的原始数据
  - 返回值:
    - 函数返回被替换过后的字符串。



函数使用举例:

```makefile
src = a.cpp b.cpp c.cpp e.cpp
# 把变量 src 中的所有文件名的后缀从 .cpp 替换为 .o
obj = $(patsubst %.cpp, %.o, $(src)) 
# obj 的值为: a.o b.o c.o e.o
```



## 6. makefile 的编写



```makefile
# 添加自定义变量 -> makefile中注释前 使用 # 
obj=add.o  div.o  main.o  mult.o  sub.o
target=calc

$(target):$(obj)
        gcc $(obj)  -o $(target)

%.o:%.c
        gcc $< -c
```

> 这个版本的优点：文件精简不少，变得简洁了
>
> 这个版本的缺点：变量 obj 的值需要手动的写出来，如果需要编译的项目文件很多，都用手写出来不现实
>
> 改进方式：在 makefile 中使用函数



```makefile
# 添加自定义变量 -> makefile中注释前 使用 # 
# 使用函数搜索当前目录下的源文件 .c
src=$(wildcard *.c)
# 将源文件的后缀替换为 .o
# % 匹配的内容是不能被替换的, 需要替换的是第一个参数中的后缀, 替换为第二个参数中指定的后缀
# obj=$(patsubst %.cpp, %.o, $(src)) 将src中的关键字 .cpp 替换为 .o
obj=$(patsubst %.c, %.o, $(src))
target=calc

$(target):$(obj)
        gcc $(obj)  -o $(target)

%.o:%.c
        gcc $< -c
```

> 这个版本的优点：解决了自动加载项目文件的问题，解放了双手
>
> 这个版本的缺点：没有文件删除的功能，不能删除项目编译过程中生成的目标文件（*.o）和可执行程序*
>
> 改进方式：在 makefile 文件中添加新的规则用于删除生成的目标文件（*.o）和可执行程序



```makefile
# 添加自定义变量 -> makefile中注释前 使用 # 
# 使用函数搜索当前目录下的源文件 .c
src=$(wildcard *.c)
# 将源文件的后缀替换为 .o
obj=$(patsubst %.c, %.o, $(src))
target=calc
# obj 的值 xxx.o xxx.o xxx.o xx.o
$(target):$(obj)
        gcc $(obj)  -o $(target)

%.o:%.c
        gcc $< -c

# 添加规则, 删除生成文件 *.o 可执行程序
# 这个规则比较特殊, clean根本不会生成, 这是一个伪目标
clean:
        rm $(obj) $(target)
```

>  这个版本的优点：添加了新的规则（16 行）用于文件的删除，直接 make clean 就可以执行规则中的删除命令了
>
> 这个版本的缺点：在下面有具体的问题演示和分析
>
> 改进方式：在 makefile 文件中声明 clean 是一个伪目标，让 make 放弃对它的时间戳检测。

正常情况下这个版本的 makefile 是可以正常工作的，但是我们如果在这个项目目录中添加一个叫做 clean 的文件（和规则中的目标名称相同），再进行 make clean 发现这个规则就不能正常工作了。

```bash
# 在项目目录中添加一个叫 clean的文件, 然后在 make clean 这个规则中的命令就不工作了
$ ls
add.c  calc   div.c  head.h  main.o    mult.c  sub.c
add.o  div.o  main.c  makefile  mult.o  sub.o  clean  ---> 新添加的

# 使用 makefile 中的规则删除生成的目标文件和可执行程序
$ make clean
make: 'clean' is up to date. 

# 查看目录, 发现相关文件并没有被删除, make clean 失败了
$ ls
add.c  calc   div.c  head.h  main.o    mult.c  sub.c
add.o  clean  div.o  main.c  makefile  mult.o  sub.o
```

> 这个问题的关键点在于 clean 是一个伪目标，不对应任何实体文件，在前边讲关于文件时间戳更新问题的时候说过，如果目标不存在规则的命令肯定被执行， 如果目标文件存在了就需要比较规则中目标文件和依赖文件的时间戳，满足条件才执行规则的命令，否则不执行。
>
> 解决这个问题需要在 makefile 中声明 clean 是一个伪目标，这样 make 就不会对文件的时间戳进行检测，规则中的命令也就每次都会被执行了。
>
> 在 makefile 中声明一个伪目标需要使用 .PHONY 关键字，声明方式为: .PHONY:伪文件名称
>



### 6.6 最终版

```makefile
# 添加自定义变量 -> makefile中注释前 使用 # 
# 使用函数搜索当前目录下的源文件 .c
src=$(wildcard *.c)
# 将源文件的后缀替换为 .o
obj=$(patsubst %.c, %.o, $(src))
target=calc

$(target):$(obj)
        gcc $(obj)  -o $(target)

%.o:%.c
        gcc $< -c

# 添加规则, 删除生成文件 *.o 可执行程序
# 声明clean为伪文件
.PHONY:clean
clean:
        # shell命令前的 - 表示强制这个指令执行, 如果执行失败也不会终止
        -rm $(obj) $(target) 
        echo "hello, 我是测试字符串"
```



## 7. 练习题

如果觉得上边讲的内容看懂了，可以试着根据这个目录结构写出其对应的 makefile 文件。



```bash
# 目录结构
.
├── include
│   └── head.h	==> 头文件, 声明了加减乘除四个函数
├── main.c		==> 测试程序, 调用了head.h中的函数
└── src
    ├── add.c	==> 加法运算
    ├── div.c	==> 除法运算
    ├── mult.c  ==> 乘法运算
    └── sub.c   ==> 减法运算
```



根据上边的项目目录结构编写的 makefile 文件如下:

```makefile
# 最终的目标名 app
target = app
# 搜索当前项目目录下的源文件
src=$(wildcard *.c ./src/*.c)
# 将文件的后缀替换掉 .c -> .o
obj=$(patsubst %.c, %.o, $(src))
# 头文件目录
include=./include

# 第一条规则
# 依赖中都是 xx.o yy.o zz.o
# gcc命令执行的是链接操作
$(target):$(obj)
        gcc $^ -o $@

# 模式匹配规则
# 执行汇编操作, 前两步: 预处理, 编译是自动完成
%.o:%.c
        gcc $< -c -I $(include) -o $@

# 添加一个清除文件的规则
.PHONY:clean

clean:
        -rm $(obj) $(target) -f
```



















