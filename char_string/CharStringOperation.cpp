/*******************************************************************
 * 说明: c/c++ 编程中的对字符串处理的总结
 *
 * 作者: hongssun
 * 日期: 2015/11/22
 * 
 *******************************************************************/
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>

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

    printf("c1 strlen length = %ld\n", strlen(c1));
    printf("c1 sizeof length = %ld\n", sizeof(c1));

    printf("c2 strlen length = %ld\n", strlen(c2));
    printf("c2 sizeof length = %ld\n", sizeof(c2));

    printf("c3 strlen length = %ld\n", strlen(c3));
    printf("c3 sizeof length = %ld\n", sizeof(c3));

    printf("c4 strlen length = %ld\n", strlen(c4));
    printf("c4 sizeof length = %ld\n", sizeof(c4));  // with '\0'
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

void stringToCharPtr()
{
    const char *char_ptr = "C/C++ language";

    std::string char_string(char_ptr);

    std::cout<<"char ptr to string: "<<char_ptr<<std::endl;


    std::string str = "C/C++ language";

    const char* str_ptr = str.c_str();

    printf("string to char ptr: %s\n", str_ptr);
}

void stringTocharArray(void)
{
    char c[] = "C/C++ language";

    std::string str(c);

    std::cout<<"char array to string: "<<str<<std::endl;


    char char_array[100];
    strncpy(char_array, str.c_str(), str.length());

    printf("string to char array: %s\n", char_array);

}

int main(int argc, char* argv[])
{
    //testNul();
     
    //calCharArrayLength();

    //charPtrInit();

    //modifyCharPtrValue();

    stringToCharPtr();

    stringTocharArray();

    return 0;
}

