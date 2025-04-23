#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(const RPN &other)
{
    *this = other;
}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
    {
        this->_stack = other._stack;
    }
    return *this;
}

const char *RPN::ErrorException::what() const throw()
{
    return "Error";
}

void RPN::processInput(const std::string &input)
{
    std::istringstream iss(input);
    std::string token;

    try {
        while (iss >> token)
        {
            if (isdigit(token[0]))
            {
                _stack.push(atoi(token.c_str()));
            }
            else
        {
                if (_stack.size() < 2)
                    throw ErrorException();
                int b = _stack.top();
                _stack.pop();
                int a = _stack.top();
                _stack.pop();

                switch (token[0])
                {
                    case '+':
                        _stack.push(a + b);
                        break;
                    case '-':
                        _stack.push(a - b);
                        break;
                    case '*':
                        _stack.push(a * b);
                        break;
                    case '/':
                        if (b == 0)
                            throw ErrorException();
                        _stack.push(a / b);
                        break;
                    default:
                        throw ErrorException();
                }
            }
        }
        if (_stack.size() != 1)
            throw ErrorException();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
    std::cout << _stack.top() << std::endl;
}
