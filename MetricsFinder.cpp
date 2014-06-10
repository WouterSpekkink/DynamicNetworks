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
    
    std::vector<MatrixMulti> currentCollection = sourceCollection->GetCollection();
    std::vector<short> community;

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
	std::vector<short> sumWeightsWithin;
	for(std::vector<short>::size_type i = 0; i != currentData.size(); i++) {
	    sumWeightsWithin.push_back = 0;
	}
	// We initially set the sum of the weights of links incident to nodes in the currentcommunity to 0 (E-tot).
	std::vector<short> sumWeightsTotal;
	for(std::vector<short>size_type i = 0; i != currentData.size(); j++) {
	    sumWeightsTotal.push_back(0);
	}
	// We initially set the sum of all incident linkages to 0 (k-i).
	std::vector<short> sumIncidentNode;
	for(std::vector<short>::size_type i = 0; i != currentData.size(); i++) {
	      sumIncidentNode.push_back(0);
	}
	// We initially set the sum of all incident linkages within each community to 0 (k-i,in).
	std::vector<short> sumIncidentCommunity;
	for(std::<short>::size_type i = 0; i != currentData.size(); i++) {
	    sumIncidentCommunity.push_back(0);
	}
	// We initially set the sum of the weights of all the nodes in the network to 0 (m).
	short sumWeightsNetwork = 0;	
	// Let's create a variable that tests whether the optimal modularity has been reached for the current matrix.
	bool optimal = false;

	// We do the first iteration to set all variables
	for(std::vector<short>::size_type i = 0; i != currentData.size(); i++) {
	    // Every node is an i address.
	    std::vector<short> currentNode = currentData[i];
	    // Let's calculate all measures that we can calculate on the first run through the list of nodes
	    for(std::vector<short>::size_type j = 0; j != currentNode.size(); j++) {
		// Each potential neighbor is a j address.
		short currentNeighbor = currentNode[j];
		// sum of the weights incident to i
		sumIncidentNode[i] += currentNeighbor;
		// currently, the communities are unique to all nodes, so we can use this formula. We cannot use this later on.
		sumWeightsTotal[i] += currentNeighbor;
		// sum of the weights for the whole network
		sumWeightsNetwork += currentNeighbor;
	    }
	}
	// Then we iterate until optimal modularity is found
    	while (optimal == false) {
	    for(std::vector<short>::size_type i = 0; i != currentData.size(); i++) {
		short currentCommunity = community[i];
		
		// Below is just the formula. I don't know yet whether I call the variables in the right way.
		modularityGain[i] = (((sumWeightsWithin[currentCommunity] + sumIncidentCommunity[i]) / (2 * sumWeightsNetwork)) - ((sumWeightsTotal[currentCommunity] + sumIncidentNode[i]) / (2 * sumWeightsNetwork)) * ((sumWeightsTotal[currentCommunity] + sumIncidentNode[i]) / (2 * sumWeightsNetwork))) - (((sumWeightsWithin[currentCommunity]) / (2 * sumWeightsNetwork)) - ((sumWeightsTotal[currentCommunity] / (2 * sumWeightsNetwork)) * (sumWeightsTotal[currentCommunity] / (2 * sumWeightsNetwork)))  - ((sumIncidentNode[i] / (2 * sumWeightsNetwork)) * (sumIncidentNode[i] / (2 * sumWeightsNetwork))));
		
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
