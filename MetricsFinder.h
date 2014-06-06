#ifndef METRICSFINDER
#define METRICSFINDER

#include <QObject>
#include <vector>
#include <string>
#include "MatCollection.h"
#include "ProgressBar.h"

class MetricsFinder : public QObject {

    Q_OBJECT

public:
    MetricsFinder() {}

    /* This will be the constructor for metrics that involve ego
       networks. Maybe create new ones for other types of networks. */
    MetricsFinder(MatCollection *collection, QString agent, bool userSlide);

    ~MetricsFinder() {}

    const::std::vector<int> GetDataOne();
    const::std::vector<std::string> GetNames();
    const::std::vector<std::string> GetIntervals();
    const::std::string GetEgo();
    
    // Calculations requested here.
    void CalcInvolvement();    
    void CalcDegree();
    void CalcModularity();

private:
    MatCollection *sourceCollection;
    ProgressBar *loadProgress;
    QString ego;
    std::vector<std::string> namesTrans;
    std::vector<std::string> intervalTrans;
    std::vector<std::string> CalcIntervals();
    bool slide;


    /* I will probably make new vectors to hold data when necessary. 
       Let's start with just one at first */
    std::vector <int> dataOne;
};

#endif
