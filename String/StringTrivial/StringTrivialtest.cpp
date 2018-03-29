#include "StringTrivial.h"

using namespace trivial;

int main(int argc, char *argv[])
{
    std::cout << "------------------------------" << std::endl;

    String str = getString();
    std::cout << "******************************" << std::endl;

    str = getString();
    std::cout << "==============================" << std::endl;

    String str1 = std::move(str);

    std::cout << "++++++++++++++++++++++++++++++" << std::endl;

    return 0;
}
