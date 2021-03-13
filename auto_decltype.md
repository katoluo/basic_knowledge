#### auto 类型说明符

编程时常常需要把表达式的值赋值给变量，这就要求 在声明变量的时候清除地知道表达式的类型。

C++11新标准引入了**auto** 类型说明符，`auto`让编译器通过初始值来推算变量的类型。

- `auto`定义的变量必须有初始值

```cpp
// 由val1和val2相加的记过可以推断出item的类型
auto item = val1 + val2;	// item初始化为val1和val2相加的结果
```

- 一条声明语句只能有一个基本数据类型

```cpp
auto i = 0, *p = &i;	// 正确：i是整数、p是整型指针
auto sz = 0, pi = 3.14;	// 错误：sz和pi的类型不一致
```

- 使用引用其实是使用引用的对象，特别是当引用被用作初始值时，真正参与初始化的其实是引用对象的值

```cpp
int i = 0, &r = i;
auto a = r;	// a为int类型
```

- `auto`一般会忽略掉**顶层const**，同时**底层const**则会保留下来，比如当初始值是一个指向常量的指针时

```cpp
const int ci = i, &cr = ci;
auto b = ci;	// ci是顶层const,所以b为int
auto c = cr;	// cr是ci的别名，ci本身是一个顶成const，所以c是int类型
auto d = &i;	// d是int指针
auto e = &ci;	// e是一个指向整数常量的指针(对常量对象取地址是一种底层const)
```



#### decltype类型指示符

有时希望从表达式的类型推断出要定义的变量的类型，但是不想用该表达式的值初始化变量。

C++11新标准引入了类型说明符**decltype**，它的作用是选择并返回操作数的数据类型。

在此过程中，编译器分析表达式并得到它的类型，却不实际计算表达式的值。

- 如果decltype使用的表达式是一个变量，则返回该变量的类型（包括**顶层const**和**引用**在内）

```cpp
const int ci = 0, &cr = ci;
decltype(ci) x = 0; // x的类型是const int
decltype(cr) y = x; // y的类型是const int&，必须初始化，绑定到变量x
decltype(cr) z;		// 错误，z是const int&，必须初始化
```

- 如果decltype使用的表达式不是一个变量，则decltype返回表达式结果对应的类型

```cpp
int i = 42, *p = &i, &r = i;
decltype(r + 0) b;	// 加法的结果为int类型，正确
decltype(*p) c;		// 解引用，返回引用类型，必须初始化，错误
```

- 如果decltype所用的表达式来说，如果变量加上了一对括号，则得到的类型与不加括号时会有不同。

```cpp
// decltype的表达式如果是加上了括号的变量，结果将是引用
decltype((i)) d;	// 错误：d是int&，必须初始化
decltype(i) e;		// 正确：e是一个(未初始化的)int
```

> 切记：decltype((variable))(注意是双层括号)的结果永远是引用，而decltype(variable)结果只有当variable本身就是一个引用时才是引用。



