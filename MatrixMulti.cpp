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
