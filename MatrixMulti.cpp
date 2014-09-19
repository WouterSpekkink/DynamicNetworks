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
#include "MatrixMulti.h"

MatrixMulti::MatrixMulti(InputTable *table, int begin, int end)
    : mainTable(table), frameBegin(begin), frameEnd(end)
{
    partData = CalcMatrix();
}

std::vector<std::vector <short> > MatrixMulti::CalcMatrix() 
{
    std::vector<std::vector <short> > orgMatrix = mainTable->GetRowData();
    std::vector<std::vector <short> > newMatrix;
    std::vector<std::vector <short> >::iterator it;
    for(it = orgMatrix.begin(); it < orgMatrix.end(); it++) {
	std::vector<short> numbers;
	std::vector<short> tempVector = *it;
	for(int i = frameBegin - 1; i != frameEnd; i++) {
	    numbers.push_back(tempVector[i]);
	}
	newMatrix.push_back(numbers);
    }
    std::vector<std::vector <short> > adjMatrix;
    
    for(it = newMatrix.begin(); it != newMatrix.end(); it++) {
	std::vector<short> firstRow = *it;
	std::vector<std::vector <short> >::iterator it2;
	std::vector<short> newRow;
	for(it2 = newMatrix.begin(); it2 != newMatrix.end(); it2++) {
	    std::vector<short> secondRow = *it2;
	    int sum = 0;
	    for(std::vector<short>::size_type i = 0; i != (frameEnd - frameBegin + 1); i++) {
		sum = sum + (firstRow[i] * secondRow[i]);
	    }
	    newRow.push_back(sum);
	}
	adjMatrix.push_back(newRow);
    }
    return adjMatrix;
}


const std::vector<std::vector <short> > MatrixMulti::GetPartData() 
{
    return partData;
}

const std::vector<std::string> MatrixMulti::GetPartRows() 
{
    return mainTable->GetRowNames();
}
