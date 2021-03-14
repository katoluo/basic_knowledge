### :smile: C/C++

- [内联函数](https://github.com/katoluo/basic_knowledge/blob/master/inline.md)



- **构造函数初始值列表**

  构造函数的初始值有时必不可少。如果类的成员是`const`或者是**引用**的话，必须将其初始化。类似的，当成员属于某种类类型且该类型没有定义默认构造函数时，也必须将这个成员初始化。

- **拷贝构造函数**

  - 为什么参数必须是当前类的引用呢？

    在函数调用中，具有非引用类型的参数要进行拷贝初始化。如果参数不是引用类型，为了调用拷贝构造函数，则必须拷贝它的实参，但为了拷贝实参，有需要调用拷贝构造函数，如此无限循环。

  - 为什么是`const`引用呢？

    - 拷贝构造函数的目的是用其他对象的数据来初始化当前对象，并没有期望改变其他对象的数据，添加`const`限制后，这个含义更明确了
    - 另外一个原因是，添加`const`限制后，可以将`const`对象和非`const`对象传递给形参了



