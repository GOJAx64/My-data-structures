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
    Node* headerPtr;

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
List<T>::Node::Node() : dataPtr(nullptr), prev(nullptr), next(nullptr) { }

template <class T>
List<T>::Node::Node(const T& e) : dataPtr(new T(e)), prev(nullptr), next(nullptr)
{
    if(dataPtr == nullptr)
    {
        throw Exception(" Memoria no disponible, creando nodo");
    }
}

template <class T>
List<T>::Node::~Node()
{
   delete dataPtr;
}

template <class T>
T* List<T>::Node::getDataPtr()
{
   return dataPtr;
}

template <class T>
T& List<T>::Node::getData()
{
   return *dataPtr;
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
void List<T>::Node::setDataPtr(T* p)
{
    dataPtr = p;
}

template <class T>
void List<T>::Node::setData(const T& e)
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
    Node* aux(headerPtr->getNext());
    while(aux != headerPtr)
    {
        if(aux == p)
        {
            return true;
        }

        aux = aux->getNext();
    }

    return false;
}

template <class T>
void List<T>::copyAll(const List<T>& l)
{
    Node* aux(l.headerPtr->getNext());
    Node* newNode;

    while(aux != l.headerPtr)
    {
        try
        {
            if(newNode = new Node(aux->getData()) == nullptr)
            {
                throw Exception(" Memoria no disponible, copyAll");
            }
        }catch(typename List<T>::Node::Exception ex)
        {
            throw Exception(ex.what());
        }
    }
}

template <class T>
List<T>::List() : headerPtr(new Node)
{
    if(headerPtr == nullptr)
    {
        throw Exception(" La memoria no esta disponible, creando la lista.");
    }

    headerPtr->setPrev(headerPtr);
    headerPtr->setNext(headerPtr);
}

template <class T>
List<T>::List(const List<T>& l) : List()
{
    copyAll(l);
}

template <class T>
List<T>::~List()
{
    deleteAll();

    delete headerPtr;
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
    return headerPtr->getNext() == nullptr;
}

template <class T>
void List<T>::insertData(List<T>::Node* p, const T& e)
{
    if(p != nullptr and !isValidPos(p))
    {
        throw Exception(" Posicion invalida, insertData");
    }

    Node* aux;

    try
    {
        aux = new Node(e);
    }catch(typename List<T>::Node::Exception ex)
    {
        throw Exception(ex.what());
    }

    if(aux == nullptr)
    {
        throw Exception(" Memoria no disponible, insertData");
    }

    if(p == nullptr)
    {///Insertar al principio
        p = headerPtr;
    }

    aux->setPrev(p);
    aux->setNext(p->getNext());

    p->getNext()->setPrev(aux);
    p->setNext(aux);
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

    delete p;
}

template <class T>
typename List<T>::Node* List<T>::getFirstPos() const
{
    if(isEmpty())
    {
        return nullptr;
    }

    return headerPtr->getNext();
}

template <class T>
typename List<T>::Node* List<T>::getLastPos() const
{
    if(isEmpty())
    {
        return nullptr;
    }

    return headerPtr->getPrev();
}

template <class T>
typename List<T>::Node* List<T>::getPrevPos(List<T>::Node* p) const
{
    /*if(p == headerPtr->getNext() or !isValidPos(p))
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
    /*if(p == headerPtr->getPrev() or !isValidPos(p))
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
        Node* aux(headerPtr->getNext());
        while(aux != headerPtr)
        {
            if(aux->getData() == e)
            {
                return aux;
            }

            aux = aux->getNext();
        }
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

    Node* aux(headerPtr->getNext());

    while(aux != headerPtr)
    {
        result += aux->getData().toString() + "\n";

        aux = aux->getNext();
    }

    return result;
}

template <class T>
void List<T>::deleteAll()
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

#endif // LIST_H_INCLUDED

