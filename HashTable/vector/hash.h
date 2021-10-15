#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include <vector>

using namespace std;

template <class T>
class Hash{
private:
    vector<T> *table;
    int SLOTS;
    int hashFunction(string key);
    int toInt(string key);
public:
    Hash(int tableSize);
    ~Hash();
    void insertPair(T& e);
    void deletePair(string  key);
    T searchPair(string key);
    string toString();
};

template <class T>
int Hash<T>::hashFunction(string key){
    return toInt(key) % SLOTS; // Division method;
}

template <class T>
int Hash<T>::toInt(string key){
    int result(0);
    for(unsigned int i = 0; i < key.length(); i++){
        result += (int)key[i];
    }
    return 0;
}

template <class T>
Hash<T>::Hash(int tableSize){
    SLOTS = tableSize;
    table = new vector<T>[SLOTS];
}

template <class T>
Hash<T>::~Hash(){
    delete table;
    table = nullptr;
}

template <class T>
void Hash<T>::insertPair(T& e){
    table[hashFunction(e->getKey())].push_back(e);
}

template <class T>
void Hash<T>::deletePair(string key){
    int index = hashFunction(key);
    typename vector<T>::iterator j;
    unsigned int i;
    for (i = 0, j = table[index].begin(); i < table[index].size(); i++, j++) {
        if (table[index][i]->getKey() == key){
            break;
        }
    }
    if (j != table[index].end()){
        table[index].erase(j);
    }
}

template <class T>
T Hash<T>::searchPair(string key){
    int index = hashFunction(key);
    T item(nullptr);
    for (unsigned int i = 0; i < table[index].size(); i++) {
        if (table[index][i]->getKey() == key) {
            item = table[index][i];
            break;
        }
    }
    return  item;
}

template <class T>
string Hash<T>::toString(){
    int i;
    unsigned int j;
    string result="";
    for(i = 0; i < SLOTS; i++){
        for(j = 0; j < table[i].size(); j++){
            result += table[i][j]->toString();
            result += "\n";
        }
    }
    return result;
}

#endif // HASH_H_INCLUDED
