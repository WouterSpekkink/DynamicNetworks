#include "MetricsFinder.h"
#include "MatrixMulti.h"
#include <sstream>
#include <string>
#include <vector>

MetricsFinder::MetricsFinder(MatCollection *collection, QString agent, bool userSlide)
    : sourceCollection(collection), ego(agent), slide(userSlide)
{
    namesTrans = sourceCollection->GetCollRows();
    intervalTrans = CalcIntervals();
}

std::vector<std::string> MetricsFinder::CalcIntervals() 
{
    std::ostringstream convert; 
    int start = 1;
    int frame = sourceCollection->GetFrameSize();
    int end = frame;
    std::string interval;
    std::vector<std::string> tempCollection;
    
    std::vector<MatrixMulti>::size_type length =  0;
    if(slide) {
	length = sourceCollection->GetTotal();
    } else {
    	std::vector<MatrixMulti>::size_type temp = sourceCollection->GetTotal();
	temp = temp + frame - 1;
	if((temp % frame) > 0) { 
	    length = temp / frame + 1;
	} else {
	    length = temp / frame;
	}
    }
    for(std::vector<MatrixMulti>::size_type i = 0; i != length; i++) {
	convert.str(std::string()); // Clear the stringstream first
	convert << start;
	std::string tempOne = convert.str();
	convert.str(std::string());
	convert << end;
	std::string tempTwo = convert.str();
	interval = tempOne + "-" + tempTwo;
	tempCollection.push_back(interval);
	if(slide) {
	    start++;
	    frame++;
	} else {
	    start = start + frame;
	    if(i == length - 2) {
		int orgFrame = sourceCollection->GetFrameSize();
		int total = sourceCollection->GetTotal();
		end = orgFrame + total - 1;
	    } else {
		end = end + frame;
	    }
	}
	
    }
    return tempCollection;
}

void MetricsFinder::CalcInvolvement()
{
    std::string agent = ego.toStdString(); 
    int agentNumber = 0;

    // Let's make sure that the data vector is cleared.
    dataOne.clear();

    /* Next, we need to know which agent our user wants to
       have the metrics on. */
    for(std::vector<std::string>::size_type i = 0; i != namesTrans.size(); i++) {
	if(agent == namesTrans[i]) {
	    agentNumber = i;
	    break;
	}
    }

    // Initializing some variables
    std::vector<MatrixMulti> currentCollection = sourceCollection->GetCollection();
    
    // I AM NOT SURE WHETHER I NEED A PROGRESS BAR. TRYING WITHOUT FIRST
    
    // Begin Loop
    std::vector<MatrixMulti>::iterator it;
    for(it = currentCollection.begin(); it != currentCollection.end(); it++) {
	// currentMatrix will be the currently selected adjacency matrix
	MatrixMulti currentMatrix = *it;
	const std::vector<std::vector <short> > currentData = currentMatrix.GetPartData();

	// We can now simply select the row and column with the agent number
	std::vector<short> currentRow = currentData[agentNumber];
	short currentCell = currentRow[agentNumber];
	dataOne.push_back(currentCell);
    }
}

void MetricsFinder::CalcDegree()
{
    std::string agent = ego.toStdString(); 
    int agentNumber = 0;

    // Let's make sure that the data vector is cleared.
    dataOne.clear();

    /* Next, we need to know which agent our user wants to
       have the metrics on. */
    for(std::vector<std::string>::size_type i = 0; i != namesTrans.size(); i++) {
	if(agent == namesTrans[i]) {
	    agentNumber = i;
	}
    }

    // Initializing some variables
    std::vector<MatrixMulti> currentCollection = sourceCollection->GetCollection();
    
    // I AM NOT SURE WHETHER I NEED A PROGRESS BAR. TRYING WITHOUT FIRST
    
    // Begin Loop
    std::vector<MatrixMulti>::iterator it;
    for(it = currentCollection.begin(); it != currentCollection.end(); it++) {
	// currentMatrix will be the currently selected adjacency matrix
	MatrixMulti currentMatrix = *it;
	const std::vector<std::vector <short> > currentData = currentMatrix.GetPartData();
	int sum = 0;
	// We can now simply select the row and column with the agent number
	std::vector<short> currentRow = currentData[agentNumber];
	for(std::vector<int>::size_type i = 0; i != currentRow.size(); i++) {
	    int currentCell = currentRow[i];
	    if(i != agentNumber && currentCell > 0) {;
		sum = sum + 1;
	    }
	}
	dataOne.push_back(sum);
    }
}


const std::vector<int> MetricsFinder::GetDataOne()
{
    return dataOne;
}

const std::vector<std::string> MetricsFinder::GetNames()
{
    return namesTrans;
}

const std::vector<std::string> MetricsFinder::GetIntervals()
{
    return intervalTrans;
}

const std::string MetricsFinder::GetEgo()
{
    return ego.toStdString();
}
