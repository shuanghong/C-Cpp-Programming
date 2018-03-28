---
title: 字符串,字符数组,以及字符串指针等相关的操作
date: 2016-9-17 08:55:29 
categories: C++
toc: true
---

[源码](https://github.com/shuanghong/C-Cpp-Programming/blob/master/char_string/CharStringOperation.cpp)
## C 中对字符串的处理: 字符数组，字符指针

* 字符数组

 1. 定义与初始化  
char c[10] = {'C', ' ', 'L', 'a', 'n', 'g', 'u', 'a', 'g', 'e'};  
char c[11] = {"C Language"};  
char c[11] = "C Language";  
char c[] = "C Language";  
定义时初始化可以不指定数组长度, 如 char c[] = "C Language"; 编译器自动处理长度为 11.  
如果不作初始化赋值, 则必须指定长度, 如 char c[]; 是非法的.  
	
 2. 结束标志  
C 中总是以 '\0'作为串的结束符, ASCII码为NUL. '\0'由编译器自动加上.  
由于采用了'\0'标志, 字符串赋初值时无须指定数组的长度, 字符串处理函数遇到NUL时会认为字符串已经结束.  
用字符串赋值比用字符逐个赋值要多占一个字节, 用于存放结束标志'\0', 对于char c[] = "C Language" 其实际存放为
		|C| |L|a|n|g|u|a|g|e|\0|  
如果定义 char c[10] = "C Language"; 编译器会提示初始化的字符串太长.   
而 char c[10] = {'C', ' ', 'L', 'a', 'n', 'g', 'u', 'a', 'g', 'e'}; 则没有问题.  

			--- testNul()
	
 3. 求度, sizeof 与 strlen  
区别:  
a. sizeof 是运算符, 可以用类型(char/int)作参数; strlen 是函数, 只能用char*做参数, 且必须是以'\0'结尾的.  
b. 数组传递给 sizeof 作参数时不退化, 仍然代表整个数组, 传递给strlen时则退化为指针处理.  
	大部分编译程序在编译时就把 sizeof 计算过了, 是类型或变量的长度, 这就是sizeof(x)可以用来定义数组维数的原因.  
c. sizeof 计算的是分配的字符数组所占的实际内存空间的大小, 不受里面存储的内容改变, 即使在字符数组没有终止符'\0' 的	时候, 也能够计算出数组长度.  
	strlen 计算字符串的长度, 以'\0'为字符串结束.  
					
			--- calCharArrayLength()  
所以如果用字符初始化数组,  
char c[11] = {'C', ' ', 'L', 'a', 'n', 'g', 'u', 'a', 'g', 'e'};  
char c[11] = {'C', ' ', 'L', 'a', 'n', 'g', 'u', 'a', 'g', 'e', '\0'};  
char c[] = {'C', ' ', 'L', 'a', 'n', 'g', 'u', 'a', 'g', 'e', '\0'};  
三者等价, 长度均为 10.  
char c[10] = {'C', ' ', 'L', 'a', 'n', 'g', 'u', 'a', 'g', 'e'};  
char c[] = {'C', ' ', 'L', 'a', 'n', 'g', 'u', 'a', 'g', 'e'};  
两者等价, 长度未知, 因为没有结束符. 实际中不应使用, 容易出现数组越界, 导致非法访问.  
demo中c1[10] strlen = 20, sizeof = 10, 说明字符串长度为20,但实际分配的内存大小为10.  	        
如果用字符串初始化数组, 如 char c[] = "C Language"; 计算字符串长度一定要用 strlen

* 字符指针

 1. 定义与初始化  
char *string_ptr = "C language";	// 用字符串初始化  
char *string[] = "C language";  
char *string_ptr = string;			// 用字符数组初始化  
ps. 对于 char *string_ptr = "C language"; 在C++11 中则使用 const char *string_ptr = "C language"; 否则编译出错.  
参考 [http://stackoverflow.com/questions/20944784/why-is-conversion-from-string-constant-to-char-valid-in-c-but-invalid-in-c  ](http://stackoverflow.com/questions/20944784/why-is-conversion-from-string-constant-to-char-valid-in-c-but-invalid-in-c  )  

			--- charPtrInit()

 2. 与字符数组的区别  
字符数组是一个数组, 每个元素的值都可以改变; 而字符串指针指向的是一个**常量字符串, 它被存放在程序的静态数据区, 一旦定义就不能改变**.  

			--- modifyCharPtrValue()  
注: *ptr 指向的内容不能改变, 但是 ptr 指针本身可以改变, 可以指向其他的字符串.

 3. 对字符串系列操作  
参考  
[http://c.biancheng.net/cpp/u/hs2/](http://c.biancheng.net/cpp/u/hs2/)  
[http://www.cplusplus.com/reference/cstring/strcpy/?kw=strcpy](http://www.cplusplus.com/reference/cstring/strcpy/?kw=strcpy)  
通用的建议是 strncpy() 代替 strcmp(),  strncat() 代替 strcat(), strncmp() 代替 strcmp().

## C++ 中对字符串的处理: string 类
C++ 增强了对字符串的支持，既可以使用C风格的字符数组, 字符串，还可以使用内置的数据类型 string 类.  

* 初始化  
string 类有多种初始化方式, 详尽的参考 [http://www.cplusplus.com/reference/string/string/string/](http://www.cplusplus.com/reference/string/string/string/)  
常用的是直接用字符串初始化, 如 std::string s = "c++ language";

* 与 const char* 之间的互转
		
		---stringToCharPtr()

* 与 char[] 之间的互转

		---stringTocharArray()

