# GFloatingPoints
GFloatingPoints: Arbitrary Floating Point Size and Precision support for C++.
## Setup
1. Download the project from GitHub or clone the repository using the following command:
```
git clone https://github.com/GaryNLOL/GFloatingPoints.git
```
2. Add the include files to your project's folder or to your compiler's search path.
3. Add the following line to your `.cpp` file:
- If you added it to your project's folder:
```
#include "include/GFloatingPoints/GFloatingPoints.hpp"
```
- If you added it to your compiler's path:
```
#include <GFloatingPoints/GFloatingPoints.hpp>
```
4. You're ready to start using GFloatingPoints!

## Structure
### GFloatingPoints (namespace)
#### GFloat (class)
##### Public methods
`GFloat()` -> Creates a `GFloat` default initialized to 0.

`GFloat(const std::string& newVal)` -> Creates a `GFloat` from a `std::string`.

template<typename float_type, typename = typename std::enable_if<std::is_floating_point<float_type>::value || std::is_integral<float_type>::value>::type> GFloat(const float_type newVal)` -> Creates a `GFloat` from any type of integer(`int`, `long int`, `long long int`, `unsigned long long int`, `size_t`, etc) or any type of floating point(`float`,`double`,`long double`).

`std::string to_string() const` -> `Returns the object's value in the form of a `std::string`.

`friend std::ostream& operator<<(std::ostream& stream, const GFloat& num)` -> Sends the value of `num` to the output stream `stream`.

`friend std::istream& operator>>(std::istream& stream, GFloat& num)` -> Sets the value of `num` to the input value from `stream`.

`bool operator==(const GFloat& num2) const` -> Returns true if the object's value and `num2`'s value are equal. Returns false otherwise.

`bool operator!=(const GFloat& num2) const` -> Returns true if the object's value and `num2`'s value are different. Returns false otherwise.

`bool operator>(const GFloat& num2) const` -> Returns true if the object's value is higher than `num2`'s value. Returns false otherwise.

`bool operator<=(const GFloat& num2) const` -> Returns true if the object's value is lower or equal to `num2`'s value. Returns false otherwise.

`bool operator>=(const GFloat& num2) const` -> Returns true if the object's value is higher or equal to `num2`'s value. Returns false otherwise.

`bool operator<(const GFloat& num2) const` -> Returns true if the object's value is lower than `num2`'s value. Returns false otherwise.

`GFloat operator+(const GFloat& num2) const` -> Returns the value of the object plus `num2`.

`GFloat operator-(const GFloat& num2) const` -> Returns the value of the object minus `num2`.

`GFloat operator+=(const GFloat& num2)` -> Sets the object's value to itself plus `num2` and returns the object's new value.

`GFloat operator-=(const GFloat& num2)` -> Sets the object's value to itself minus `num2` and returns the object's new value.

`GFloat operator++()` -> Sets the object's value to itself plus 1 and returns the object's old value.

`GFloat operator++(int)` -> Sets the object's value to itself plus 1 and returns the object's new value.

`GFloat operator--()` -> Sets the object's value to itself minus 1 and returns the object's old value.

`GFloat operator--(int)` -> Sets the object's value to itself minus 1 and returns the object's new value.

`GFloat operator*(const GFloat& num2) const` -> Returns the value of the object multiplied by `num2`.

`GFloat operator*=(const GFloat& num2)` -> Sets the object's value to itself multiplied by `num2` and returns the object's new value.

`GFloat operator/(const GFloat& num2) const` -> Returns the value of the object divided by `num2`.

`GFloat operator/=(const GFloat& num2)` -> Sets the object's value to itself divided by `num2` and returns the object's new value.

`GFloat operator%(const GFloat& num2) const` -> Returns the value of the object modulus `num2`.

`GFloat operator%=(const GFloat& num2)` -> Sets the object's value to itself modulus `num2` and returns the object's new value.

`GFloat abs() const` -> Returns a GFloat with the object's absolute value.
