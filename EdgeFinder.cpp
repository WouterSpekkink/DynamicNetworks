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
#include "EdgeFinder.h"
#include "MatrixMulti.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "HashTable.h"

EdgeFinder::EdgeFinder(MatCollection *collection, std::string userType, bool userSlide) 
    : sourceCollection(collection), networkType(userType), slide(userSlide)
{
    namesTrans = sourceCollection->GetCollRows();
    intervalTrans = CalcIntervals(false);
    attributeInterval = CalcIntervals(true);
    edges = CalcEdges();
    slide = sourceCollection->IsSlide();
}

EdgeFinder::EdgeFinder(MatCollection *collection, std::string userType, std::string agent, bool userSlide)
    : sourceCollection(collection), networkType(userType), ego(agent), slide(userSlide)
{
    namesTrans = sourceCollection->GetCollRows();
    intervalTrans = CalcIntervals(false);
    attributeInterval = CalcIntervals(true);
    edges = CalcEdges(ego);
    slide = sourceCollection->IsSlide();
}

std::vector<std::string> EdgeFinder::CalcIntervals(bool weight) 
{
    std::ostringstream convert; 
    int start = 1;
    int frame = sourceCollection->GetFrameSize();
    int end = frame;
    std::string interval;
    std::vector<std::string> tempCollection;
    std::vector<MatrixMulti>::size_type length = 0;
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
	if(weight) {
	    interval = "[" + tempOne + "," + tempTwo + ",";
	}
	else {
	    interval = "[" + tempOne + "," + tempTwo + "]";	 
	}
	tempCollection.push_back(interval);
	if(slide) {
	    start++;
	    end++;
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

std::vector<std::vector <int> > EdgeFinder::CalcEdges() 
{
    /* The standard situation is that frameCount is 0; 
       For other situations we will make if conditionals */
    int frameCount = 0;
    // Initializing some variables and objects
    if(networkType == "Partial Network - Static") {
	frameCount = sourceCollection->GetBegin() - 1;
    }
    
    std::vector<MatrixMulti> currentCollection = sourceCollection->GetCollection();
    std::vector<std::string> rowNames = namesTrans;
    // The dimension of the tables is equal to the number of names
    unsigned int dim = rowNames.size();
    // The size of this hash table is always based on the dimensions
    // of the underlying matrices.
    HashClass edgeHash(dim);
    
    int step = 1;
    int max = currentCollection.size();
    loadProgress = new ProgressBar(0, 1, max);
    loadProgress->setAttribute(Qt::WA_DeleteOnClose);
    loadProgress->setModal(true);
    loadProgress->show();
    
    // Beginning of the loop
    std::vector<MatrixMulti>::iterator it;
    for(it = currentCollection.begin(); it != currentCollection.end(); it++) {
	
	// currentMatrix is the current adjacency matrix
	MatrixMulti currentMatrix = *it;
	const std::vector<std::vector <short> > currentData = currentMatrix.GetPartData();
	
	// Here i iterates through rows
	for(std::vector<std::vector <int> >::size_type i = 0; i != currentData.size(); i++) {  
	    std::vector<short> currentRow = currentData[i];
	    for(std::vector<short>::size_type j = 0; j != currentRow.size(); j++) { 
		int currentCell = currentRow[j];
		
		// We don't want to include the i,j cells of the table, which are self-loops
		if(currentCell > 0 && i != j) {
		    std::vector<int> tempVec;
		    tempVec.push_back(i);
		    tempVec.push_back(j);
		    
		    /* The graph is undirected, so the edge (for example) 2-1 should be
		       treated as being equivalent to 1-2. Therefore we sort the vector.*/
		    sort(tempVec.begin(), tempVec.end());
		    
		    /* We can use tempVec as the key name, but we'll copy it for now,
		       because we are going to change tempVec later. Just to be sure...*/
		    std::vector<int> keyname = tempVec;
		    
		    /* Let's first check whether the keyname in question is already in use
		       If so, then we need to check whether the edge is from the same frame
		       In that case we don't want to do anything with it.
		       If it is from the same frame, then the last entry in the vector
		       at the index should be of the same value as the current value
		       if frameCount.*/
		    
		    if(edgeHash.InUse(keyname)) {
			std::vector<int> tempVec = edgeHash.Get(keyname);
			if(networkType == "Partial Network - Static") {
			    if(tempVec[tempVec.size() - 1] != frameCount) {
				tempVec[2] = tempVec[2] + 1;
				tempVec.push_back(frameCount);
				edgeHash.Set(keyname, tempVec);
			    } 
			} else {
			    if(tempVec[tempVec.size() - 2] != frameCount) {
				tempVec.push_back(frameCount);
				tempVec.push_back(currentCell);
				edgeHash.Set(keyname, tempVec);
			    }
			}
		    } else {
			if(networkType == "Partial Network - Static") {
			    tempVec.push_back(1);
			    tempVec.push_back(frameCount);
			    edgeHash.Set(keyname, tempVec);
			} else {
			    tempVec.push_back(frameCount);
			    tempVec.push_back(currentCell);
			    edgeHash.Set(keyname, tempVec);
			}
		    }
		}
	    }
	}
	loadProgress->setProgress(step);
	step++;
	frameCount++;
    }
    loadProgress->close();
    delete loadProgress;
    return edgeHash.GetData(); 
}    
std::vector<std::vector <int> > EdgeFinder::CalcEdges(std::string agent) 
{ 
    int agentIndex = 0;
    for(std::vector<std::string>::size_type i = 0; i != namesTrans.size(); i++) {
	if(agent == namesTrans[i]) {
	    agentIndex = i;
	    break;
	}
    }
        
    /* The standard situation is that frameCount is 0; 
       For other situations we will make if conditionals */
    int frameCount = 0;
    // Initializing some variables and objects
    if(networkType == "Ego Network - Static") {
	frameCount = sourceCollection->GetBegin() - 1;
    }
    
    std::vector<MatrixMulti> currentCollection = sourceCollection->GetCollection();
    std::vector<std::string> rowNames = namesTrans;
    // The dimension of the tables is equal to the number of names
    unsigned int dim = rowNames.size();
    // The size of this hash table is always based on the dimensions
    // of the underlying matrices.
    HashClass edgeHash(dim);

    
    int step = 1;
    int max = currentCollection.size();
    loadProgress = new ProgressBar(0, 1, max);
    loadProgress->setAttribute(Qt::WA_DeleteOnClose);
    loadProgress->setModal(true);
    loadProgress->show();
    
    // Beginning of the loop
    std::vector<MatrixMulti>::iterator it;
    for(it = currentCollection.begin(); it != currentCollection.end(); it++) {

	// currentMatrix is the current adjacency matrix
	MatrixMulti currentMatrix = *it;
	const std::vector<std::vector <short> > currentData = currentMatrix.GetPartData();
	
	std::vector<short> currentRow = currentData[agentIndex];
	std::vector<short> neighbors;	
	for(std::vector<short>::size_type i = 0; i != currentRow.size(); i++) {
	    int currentCell = currentRow[i];
	    
	    // We don't want to include self loops
	    if(currentCell > 0 && agentIndex != i) {
		std::vector<int> tempVec;
		tempVec.push_back(agentIndex);
		tempVec.push_back(i);
		neighbors.push_back(i);
			    
		/* We can use tempVec as the key name, but we'll copy it for now,
		   because we are going to change tempVec later. Just to be sure...*/
		std::vector<int> keyname = tempVec;
		
		/* Let's first check whether the keyname in question is already in use
		   If so, then we need to check whether the edge is from the same frame
		   In that case we don't want to do anything with it.
		   If it is from the same frame, then the last entry in the vector
		   at the index should be of the same value as the current value
		   if frameCount.*/
		
		if(edgeHash.InUse(keyname)) {
		    std::vector<int> tempVec = edgeHash.Get(keyname);
		    if(networkType == "Ego Network - Static") {
			if(tempVec[tempVec.size() - 1] != frameCount) {
			    tempVec[2] = tempVec[2] + 1;
			    tempVec.push_back((short)frameCount);
			    edgeHash.Set(keyname, tempVec);
			} 
		    } else {
			if(tempVec[tempVec.size() - 2] != frameCount) {
			    tempVec.push_back(frameCount);
			    tempVec.push_back(currentCell);
			    edgeHash.Set(keyname, tempVec);
			}
		    }
		} else {
		    if(networkType == "Ego Network - Static") {
			tempVec.push_back(1);
			tempVec.push_back(frameCount);
			edgeHash.Set(keyname, tempVec);
		    } else {
			tempVec.push_back(frameCount);
			tempVec.push_back(currentCell);
			edgeHash.Set(keyname, tempVec);
		    }
		}
	    }
	}
	for(std::vector<int>::size_type i = 0; i != neighbors.size(); i++) {
	    int currentNeighbor = neighbors[i];
	    std::vector<short> currentRow = currentData[currentNeighbor];
	    for(std::vector<short>::size_type j = 0; j != currentRow.size(); j++) {
		int currentCell = currentRow[j];
		// In this case we also don't want the edge with the original ego 
		if(currentCell > 0 && currentNeighbor != j && j != agentIndex) {
		    std::vector<int> tempVec;
		    tempVec.push_back(currentNeighbor);
		    tempVec.push_back(j);
		    sort(tempVec.begin(), tempVec.end());
		    std::vector<int> keyname = tempVec;
		    if(edgeHash.InUse(keyname)) {
			std::vector<int> tempVec = edgeHash.Get(keyname);
			if(networkType == "Ego Network - Static") {
			    if(tempVec[tempVec.size() - 1] != frameCount) {
				tempVec[2] = tempVec[2] + 1;
				tempVec.push_back(frameCount);
				edgeHash.Set(keyname, tempVec);
			    }
			} else {
			    if(tempVec[tempVec.size() - 2] != frameCount) {
				tempVec.push_back(frameCount);
				tempVec.push_back(currentCell);
				edgeHash.Set(keyname, tempVec);
			    }
			}
		    } else {
			if(networkType == "Ego Network - Static") {
			    tempVec.push_back(1);
			    tempVec.push_back(frameCount);
			    edgeHash.Set(keyname, tempVec);
			} else {
			    tempVec.push_back(frameCount);
			    tempVec.push_back(currentCell);
			    edgeHash.Set(keyname, tempVec);
			}
		    }
		}
	    }
	}
	
	loadProgress->setProgress(step);
	step++;
	frameCount++;
    }
    loadProgress->close();
    delete loadProgress;
    return edgeHash.GetData();
}

const std::vector<std::vector <int> > EdgeFinder::GetEdges()
{
    return edges;
}

const std::vector<std::string> EdgeFinder::GetNames() 
{
    return namesTrans;
}

const std::vector<std::string> EdgeFinder::GetIntervals() 
{
    return intervalTrans;
}
 
const std::vector<std::string> EdgeFinder::GetAttributeInterval()
{
    return attributeInterval;
}

const std::vector<std::string> EdgeFinder::GetHeader() 
{
    return sourceCollection->GetColNames();
}

 
