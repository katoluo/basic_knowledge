# Lambda表达式

文章引自 [:book:点](https://subingwen.cn/cpp/lambda/)

## 1. 基本用法

lambda 表达式是 C++11 最重要也是最常用的特性之一，这是现代编程语言的一个特点，lambda 表达式有如下的一些优点：

- 声明式的编程风格：就地匿名定义目标函数或函数对象，不需要额外写一个命名函数或函数对象。
- 简洁：避免了代码膨胀和功能分散，让开发更加高效。
- 在需要的时间和地点实现功能闭包，使程序更加灵活。

lambda 表达式定义了一个匿名函数，并且可以捕获一定范围内的变量。lambda 表达式的语法形式简单归纳如下：

```cpp
[capture list](parameter list) opt -> return value { function body }
```

- 捕获列表 []: 捕获一定范围内的变量
- 参数列表 (): 和普通函数的参数列表一样，如果没有参数参数列表可以省略不写。
- opt 选项， 不需要可以省略
  - mutable: 可以修改按值传递进来的拷贝（注意是能修改拷贝，而不是值本身）
  - exception: 指定函数抛出的异常，如抛出整数类型的异常，可以使用 throw ()
- 返回值类型：在 C++11 中，lambda 表达式的返回值是通过返回值后置语法来定义的
- 函数体：函数的实现，这部分不能省略，但函数体可以为空



## 2. 捕获列表

lambda 表达式的捕获列表可以捕获一定范围内的变量，具体使用方式如下：

- [] - 不捕捉任何变量
- [&] - 捕获外部作用域中所有变量，并作为引用在函数体内使用 (按引用捕获)
- [=] - 捕获外部作用域中所有变量，并作为副本在函数体内使用 (按值捕获)
  - 拷贝的副本在匿名函数体内部是只读的
- [=, &foo] - 按值捕获外部作用域中所有变量，并按照引用捕获外部变量 foo
- [bar] - 按值捕获 bar 变量，同时不捕获其他变量
- [&bar] - 按引用捕获 bar 变量，同时不捕获其他变量
- [this] - 捕获当前类中的 this 指针
  - 让 lambda 表达式拥有和当前类成员函数同样的访问权限
  - 如果已经使用了 & 或者 =, 默认添加此选项

下面通过一个例子，看一下初始化列表的具体用法：

```cpp
#include <iostream>
#include <functional>
using namespace std;

class Test
{
public:
    void output(int x, int y)
    {
        auto x1 = [] {return m_number; };                      // error
        auto x2 = [=] {return m_number + x + y; };             // ok
        auto x3 = [&] {return m_number + x + y; };             // ok
        auto x4 = [this] {return m_number; };                  // ok
        auto x5 = [this] {return m_number + x + y; };          // error
        auto x6 = [this, x, y] {return m_number + x + y; };    // ok
        auto x7 = [this] {return m_number++; };                // ok
    }
    int m_number = 100;
};
```

- x1：错误，没有捕获外部变量，不能使用类成员 m_number
- x2：正确，以值拷贝的方式捕获所有外部变量
- x3：正确，以引用的方式捕获所有外部变量
- x4：正确，捕获 this 指针，可访问对象内部成员
- x5：错误，捕获 this 指针，可访问类内部成员，没有捕获到变量 x，y，因此不能访问。
- x6：正确，捕获 this 指针，x，y
- x7：正确，捕获 this 指针，并且可以修改对象内部变量的值

```cpp
int main(void)
{
    int a = 10, b = 20;
    auto f1 = [] {return a; };                        // error
    auto f2 = [&] {return a++; };                     // ok
    auto f3 = [=] {return a; };                       // ok
    auto f4 = [=] {return a++; };                     // error
    auto f5 = [a] {return a + b; };                   // error
    auto f6 = [a, &b] {return a + (b++); };           // ok
    auto f7 = [=, &b] {return a + (b++); };           // ok

    return 0;
}
```

- f1：错误，没有捕获外部变量，因此无法访问变量 a
- f2：正确，使用引用的方式捕获外部变量，可读写
- f3：正确，使用值拷贝的方式捕获外部变量，可读
- f4：错误，使用值拷贝的方式捕获外部变量，可读不能写
- f5：错误，使用拷贝的方式捕获了外部变量 a，没有捕获外部变量 b，因此无法访问变量 b
- f6：正确，使用拷贝的方式捕获了外部变量 a，只读，使用引用的方式捕获外部变量 b，可读写
- f7：正确，使用值拷贝的方式捕获所有外部变量以及 b 的引用，b 可读写，其他只读

在匿名函数内部，需要通过 lambda 表达式的捕获列表控制如何捕获外部变量，以及访问哪些变量。默认状态下 lambda 表达式无法修改通过复制方式捕获外部变量，如果希望修改这些外部变量，需要通过引用的方式进行捕获。



## 3. 返回值

很多时候，lambda 表达式的返回值是非常明显的，因此在 C++11 中允许省略 lambda 表达式的返回值。

```cpp
// 完整的lambda表达式定义
auto f = [](int a) -> int
{
    return a+10;  
};

// 忽略返回值的lambda表达式定义
auto f = [](int a)
{
    return a+10;  
};
```

一般情况下，不指定 lambda 表达式的返回值，编译器会根据 return 语句自动推导返回值的类型，但需要注意的是`初始化列表不能用于返回值的自动推导`。

```cpp
// ok，可以自动推导出返回值类型
auto f = [](int i)
{
    return i;
}

// error，不能推导出返回值类型
auto f1 = []()
{
    return {1, 2};	// 初始化列表作为函数返回值
}
```



## 4. 函数本质

使用 lambda 表达式捕获列表捕获外部变量，如果希望去修改按值捕获的外部变量，那么应该如何处理呢？这就需要使用 mutable 选项，被mutable修改是lambda表达式就算没有参数也要写明参数列表，并且可以去掉按值捕获的外部变量的只读（const）属性。

```cpp
int a = 0;
auto f1 = [=] {return a++; };              // error, 按值捕获外部变量, a是只读的
auto f2 = [=]()mutable {return a++; };     // ok
```

最后再剖析一下为什么通过值拷贝的方式捕获的外部变量是只读的:

- lambda表达式的类型在C++11中会被看做是一个带operator()的类，即仿函数。
- 按照C++标准，lambda表达式的operator()默认是const的，一个const成员函数是无法修改成员变量值的。

mutable 选项的作用就在于取消 operator () 的 const 属性。

因为 lambda 表达式在 C++ 中会被看做是一个仿函数，因此可以使用std::function和std::bind来存储和操作lambda表达式：

```cpp
#include <iostream>
#include <functional>
using namespace std;

int main(void)
{
    // 包装可调用函数
    std::function<int(int)> f1 = [](int a) {return a; };
    // 绑定可调用函数
    std::function<int(int)> f2 = bind([](int a) {return a; }, placeholders::_1);

    // 函数调用
    cout << f1(100) << endl;
    cout << f2(200) << endl;
    return 0;
}
```

对于没有捕获任何变量的 lambda 表达式，还可以转换成一个普通的函数指针：

```cpp
using func_ptr = int(*)(int);
// 没有捕获任何外部变量的匿名函数
func_ptr f = [](int a)
{
    return a;  
};
// 函数调用
f(1314);
```

