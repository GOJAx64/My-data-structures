#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <exception>
#include <string>

#define ARRAYSIZE 1024

class Queue
{
private:
    int data[ARRAYSIZE];
    int frontPos;
    int endPos;

    void copyAll(const Queue&);

public:
    class QueueException : public std::exception
    {
    private:
        std::string msg;

    public:
        explicit QueueException(const char* message) : msg(message) { }
        explicit QueueException(const std::string& message) : msg(message) { }
        virtual ~QueueException() throw () { }
        virtual const char* what() const throw()
        {
            return msg.c_str();
        }
    };

    Queue();
    Queue(const Queue&);

    bool isEmty();
    bool isFull();

    void enqueue(const int&);

    void dequeue();

    int getFront();

    Queue& operator = (const Queue&);
};

#endif // QUEUE_H_INCLUDED
