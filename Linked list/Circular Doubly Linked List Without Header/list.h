#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <string>
#include <exception>

///Definicion

template <class T>
class List
{
    public:
    class Node
    {
    private:
        T data;
        Node* prev;
        Node* next;

    public:
        Node();
        Node(const T&);

        T& getData();
        Node* getPrev() const;
        Node* getNext() const;

        void setData(const T&);
        void setPrev(Node*);
        void setNext(Node*);
    };

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
    Node* anchor;

    bool isValidPos(Node*);

    void copyAll(const List&);

    public:

    List();
    List(const List&);

    ~List();

    bool isEmpty() const;

    void insertData(Node*, const T&);
    void deleteData(Node*);

    Node* getFirstPos() const;
    Node* getLastPos() const;
    Node* getPrevPos(Node*) const;
    Node* getNextPos(Node*) const;

    Node* findData(const T&) const;

    T& retrieve(Node*);

    std::string toString() const;

    void deleteAll();

    List& operator = (const List&);
};

///Implementacion

using namespace std;

///Node

template <class T>
List<T>::Node::Node() : next(nullptr) { }

template <class T>
List<T>::Node::Node(const T& e) : data(e), next(nullptr) { }

template <class T>
T& List<T>::Node::getData()
{
   return data;
}

template <class T>
typename List<T>::Node* List<T>::Node::getPrev() const
{
    return prev;
}

template <class T>
typename List<T>::Node* List<T>::Node::getNext() const
{
    return next;
}

template <class T>
void List<T>::Node::setData(const T& e)
{
    data = e;
}

template <class T>
void List<T>::Node::setPrev(List<T>::Node* p)
{
    prev = p;
}

template <class T>
void List<T>::Node::setNext(List<T>::Node* p)
{
    next = p;
}

///List

template <class T>
bool List<T>::isValidPos(List<T>::Node* p)
{
    if(!isEmpty())
    {
        Node* aux(anchor);
        do
        {
            if(aux == p)
            {
                return true;
            }

            aux = aux->getNext();
        }while(aux != anchor);
    }

    return false;
}

template <class T>
void List<T>::copyAll(const List<T>& l)
{
    if(!l.isEmpty()){
        Node* aux(l.anchor);
        Node* lastInserted(nullptr);
        Node* newNode;
        do{
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
                newNode->setPrev(lastInserted);
            }

            lastInserted = newNode;

            aux = aux->getNext();
        }while(aux != l.anchor);

        lastInserted->setNext(anchor);
        anchor->setPrev(lastInserted);
    }
}

template <class T>
List<T>::List() : anchor(nullptr) { }

template <class T>
List<T>::List(const List<T>& l) : anchor(nullptr)
{
    copyAll(l);
}

template <class T>
List<T>::~List()
{
    deleteAll();
}

template <class T>
List<T>& List<T>::operator = (const List<T>& l)
{
    deleteAll();

    copyAll(l);

    return *this;
}

template <class T>
bool List<T>::isEmpty() const
{
    return anchor == nullptr;
}

template <class T>
void List<T>::insertData(List<T>::Node* p, const T& e)
{
    if(p != nullptr and !isValidPos(p))
    {
        throw Exception(" Posicion invalida, insertData");
    }

    Node* aux(new Node(e));

    if(aux == nullptr)
    {
        throw Exception(" Memoria no disponible, insertData");
    }

    if(p == nullptr)
    {///Insertar al principio
        if(isEmpty()){///Inserta el primer elemento
            aux->setPrev(aux);
            aux->setNext(aux);
        }
        else{///Hay más de un elemento
            aux->setPrev(getLastPos());
            aux->setNext(anchor);

            getLastPos()->setNext(aux);
            anchor->setPrev(aux);
        }

        anchor = aux;
    }
    else
    {///Insertar en cualquier otra posicion
        aux->setPrev(p);
        aux->setNext(p->getNext());

        p->getNext()->setPrev(aux);
        p->setNext(aux);
    }
}

template <class T>
void List<T>::deleteData(List<T>::Node* p)
{
    if(!isValidPos(p))
    {
        throw Exception(" Posicion invalida, deleteData.");
    }

    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrev(p->getPrev());

    if(p == anchor)
    {
        if(p->getNext() == p)
        {///Es el unico que queda
            anchor = nullptr;
        }
        else
        {///Hay mas de un elemento en la lista
            anchor = anchor->getNext();
        }
    }

    delete p;
}

template <class T>
typename List<T>::Node* List<T>::getFirstPos() const
{
    return anchor;
}

template <class T>
typename List<T>::Node* List<T>::getLastPos() const
{
    if(isEmpty())
    {
        return nullptr;
    }

    return anchor->getPrev();
}

template <class T>
typename List<T>::Node* List<T>::getPrevPos(List<T>::Node* p) const
{
    /*if(p == anchor or !isValidPos(p))
    {
        return nullptr;
    }*////Para que el primer elemento no regrese el ultimo.
    if(!isValidPos(p))
    {
        return nullptr;
    }

    return p->getPrev();
}

template <class T>
typename List<T>::Node* List<T>::getNextPos(List<T>::Node* p) const
{
    /*if(p == getLastPos() or !isValidPos(p))
    {
        return nullptr;
    }*////Para que el ultimo elemento no regrese el primero.
    if(!isValidPos(p))
    {
        return nullptr;
    }

    return p->getNext();
}

template <class T>
typename List<T>::Node* List<T>::findData(const T& e) const
{
    if(!isEmpty())
    {
        Node* aux(anchor);
        do
        {
            if(aux->getData() == e)
            {
                return aux;
            }

            aux = aux->getNext();
        }while(aux != anchor);
    }

    return nullptr;
}

template <class T>
T& List<T>::retrieve(List<T>::Node* p)
{
    if(!isValidPos(p))
    {
        throw Exception(" Posicion invalida, retireve");
    }

    return p->getData();
}

template <class T>
std::string List<T>::toString() const
{
    /*if(isEmpty()){
        return "";
    }*/

    std::string result;

    if(!isEmpty()){
        Node* aux(anchor);
        do{
            result += aux->getData().toString() + "\n";

            aux = aux->getNext();
        }while(aux != anchor);
    }

    return result;
}

template <class T>
void List<T>::deleteAll()
{
    if(!isEmpty())
    {
        Node* mark(anchor);
        Node* aux;

        do{
            aux = anchor;

            anchor = anchor->getNext();

            delete aux;
        }while(anchor != mark);

        anchor = nullptr;
    }
}

#endif // LIST_H_INCLUDED

