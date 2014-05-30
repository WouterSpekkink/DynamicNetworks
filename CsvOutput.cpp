#include "CsvOutput.h"
#include <fstream>
#include <QFileDialog>

bool CsvOutput(MatrixMulti *matrix, std::string filename, std::string sep) 
{
    std::ofstream fileOut(filename.c_str()); 
    if(!fileOut.is_open()) {
	return false;
    }
    MatrixMulti *outputMatrix = matrix; //Pointer to the matrix to be written
    std::vector<std::vector <short> > data = outputMatrix->GetPartData();
    std::vector<std::string> rowNames = outputMatrix->GetPartRows();
    fileOut << sep;
    std::vector<std::string>::iterator it;
    for(it = rowNames.begin(); it != rowNames.end(); it++) {
	fileOut << *it << sep;
    }
    fileOut << '\n';
    
    for(std::vector<std::string>::size_type i = 0; i != rowNames.size(); i++) {
	fileOut << rowNames[i] << sep;
	std::vector<short> currentRow = data[i];
	std::vector<short>::iterator it2;
	for(it2 = currentRow.begin(); it2 != currentRow.end(); it2++) {
	    fileOut << *it2 << sep;
	}
	fileOut << '\n';  
    }
    fileOut.close();
    return true;
}
  
bool CsvOutput(MatCollection *collection, std::string filename, std::string sep) 
{
    std::ofstream fileOut(filename.c_str()); 
    if(!fileOut.is_open()) {
	return false;
    }
    std::vector<MatrixMulti> outputCol = collection->GetCollection();
    std::vector<MatrixMulti>::iterator collit;
    for(collit = outputCol.begin(); collit != outputCol.end(); collit++) {
	MatrixMulti currentMat = *collit;
	std::vector<std::vector <short> > data = currentMat.GetPartData();
	std::vector<std::string> rowNames = currentMat.GetPartRows();
	fileOut << sep;
	std::vector<std::string>::iterator it;
	for(it = rowNames.begin(); it != rowNames.end(); it++) {
	    fileOut << *it << sep;
	}
	fileOut << '\n';
	
	for(std::vector<std::string>::size_type i = 0; i != rowNames.size(); i++) {
	    fileOut << rowNames[i] << sep;
	    std::vector<short> currentRow = data[i];
	    std::vector<short>::iterator it2;
	    for(it2 = currentRow.begin(); it2 != currentRow.end(); it2++) {
		fileOut << *it2 << sep;
	    }
	    fileOut << '\n';  
	}
    }
    fileOut.close();
    return true;
}
  
