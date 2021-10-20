#include <iostream>
#include <random>
#include <functional>
#include <chrono>

#include "queue.h"

using namespace std;

int main()
{
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> intDistribution(111, 999);
    auto intDice = bind(intDistribution, generator);

    Queue<int> myCola;
    int data;

    try
    {
        for(int i(0); i < 20; i++)
        {
            data = intDice();

            cout << " Encolando: " << data << endl;

            myCola.enqueue(data);
        }
    }
    catch(Queue<int>::Exception ex)
    {
        cout << ex.what() << endl;
    }

    cout << endl << endl;

    cout << " Contenido de la cola: " << endl;

    while(!myCola.isEmpty())
    {
        cout << myCola.getFront() << endl;

        myCola.dequeue();
    }

    cout << endl << endl;

    return 0;
}
