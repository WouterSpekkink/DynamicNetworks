// This program is ready to be turned into a class now


#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "InputTable.h"


InputTable::InputTable(QWidget *parent) 
    : nrow(0), ncol(0)
{
}

void InputTable::readData(const QString &fileName, const QString &sep) 
{
    const std::string file = fileName.toStdString();
    const std::string delimiter = sep.toStdString();

    // Let's make suer that the data vector is emptied, before making a new one
    rowData.clear();
    header.clear();
    rowNames.clear();
    nrow = 0;
    ncol = 0;
    
    std::istringstream convert(delimiter.c_str());
    char del;
    convert >> del;
           
    ReadFile(file, del);
}

void InputTable::ReadFile(const std::string &inputFile, const char &del) 
{
    std::vector <std::vector <std::string> > dataVector;
    std::ifstream myFile (inputFile.c_str());
    while(myFile) {
	std::string buffer;
	if(!getline(myFile, buffer)) break;
	
	std::istringstream stringStream(buffer);
	std::vector <std::string> record;
		
	while (stringStream) {
	    std::string s;
	    if(!getline(stringStream, s, del)) break;
	    record.push_back(s);
	}
	dataVector.push_back(record);
    }
    
    std::vector<std::vector <std::string> >::iterator it;
    for(it = dataVector.begin(); it != dataVector.end(); it++) {
	if(it == dataVector.begin()) {// The first line is always the header
	    std::vector<std::string> tempVector = *it;
	    std::vector<std::string>::iterator it2;
	    for(it2 = tempVector.begin() + 1; it2 != tempVector.end(); it2++)
		header.push_back(*it2);
	    ncol = header.size(); // - 1 for empty space;
	} else {
	    std::vector<std::string> tempVector = *it;
	    rowNames.push_back(tempVector[0]); // This makes the vector of row names
	    std::vector <std::string>::iterator it2;
	    std::vector <int> numbers;
	    
	    for(it2 = tempVector.begin() + 1; it2 != tempVector.end(); it2++) {
		int tempNumber = 0;
		std::istringstream convert(*it2);
		convert >> tempNumber;
		numbers.push_back(tempNumber);
	    }
	    rowData.push_back(numbers);
	}
    }
    nrow = rowNames.size();
    emit importFinished();
}

int InputTable::GetRows() 
{
    return nrow;
}

int InputTable::GetCols() 
{
    return ncol;
}

const std::vector<std::string> InputTable::GetHeader() 
{
    return header;
}

const std::vector<std::string> InputTable::GetRowNames() 
{
    return rowNames;
}

const std::vector<std::vector <int> > InputTable::GetRowData() 
{
    return rowData;
}





