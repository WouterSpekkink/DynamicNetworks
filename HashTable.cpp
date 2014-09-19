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
