#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <string>
#include <exception>

///Definicion

template <class T>
class List
{
    public:///Ultima opcion
    ///class Node;
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

    std::string toString();

    void deleteAll();

    List& operator = (const List&);
};

///Implementacion

using namespace std;

///Node

template <class T>
List<T>::Node::Node() : prev(nullptr), next(nullptr) { }

template <class T>
List<T>::Node::Node(const T& e) : data(e), prev(nullptr), next(nullptr) { }

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

template <class T>///Validacion de posicion
bool List<T>::isValidPos(List<T>::Node* p)
{
    Node* aux(anchor);
    while(aux != nullptr)
    {
        if(aux == p)
        {
            return true;
        }

        aux = aux->getNext();
    }

    return false;
}

template <class T>///Copiar lista
void List<T>::copyAll(const List<T>& l)
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
            newNode->setPrev(lastInserted);
        }

        lastInserted = newNode;

        aux = aux->getNext();
    }
}

template <class T>///Constructor
List<T>::List() : anchor(nullptr) { }

template <class T>///Constructor copia
List<T>::List(const List<T>& l) : anchor(nullptr)
{
    copyAll(l);
}

template <class T>///Desconstructor
List<T>::~List()
{
    deleteAll();
}

template <class T>///Operador de igual
List<T>& List<T>::operator = (const List<T>& l)
{
    deleteAll();

    copyAll(l);

    return *this;
}

template <class T>///Si esta vacia la lista
bool List<T>::isEmpty() const
{
    return anchor == nullptr;
}

template <class T>///Insertar Dato
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
        aux->setNext(anchor);

        if(anchor != nullptr)
        {///No esta vacia
            anchor->setPrev(aux);
        }

        anchor = aux;
    }
    else
    {///Insertar en cualquier otra posicion
        aux->setPrev(p);
        aux->setNext(p->getNext());

        if(p->getNext() != nullptr)
        {///Si hay un nado siguiente
            p->getNext()->setPrev(aux);
        }

        p->setNext(aux);
    }
}

template <class T>///Eliminar Dato
void List<T>::deleteData(List<T>::Node* p)
{
    if(!isValidPos(p))
    {
        throw Exception(" Posicion invalida, deleteData.");
    }

    if(p->getPrev() != nullptr)
    {///Si hay un anterior
        p->getPrev()->setNext(p->getNext());
    }

    if(p->getNext() != nullptr)
    {///Si hay un siguiente
        p->getNext()->setPrev(p->getPrev());
    }

    if(p == anchor)
    {///Eliminando el primero
        anchor = anchor->getNext();
    }

    delete p;
}

template <class T>///Primera Posicion
typename List<T>::Node* List<T>::getFirstPos() const
{
    return anchor;
}

template <class T>///Ultima Posicion
typename List<T>::Node* List<T>::getLastPos() const
{
    if(isEmpty())
    {
        return nullptr;
    }

    Node* aux(anchor);
    while(aux->getNext() != nullptr)
    {
        aux = aux->getNext();
    }

    return aux;
}

template <class T>///Posicion antes
typename List<T>::Node* List<T>::getPrevPos(List<T>::Node* p) const
{
    if(!isValidPos(p))
    {
        return nullptr;
    }

    return p->getPrev();
}

template <class T>///Posicion despues
typename List<T>::Node* List<T>::getNextPos(List<T>::Node* p) const
{
    if(!isValidPos(p))
    {
        return nullptr;
    }

    return p->getNext();
}

template <class T>///Busqueda
typename List<T>::Node* List<T>::findData(const T& e) const
{
    Node* aux(anchor);
    while(aux != nullptr and aux->getData() != e)
    {
        aux = aux->getNext();
    }

    return aux;
}

template <class T>///Recuperar posicion
T& List<T>::retrieve(List<T>::Node* p)
{
    if(!isValidPos(p))
    {
        throw Exception(" Posicion invalida, retireve");
    }

    return p->getData();
}

template <class T>///"Imprimir en pantalla"
std::string List<T>::toString()
{
    std::string result;

    Node* aux(anchor);
    while(aux != nullptr)
    {
        result += aux->getData().toString() + "\n";

        aux = aux->getNext();
    }

    return result;
}

template <class T>///Borrar todo
void List<T>::deleteAll()
{
    Node* aux;

    while(anchor != nullptr)
    {
        aux = anchor;

        anchor = anchor->getNext();

        delete aux;
    }
}

#endif // LIST_H_INCLUDED

