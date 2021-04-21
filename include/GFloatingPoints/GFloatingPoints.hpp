/*******************************************************************************************
 *   X X X X  X X X X  X        X X X X  X X X X  X X X X X  X X X X X  X       X    X X X X
 * X          X        X        X     X  X     X      X          X      X X     X  X
 * X   X X X  X X X X  X        X     X  X X X X      X          X      X   X   X  X   X X X
 * X       X  X        X        X     X  X     X      X          X      X     X X  X       X
 *   X X X    X        X X X X  X X X X  X     X      X      X X X X X  X       X    X X X
 *******************************************************************************************
 *
 * This file is part of GFloatingPoints by GaryNLOL.
 * Special thanks to my family and µ's.
 *
 * MIT License
 * Copyright (c) 2020 GaryNLOL
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************************/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

namespace GFloatingPoints
{
    class GFloat
    {
    private:
        bool is_negative;
        std::string integral_val;
        std::string decimal_val;
        static bool isValidInput(const std::string& str)
        {
            if(str.size() == 0 || str == "-" || str == "." || str == "-.")
                return false;
            bool did_point_appear = false;
            for(unsigned int i = (str[0] == '-'); i < str.size(); i++)
            {
                if(!std::isdigit(str[i]))
                {
                    if(str[i] == '.' && !did_point_appear)
                        did_point_appear = true;
                    else
                        return false;
                }
            }
            return true;
        }
        void deleteTrailingZeroes()
        {
            for(std::string::size_type i = 0; i < this->integral_val.size(); i++)
            {
                if(i == this->integral_val.size()-1 || this->integral_val[i] != '0')
                {
                    this->integral_val.erase(0,i);
                    break;
                }
            }
            for(std::string::size_type i = this->decimal_val.size()-1; true /*(i >= 0)*/; i--)
            {
                if(i == 0 || this->decimal_val[i] != '0')
                {
                    this->decimal_val.erase(i+1,this->decimal_val.size()-i-1);
                    break;
                }
            }
        }
    public:
        GFloat()
        {
            this->is_negative = false;
            this->integral_val = "0";
            this->decimal_val = "0";
        }
        GFloat(const std::string& new_val)
        {
            if(!isValidInput(new_val))
                throw std::invalid_argument("GFloat::GFloat(" + new_val + ")");
            this->is_negative = (new_val[0] == '-');
            std::string ::size_type point_index = new_val.find('.');
            if(point_index == new_val.npos || point_index == new_val.size()-1)
            {
                this->integral_val = new_val.substr(this->is_negative,new_val.size()-this->is_negative-(point_index == new_val.size()-1));
                this->decimal_val = "0";
            }
            else if(point_index == this->is_negative)
            {
                this->integral_val = "0";
                this->decimal_val = new_val.substr(this->is_negative+1,new_val.size()-this->is_negative-1);
            }
            else
            {
                this->integral_val = new_val.substr(this->is_negative,point_index-this->is_negative);
                this->decimal_val = new_val.substr(point_index+1,new_val.size()-point_index-1);
            }
            this->deleteTrailingZeroes();
        }
        template<typename float_type, typename = typename std::enable_if<std::is_floating_point<float_type>::value || std::is_integral<float_type>::value>::type>
        GFloat(const float_type new_val)
        {
            *this = GFloat(std::to_string(new_val));
        }
        std::string to_string() const
        {
            return (is_negative ? "-":"") + integral_val + "." + decimal_val;
        }
        friend std::ostream& operator<<(std::ostream& stream, const GFloat& num)
        {
            stream << num.to_string();
            return stream;
        }
        friend std::istream& operator>>(std::istream& stream, GFloat& num)
        {
            std::string check_str;
            stream >> check_str;
            num = GFloat(check_str);
            return stream;
        }
        bool operator==(const GFloat& num2) const
        {
            return this->is_negative == num2.is_negative && this->integral_val == num2.integral_val && this->decimal_val == num2.decimal_val;
        }
        bool operator!=(const GFloat& num2) const
        {
            return !(*this == num2);
        }
        GFloat abs() const
        {
            GFloat ret = *this;
            ret.is_negative = false;
            return ret;
        }
        bool operator>(const GFloat& num2) const
        {
            if(this->is_negative != num2.is_negative)
                return !this->is_negative;
            if(*this == num2)
                return false;
            if(this->is_negative)
                return this->abs() < num2.abs();
            if(this->integral_val.size() != num2.integral_val.size())
                return this->integral_val.size() > num2.integral_val.size();
            for(std::string::size_type i = 0; i < this->integral_val.size(); i++)
            {
                if(this->integral_val[i] > num2.integral_val[i])
                    return true;
                else if(this->integral_val[i] < num2.integral_val[i])
                    return false;
            }
            if(this->decimal_val.size() != num2.decimal_val.size())
                return this->decimal_val.size() > num2.decimal_val.size();
            for(std::string::size_type i = 0; i < this->decimal_val.size(); i++)
            {
                if(this->decimal_val[i] > num2.decimal_val[i])
                    return true;
                else if(this->decimal_val[i] < num2.decimal_val[i])
                    return false;
            }
            throw std::invalid_argument("GFloat::operator>(Impossible result)");
        }
        bool operator<(const GFloat& num2) const
        {
            return !((*this > num2) || (*this == num2));
        }
        bool operator>=(const GFloat& num2) const
        {
            return (*this == num2) || (*this > num2);
        }
        bool operator<=(const GFloat& num2) const
        {
            return (*this == num2) || (*this < num2);
        }
        GFloat operator+(const GFloat& num2)
        {
            if(this->is_negative == num2.is_negative)
            {
                std::string answer;
                int carry = 0;
                for(std::string::size_type i = std::max(this->decimal_val.size()-1,num2.decimal_val.size()-1); true /*Check break at the end of the block*/; i--)
                {
                    int operand1 = (i < this->decimal_val.size()) ? (this->decimal_val[i]-'0'):(0);
                    int operand2 = (i < num2.decimal_val.size()) ? (num2.decimal_val[i]-'0'):(0);
                    int result = operand1 + operand2 + carry;
                    if(result >= 10)
                    {
                        result -= 10;
                        carry = 1;
                    }
                    else
                    {
                        carry = 0;
                    }
                    answer += char(result + '0');
                    if(i == 0)
                        break;
                }
                answer += ".";
                for(int i = this->integral_val.size()-1, j = num2.integral_val.size()-1; i >= 0 || j >= 0 || carry != 0; i--, j--)
                {
                    int operand1 = (i >= 0) ? (this->integral_val[i]-'0'):0;
                    int operand2 = (j >= 0) ? (num2.integral_val[j]-'0'):0;
                    int result = operand1 + operand2 + carry;
                    if(result >= 10)
                    {
                        result -= 10;
                        carry = 1;
                    }
                    else
                    {
                        carry = 0;
                    }
                    answer += char(result + '0');
                }
                answer = (this->is_negative ? "-":"") + std::string(answer.rbegin(),answer.rend());
                return GFloat(answer);
            }
            else
            {
                if(this->abs() == num2.abs())
                    return GFloat(0);
                const GFloat& positive = this->is_negative ? num2.abs():this->abs();
                const GFloat& negative = this->is_negative ? this->abs():num2.abs();
                bool is_result_negative = negative > positive;
                std::string answer;
                int carry = 0;
                for(std::string::size_type i = std::max(positive.decimal_val.size()-1,negative.decimal_val.size()-1); true /*Check break at the end of the block*/; i--)
                {
                    int operand1 = (i < positive.decimal_val.size()) ? (positive.decimal_val[i]-'0'):(0);
                    int operand2 = (i < negative.decimal_val.size()) ? (negative.decimal_val[i]-'0'):(0);
                    int result;
                    if(is_result_negative)
                        result = operand2 - (operand1 + carry);
                    else
                        result = operand1 - (operand2 + carry);
                    if(result < 0)
                    {
                        result += 10;
                        carry = 1;
                    }
                    else
                    {
                        carry = 0;
                    }
                    answer += char(result + '0');
                    if(i == 0)
                        break;
                }
                answer += ".";
                for(int i = positive.integral_val.size()-1, j = negative.integral_val.size()-1; i >= 0 || j >= 0; i--, j--)
                {
                    int operand1 = (i >= 0) ? (positive.integral_val[i]-'0'):0;
                    int operand2 = (j >= 0) ? (negative.integral_val[j]-'0'):0;
                    int result;
                    if(is_result_negative)
                        result = operand2 - (operand1 + carry);
                    else
                        result = operand1 - (operand2 + carry);
                    if(result < 0)
                    {
                        result += 10;
                        carry = 1;
                    }
                    else
                    {
                        carry = 0;
                    }
                    answer += char(result + '0');
                }
                answer = (is_result_negative ? "-":"") + std::string(answer.rbegin(),answer.rend());
                return GFloat(answer);
            }
        }
        GFloat operator +=(const GFloat& num2)
        {
            *this = *this + num2;
            return *this;
        }
        GFloat operator-(const GFloat& num2)
        {
            GFloat tmp = num2;
            tmp.is_negative = !tmp.is_negative;
            return *this + tmp;
        }
        GFloat operator -=(const GFloat& num2)
        {
            *this = *this - num2;
            return *this;
        }
        GFloat operator++(int)
        {
            GFloat tmp = *this;
            *this += GFloat(1);
            return tmp;
        }
        GFloat operator--(int)
        {
            GFloat tmp = *this;
            *this -= GFloat(1);
            return tmp;
        }
        GFloat operator++()
        {
            *this += GFloat(1);
            return *this;
        }
        GFloat operator--()
        {
            *this -= 1;
            return *this;
        }
        GFloat operator*(const GFloat& num2) const
        {
            if((this->integral_val == "0" && this->decimal_val == "0") || (num2.integral_val == "0" && num2.decimal_val == "0"))
                return GFloat(0);
            std::vector<GFloat> unitary_results;
            const std::string num1_val = this->integral_val + this->decimal_val;
            const std::string num2_val = num2.integral_val + num2.decimal_val;
            for(int i = num1_val.size()-1; i >= 0; i--)
            {
                std::string unitary_answer;
                int carry = 0;
                int operand1 = num1_val[i] - '0';
                for(int j = num2_val.size()-1; j >= 0 || carry != 0; j--)
                {
                    int operand2 = (j >= 0) ? (num2_val[j]-'0'):(0);
                    int result = operand1 * operand2 + carry;
                    carry = result/10;
                    result %= 10;
                    unitary_answer += char(result + 48);
                }
                unitary_answer = std::string(unitary_answer.rbegin(),unitary_answer.rend()) + std::string(unitary_results.size(),'0');
                unitary_results.push_back(GFloat(unitary_answer));
            }
            GFloat answer;
            for(unsigned int i = 0; i < unitary_results.size(); i++)
                answer += unitary_results[i];
            answer.decimal_val = answer.integral_val.substr(answer.integral_val.size()-(this->decimal_val.size()+num2.decimal_val.size()),this->decimal_val.size()+num2.decimal_val.size());
            answer.integral_val = answer.integral_val.substr(0,answer.integral_val.size()-(this->decimal_val.size()+num2.decimal_val.size()));
            answer.is_negative = (this->is_negative != num2.is_negative);
            answer.deleteTrailingZeroes();
            return answer;
        }
        GFloat operator*=(const GFloat& num2)
        {
            *this = *this * num2;
            return *this;
        }
        GFloat operator/(const GFloat& num2) const
        {
            unsigned int maxDecimalsNow = std::max(this->decimal_val.size(),num2.decimal_val.size()) - (this->decimal_val == "0" && num2.decimal_val == "0");
            const GFloat dividend = (this->abs() * pow(10,maxDecimalsNow));
            const GFloat divisor = (num2.abs() * pow(10,maxDecimalsNow));
            GFloat remainder;
            remainder.integral_val = "";
            std::string cocient;
            unsigned int precision = getPrecision();
            unsigned int current_index = 0;
            bool point = false;
            while((cocient.find('.') == cocient.npos || cocient.size()-cocient.find('.') < precision) && !(remainder == 0 && current_index >= dividend.integral_val.size()))
            {
                if(current_index >= dividend.integral_val.size())
                {
                    if(!point)
                    {
                        cocient += '.';
                        point = true;
                    }
                    remainder.integral_val += '0';
                }
                else
                {
                    remainder.integral_val += dividend.integral_val[current_index];
                    current_index++;
                }
                if(divisor > remainder)
                {
                    cocient += "0";
                }
                else
                {
                    unsigned int counter = 0;
                    while(remainder >= divisor)
                    {
                        remainder -= divisor;
                        counter++;
                    }
                    cocient += char(counter + '0');
                }
            }
            cocient = (this->is_negative == num2.is_negative ? "":"-") + cocient;
            return GFloat(cocient);
        }
        GFloat operator/=(const GFloat& num2)
        {
            *this = *this / num2;
            return *this;
        }
        GFloat operator%(const GFloat& num2) const
        {
            unsigned int max_decimals_now = std::max(this->decimal_val.size(),num2.decimal_val.size()) - (this->decimal_val == "0" && num2.decimal_val == "0");
            const GFloat dividend = (this->abs() * GFloat(pow(10,max_decimals_now)));
            const GFloat divisor = (num2.abs() * GFloat(pow(10,max_decimals_now)));
            GFloat remainder;
            remainder.integral_val = "";
            std::string cocient;
            unsigned int current_index = 0;
            while(!(remainder == 0 && current_index >= dividend.integral_val.size()))
            {
                if(current_index >= dividend.integral_val.size())
                {
                    remainder.deleteTrailingZeroes();
                    return remainder / GFloat(pow(10,max_decimals_now));
                }
                else
                {
                    remainder.integral_val += dividend.integral_val[current_index];
                    current_index++;
                }
                while(divisor <= remainder)
                {
                    remainder -= divisor;
                }
            }
            return GFloat(0);
        }
        GFloat operator%=(const GFloat& num2)
        {
            *this = *this % num2;
            return *this;
        }
        static unsigned int setPrecision(unsigned int new_precision)
        {
            static unsigned int precision = 10;
            if(new_precision == 0)
            {
                return precision;
            }
            else
            {
                precision = new_precision;
                return 0;
            }
        }
        static unsigned int getPrecision()
        {
            return setPrecision(0);
        }
    };
}
