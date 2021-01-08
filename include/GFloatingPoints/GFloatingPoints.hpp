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
        bool isNegative;
        std::string integralVal;
        std::string decimalVal;
        static bool isValidInput(const std::string& str)
        {
            if(str.size() == 0 || str == "-" || str == "." || str == "-.")
                return false;
            bool pointAppeared = false;
            for(unsigned int i = (str[0] == '-'); i < str.size(); i++)
            {
                if(!std::isdigit(str[i]))
                {
                    if(str[i] == '.' && !pointAppeared)
                        pointAppeared = true;
                    else
                        return false;
                }
            }
            return true;
        }
        void deleteTrailingZeroes()
        {
            for(std::string::size_type i = 0; i < this->integralVal.size(); i++)
            {
                if(i == this->integralVal.size()-1 || this->integralVal[i] != '0')
                {
                    this->integralVal.erase(0,i);
                    break;
                }
            }
            for(std::string::size_type i = this->decimalVal.size()-1; true /*(i >= 0)*/; i--)
            {
                if(i == 0 || this->decimalVal[i] != '0')
                {
                    this->decimalVal.erase(i+1,this->decimalVal.size()-i-1);
                    break;
                }
            }
        }
    public:
        GFloat()
        {
            this->isNegative = false;
            this->integralVal = "0";
            this->decimalVal = "0";
        }
        GFloat(const std::string& newVal)
        {
            if(!isValidInput(newVal))
                throw std::invalid_argument("GFloat::GFloat(" + newVal + ")");
            this->isNegative = (newVal[0] == '-');
            std::string ::size_type pointIndex = newVal.find('.');
            if(pointIndex == newVal.npos || pointIndex == newVal.size()-1)
            {
                this->integralVal = newVal.substr(this->isNegative,newVal.size()-this->isNegative-(pointIndex == newVal.size()-1));
                this->decimalVal = "0";
            }
            else if(pointIndex == this->isNegative)
            {
                this->integralVal = "0";
                this->decimalVal = newVal.substr(this->isNegative+1,newVal.size()-this->isNegative-1);
            }
            else
            {
                this->integralVal = newVal.substr(this->isNegative,pointIndex-this->isNegative);
                this->decimalVal = newVal.substr(pointIndex+1,newVal.size()-pointIndex-1);
            }
            this->deleteTrailingZeroes();
        }
        template<typename float_type, typename = typename std::enable_if<std::is_floating_point<float_type>::value || std::is_integral<float_type>::value>::type>
        GFloat(const float_type newVal)
        {
            *this = GFloat(std::to_string(newVal));
        }
        std::string to_string() const
        {
            return (isNegative ? "-":"") + integralVal + "." + decimalVal;
        }
        friend std::ostream& operator<<(std::ostream& stream, const GFloat& num)
        {
            stream << num.to_string();
            return stream;
        }
        friend std::istream& operator>>(std::istream& stream, GFloat& num)
        {
            std::string checkStr;
            stream >> checkStr;
            num = GFloat(checkStr);
            return stream;
        }
        bool operator==(const GFloat& num2) const
        {
            return this->isNegative == num2.isNegative && this->integralVal == num2.integralVal && this->decimalVal == num2.decimalVal;
        }
        bool operator!=(const GFloat& num2) const
        {
            return !(*this == num2);
        }
        GFloat abs() const
        {
            GFloat ret = *this;
            ret.isNegative = false;
            return ret;
        }
        bool operator>(const GFloat& num2) const
        {
            if(this->isNegative != num2.isNegative)
                return !this->isNegative;
            if(*this == num2)
                return false;
            if(this->isNegative)
                return this->abs() < num2.abs();
            if(this->integralVal.size() != num2.integralVal.size())
                return this->integralVal.size() > num2.integralVal.size();
            for(std::string::size_type i = 0; i < this->integralVal.size(); i++)
            {
                if(this->integralVal[i] > num2.integralVal[i])
                    return true;
                else if(this->integralVal[i] < num2.integralVal[i])
                    return false;
            }
            if(this->decimalVal.size() != num2.decimalVal.size())
                return this->decimalVal.size() > num2.decimalVal.size();
            for(std::string::size_type i = 0; i < this->decimalVal.size(); i++)
            {
                if(this->decimalVal[i] > num2.decimalVal[i])
                    return true;
                else if(this->decimalVal[i] < num2.decimalVal[i])
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
            if(this->isNegative == num2.isNegative)
            {
                std::string answer;
                int carry = 0;
                for(std::string::size_type i = std::max(this->decimalVal.size()-1,num2.decimalVal.size()-1); true /*Check break at the end of the block*/; i--)
                {
                    int operand1 = (i < this->decimalVal.size()) ? (this->decimalVal[i]-'0'):(0);
                    int operand2 = (i < num2.decimalVal.size()) ? (num2.decimalVal[i]-'0'):(0);
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
                for(int i = this->integralVal.size()-1, j = num2.integralVal.size()-1; i >= 0 || j >= 0 || carry != 0 /*Check break at the end of the block*/; i--, j--)
                {
                    int operand1 = (i >= 0) ? (this->integralVal[i]-'0'):0;
                    int operand2 = (j >= 0) ? (num2.integralVal[j]-'0'):0;
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
                answer = (this->isNegative ? "-":"") + std::string(answer.rbegin(),answer.rend());
                return GFloat(answer);
            }
            else
            {
                if(this->abs() == num2.abs())
                    return GFloat(0);
                const GFloat& positive = this->isNegative ? num2.abs():this->abs();
                const GFloat& negative = this->isNegative ? this->abs():num2.abs();
                bool resultIsNegative = negative > positive;
                std::string answer;
                int carry = 0;
                for(std::string::size_type i = std::max(positive.decimalVal.size()-1,negative.decimalVal.size()-1); true /*Check break at the end of the block*/; i--)
                {
                    int operand1 = (i < positive.decimalVal.size()) ? (positive.decimalVal[i]-'0'):(0);
                    int operand2 = (i < negative.decimalVal.size()) ? (negative.decimalVal[i]-'0'):(0);
                    int result;
                    if(resultIsNegative)
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
                for(int i = positive.integralVal.size()-1, j = negative.integralVal.size()-1; i >= 0 || j >= 0 /*Check break at the end of the block*/; i--, j--)
                {
                    int operand1 = (i >= 0) ? (positive.integralVal[i]-'0'):0;
                    int operand2 = (j >= 0) ? (negative.integralVal[j]-'0'):0;
                    int result;
                    if(resultIsNegative)
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
                answer = (resultIsNegative ? "-":"") + std::string(answer.rbegin(),answer.rend());
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
            tmp.isNegative = !tmp.isNegative;
            return *this + tmp;
        }
        GFloat operator -=(const GFloat& num2)
        {
            *this = *this - num2;
            return *this;
        }
        GFloat operator++()
        {
            GFloat tmp = *this;
            *this += GFloat(1);
            return tmp;
        }
        GFloat operator--()
        {
            GFloat tmp = *this;
            *this -= GFloat(1);
            return tmp;
        }
        GFloat operator++(int)
        {
            *this += GFloat(1);
            return *this;
        }
        GFloat operator--(int)
        {
            *this -= 1;
            return *this;
        }
        GFloat operator*(const GFloat& num2) const
        {
            if((this->integralVal == "0" && this->decimalVal == "0") || (num2.integralVal == "0" && num2.decimalVal == "0"))
                return GFloat(0);
            std::vector<GFloat> unitaryResults;
            const std::string num1val = this->integralVal + this->decimalVal;
            const std::string num2val = num2.integralVal + num2.decimalVal;
            for(int i = num1val.size()-1; i >= 0; i--)
            {
                std::string unitaryAnswer;
                int carry = 0;
                int operand1 = num1val[i] - '0';
                for(int j = num2val.size()-1; j >= 0 || carry != 0; j--)
                {
                    int operand2 = (j >= 0) ? (num2val[j]-'0'):(0);
                    int result = operand1 * operand2 + carry;
                    carry = result/10;
                    result %= 10;
                    unitaryAnswer += char(result + 48);
                }
                unitaryAnswer = std::string(unitaryAnswer.rbegin(),unitaryAnswer.rend()) + std::string(unitaryResults.size(),'0');
                unitaryResults.push_back(GFloat(unitaryAnswer));
            }
            GFloat answer;
            for(unsigned int i = 0; i < unitaryResults.size(); i++)
                answer += unitaryResults[i];
            answer.decimalVal = answer.integralVal.substr(answer.integralVal.size()-(this->decimalVal.size()+num2.decimalVal.size()),this->decimalVal.size()+num2.decimalVal.size());
            answer.integralVal = answer.integralVal.substr(0,answer.integralVal.size()-(this->decimalVal.size()+num2.decimalVal.size()));
            answer.isNegative = (this->isNegative != num2.isNegative);
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
            unsigned int maxDecimalsNow = std::max(this->decimalVal.size(),num2.decimalVal.size()) - (this->decimalVal == "0" && num2.decimalVal == "0");
            const GFloat dividend = (this->abs() * pow(10,maxDecimalsNow));
            const GFloat divisor = (num2.abs() * pow(10,maxDecimalsNow));
            GFloat remainder;
            remainder.integralVal = "";
            std::string cocient;
            unsigned int precision = getPrecision();
            unsigned int currentIndex = 0;
            bool point = false;
            while((cocient.find('.') == cocient.npos || cocient.size()-cocient.find('.') < precision) && !(remainder == 0 && currentIndex >= dividend.integralVal.size()))
            {
                if(currentIndex >= dividend.integralVal.size())
                {
                    if(!point)
                    {
                        cocient += '.';
                        point = true;
                    }
                    remainder.integralVal += '0';
                }
                else
                {
                    remainder.integralVal += dividend.integralVal[currentIndex];
                    currentIndex++;
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
            cocient = (this->isNegative == num2.isNegative ? "":"-") + cocient;
            return GFloat(cocient);
        }
        GFloat operator/=(const GFloat& num2)
        {
            *this = *this / num2;
            return *this;
        }
        GFloat operator%(const GFloat& num2) const
        {
            unsigned int maxDecimalsNow = std::max(this->decimalVal.size(),num2.decimalVal.size()) - (this->decimalVal == "0" && num2.decimalVal == "0");
            const GFloat dividend = (this->abs() * GFloat(pow(10,maxDecimalsNow)));
            const GFloat divisor = (num2.abs() * GFloat(pow(10,maxDecimalsNow)));
            GFloat remainder;
            remainder.integralVal = "";
            std::string cocient;
            unsigned int currentIndex = 0;
            while(!(remainder == 0 && currentIndex >= dividend.integralVal.size()))
            {
                if(currentIndex >= dividend.integralVal.size())
                {
                    remainder.deleteTrailingZeroes();
                    return remainder / GFloat(pow(10,maxDecimalsNow));
                }
                else
                {
                    remainder.integralVal += dividend.integralVal[currentIndex];
                    currentIndex++;
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
        static unsigned int setPrecision(unsigned int newPrecision)
        {
            static unsigned int precision = 10;
            if(newPrecision == 0)
            {
                return precision;
            }
            else
            {
                precision = newPrecision;
                return 0;
            }
        }
        static unsigned int getPrecision()
        {
            return setPrecision(0);
        }
    };
}
