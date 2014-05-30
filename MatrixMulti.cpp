#include "MatrixMulti.h"

MatrixMulti::MatrixMulti(InputTable *table, int begin, int end)
    : mainTable(table), frameBegin(begin), frameEnd(end)
{
    partData = CalcMatrix();
}

std::vector<std::vector <int> > MatrixMulti::CalcMatrix() 
{
    std::vector<std::vector <int> > orgMatrix = mainTable->GetRowData();
    std::vector<std::vector <int> > newMatrix;
    std::vector<std::vector <int> >::iterator it;
    for(it = orgMatrix.begin(); it < orgMatrix.end(); it++) {
	std::vector<int> numbers;
	std::vector<int> tempVector = *it;
	for(int i = frameBegin - 1; i != frameEnd; i++) {
	    numbers.push_back(tempVector[i]);
	}
	newMatrix.push_back(numbers);
    }
    std::vector<std::vector <int> > adjMatrix;
    
    for(it = newMatrix.begin(); it != newMatrix.end(); it++) {
	std::vector<int> firstRow = *it;
	std::vector<std::vector <int> >::iterator it2;
	std::vector<int> newRow;
	for(it2 = newMatrix.begin(); it2 != newMatrix.end(); it2++) {
	    std::vector<int> secondRow = *it2;
	    int sum = 0;
	    for(std::vector<int>::size_type i = 0; i != (frameEnd - frameBegin + 1); i++) {
		sum = sum + (firstRow[i] * secondRow[i]);
	    }
	    newRow.push_back(sum);
	}
	adjMatrix.push_back(newRow);
    }
    return adjMatrix;
}


const std::vector<std::vector <int> > MatrixMulti::GetPartData() 
{
    return partData;
}

const std::vector<std::string> MatrixMulti::GetPartRows() 
{
    return mainTable->GetRowNames();
}
