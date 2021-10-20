#include "stack.h"

void Stack::copyAll(const Stack& s)
{
    int i(0);

    while(i <= s.top)
    {
        data[i] = s.data[i];

        i++;
    }

    this->top = s.top;
}

Stack::Stack() : top(-1) { }

Stack::Stack(const Stack& s)
{
    copyAll(s);
}

bool Stack::isEmpty()
{
    return top == -1;
}

bool Stack::isFull()
{
    return top == ARRAYSIZE - 1;
}

void Stack::push(const int& e)
{
    if(isFull())
    {
        throw StackException(" Desbordamiento de datos, push");
    }

    top++;

    data[top] = e;
}

int Stack::pop()
{
    if(isEmpty())
    {
        throw StackException(" Insuficiencia de datos, pop");
    }

    return data[top--];
}

int Stack::getTop()
{
    if(isEmpty())
    {
        throw StackException(" Insuficiencia de datos, getTop");
    }

    return data[top];
}

Stack& Stack::operator =( const Stack& s)
{
    copyAll(s);

    return *this;
}
