#include <iostream>
#include <stdlib.h>
#include <string>

#include "list.h"
#include "student.h"
#include "name.h"
#include "date.h"

using namespace std;

int main()
{
    List<Student> myList;
    Student myStudent;
    ///Name myName;
    ///Date myDate;

    string myStr;
    ///float myFloat;
    ///char op;
    ///int pos;

    /*do
    {
        cout << endl;
        cout << " Codigo: ";
        getline(cin, myStr);
        myStudent.setCode(myStr);

        cout << " Nombre [last,first]:  ";
        getline(cin, myStr, ',');
        myName.setLast(myStr);
        getline(cin, myStr);
        myName.setFirst(myStr);
        myStudent.setName(myName);

        cout << " Fecha de nacimiento [AAAA/MM/DD]: ";
        getline(cin, myStr, '/');
        myDate.setYear(atoi(myStr.c_str()));
        getline(cin, myStr, '/');
        myDate.setMonth(atoi(myStr.c_str()));
        getline(cin, myStr);
        myDate.setDay(atoi(myStr.c_str()));
        myStudent.setBirthDate(myDate);

        cout << " Carrera: ";
        getline(cin, myStr);
        myStudent.setCareer(myStr);

        cout << " Fecha de inicio [AAAA/MM/DD]: ";
        getline(cin, myStr, '/');
        myDate.setYear(atoi(myStr.c_str()));
        getline(cin, myStr, '/');
        myDate.setMonth(atoi(myStr.c_str()));
        getline(cin, myStr);
        myDate.setDay(atoi(myStr.c_str()));
        myStudent.setSartDate(myDate);

        cout << " Promedio: ";
        cin>> myFloat;
        myStudent.setGrade(myFloat);

        try{
            myList.insertData(myList.getLastPos(), myStudent);
        }catch (ListException ex){
            cout << ex.what() << endl;

            break;
        }

        cout << endl << " Estudiante insertado exitosamente" << endl << endl;

        do
        {
            cout << " Insertar otro? (S/N): ";
            cin >> op;
            cin.ignore();

            op = toupper(op);
        }while(op != 'S' and op != 'N');

    }while(op == 'S');

    cout << endl << endl;

    cout << " Contenido de la lista: " << endl << endl;

    cout << myList.toString();

    cout << endl << endl;

    cout << " Escribiendo al disco..." << endl;

    myList.writeToDisk("alumnos");///Creacion del archivo "alumnos"*/


    myList.readFromDisk("alumnos");///Garga el archivo "alumnos"

    cout << endl << endl;

    cout << "Contenido de la lista: " << endl;

    cout << myList.toString() << endl; ///Mostrar el contenido dentro del archivo "alumnos"

    /*cout << " Codigo a buscar: ";
    getline(cin, myStr);

    myStudent.setCode(myStr);

   pos = myList.findDataL(myStudent);///Busqueda Lineal

    cout << endl;

    if(pos == -1)
    {
        cout << " El estudiante con el codigo " << myStr << " no se encuentra en la lista";
    }
    else
    {
       cout << " El estudiante con codigo " << myStr << " esta en la posicion " << pos << " si esta en la lista";
       cout << " Registro completo del estudiante: " << endl;
       cout << myList.retrieve(pos).toString() << endl;
    }*/

    cout << endl;

    /*pos = myList.findDataB(myStudent);///Busqueda Binaria

    cout << endl;

    if(pos == -1)
    {
        cout << " El estudiante con el codigo " << myStr << " no se encuentra en la lista";
    }
    else
    {
        cout << endl << " El estudiante con codigo " << myStr << " esta en la posicion " << pos << " esta en la lista";
        cout << endl << " Registro completo del estudiante: " << endl << endl;
        cout << myList.retrieve(pos).toString() << endl;
    }*/

    /*cout << endl << endl;

    cout << " Ordenando la lista..." << endl; ///Ordenamiento Burbuja Mejorado

    myList.bubbleSortData();

    cout << endl << endl;

    cout << "Contenido de la lista: " << endl;

    cout << myList.toString() << endl;*/


    /*cout << endl << " Ordenando la lista..." << endl; ///Ordenamiento Shell

    myList.shellSortData();

    cout << endl << endl;

    cout << "Contenido de la lista: " << endl;

    cout << myList.toString() << endl;*/


    /*cout << endl << " Ordenando la lista..." << endl; ///Ordenamiento por Insercion

    myList.insertData();

    cout << endl << endl;

    cout << "Contenido de la lista: " << endl;

    cout << myList.toString() << endl;*/

    /*cout << endl << " Ordenando la lista..." << endl; ///Ordenamiento por Seleccion

    myList.selectSortData();

    cout << endl << endl;

    cout << "Contenido de la lista: " << endl;

    cout << myList.toString() << endl;*/

    cout << endl << " Ordenando la lista..." << endl; ///Ordenamiento por MergeSort

    myList.mergeSortData();

    cout << endl << endl;

    cout << "Contenido de la lista: " << endl;

    cout << myList.toString() << endl;

    cout << endl << " Ordenando la lista..." << endl; ///Ordenamiento por QuickSort

    myList.quickSortData();

    cout << endl << endl;

    cout << "Contenido de la lista: " << endl;

    cout << myList.toString() << endl;

    return 0;
}
