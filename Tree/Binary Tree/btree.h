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

        void deleteAll(Node*);

        Node*& getTheLowest(Node*&);

        Node*& getTheHighest(Node*&);

        int getHeigth(Node*&);

        void parsePreOrder(Node*&);

        void parseInOrder(Node*&);

        void parsePostOrder(Node*&);

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

        int getHeigth();

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
    if(r == nullptr) {
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

    if(e < r->getData()) {
        insertData(r->getLeft(), e);
        }
    else {
        insertData(r->getRight(), e);
        }
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
void BTree<T>::deleteAll(BTree<T>::Node* r) {
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
int BTree<T>::getHeigth(BTree<T>::Node*& r) {
    if(r == nullptr) {
        return 0;
        }

    int leftHeigth(getHeigth(r->getLeft()));
    int rightHeigth(getHeigth(r->getRight()));

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
int BTree<T>::getHeigth() {
    return getHeigth(root);
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

#endif // BTREE_H_INCLUDED
