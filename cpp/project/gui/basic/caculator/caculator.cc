#include "caculator.hpp"
#include <iostream>
#include <cassert>

Caculator::DataType Caculator::run(const std::string &exp)
{
    auto is_in_table = [](char c, const std::string &table) {
        return table.find(c) != std::string::npos; };
    std::string nexp = '#' + exp;
    std::stack<DataType> num;
    std::stack<char> op;
    for (size_t i = 0; i < nexp.size(); ++i)
    {
        char c = nexp[i];
        if (is_in_table(c, OPS))
        {
            char next_c = op.top();
            if (is_priorier(next_c, c) || is_equal(next_c, c))
                advance(op, num);
            op.push(c);
        }
        else if (std::isdigit(c))
        {
            std::string v;
            while (i < nexp.size() && is_in_table(nexp[i], DIGITS))
                v += nexp[i++];
            i--;
            num.push(std::stod(v));
        }
        else if (is_in_table(c, MATCHR))
        {
            char matchc = MATCH.at(c);
            while (op.top() != matchc)
                advance(op, num);
            op.pop();
        }
        else if (is_in_table(c, MATCHL))
        {
            op.push(c);
        }
        else
        {
            std::cerr << "error char " << c;
        }
    }
    assert(num.size() == 1);
    return num.top();
}

void Caculator::advance(std::stack<char> &ops, std::stack<DataType> &nums)
{
   int x, y;
   x = nums.top();
   nums.pop();
   y = nums.top();
   nums.pop();
   nums.push(func_factory(ops.top())(y, x));
   ops.pop();
}

bool Caculator::is_priorier(char left, char right) const
{
    return PRIORITY.at(left) > PRIORITY.at(right);
}

bool Caculator::is_equal(char left, char right) const
{
    return PRIORITY.at(left) == PRIORITY.at(right);
}

Caculator::func_t Caculator::func_factory(char op) const
{
    switch(op)
    {
        case '+': return [] (DataType x, DataType y) { return x + y; };
        case '-': return [] (DataType x, DataType y) { return x - y; };
        case '*': return [] (DataType x, DataType y) { return x * y; };
        case '/': return [] (DataType x, DataType y) { return x / y; };
        default: return nullptr;
    }
}

