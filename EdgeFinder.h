#ifndef EDGEFINDER_H
#define EDGEFINDER_H

#include <QObject>
#include <vector>
#include <string>
#include "MatCollection.h"
#include "ProgressBar.h"

class EdgeFinder : public QObject {
  
    Q_OBJECT

public:
    EdgeFinder() {}

    // This constructor expects that a type of network is indicated
    EdgeFinder(MatCollection *collection, std::string userType, bool userSlide);

    // This constructor also expects an ego
    EdgeFinder(MatCollection *collection, std::string userType, std::string agent, bool userSlide);

    ~EdgeFinder() {}

    const std::vector<std::vector <int> > GetEdges();
    const std::vector<std::string> GetNames();
    const std::vector<std::string> GetIntervals();
    const std::vector<std::string> GetAttributeInterval();
    const std::vector<std::string> GetHeader();

private:
    MatCollection *sourceCollection;
    std::vector<std::vector <int> > edges;
    std::vector<std::string> namesTrans;
    std::vector<std::string> intervalTrans;
    std::vector<std::string> attributeInterval;
    std::string networkType;
    std::string ego;
    bool slide;
    ProgressBar *loadProgress;
    
    /* CalcIntervals() creates the translation list for time intervals
       CalcEdges fills the vector of edges */
    std::vector<std::string> CalcIntervals(bool weight);
    std::vector<std::vector <int> > CalcEdges();
    std::vector<std::vector <int> > CalcEdges(std::string agent);

    /* The collection is the collection of adjacency matrices that 
       we will get our edges from. namesTrans and intervalTrans are
       used to translate the edges (stored as ints) to source and target
       names and to strings that represent time intervals.
       networkType is used to determine what type of network should be 
       created. */

};

#endif
