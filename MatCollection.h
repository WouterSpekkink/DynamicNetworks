#ifndef MATCOLLECTION_H
#define MATCOLLECTION_H

#include "MatrixMulti.h"
#include <QObject>
#include "ProgressBar.h"

class MatCollection : public QObject {

    Q_OBJECT

public:
       
    MatCollection() {}

    MatCollection(InputTable *table, int frame, bool userSlide);
    MatCollection(InputTable *table, int userBeg, int userEnd, bool userSlide);

    ~MatCollection() {}

    const std::vector<MatrixMulti> GetCollection();
    const std::vector<std::string> GetCollRows();
    const std::vector<std::string> GetColNames();
    bool IsSlide();
    int GetFrameSize();
    int GetTotal();
    int GetBegin();

private:
    int frameSize;
    InputTable *mainTable;
    std::vector<MatrixMulti> collection;
    int begin;
    int total;
    ProgressBar *loadProgress;
    bool slide;
      
    std::vector<MatrixMulti> FillCollection();
    
};


#endif
