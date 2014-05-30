#ifndef TWOMODEEDGES_H
#define TWOMODEEDGES_H

#include <QObject>
#include <vector>
#include <string>
#include "InputTable.h"
#include "ProgressBar.h"

class TwoModeEdges : public QObject {

    Q_OBJECT

public:
    TwoModeEdges() {};

    TwoModeEdges(InputTable *input);

    ~TwoModeEdges() {};

    const std::vector<std::vector <int> > GetEdges();
    const std::vector<std::string> GetNames();
    const std::vector<std::string> GetIntervals();
    const std::vector<std::string> GetHeader();

private:
    InputTable *mainTable;
    std::vector<std::vector <int> > edges;
    std::vector<std::string> namesTrans;
    std::vector<std::string> header;
    std::vector<std::string> intervalTrans;
    std::vector<std::vector <int> > rowData;
    ProgressBar *loadProgress;
    
    std::vector<std::string> CalcIntervals();
    std::vector<std::vector <int> > CalcEdges();
};

#endif
