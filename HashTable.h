/*
 Copyright 2014 Wouter Spekkink
 Authors : Wouter Spekkink <wouter.spekkink@gmail.com>
 Website : http://www.wouterspekkink.org

 This file is part of Dynamic Networks.

 DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.

 Copyright 2014 Wouter Spekkink. All rights reserved.

 Dynamic Networks is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Dynamic Networks is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

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
