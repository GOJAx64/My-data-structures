#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <exception>
#include <string>

#define ARRAYSIZE 1024
class Stack
{
private:
    int data[ARRAYSIZE];
    int top;

    void copyAll(const Stack&);

public:
    class StackException : public std::exception
    {
    private:
        std::string msg;

    public:
        explicit StackException(const char* message) : msg(message) { }

        explicit StackException(const std::string& message) : msg(message) { }

        virtual ~StackException() throw () { }

        virtual const char* what() const throw ()
        {
            return msg.c_str();
        }

    };

    Stack();
    Stack(const Stack&);

    bool isEmpty();
    bool isFull();

    void push(const int&);

    int pop();

    int getTop();

    Stack& operator = (const Stack&);

};

#endif // STACK_H_INCLUDED
