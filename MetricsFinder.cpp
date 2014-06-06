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

void CalcModularity()
{
    // I'll need a Progress Bar and maybe a Hash table?

    // Let's make sure that the data vector is cleared.
    dataOne.clear();
    
    // THE BELOW ACTUALLY WON'T WORK BECAUSE THE WEIGHTS ARE LACKING. I NEED TO MAKE A NEW MATRIXMULTI COLLECTION HERE MANUALLY. NO PROBS...

    //std::vector<MatrixMulti> currentCollection = sourceCollection->GetCollection();
    //std::vector<short> community;

    // So here is where the algorithm should go
    // I need to iterate through all matrices
    std::vector<MatrixMulti>::iterator it;
    for(it = currentCollection.begin(); it != currentCollection.end(); it++) {
	MatrixMulti currentMatrix = *it;
	const std::vector<std::vector <short> > currentData = currentMatrix.GetPartData();
	for(std::vector<short>::size_type i = 0; i != currentData.size(); i++) { // Should it be .size() or .end()?
	    // First I need to put every node in its own community (C)
	    community.push_back(i);
	}
	// We initially set the modularityGain for each node to 0.0 (Qdelta)
	std::vector<double> modularityGain;
	for(std::vector<short>::size_type i = 0; i != currentData.size(); i++) {
	    modularityGain.push_back(0.0);
	}
	// We initially set the sum of the weights within each community to 0 (E-in).
	std::vector<std::vector <short> > sumWeightsWithinVector;
	for(std::vector<short>::size_type i = 0; i != currentData.size(); i++) {
	    std::vector<short> sumWeightsWithin;
	    for(std::vector<short>::size_type j = 0; j != currentData.size(); j++) {
		sumWeightsWithin.push_back = 0;
	    }
	    sumWeightsWithinVector.push_back(sumWeightsWithin);
	}
	// We initially set the sum of the weights of links incident to nodes in the currentcommunity to 0 (E-tot).
	std::vector<std::vector <short> > sumWeightsTotalVector;
	for(std::vectorstd::vector <short> >size_type i = 0; i != currentData.size(); i++) {
	    std::vector<short> sumWeightsTotal;
	    for(std::vector<short>size_type j = 0; j != currentData.size(); j++) {
		sumWeightsTotal.push_back(0);
	    }
	    sumWeightsTotalVector.push_back(sumWeightsTotal);
	}
	// We initially set the sum of all incident linkages to 0 (k-i).
	std::vector<std::vector <short> > sumIncidentAllVector;
	for(std::vector<short>::size_type i = 0; i != currentData.size(); i++) {
	    std::vector<short> sumIncidentAll;
	    for(std::vector<short>::size_type j = 0; j != currentData.size(); j++) {
		sumIncidentAll.push_back(0);
	    }
	    sumIncidentAllVector.push_back(sumIncidentAll);
	}
	// We initially set the sum of all incident linkages within each community to 0 (k-i,in).
	std::vector<std::vector <short> > sumIncidentCommunityVector;
	for(std::vector<short>::size_type i = 0; i != currentData.size(); i++) {
	    std::vector<short> sumIncidentCommunity;
	    for(std::<short>::size_type j = 0; j != currentData.size(); j++) {
		sumIncidentCommunity.push_back(0);
	    }
	    sumIncidentCommunityVector.push_back(sumIncidentCommunity);
	}
	// We initially set the sum of the weights of all the nodes in the network to 0 (m).
	short sumWeightsNetwork = 0;	

	// The below part should be the iterated part for all matrices
	for(std::vector<short>::size_type i = 0; i != currentData.size(); i++) {
	    // Every node is an i address.
	    std::vector<short> currentNode = currentData[i];
	    for(std::vector<short>::size_type j = 0; j != currentNode.size(); j++) {
		// Each potential neighbor is a j address.
		short currentNeighbor = currentNode[j];
		if(i != j && currentNeighbor > 0) {
		    sumIncident[i] = sumIncident[i] + currentNeighbor; 
		    if(community[i] == community[j]) {
			communityWeight[i] = communityWeight[i] + currentNeighbor;
		    }
		}
	    }
	}
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