bool CsvOutput(EdgeFinder *edges, std::string networkType, std::string filename, std::string sep) {
    std::ofstream fileOut(filename.c_str());
    if(!fileOut.is_open()) {
	return false;
    }
    std::vector<std::vector <int> > myEdges = edges->GetEdges();
    std::vector<std::string> edgeNames = edges->GetNames();
    std::vector<std::string> edgeIntervals = edges->GetIntervals();
    std::vector<std::string> attributeIntervals = edges->GetAttributeInterval();
    std::vector<std::string> colNames = edges->GetHeader();
    
    // Below part write the header
    if(networkType == "Whole Network - Dynamic" || networkType == "Ego Network - Dynamic") {
	fileOut << "Source" << sep << "Target" << sep << "Type" << sep << "Weight" << sep << "Time Interval";
	fileOut << '\n';
    } else if(networkType == "Partial Network - Static" || networkType == "Ego Network - Static") {
	fileOut << "Source" << sep << "Target" << sep << "Type" << sep << "Weight" << sep << "Appearance";
	fileOut << '\n';
    }
    
    std::vector<std::vector <int> >::iterator it;
    for(it  = myEdges.begin(); it != myEdges.end(); it++) {
	// Writing the edges below
	std::vector<int> currentEntry = *it;
	if(!currentEntry.empty()) {      

	    if(networkType == "Whole Network - Dynamic" || networkType == "Ego Network - Dynamic") {
		fileOut << edgeNames[currentEntry[0]] << sep << edgeNames[currentEntry[1]] << sep << "Undirected" << sep;
		fileOut << "<";
		for(unsigned int i = 2; i != currentEntry.size() - 2; i++) {
		    if(i % 2 == 0) { 
			fileOut << attributeIntervals[currentEntry[i]];
		    } else {
			fileOut << currentEntry[i] << "],";
		    }
		}
		fileOut << attributeIntervals[currentEntry[currentEntry.size() - 2]];
		fileOut << currentEntry[currentEntry.size() - 1] << "]>" << sep;
	    }
	    else if(networkType == "Partial Network - Static" || networkType == "Ego Network - Static") {
		fileOut << edgeNames[currentEntry[0]] << sep << edgeNames[currentEntry[1]] << sep << "Undirected" << sep << currentEntry[2] << sep;
	    }
	    
	    if(networkType == "Whole Network - Dynamic" || networkType == "Ego Network - Dynamic") {
		fileOut << "<";
		for(unsigned int i = 2; i != currentEntry.size() - 2; i++) {
		    if(i % 2 == 0) {
			fileOut << edgeIntervals[currentEntry[i]] << ",";
		    }
		}
		fileOut << edgeIntervals[currentEntry[currentEntry.size() - 2]] << ">";
		fileOut << '\n';
				    
	    } else if(networkType == "Partial Network - Static" || networkType == "Ego Network - Static") {
		for(unsigned int i = 3; i != currentEntry.size() - 1; i++) {
		    fileOut << colNames[currentEntry[i]] << " - ";
		}
		fileOut << colNames[currentEntry[currentEntry.size()- 1]];
		fileOut << '\n';
	    }
	}
    }
    fileOut.close();
    return true;
}

bool CsvOutput(MetricsFinder *metrics, std::string filename, std::string sep, std::string metric)
{
    // The implementation should depend on the type of metric to be written
    if(metric == "Involvement" || metric == "Degree") {
	// Let's first initialize some variables.
	std::vector<int> data = metrics->GetDataOne();
	std::vector<std::string> names = metrics->GetNames();
	std::vector<std::string> intervals = metrics->GetIntervals();
	std::string agent = metrics->GetEgo();

	std::ofstream fileOut(filename.c_str());
	if(!fileOut.is_open()) {
	    return false;
	}
	if(metric == "Involvement") {
	    fileOut << "Involvement data for " << agent << ":\n";
	    fileOut << "Time Step" << sep << "Interval" << sep << "Involvement\n";
	}
	if(metric == "Degree") {
	    fileOut << "Degree data for " << agent << ":\n";
	    fileOut << "Time Step" << sep << "Interval" << sep << "Degree\n";
	}
	for(std::vector<int>::size_type i = 0; i != data.size(); i++) {
	    fileOut << "t" << i + 1 << sep;
	    fileOut << intervals[i] << sep;
	    fileOut << data[i] << "\n";
	}
	fileOut.close();
    }
    return true;
}

bool CsvOutput(TwoModeEdges *edges, std::string filename, std::string sep) 
{
    std::ofstream fileOut(filename.c_str());
    if(!fileOut.is_open()) {
	return false;
    }
    std::vector<std::vector <short> > myEdges = edges->GetEdges();
    std::vector<std::string> edgeNames = edges->GetNames();
    std::vector<std::string> edgeIntervals = edges->GetIntervals();
    std::vector<std::string> colNames = edges->GetHeader();
    int weight = 1;
  
    fileOut << "Source" << sep << "Target" << sep << "Type" << sep << "Weight" << sep << "Time Interval\n";
    
    std::vector<std::vector <short> >::iterator it;
    for(it = myEdges.begin(); it != myEdges.end(); it++) {
	std::vector<short> currentEntry = *it;
	if(!currentEntry.empty()) {
	    fileOut << edgeNames[currentEntry[1]] << sep << colNames[currentEntry[0]] << sep << "Undirected" << sep << weight << sep;
	    fileOut << edgeIntervals[currentEntry[0]] ;
	    fileOut << "\n";
	}
    }
    fileOut.close();
    return true;
}
