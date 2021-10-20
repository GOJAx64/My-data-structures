#include <iostream>
#include <random>
#include <functional>
#include <chrono>

#include "stack.h"

using namespace std;

int main()
{
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> intDistribution(111, 999);
    auto intDice = bind(intDistribution, generator);

    Stack<int> myPila;
    int data;

    for(int i(0); i < 20; i++)
    {
        data = intDice();

        cout << " Apilando: " << data << endl;

        myPila.push(data);
    }

    Stack<int> otherPila;

    otherPila = myPila;

    cout << endl << endl;

    cout << " Volcado de pila: " << endl;

    try
    {
        while(!myPila.isEmpty())
        {
        cout << myPila.pop() << endl;

        }
    }
    catch (Stack<int>::Exception ex)
    {
        cout << ex.what();
    }

    cout << endl << endl;

    cout << endl << endl;

    cout << " Volcado de la OTRA pila: " << endl;

    while(!otherPila.isEmpty())
    {
        cout << otherPila.pop() << endl;
    }

    cout << endl << endl;

    return 0;
}
