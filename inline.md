# inline内联函数



> 通常，函数调用都有一定的开销，因为函数的调用过程包括建立调用、传递参数、跳转到函数代码并返回。
>
> 程序执行到函数调用指令时，程序将在函数调用后立即存储该指令的内存地址，并将函数参数复制到堆栈，跳到标记函数起点的内存单元，执行函数代码（也许还需要将返回值放入到寄存器中），然后跳回到地址被保存的指令处。

#### 特征

- 相当于把内联函数里面的内容写在调用内联函数处
- 相当于不用执行进入函数的步骤，直接执行函数体
- 相当于宏，却比宏多了类型检查，真正具有函数特性
- 编译器一般不內联包含循环、递归、switch等复杂操作的内联函数
- 在类声明中定义的函数，除了虚函数的其他函数都会自动隐式地当成内联函数



#### 编译器对inline函数的处理步骤

1. 将`inline`函数体复制到`inline`函数调用点处
2. 为所有`inline`函数中的局部变量分配内存空间
3. 将`inline`函数的输入参数和返回值映射到调用方法的局部变量空间中
4. 如果`inline`函数有多个返回点，将其转变为`inline`函数代码块末尾的分支（使用GOTO）



#### 优缺点

**优点：**

- 内联函数同宏函数一样将在被调用处进行代码展开，省去了参数压栈、栈帧开辟与回收，结果返回等，从而提高程序运行速度
- 内联函数相比宏函数来说，在代码展开时，会做安全检查或自动类型转换（同普通函数），而宏定义则不会
- 在类中声明同时定义的成员函数，自动转化为内联函数，因此内联函数可以访问类的成员变量，宏定义则不能
- 内联函数在运行时可调试，而宏定义不可以



**缺点：**

- 代码膨胀。内联是以代码膨胀（复制）为代价，消除函数调用带来的开销。如果执行函数代码的时间比处理函数调用机制的时间长，则节省的时间只占整个过程的很小一部分，效率的收获很少。另一方面，每一处内联函数的调用都要复制代码，将使程序的总代码量增大，消耗更多的内存空间
- `inline `函数无法随着函数库升级而升级。`inline` 函数的改变需要重新编译，不像 `non-inline` 可以直接链接
- 是否内联，程序员不可控。内联函数只是对编译器的建议，是否对函数内联，决定权在于编译器


