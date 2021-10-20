#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "list.h"

template<class T>
class Stack : public List<T>
{
public:
    void push(const T&);

    T pop();

    T getTop();
};

template<class T>
void Stack<T>::push(const T& e)
{
    this->insertData(nullptr, e);
}

template<class T>
T Stack<T>::pop()
{
    T result(this->retrieve(this->getLastPos()));

    this->deleteData(this->getLastPos());

    return result;
}

template<class T>
T Stack<T>::getTop()
{
    return this->retrieve(this->getLastPos());
}

#endif // STACK_H_INCLUDED
