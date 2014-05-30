////////////////////////////////////////////////////
// SHOULD IS STILL MAKE A DECONSTRUCTOR FOR THIS? //
////////////////////////////////////////////////////

#ifndef MATRIXMULTI_H
#define MATRIXMULTI_H
#include <vector>
#include "InputTable.h"

class MatrixMulti {

public:
    MatrixMulti(InputTable *table, int begin, int end);
    const std::vector<std::vector <int> > GetPartData();
    const std::vector<std::string> GetPartRows();
    
private:
    std::vector<std::vector <int> > rowData;
    int frameBegin;
    int frameEnd;
    InputTable *mainTable;
    std::vector<std::vector <int> > partData;
    std::vector<std::vector <int> > CalcMatrix();

    // CalcMatrix() makes an adjacency matrix for the part
    // of the incidence matrix that is assigned to the 
    // specific instance of this object.
    
};
#endif
