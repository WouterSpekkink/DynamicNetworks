#include "HashTable.h"
#include <vector>
#include <string>

HashClass::HashClass(unsigned int dim) 
{
    tableSize = dim;
    tableSize = (dim * dim);
        dimension = dim;
    // All these vectors will be empty at first.
    data = new std::vector<int>[tableSize];
}

int HashClass::Hash(std::vector<int> key) 
{
    int index = (key[0]) * dimension + key[1];
    return index;
}

void HashClass::Set(std::vector<int> key, const std::vector<int>& value) 
{
    unsigned int index = Hash(key);
    data[index] = value;
}

std::vector<int> HashClass::Get(std::vector<int> key) 
{
    unsigned int index = Hash(key);
    return data[index];
}

bool HashClass::InUse(std::vector<int> key)
{
    unsigned int index = Hash(key);
    if(data[index].empty())
	return false;
    else 
	return true;
}

const std::vector<std::vector <int> > HashClass::GetData() 
{
    std::vector<std::vector<int> > temp;
    for(int i = 0; i != tableSize; i++) {
	temp.push_back(data[i]);
    } 
    return temp;
}
