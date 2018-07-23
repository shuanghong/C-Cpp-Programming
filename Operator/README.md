# 运算符

## 逻辑运算符短路

* 对于逻辑或运算符 ||, 若第一运算数为 true, 则不求值第二运算数.

		int a = 1, b = 1, c = 2, d = 3;
	
	    if ((a == b) || (b == c) && (c > d))
	    {
	        printf("a = %d, b = %d\n", a, b);
	    }
	    else 
	        printf("c = %d, d = %d\n", c, d);

	output:

		a = 1, b = 1

	代码 if ((a == b) || (b == c)) 中, (a == b) 条件成立, 后面的逻辑判断被短路, 即使添加 && (c > d), 条件仍然成立。   
	正确的写法是 将逻辑或的部分当作一个整体.

		if (((a == b) || (b == c)) && (c > d)) 或者 if ((c > d) && ((a == b) || (b == c)))

	**这个在新写代码时可能会注意到, 但是如果是在已有逻辑上再添加新的判断条件, 很可能被忽视。**

	PS. operator&& 和 operator|| 的短路求值属性不应用于重载, 重载的运算符表现类似函数调用, 并始终求值两个运算数

参考 [http://zh.cppreference.com/w/cpp/language/operator_logical](http://zh.cppreference.com/w/cpp/language/operator_logical)

* 对于逻辑与运算符 &&, 若第一运算数为 false, 则不求值第二运算数.

	比如下面的代码防止除 0
	
		if (b != 0 && a/b > 1)  

* 如果不想要短路的效果, 使用运算符 &, |

	运算符 & 或者 |, 当操作数是 bool 类型时, 计算操作数的逻辑与、或; 当操作数是数值类型时, 执行按位与、或.

		int main( )
		{
			int a = 1, b = 2, c = 2, d = 3;
			
			if ((a > b) & ((c = a+b) > d))
			{
			   printf(" c = %d\n", c);
			}
			else 
			    printf("c = %d\n", c);
			    
			return 0;
		}

	output:

		c = 3

## 运算符优先级 ? :

	int a = 1, b = 2;
    int t = 1;

    int val1 = a + t ? a : b;	// + 优先级高于 ?：, 结果为 a
    int val2 = a + (t ? a : b); 

    printf("val1 = %d, val2 = %d\n", val1, val2);
output:

	val1 = 1, val2 = 2

运算符 + 优先级高于 ?:, 所以如果是想得到 a + 的效果, 三目运算加上括号.


		
	
