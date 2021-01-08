#include "include/GFloatingPoints/GFloatingPoints.hpp"
#include <iostream>

int main()
{
    using namespace GFloatingPoints;
    std::cout << "Convertible from float's and std::string's!" << std::endl;
    std::cout << "Does not pollute the global namespace! (The class is inside it's own namespace)." << std::endl;
    std::cout << "Set the precision of the floats yourself with GFloatingPoints::setPresicion()" << std::endl;

    GFloat num1(ULONG_LONG_MAX);
    num1 += GFloat(1.5);
    std::cout << "Higher than ULONG_LONG_MAX!" << std::endl;
    std::cout << "num1 = " << num1 << std::endl;
    std::cout << std::endl;

    GFloat num2 = num1 * -1 - 100;
    std::cout << "Lower than -1 * ULONG_LONG_MIN!" << std::endl;
    std::cout << "num2 = " << num2 << std::endl;
    std::cout << std::endl;

    GFloat num3 = num1 + num2;
    std::cout << "Supports sums..." << std::endl;
    std::cout << "num3 = num2 + num1 = " << num3 << std::endl;
    std::cout << std::endl;

    GFloat num4 = num3 - num2;
    std::cout << "Substractions..." << std::endl;
    std::cout << "num4 = num3 - num2 = num1 = " << num4 << std::endl;
    std::cout << std::endl;

    GFloat num5 = GFloat(6453.45) * GFloat(6758.44);
    std::cout << "Multiplications" << std::endl;
    std::cout << "num5 = 6453.45 * 6758.44 = " << num5 << std::endl;
    std::cout << std::endl;

    GFloat num6 = GFloat("477978547397979") / 14546;
    std::cout << "Divisions!" << std::endl;
    std::cout << "num6 = 477978547397979 / 14546 = " << num6 << std::endl;
    std::cout << std::endl;

    GFloat num7 = GFloat("477978547397979") % GFloat(14546);
    std::cout << "Modulus!!" << std::endl;
    std::cout << "num7 = 477978547397979 % 14546 = " << num7 << std::endl;
    std::cout << std::endl;

    GFloat num8 = GFloat(INT_MIN).abs();
    std::cout << "And more!!!!!" << std::endl;
    std::cout << "num8 = | INT_MIN | = " << num8 << std::endl;
    std::cout << std::endl;

    std::cout << "And even more, more, more is coming soon!" << std::endl;
    return 0;
}
