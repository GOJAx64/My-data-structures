#include <iostream>
#include <chrono>
#include <random>
#include <functional>

#include "btree.h"

using namespace std;

int main() {
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> intDistribution(111, 999);
    auto intDice = bind(intDistribution, generator);

    BTree<int> myArbol;
    ///BTree<int>::Node* pos;
    int data;

    try {
    for(int i(0); i < 20; i++) {
        data = intDice();

        cout << " Insertando: " << data << endl;

        myArbol.insertData(data);
        }
    }
    catch(BTree<int>::Exception ex) {
        cout << ex.what() << endl;
        }

    cout << endl << endl;

    cout << " Altura del arbol: " << myArbol.getHeight() << endl;
    /*
    cout << endl << endl;

    myArbol.parseInOrder();

    cout << endl << endl;

    cout << " Eliminar elemento: ";
    cin>>ing;

    pos = myArbol.findData(ing);

    if(pos != nullptr) {
        myArbol.deleteData(pos);
    }

    cout << endl << endl;

    myArbol.parseInOrder();
    */
    cout << endl << endl;

    return 0;
    }
