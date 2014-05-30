#include "TwoModeEdges.h"
#include <sstream>

TwoModeEdges::TwoModeEdges(InputTable *input) 
    : mainTable(input) 
{
    namesTrans = mainTable->GetRowNames();
    header = mainTable->GetHeader();
    rowData = mainTable->GetRowData();
    intervalTrans = CalcIntervals();
    edges = CalcEdges();
}

std::vector<std::string> TwoModeEdges::CalcIntervals() 
{
    std::string interval;
    std::ostringstream convert;
    std::vector<std::string> tempCollection;
    for(unsigned int i = 0; i != header.size(); i++) {
	convert.str(std::string());
	convert << i + 1;
	std::string tempOne = convert.str();
	convert.str(std::string());
	convert << i + 1;
	std::string tempTwo = convert.str();
	interval = "<[" + tempOne + "," + tempTwo + "]>";
	tempCollection.push_back(interval);
    }
    return tempCollection;
}

std::vector<std::vector <short> > TwoModeEdges::CalcEdges()
{
    int step = 1;
    int max = header.size();
    loadProgress = new ProgressBar(0, 1, max);
    loadProgress->setAttribute(Qt::WA_DeleteOnClose);
    loadProgress->setModal(true);
    loadProgress->show();
    std::vector<std::vector <short> > finalVec;

    for(std::vector<std::string>::size_type i = 0; i != header.size(); i++) {
	for(std::vector<std::vector <int> >::size_type j = 0; j != rowData.size(); j++) {
	    std::vector<short> currentRow = rowData[j];
	    if(currentRow[i] > 0) {
		std::vector<short> tempVec;
		tempVec.push_back(i);
		tempVec.push_back(j);
		finalVec.push_back(tempVec);
	    }
	}
	loadProgress->setProgress(step);
	step++;
    }
    loadProgress->close();
    delete loadProgress;
    return finalVec;
}

const std::vector<std::vector <short> > TwoModeEdges::GetEdges()
{
    return edges;
}

const std::vector<std::string> TwoModeEdges::GetNames()
{
    return namesTrans;
}

const std::vector<std::string> TwoModeEdges::GetIntervals()
{
    return intervalTrans;
}

const std::vector<std::string> TwoModeEdges::GetHeader() 
{
    return header;
}
