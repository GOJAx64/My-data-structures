#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <string>
#include <exception>

///Definicion

template <class T>
class Stack
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
            T data;
            Node* next;

        public:
            Node();
            Node(const T&);

            T& getData();
            Node* getNext() const;

            void setData(const T&);
            void setNext(Node*);
        };

    Node* anchor;

    void copyAll(const Stack&);

    void deleteAll();

    public:

    Stack();
    Stack(const Stack&);

    ~Stack();

    bool isEmpty() const;

    void push(const T&);
    T pop();

    T& getTop();

    Stack& operator = (const Stack&);
};

///Implementacion

using namespace std;

///Node

template <class T>
Stack<T>::Node::Node() : next(nullptr) { }

template <class T>
Stack<T>::Node::Node(const T& e) : data(e), next(nullptr) { }

template <class T>
T& Stack<T>::Node::getData()
{
   return data;
}

template <class T>
typename Stack<T>::Node* Stack<T>::Node::getNext() const
{
    return next;
}

template <class T>
void Stack<T>::Node::setData(const T& e)
{
    data = e;
}

template <class T>
void Stack<T>::Node::setNext(Stack<T>::Node* p)
{
    next = p;
}

///Stack

///private

template <class T>///Copiar Stack
void Stack<T>::copyAll(const Stack<T>& l)
{
    Node* aux(l.anchor);
    Node* lastInserted(nullptr);
    Node* newNode;

    while(aux != nullptr)
    {
        newNode = new Node(aux->getData());

        if(newNode == nullptr)
        {
            throw Exception("Memoria no disponible, copyAll");
        }

        if(lastInserted == nullptr)
        {
            anchor = newNode;
        }
        else
        {
            lastInserted->setNext(newNode);
        }

        lastInserted = newNode;

        aux = aux->getNext();
    }
}

template <class T>///Borrar todo
void Stack<T>::deleteAll()
{
    Node* aux;

    while(anchor != nullptr)
    {
        aux = anchor;

        anchor = anchor->getNext();

        delete aux;
    }
}

///public

template <class T>///Constructor
Stack<T>::Stack() : anchor(nullptr) { }

template <class T>///Constructor copia
Stack<T>::Stack(const Stack<T>& l) : anchor(nullptr)
{
    copyAll(l);
}

template <class T>///Desconstructor
Stack<T>::~Stack()
{
    deleteAll();
}

template <class T>///Operador de igual
Stack<T>& Stack<T>::operator = (const Stack<T>& l)
{
    deleteAll();

    copyAll(l);

    return *this;
}

template <class T>///Si esta vacia la lista
bool Stack<T>::isEmpty() const
{
    return anchor == nullptr;
}

template <class T>///Insertar Dato
void Stack<T>::push(const T& e)
{
    Node* aux(new Node(e));

    if(aux == nullptr)
    {
        throw Exception(" Memoria no disponible, push");
    }

    aux->setNext(anchor);

    anchor = aux;
}

template <class T>///Eliminar Dato
T Stack<T>::pop()
{
    if(isEmpty())
    {
        throw Exception(" Insuficiencia de datos, pop");
    }

    T result(anchor->getData());

    Node* aux(anchor);

    anchor = anchor->getNext();

    delete aux;

    return result;

}

template <class T>///Recuperar posicion
T& Stack<T>::getTop()
{
    if(isEmpty())
    {
        throw Exception(" Insuficiencia de datos, getTop");
    }

    return anchor->getData();
}

#endif // STACK_H_INCLUDED

