#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

class HashClass{
    std::vector<int> *data;
    unsigned int tableSize;
    unsigned int dimension;
    int Hash(std::vector<int> key);
    int HashSimple(int key);

 public:
    HashClass(unsigned int dim); 
    
    
    ~HashClass() {
	delete[] data;
    }
    
    void Set(std::vector<int> key, const std::vector<int>& value);  
    std::vector<int> Get(std::vector<int> key);
    bool InUse(std::vector<int> key);
    unsigned int GetTableSize();
    const std::vector<std::vector <int> > GetData();
    
};

#endif
