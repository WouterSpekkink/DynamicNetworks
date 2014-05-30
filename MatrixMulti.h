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
    const std::vector<std::vector <short> > GetPartData();
    const std::vector<std::string> GetPartRows();
    
private:
    std::vector<std::vector <short> > rowData;
    int frameBegin;
    int frameEnd;
    InputTable *mainTable;
    std::vector<std::vector <short> > partData;
    std::vector<std::vector <short> > CalcMatrix();

    // CalcMatrix() makes an adjacency matrix for the part
    // of the incidence matrix that is assigned to the 
    // specific instance of this object.
    
};
#endif
