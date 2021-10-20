#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <exception>
#include <string>

template <class T, int ARRAYSIZE = 1024>
class Queue
{
private:
    T data[ARRAYSIZE];
    int frontPos;
    int endPos;

    void copyAll(const Queue<T, ARRAYSIZE>&);

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
    Queue(const Queue<T, ARRAYSIZE>&);

    bool isEmty();
    bool isFull();

    void enqueue(const T&);

    void dequeue();

    T getFront();

    Queue<T, ARRAYSIZE>& operator = (const Queue<T, ARRAYSIZE>&);
};

template <class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::copyAll(const Queue<T, ARRAYSIZE>& q)
{
    int i(0), j(0);

    while(i <= q.frontPos)
    {
        data[i] = q.data[i];

        i++;
    }

    this->frontPos = q.frontPos;
}

template <class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue() : frontPos(0), endPos(ARRAYSIZE -1 ) { }

template <class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>::Queue(const Queue<T, ARRAYSIZE>& q)
{
    copyAll(q);
}

template <class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isEmty()
{
    return frontPos == endPos + 1
            or (frontPos == 0 and endPos == ARRAYSIZE - 1);
}

template <class T, int ARRAYSIZE>
bool Queue<T, ARRAYSIZE>::isFull()
{
    return frontPos == endPos + 2
            or (frontPos == 0 and endPos == ARRAYSIZE - 2)
            or (frontPos == 1 and endPos == ARRAYSIZE - 1);
}

template <class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::enqueue(const T& e)
{
    if(isFull())
    {
        throw QueueException( "Desbordamiento de datos, enqueue");
    }

    data[endPos = ++endPos == ARRAYSIZE ? 0 : endPos] = e;
}

template <class T, int ARRAYSIZE>
void Queue<T, ARRAYSIZE>::dequeue()
{
    if(isEmty())
    {
        throw QueueException(" Insuficiencia de datos, dequeue");
    }

    T result(data[frontPos]);

    if(++frontPos == ARRAYSIZE)
    {
        frontPos = 0;
    }
}

template <class T, int ARRAYSIZE>
T Queue<T, ARRAYSIZE>::getFront()
{
    if(isEmty())
    {
        throw QueueException(" Insuficiencia de datos, getFront");
    }

    return data[frontPos];
}

template <class T, int ARRAYSIZE>
Queue<T, ARRAYSIZE>& Queue<T, ARRAYSIZE>::operator=(const Queue<T, ARRAYSIZE>& q)
{
    copyAll(q);

    return *this;
}

#endif // QUEUE_H_INCLUDED
