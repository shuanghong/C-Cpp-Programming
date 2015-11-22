/*******************************************************************
 * 说明: c/c++ 编程中的对字符串处理的总结
 *
 * 作者: hongssun
 * 日期: 2015/11/22
 * 
 *******************************************************************/
#include <stdio.h>
#include <string.h>

void testNul(void)
{
    char c1[10] = {'C', ' ', 'L', 'a', 'n', 'g', 'u', 'a', 'g', 'e'};
    //char c[10] = "C Language";
    char c2[11] = "C Language";

}


void calCharArrayLength(void)
{
    char c1[10] = {'C', ' ', 'L', 'a', 'n', 'g', 'u', 'a', 'g', 'e'};   // without NULL '\0'
    char c2[11] = {'C', ' ', 'L', 'a', 'n', 'g', 'u', 'a', 'g', 'e'};   // with c2[10] = '\0'
    char c3[11] = {'C', ' ', 'L', 'a', 'n', 'g', 'u', 'a', 'g', 'e', '\0'};   // with NULL '\0'
    char c4[] = "C Language";

    printf("c1 strlen length = %d\n", strlen(c1));
    printf("c1 sizeof length = %d\n", sizeof(c1));

    printf("c2 strlen length = %d\n", strlen(c2));
    printf("c2 sizeof length = %d\n", sizeof(c2));

    printf("c3 strlen length = %d\n", strlen(c3));
    printf("c3 sizeof length = %d\n", sizeof(c3));

    printf("c4 strlen length = %d\n", strlen(c4));
    printf("c4 sizeof length = %d\n", sizeof(c4));  // with '\0'
/*******************************************************************
 * 
c1 strlen length = 20
c1 sizeof length = 10
c2 strlen length = 10
c2 sizeof length = 11
c3 strlen length = 10
c3 sizeof length = 11
(c2 == c3)

c4 strlen length = 10
c4 sizeof length = 11
 *
 *******************************************************************/

}


void charPtrInit()
{
    //char *string_ptr = "C language";
    const char *string_ptr = "C language";
    printf("%s\n", string_ptr);

}

void modifyCharPtrValue(void)
{
    char str[11] = "C language";
    char *str_ptr = str;
    *str_ptr = 'D';           // modify the first char

    printf("str = %s\n", str);

    const char *string_ptr = "C language";
    // *string_ptr = "D language"; // error
    string_ptr = str;
    printf("string_ptr = %s\n", string_ptr);
}




int main(int argc, char* argv[])
{
    //testNul();
     
    //calCharArrayLength();

    //charPtrInit();

    modifyCharPtrValue();

    return 0;
}












