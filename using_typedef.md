#### 类型别名

类型别名（type alias）是一个名字，它是某种类型的同义词。使用类型别名有很多好处，它让复杂的类型名字变得简单明了、易于理解和使用，还有助于程序员清楚地知道使用该类型的真实目的。

**typedef:**

```cpp
typedef double wages;	// wages 是 double 的同义词
typedef wages base, *p;	// base 是 double 的同义词，p是double*的同义词
```

**using:**

c++11新标准规定了一种新方法using。

```cpp
using SI = Sales_item;
```



**指针、常量和类型别名**

如果某个类型别名指代的是复合类型或常量，那么把它用到声明语句里就会产生意想不到的后果。例如下面的声明语句用到了类型`pstring`，它实际上是类型`char*`的别名：

```cpp
typedef char *pstring;
const pstring cstr  = 0;	// cstr是指向char的常量指针
const pstring *ps;	// ps是一个指针，它的对象是指向char的常量指针
```

上述两条声明语句的基本数据类型都是`const pstring`，和过去一样，`const`是对给定类型的修饰。`pstring`实际上是指向`char`的指针，因此，`const pstring`就是指向`char`的常量指针，而非指向常量字符的指针。

遇到一条使用了类型别名的声明语句时，人们往往会错误地尝试把类型别名替换成它本来的样子，以理解该语句的含义：

```cpp
const char *cstr = 0;	// 是对const pstring cstr的错误理解
```

再强调一遍：这种理解是错误的。声明语句中用到`pstring`时，其基本数据类型是指针。可是用`char*`重写了声明语句后，数据类型就变成了声明符的一部分。这样改写的结果是，`const char`生了基本数据类型。前后两种声明含义截然不同，前者声明了一个指向`char`的常量指针，改写后的形式则声明了一个指向`const char`的指针。

