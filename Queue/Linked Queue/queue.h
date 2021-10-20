#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <string>
#include <exception>

///Definicion

template <class T>
class Queue
{
    public:
    class Exception: public std::exception
    {
    private:
        std::string msg;

    public:
        explicit Exception(const char* message) : msg(message) { }

        explicit Exception(const std::string& message) : msg(message) { }

        virtual ~Exception() throw () { }

        virtual const char* what() const throw () {
                return msg.c_str();
        }
    };

    private:
    class Node
    {
        private:
            T* dataPtr;
            Node* prev;
            Node* next;

        public:
            class Exception: public std::exception
            {
            private:
                std::string msg;

            public:
                explicit Exception(const char* message) : msg(message) { }

                explicit Exception(const std::string& message) : msg(message) { }

                virtual ~Exception() throw () { }

                virtual const char* what() const throw () {
                        return msg.c_str();
                }
            };
            Node();
            Node(const T&);

            ~Node();

            T* getDataPtr();
            T& getData();
            Node* getPrev() const;
            Node* getNext() const;

            void setDataPtr(T*);
            void setData(const T&);
            void setPrev(Node*);
            void setNext(Node*);
    };

    Node* headerPtr;

    void copyAll(const Queue&);

    void deleteAll();

    public:

    Queue();
    Queue(const Queue&);

    ~Queue();

    bool isEmpty() const;

    void enqueue(const T&);
    T dequeue();

    T& getFront();

    Queue& operator = (const Queue&);
};

///Implementacion

using namespace std;

///Node

template <class T>
Queue<T>::Node::Node() : dataPtr(nullptr), prev(nullptr), next(nullptr) { }

template <class T>
Queue<T>::Node::Node(const T& e) : dataPtr(new T(e)), prev(nullptr), next(nullptr)
{
    if(dataPtr == nullptr)
    {
        throw Exception(" Memoria no disponible, creando nodo");
    }
}

template <class T>
Queue<T>::Node::~Node()
{
    dataPtr = nullptr;
}

template <class T>
T* Queue<T>::Node::getDataPtr()
{
   return dataPtr;
}

template <class T>
T& Queue<T>::Node::getData()
{
   return *dataPtr;
}

template <class T>
typename Queue<T>::Node* Queue<T>::Node::getPrev() const
{
    return prev;
}

template <class T>
typename Queue<T>::Node* Queue<T>::Node::getNext() const
{
    return next;
}

template <class T>
void Queue<T>::Node::setDataPtr(T* p)
{
    dataPtr = p;
}

template <class T>
void Queue<T>::Node::setData(const T& e)
{
    if(dataPtr == nullptr and (dataPtr = new T(e)) == nullptr)
    {
        throw Exception(" Memoria no disponible, Node::setData.");
    }

    else
    {
        *dataPtr = e;
    }

}

template <class T>
void Queue<T>::Node::setPrev(Queue<T>::Node* p)
{
    prev = p;
}

template <class T>
void Queue<T>::Node::setNext(Queue<T>::Node* p)
{
    next = p;
}

///Queue

///private

template <class T>
void Queue<T>::copyAll(const Queue<T>& l)
{
    if(!l.isEmpty()){
        Node* aux(l.headerPtr->getNext());
        Node* newNode;
        while(aux != l.headerPtr)
        {
            try {
                if(newNode = new Node(aux->getData()) == nullptr)
                {
                    throw Exception(" Memoria no disponible, copyAll");
                }
            } catch (typename Queue<T>::Node::Exception ex)
            {
                throw Exception(ex.what());
            }
        }

    }
}

template <class T>
void Queue<T>::deleteAll()
{
        Node* aux;

        while(headerPtr->getNext() != headerPtr);
        {
            aux = headerPtr->getNext();

            headerPtr->setNext(aux->getNext());

            delete aux;
        }

        headerPtr->setPrev(headerPtr);
}

///public

template <class T>
Queue<T>::Queue() : headerPtr(new Node)
{
    if(headerPtr == nullptr)
    {
        throw Exception(" La memoria no esta disponible, creando la Queue.");
    }

    headerPtr->setPrev(headerPtr);
    headerPtr->setNext(headerPtr);
}

template <class T>
Queue<T>::Queue(const Queue<T>& l) : Queue()
{
    copyAll(l);
}

template <class T>
Queue<T>::~Queue()
{
    deleteAll();

    delete headerPtr;
}

template <class T>
Queue<T>& Queue<T>::operator = (const Queue<T>& l)
{
    deleteAll();

    copyAll(l);

    return *this;
}

template <class T>
bool Queue<T>::isEmpty() const
{
    return headerPtr->getNext() == nullptr;
}

template <class T>
void Queue<T>::enqueue(const T& e)
{
    Node* aux;

    try {
       aux = new Node(e);
    } catch(typename Queue<T>::Node::Exception ex) {
        throw Exception(ex.what());
    }

    if(aux == nullptr)
    {
        throw Exception(" Memoria no disponible, enqueue.");
    }

    aux->setPrev(headerPtr->getPrev());
    aux->setNext(headerPtr);

    headerPtr->getPrev()->setNext(aux);
    headerPtr->setPrev(aux);
}

template <class T>
T Queue<T>::dequeue()
{
    if(isEmpty())
    {
        throw Exception(" Insuficiencia de datos, dequeue.");
    }

    T result(headerPtr->getNext()->getData());

    Node* aux(headerPtr->getNext());

    aux->getPrev()->setNext(aux->getNext());
    aux->getNext()->setPrev(aux->getPrev());

    delete aux;

    return result;
}

template <class T>
T& Queue<T>::getFront()
{
    if(isEmpty())
    {
        throw Exception(" Insuficiencia de dato, getFront");
    }

    return headerPtr->getNext()->getData();
}

#endif // QUEUE_H_INCLUDED

