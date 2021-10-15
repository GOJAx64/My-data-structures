#include <iostream>
#include <algorithm>
#include "hash.h"
#define INSERT 1
#define DELETE 2
#define SEARCH 3
#define DISPLAY 4
#define EXIT 5

using namespace std;

class Snack{
private:
    string key;
    string name;
public:
    Snack(){}
    Snack(string key, string name){
        this->key = key;
        this->name= name;
    }
    string getKey(){
        return key;
    }
    string getName(){
        return name;
    }
    string toString(){
        return key + " " + name;
    }
    void setKey(string& key){
        this->key = key;
    }
    void setName(string& name){
        this->name= name;
    }
};

void insertSnack(Hash<Snack*>& table){
    string key, name;
    Snack* newSnack;

    cout << "Snack's key: ";
    cin.get();
    getline(cin, key);
    cout << "Snack's name: ";
    getline(cin, name);

    newSnack = new Snack(key,name);
    table.insertPair(newSnack);
}

void deleteSnack(Hash<Snack*>& table){
    string key;
    cout << "Snack's key: ";
    cin.get();
    getline(cin,key);
    table.deletePair(key);
}

void searchSnack(Hash<Snack*>& table){
    string key;
    Snack *snack;
    cout << "Snack's key: ";
    cin.get();
    getline(cin,key);
    snack = table.searchPair(key);
    if(snack){
        cout << "Search: " << snack->toString() << endl;
    }
    else{
        cout << "There's no results" << endl;
    }
}

void displaySnacks(Hash<Snack*>& table){
    cout << "SNACKS' LIST" << endl;
    cout << table.toString() << endl;
    cin.get();
}

void clearScreen(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void pause(){
    cout << "Press any bottom to continue . . .";
    cin.get();
    clearScreen();
}

int menuOption(){
    int option;
    cout << "Main menu" << endl;
    cout << "1) Insert snack" << endl;
    cout << "2) Delete snack" << endl;
    cout << "3) Search snack" << endl;
    cout << "4) Display snacks" << endl;
    cout << "5) Exit" << endl;
    cout << "OPTION: ";
    cin >> option;
    return option;
}

int main(){
    Hash<Snack*> snacksTable(367); //Choose
    bool programIsRunning(true);
    do{
        switch(menuOption()){
            case INSERT:    insertSnack(snacksTable);       break;
            case DELETE:    deleteSnack(snacksTable);       break;
            case SEARCH:    searchSnack(snacksTable);       break;
            case DISPLAY:   displaySnacks(snacksTable);     break;
            case EXIT:      programIsRunning= false;        break;
            default:        cout << "Invalid option" << endl;
        }
        pause();
    }while(programIsRunning);
    return 0;
}
