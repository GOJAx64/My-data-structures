#include "queue.h"

void Queue::copyAll(const Queue& q)
{
    int i(0), j(0);

    while(i <= q.frontPos)
    {
        data[i] = q.data[i];

        i++;
    }

    this->frontPos = q.frontPos;
}

Queue::Queue() : frontPos(0), endPos(ARRAYSIZE -1 ) { }

Queue::Queue(const Queue& q)
{
    copyAll(q);
}

bool Queue::isEmty()
{
    return frontPos == endPos + 1
            or (frontPos == 0 and endPos == ARRAYSIZE - 1);
}

bool Queue::isFull()
{
    return frontPos == endPos + 2
            or (frontPos == 0 and endPos == ARRAYSIZE - 2)
            or (frontPos == 1 and endPos == ARRAYSIZE - 1);
}

void Queue::enqueue(const int& e)
{
    if(isFull())
    {
        throw QueueException( "Desbordamiento de datos, enqueue");
    }

    data[endPos = ++endPos == ARRAYSIZE ? 0 : endPos] = e;
}

void Queue::dequeue()
{
    if(isEmty())
    {
        throw QueueException(" Insuficiencia de datos, dequeue");
    }

    int result(data[frontPos]);

    if(++frontPos == ARRAYSIZE)
    {
        frontPos = 0;
    }
}

int Queue::getFront()
{
    if(isEmty())
    {
        throw QueueException(" Insuficiencia de datos, getFront");
    }

    return data[frontPos];
}

Queue& Queue::operator=(const Queue& q)
{
    copyAll(q);

    return *this;
}
