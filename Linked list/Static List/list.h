#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <fstream>
#include <iostream>
#include <string>

#include "listexception.h"

template <class T, int ARRAYSIZE = 1024>
class List
{
private:
    T data[ARRAYSIZE];
    int last;

    bool isValidPos(const int&);

    void copyAll(const List<T, ARRAYSIZE>&);

    void swapData(T&, T&);

    void mergeSortData(const int&, const int&);

    void quickSortData(const int&, const int&);

public:

    List();
    List(const List<T, ARRAYSIZE>&);

    bool isEmpty();
    bool isFull();

    void insertData(const int&, const T&);
    void deleteData(const int&);

    int getFirstPos();
    int getLastPos();
    int getPrevPos(const int&);
    int getNextPod(const int&);

    int findDataL(const T&);
    int findDataB(const T&);


    T& retrieve(const int&);

    void bubbleSortData();
    void shellSortData();
    void insertSortData();
    void selectSortData();
    void mergeSortData();
    void quickSortData();

    std::string toString();

    void deleteAll();

    void writeToDisk(const std::string&);
    void readFromDisk(const std::string&);

    List<T, ARRAYSIZE>& operator = (const List <T, ARRAYSIZE>&);
};

using namespace std;

template <class T, int ARRAYSIZE>///Validacion de posicion
bool List<T, ARRAYSIZE>::isValidPos(const int& p)
{
    return p > -1 and p <= last;
}

template <class T, int ARRAYSIZE>///Copiar lista
void List<T, ARRAYSIZE>::copyAll(const List<T, ARRAYSIZE>& l)
{
    int i(0);

    while(i <= l.last)
    {
        data[i] = l.data[i];

        i++;
    }

    this -> last = l.last;
}

template <class T, int ARRAYSIZE>///Constructor
List<T, ARRAYSIZE>::List() : last(-1) { }

template <class T, int ARRAYSIZE>///Constructor copia
List<T, ARRAYSIZE>::List(const List<T, ARRAYSIZE>& l)
{
    copyAll(l);
}


template <class T, int ARRAYSIZE>///Si esta vacia la lista
bool List<T, ARRAYSIZE>::isEmpty()
{
    return last == - 1;
}

template <class T, int ARRAYSIZE>///Si esta llena la lista
bool List<T, ARRAYSIZE>::isFull()
{
    return last == ARRAYSIZE - 1;
}

template <class T, int ARRAYSIZE>///Insertar Dato
void List<T, ARRAYSIZE>::insertData(const int& p, const T& e)
{
    if(isFull())
    {
        throw ListException("Desbordamiento de datos, insertData");
    }

    if(p != -1 and !isValidPos(p))
    {
        throw ListException("Posicion invalida, insertData");
    }

    int i(last);

    while(i > p)
    {
        data[i + 1] = data[i];

        i--;
    }

    data[p + 1] = e;

    last++;
}

template <class T, int ARRAYSIZE>///Eliminar Dato
void List<T, ARRAYSIZE>::deleteData(const int& p)
{
    if(!isValidPos(p))
    {
        throw ListException("Posicion invalida, deleteData");
    }

    int i(p);

    while(i < last)
    {
        data[i] = data[i + 1];

        i++;
    }

    last--;
}

