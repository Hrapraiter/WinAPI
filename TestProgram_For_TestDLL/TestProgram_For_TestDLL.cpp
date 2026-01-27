#include <iostream>
#include "MyFunction.h"

//#define COLOR

#ifdef COLOR
//на линукс ситемах пример мобильный компилятор это будет выглядеть 
// как \033[31m  тоесть все коды [(value)m одинаковы и там и там
// но это не совсем коректно работает на винде поэтому при компиляции 
// будет мешанина из кодов и текста ( фиксисится тем что используется другая консоль # не системная #)
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"

#define F_RESET "\x1b[0m"
#define F_BOLD  "\x1b[1m"

#else

#define RED     '\0'
#define GREEN   '\0'
#define YELLOW  '\0'

#define F_RESET '\0'
#define F_BOLD  '\0'

#endif //COLOR

void v_print(const std::vector<int>& vect)
{
    for (const int& elem : vect)
        std::cout << elem << ' ';
    std::cout << '\n';
}
int main()
{
    std::vector<int> vect = { 1,2,3,4,5,6,7,8 };
    std::cout << "Base Vect : " << GREEN;
    v_print(vect);

    Select(vect, [](int elem) { return elem + 1; });
    std::cout << YELLOW << "Select (+1) : "  << F_BOLD << GREEN;
    v_print(vect);

    std::cout << RED << "Where (%2 == 0) : " << F_BOLD << GREEN;
    Where(vect, [](int elem) {return elem % 2 == 0; });
    v_print(vect);
    std::cout << F_RESET;

    std::cout << "\n\n";
    system("pause");

    return 0;
}
