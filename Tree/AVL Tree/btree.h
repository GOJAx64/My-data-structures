/*
    Optimizar el arbol:
    - atributo de saber cual es la altura de cada sub-arbol
    - atributo de lista doblemente ligados (Cada hijo sabe cual es su padre)

    Elemento faltante:
    - Eliminar dato
*/

#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include <exception>
#include <string>

template <class T>
class BTree {
    public:
        class Node {
            private:
                T* dataPtr;
                Node* left;
                Node* right;

            public:
                class Exception : public std::exception {
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

                Node*& getLeft();
                Node*& getRight();

                void setDataPTr(T*);
                void setData(const T&);
                void setLeft(Node*&);
                void setRight(Node*&);
            };

        class Exception : public std::exception {
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
        Node* root;

        void copyAll(Node*&, Node*&);

        void insertData(Node*&, const T&);

        Node*& findData(Node*&, const T&);

        void deleteAll(Node*&);

        Node*& getTheLowest(Node*&);

        Node*& getTheHighest(Node*&);

        int getHeight(Node*&);

        void parsePreOrder(Node*&);

        void parseInOrder(Node*&);

        void parsePostOrder(Node*&);

        int getBalanceFactor(Node*&);

        void doSimpleLeftRot(Node*&);

        void doSimpleRightRot(Node*&);

        void doDoubleLeftRot(Node*&);

        void doDoubleRightRot(Node*&);

        void doBalancing(Node*&);

        void swapData(T&, T&);

    public:
        BTree();
        BTree(const BTree&);

        ~BTree();

        bool isEmpty() const;

        void insertData(const T&);

        Node*& findData(const T&);

        T& retrieve(Node*&);

        void parsePreOrder();

        void parseInOrder();

        void parsePostOrder();

        void deleteData(Node*&);

        bool isLeaf(Node*&) const;

        int getHeight();

        void deleteAll();

