#### 使用=default

可以通过将拷贝控制成员定义为=default来显示要求编译器生成合成的版本：

```cpp
class Sales_data {
public:
    // 拷贝控制成员；使用default
    Sales_data() = default;
    Sales_data(const Sales_data&) = default;
    Sales_data& operator= (const Sales_data&);
    ~Sales_data() = default;
};
Sales_data& Sales_data::operator= (const Sales_data&) = default;
```

当不希望合成的成员是内联函数，应该只对成员的类外定义使用=default，就像对拷贝赋值符所做的那样。

> 只能对具有合成版本的成员函数使用=default（即，默认构造函数、拷贝构造函数、拷贝赋值运算符、移动构造函数和移动赋值运算符）



#### 阻止拷贝

对有些类来说，拷贝构造函数和拷贝赋值运算符没有合理的意义。在此情况下，定义类时必须采用某种机制阻止拷贝或赋值。

**定义删除的函数**

在新标准下，可以通过将拷贝构造函数和拷贝赋值运算符定义为删除的函数来阻止拷贝。

删除的函数是这样一种函数：虽然声明了它们，但不能以任何方式使用它们。

在函数的参数列表后面加上=delete来指出希望将它定义为删除的：

```cpp
class NOCopy {
    NoCopy() = default;	// 使用合成的默认构造函数
    NoCopy(const NoCopy&) = delete;	// 阻止拷贝
    NoCopy& operator=(const NoCopy&) = delete;	// 阻止赋值
    ~NoCopy() = default;	// 使用合成的析构函数
};
```

- 与=default不同，=delete必须出现在函数第一次声明的时候。

- 可以对任何函数指定=delete，只能对可以合成的默认构造函数或拷贝构造成员使用=default

> 当析构函数被定义为删除的函数时，编译器不允许定义该类型的变量或创建该类的临时对象。可以动态分配这种类型的对象，但不能释放这些对象。
>
> 合成的拷贝控制成员可能是删除的



**private拷贝控制**

在新标准发布之前，类 是通过将其拷贝构造函数和拷贝赋值运算符声明为private的来阻止拷贝：

```cpp
class PrivateCopy {
    PricateCopy(const PrivateCopy&);
    PrivateCopy& operator= (const PrivateCopy&);
public:
    PrivateCopy() = default;
    ~PrivateCopy();
}
```

