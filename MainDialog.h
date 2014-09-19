#ifndef MAINDIALOG_H
#define MAINDIALOG_H

// See what more to add later
#include <QtGui>
#include <QApplication>
#include <QDialog>
#include "InputTable.h"
#include "MatCollection.h"
#include "EdgeFinder.h"
#include "CsvOutput.h"
//#include "MetricsFinder.h"
#include "ActorSelectionDialog.h"
#include "MetricsDialog.h"
#include "TwoModeEdges.h"
#include <vector>
#include <string>

class QPushButton;
class QComboBox;
class QLabel;
class QSpinBox;
class QCheckBox;

class MainDialog : public QDialog {

    Q_OBJECT

public:
    MainDialog(QWidget *parent=0);

signals:
    void sendFile(const QString &file, const QString &sep);

private slots:
    void getFile();
    void setSep(const QString &selection);
    void setNetworkType(const QString &selection);
    void enableNetwork();
    void fireFileSend();
    void enableCalc();
    void calculateNetwork();
    void getDetails();
    void setGranularity(int value);
    void resetFileImport();
    void setLowerBound(int value);
    void setUpperBound(int value);
    void chooseGranBound(const QString &selection);
    void findEdges();
    void enableEdges();
    void enableSave();
    void saveEdgesFile();
    //void enableMetrics();
    //void openMetricsDialog();
    void openAgentDialog();
    void closing();
   
private:
    QLabel *topLabel;
    QLabel *middleLabel;
    QLabel *lowerLabel;
    QString fileName;
    QString sep; 
    QString networkType;
    QPushButton *openFile;
    QComboBox *sepSelector;
    QPushButton *importFile;
    InputTable *inputTable;
    QComboBox *networkSelector;
    QPushButton *exitButton;
    MatCollection *matCollection;
    QPushButton *goNetwork;
    std::vector<std::string> tableHeader;
    std::vector<std::string> nameList;
    int maxGranularity;  
    int curGranularity;
    QLabel *granLabel;
    QSpinBox *chooseGranularity;
    int lowerBound;
    int upperBound;
    QSlider *chooseLowerBound;
    QSlider *chooseUpperBound;
    QSpinBox *monitorUpper;
    QSpinBox *monitorLower;
    QLabel *lowerMonLabel;
    QLabel *upperMonLabel;
    EdgeFinder *edgeFinder;
    QPushButton *goEdges;
    QPushButton *saveEdges;
    QPushButton *openMetrics;
    QString selectedAgent;
    QLabel *agentLabel;
    QLabel *currentAgent;
    QPushButton *changeAgent;
    QCheckBox *slide;
    TwoModeEdges *twoModeEdges;

};

#endif