        BTree& operator = (const BTree&);
    };

///Nodo

template <class T>
BTree<T>::Node::Node() : dataPtr(nullptr), left(nullptr), right(nullptr) { }

template <class T>
BTree<T>::Node::Node(const T& e) : dataPtr(new T(e)), left(nullptr), right(nullptr) {
    if(dataPtr == nullptr) {
        throw Exception(" Memoria no disponible, creando nodo");
        }
    }

template <class T>
BTree<T>::Node::~Node() {
    delete dataPtr;
    }

template <class T>
T* BTree<T>::Node::getDataPtr() {
    return dataPtr;
    }

template <class T>
T& BTree<T>::Node::getData() {
    return *dataPtr;
    }

template <class T>
typename BTree<T>::Node*& BTree<T>::Node::getLeft() {
    return left;
    }

template <class T>
typename BTree<T>::Node*& BTree<T>::Node::getRight() {
    return right;
    }

template <class T>
void BTree<T>::Node::setDataPTr(T* p) {
    dataPtr = p;
    }

template <class T>
void BTree<T>::Node::setData(const T& e) {
    if(dataPtr == nullptr and (dataPtr = new T(e)) == nullptr) {

        throw Exception(" Memoria no disponible, Node::setData");
        }
    else {
        *dataPtr = e;
        }
    }

template <class T>
void BTree<T>::Node::setLeft(BTree<T>::Node*& p) {
    left = p;
    }

template <class T>
void BTree<T>::Node::setRight(BTree<T>::Node*& p) {
    right = p;
    }

///BTree

///private

template <class T>
void BTree<T>::copyAll(Node*& orig, Node*& dest) {
    if(orig == nullptr) {
        return;
        }

    dest = new Node(orig->getData());

    copyAll(orig->getLeft(), dest->getLeft());
    copyAll(orig->getRight(), dest->getRight());
    }

template <class T>
void BTree<T>::insertData(BTree<T>::Node*& r, const T& e) {
    if(r == nullptr) { ///Inserta como hoja (balanceada) (no recursivo)
        try {
            if((r = new Node(e)) == nullptr) {
                throw Exception(" Memoria no disponible, insertData.");
                }
            }
        catch(typename Node::Exception ex) {
            throw Exception(ex.what());
            }

        return;
        }

    ///Insercion recursiva
    if(e < r->getData()) {
        insertData(r->getLeft(), e);
        }
    else {
        insertData(r->getRight(), e);
        }
    ///Aqui sale de la recursion

    ///Revisar factor de equilibrio, aplicar rotaciones
    doBalancing(r);
    }

template <class T>
typename BTree<T>::Node*& BTree<T>::findData(BTree<T>::Node*& r, const T& e) {
    if(r == nullptr or r->getData() == e) {
        return r;
        }

    if(e < r->getData()) {
        return findData(r->getLeft(), e);
        }
    else {
        return findData(r->getRight(), e);
        }
    }

template <class T>
void BTree<T>::deleteAll(BTree<T>::Node*& r) {
    if(r == nullptr) {
        return;
        }

    deleteAll(r->getLeft());
    deleteAll(r->getRight());

    delete r;

    r = nullptr;
    }

template <class T>
typename BTree<T>::Node*& BTree<T>::getTheLowest(BTree<T>::Node*& r) {
    if(r == nullptr or r->getLeft() == nullptr) {
        return r;
        }

    return getTheLowest(r->getLeft());
    }

template <class T>
typename BTree<T>::Node*& BTree<T>::getTheHighest(BTree<T>::Node*& r) {
    if(r == nullptr or r->getRight() == nullptr) {
        return r;
        }

    return getTheHighest(r->getRight());
    }

template <class T>
int BTree<T>::getHeight(BTree<T>::Node*& r) {
    if(r == nullptr) {
        return 0;
        }

    int leftHeigth(getHeight(r->getLeft()));
    int rightHeigth(getHeight(r->getRight()));

    return (leftHeigth > rightHeigth ? leftHeigth : rightHeigth) + 1;
    }

template <class T>
void BTree<T>::parsePreOrder(BTree<T>::Node*& r) {
    if(r == nullptr) {
        return;
        }

    std::cout << r->getData() << ", ";
    parsePreOrder(r->getLeft());
    parsePreOrder(r->getRight());
    }

template <class T>
void BTree<T>::parseInOrder(BTree<T>::Node*& r) {
    if(r == nullptr) {
        return;
        }

    parseInOrder(r->getLeft());
    std::cout << r->getData() << ", ";
    parseInOrder(r->getRight());
    }

template <class T>
void BTree<T>::parsePostOrder(BTree<T>::Node*& r) {
    if(r == nullptr) {
        return;
        }

    parsePostOrder(r->getLeft());
    parsePostOrder(r->getRight());
    std::cout << r->getData() << ", ";
    }


template <class T>
void BTree<T>::swapData(T& a, T& b) {
    T aux;

    aux = a;
    a = b;
    b= aux;
    }

///public

template <class T>
BTree<T>::BTree() : root(nullptr) { }

template <class T>
BTree<T>::BTree(const BTree<T>& t) : root(nullptr) {
    copyAll(t.root, root);
    }

template <class T>
BTree<T>::~BTree() {
    deleteAll();
    }

template <class T>
bool BTree<T>::isEmpty() const {
    return root == nullptr;
    }

template <class T>
void BTree<T>::insertData(const T& e) {
    insertData(root, e);
    }

template <class T>
typename BTree<T>::Node*& BTree<T>::findData(const T& e) {
    return findData(root, e);
    }

template <class T>
T& BTree<T>::retrieve(BTree<T>::Node*& r) {
    if(r == nullptr) {
        throw Exception(" Posicion invalida, retireve.");
        }

    return r->getData();
    }

template <class T>
void BTree<T>::parsePreOrder() {
    parsePreOrder(root);
    }

template <class T>
void BTree<T>::parseInOrder() {
    parseInOrder(root);
    }

template <class T>
void BTree<T>::parsePostOrder() {
    parsePostOrder(root);
    }

template <class T>
void BTree<T>::deleteData(BTree<T>::Node*& r) {
    if(r == nullptr) {
        throw Exception(" Posicion invalida, deleteData.");
        }

    if(isLeaf(r)) {
        delete r;

        r = nullptr;

        return;
        }

    Node*& substitute(r->getLeft() != nullptr ? getTheHighest(r->getLeft()) : getTheLowest(r->getRight()));

    swapData(r->getData(), substitute->getData());

    deleteData(substitute);
    }

template <class T>
bool BTree<T>::isLeaf(BTree<T>::Node*& r) const {
    return r != nullptr and r->getLeft() == r->getRight();
    }

template <class T>
int BTree<T>::getHeight() {
    return getHeight(root);
    }

template <class T>
void BTree<T>::deleteAll() {
    deleteAll(root);
    }

template <class T>
BTree<T>& BTree<T>::operator=(const BTree<T>& t) {
    deleteAll();

    copyAll(t);

    return *this;
    }

template <class T>
int BTree<T>::getBalanceFactor(BTree<T>::Node*& r) {
    return getHeight(r->getRight()) - getHeight(r->getLeft());
    }

template <class T>
void BTree<T>::doSimpleLeftRot(BTree<T>::Node*& r) {
    Node* aux1(r->getRight());
    Node* aux2(aux1->getLeft());

    r->setRight(aux2);
    aux1->setLeft(r);
    r = aux1;
    }

template <class T>
void BTree<T>::doSimpleRightRot(BTree<T>::Node*& r) {
    Node* aux1(r->getLeft());
    Node* aux2(aux1->getRight());

    r->setLeft(aux2);
    aux1->setRight(r);
    r = aux1;
    }

template <class T>
void BTree<T>::doDoubleLeftRot(BTree<T>::Node*& r) {
    doSimpleRightRot(r->getRight());
    doSimpleLeftRot(r);
    }

template <class T>
void BTree<T>::doDoubleRightRot(BTree<T>::Node*& r) {
    doSimpleLeftRot(r->getLeft());
    doSimpleRightRot(r);
    }

template <class T>
void BTree<T>::doBalancing(BTree<T>::Node*& r) {
    switch(getBalanceFactor(r)) {
    case 2: ///Desbalanceo a la derecha, aplicar rotacion a la izquierda.
        if(getBalanceFactor(r->getRight()) == 1) { ///Coincide signo, simple
            std::cout << " RSI - " << r->getData() << std::endl;
            doSimpleLeftRot(r);
            }
        else { ///No coincide signo, doble
            std::cout << " RDI - " << r->getData() << std::endl;
            doDoubleLeftRot(r);
        }

        break;

    case -2: ///Desbalanceo a la izquierda, aplicar rotacion a la derecha.
        if(getBalanceFactor(r->getLeft()) == -1) { ///Coincide signo, simple
            std::cout << " RSD - " << r->getData() << std::endl;
            doSimpleRightRot(r);
            }
        else { ///No coincide signo, double
            std::cout << " RDD - " << r->getData() << std::endl;
            doDoubleRightRot(r);
        }

        break;
        }
    }

#endif // BTREE_H_INCLUDED