template <class T, int ARRAYSIZE>///Primera Posicion
int List<T, ARRAYSIZE>::getFirstPos()
{
    if(isEmpty())
    {
        return -1;
    }

    return 0;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getLastPos()///Ultima Posicion
{
    return last;
}

template <class T, int ARRAYSIZE>///Posicion antes
int List<T, ARRAYSIZE>::getPrevPos(const int& p)
{
    if(!isValidPos(p))
    {
        return -1;
    }

    return p - 1;
}

template <class T, int ARRAYSIZE>///Posicion despues
int List<T, ARRAYSIZE>::getNextPod(const int& p)
{
    if(p == last or !isValidPos(p))
    {
        return -1;
    }

    return p + 1;
}

template <class T, int ARRAYSIZE>///Busqueda Lineal
int List<T, ARRAYSIZE>::findDataL(const T& e)
{
    int i(0);
    while(i <= last)
    {
        if(data[i] == e)
        {
            return i;
        }
        i++;
    }
    return -1;
}

template <class T, int ARRAYSIZE>///Busqueda Binaria
int List<T, ARRAYSIZE>::findDataB(const T& e)
{
    int i(0), j(last), m;

    while(i <= j)
    {
        m = (i + j) / 2;

        if(data[m] == e)
        {
            return m;
        }

        if(e < data[m])
        {
            j = m - 1;
        }
        else
        {
            i = m + 1;
        }
    }

    return -1;
}

template <class T, int ARRAYSIZE>///Recuperar posicion
T& List<T, ARRAYSIZE>::retrieve(const int& p)
{
    if(!isValidPos(p))
    {
        throw ListException("Posicion invalida, retrieve");
    }

    return data[p];
}

template <class T, int ARRAYSIZE>///Auxiliar de intercambio.
void List<T, ARRAYSIZE>::swapData(T& a, T& b)
{
    T aux(a);
    a = b;
    b = aux;
}

template <class T, int ARRAYSIZE>///Ordenamiento Burbuja Mejorado
void List<T, ARRAYSIZE>::bubbleSortData()
{
    int i(last), j;
    bool flag;

    do
    {
        flag = false;

        j = 0;
        while(j < i)
        {
            if(data[j] > data[j + 1])
            {
                swapData(data[j], data[j+1]);

                flag = true;
            }

            j++;
        }

        i--;
    }while(flag);
}

template <class T, int ARRAYSIZE>///Ordenamiento por Shell
void List<T, ARRAYSIZE>::shellSortData()
{
    float fact(3.0/4.0);
    int dif((last + 1) * fact), lim, i;

    while(dif > 0)
    {
        lim = last - dif;

        i = 0;
        while(i <= lim)
        {
            if(data[i] > data[i + dif])
            {
                swapData(data[i], data[i + dif]);
            }

            i++;
        }

        dif*= fact;
    }

}

template <class T, int ARRAYSIZE>///Ordenamiento por Insercion
void List<T, ARRAYSIZE>::insertSortData()
{
    int i(1), j;
    T aux;

    while(i <= last)
    {
        aux = data[i];

        j = i;

        while(j > 0 and aux < data[j - 1])
        {
            data[j] = data[j - 1];

            j--;
        }

        if(i != j)
        {
            data[j] = aux;
        }

        i++;
    }

}

template <class T, int ARRAYSIZE>///Ordenamiento por Seleccion
void List<T, ARRAYSIZE>::selectSortData()
{
    int i(0), j, m;

    while(i < last)
    {
        m = i;

        j = i + 1;

        while(j <= last)
        {
            if(data[j] < data[m])
            {
                m = j;
            }

            j++;
        }

        if(i != m)
        {
            swapData(data[i], data[m]);
        }

        i++;
    }

}

template <class T, int ARRAYSIZE>///Ordenamiento por MergeSort
void List<T, ARRAYSIZE>::mergeSortData()
{
    mergeSortData(0, last);
}

template <class T, int ARRAYSIZE>///Ordenamiento por MergeSort
void List<T, ARRAYSIZE>::mergeSortData(const int& leftEdge, const int& rightEdge)
{
    if(leftEdge >= rightEdge)///Criterrio de paro
    {
        return;
    }

    /// Divide y venceras
    int m((leftEdge + rightEdge) / 2);

    mergeSortData(leftEdge, m);
    mergeSortData(m + 1, rightEdge);

    ///Copia temporal
    T temp[ARRAYSIZE];

    for(int z(leftEdge); z <= rightEdge; z++)
    {
        temp[z] = data[z];
    }

    ///Intercalacion
    int i(leftEdge), j(m + 1), x(leftEdge);

    while(i <= m and j <= rightEdge)
    {
        while(i <= m and temp[i] <= temp[j])
        {
            data[x++] = temp[i++];
        }

        if(i <= m)
        {
            while(j <= rightEdge and temp[j] <= temp[i])
            {
                data[x++] = temp[j++];
            }
        }
    }

        while(i <= m)
        {
            data[x++] = temp[i++];
        }
        while(j <= rightEdge)
        {
              data[x++] = temp[j++];
        }
}

template <class T, int ARRAYSIZE>///Ordenamiento por QuickSort
void List<T, ARRAYSIZE>::quickSortData()
{
    quickSortData(0, last);
}

template <class T, int ARRAYSIZE>///Ordenamiento por QuickSort
void List<T, ARRAYSIZE>::quickSortData(const int& leftEdge, const int& rightEdge)
{
    if(leftEdge >= rightEdge)///Criterio de paro
    {
        return;
    }

    ///Separacion
    int i(leftEdge), j(rightEdge);

    while(i < j)
    {
        while(i < j and data[i] <= data[rightEdge])
        {
            i++;
        }

        while(i < j and data[j] >= data[rightEdge])
        {
            j--;
        }

        if(i != j)
        {
            swapData(data[i], data[j]);
        }
    }

    if(i != rightEdge)
    {
        swapData(data[i], data[j]);
    }

    ///Divide y venceras
    quickSortData(leftEdge, i - 1);
    quickSortData(i + 1, rightEdge);
}

template <class T, int ARRAYSIZE>///"Imprimir en pantalla"
string List<T, ARRAYSIZE>::toString()
{
    string result;
    int i(0);

    while(i <= last)
    {
        result+= data[i++].toString() + "\n";

    }

    return result;
}

template <class T, int ARRAYSIZE>///Borrar todo
void List<T, ARRAYSIZE>::deleteAll()
{
    last = -1;
}

template <class T, int ARRAYSIZE>///Escribe un archivo (creacion de archivo)
void List<T, ARRAYSIZE>::writeToDisk(const string& fileName)
{
  ofstream myFile;

  myFile.open(fileName, ios_base::trunc);

  if(!myFile.is_open())
  {
    throw ListException("No se pudo abrir el archivo para escritura");
  }

  int i(0);

  while(i <= last)
  {
    myFile << data[i++] << endl;
  }

  myFile.close();
}

template <class T, int ARRAYSIZE>///Mostrar un archivo (abre un archivo)
void List<T, ARRAYSIZE>::readFromDisk(const string& fileName)
{
    ifstream myFile;
    T data;

    myFile.open(fileName);

    if(!myFile.is_open())
    {
        throw ListException("No se pudo abrir el archivo para lectura");
    }

    deleteAll();

    try
    {
        while(myFile >> data)
        {
            insertData(getLastPos(), data);
        }
    }catch(ListException ex)
    {
        myFile.close();

        string msg("Error durante la lectura de archivo, no se puede insertar; ");
        msg+= ex.what();

        throw ListException(msg);
    }

    myFile.close();
}

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>& List<T, ARRAYSIZE>::operator=(const List<T, ARRAYSIZE>& l)
{
    copyAll(l);

    return *this;
}


#endif // LIST_H_INCLUDED
