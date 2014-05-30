#include <QtGui>

#include "MainDialog.h"
#include <QFileDialog>
#include <QMessageBox>

// Constructor
MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
{
    inputTable = new InputTable();
    matCollection = new MatCollection();
    edgeFinder = new EdgeFinder();
    twoModeEdges = new TwoModeEdges();

    exitButton = new QPushButton(tr("Exit Program"));
    
    topLabel = new QLabel(tr("<h3>File import</h3>"));

    openFile = new QPushButton(tr("Open File"));
    
    sepSelector = new QComboBox(this);
    sepSelector->addItem("-Select a delimiter-");
    sepSelector->addItem(",");
    sepSelector->addItem(";");
    sepSelector->addItem("|");
    sepSelector->addItem("tab");
    
    importFile = new QPushButton(tr("Import"));

    middleLabel = new QLabel(tr("<h3>Network selection</h3>"));

    networkSelector = new QComboBox(this);
    networkSelector->addItem("-Select a network type-");
    networkSelector->addItem("Whole Network - Dynamic");
    networkSelector->addItem("Partial Network - Static");
    networkSelector->addItem("Ego Network - Dynamic");
    networkSelector->addItem("Ego Network - Static");
    networkSelector->addItem("Two Mode Network - Dynamic");
    networkSelector->setEnabled(false);

    agentLabel = new QLabel("Selected Node: ");
    currentAgent = new QLabel("NA");
    changeAgent = new QPushButton(tr("Change Node"));
    changeAgent->setEnabled(false);

    goNetwork = new QPushButton(tr("Start Calculation"));
    goNetwork->setEnabled(false);

    granLabel = new QLabel(tr("Set Granularity: "));
    chooseGranularity = new QSpinBox;
    chooseGranularity->setEnabled(false);
    slide = new QCheckBox(tr("Sliding frame"));
    slide->setEnabled(false);

    chooseLowerBound = new QSlider;
    chooseUpperBound = new QSlider;
    chooseLowerBound->setEnabled(false);
    chooseUpperBound->setEnabled(false);
    monitorLower = new QSpinBox();
    monitorLower->setEnabled(false);
    monitorUpper = new QSpinBox();
    monitorUpper->setEnabled(false);
    lowerMonLabel = new QLabel(tr("Lower Bound: "));
    upperMonLabel = new QLabel(tr("Upper Bound: "));

    lowerLabel = new QLabel(tr("<h3>Edge Finder & Metrics</h3>"));
    
    goEdges = new QPushButton(tr("Find Edges"));
    goEdges->setEnabled(false);

    saveEdges = new QPushButton(tr("Save Edges File"));
    saveEdges->setEnabled(false);

    openMetrics = new QPushButton(tr("Metrics"));
    openMetrics->setEnabled(false);

    connect(openFile, SIGNAL(clicked()), this, SLOT(getFile()));
    connect(sepSelector, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(setSep(const QString &)));
    connect(importFile, SIGNAL(clicked()), this, SLOT(resetFileImport()));
    connect(importFile, SIGNAL(clicked()), this, SLOT(fireFileSend()));
     connect(this, SIGNAL(sendFile(const QString &, const QString &)), inputTable, SLOT(readData(const QString &, const QString &)));
    connect(inputTable, SIGNAL(importFinished()), this, SLOT(enableNetwork()));
    connect(inputTable, SIGNAL(importFinished()), this, SLOT(getDetails()));
    connect(exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(networkSelector, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(setNetworkType(const QString &)));
    connect(networkSelector, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(enableCalc()));
    connect(networkSelector, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(chooseGranBound(const QString &)));
    connect(goNetwork, SIGNAL(clicked()), this, SLOT(calculateNetwork()));
    connect(chooseGranularity, SIGNAL(valueChanged(int)), this, SLOT(setGranularity(int)));
    connect(chooseLowerBound, SIGNAL(valueChanged(int)), this, SLOT(setLowerBound(int)));
    connect(chooseUpperBound, SIGNAL(valueChanged(int)), this, SLOT(setUpperBound(int)));
    connect(chooseLowerBound, SIGNAL(valueChanged(int)), monitorLower, SLOT(setValue(int)));
    connect(chooseUpperBound, SIGNAL(valueChanged(int)), monitorUpper, SLOT(setValue(int)));
    connect(monitorLower, SIGNAL(valueChanged(int)), chooseLowerBound, SLOT(setValue(int)));
    connect(monitorUpper, SIGNAL(valueChanged(int)), chooseUpperBound, SLOT(setValue(int)));
    connect(goNetwork, SIGNAL(clicked()), this, SLOT(enableEdges()));
    connect(goNetwork, SIGNAL(clicked()), this, SLOT(enableMetrics()));
    connect(goEdges, SIGNAL(clicked()), this, SLOT(findEdges()));
    connect(goEdges, SIGNAL(clicked()), this, SLOT(enableSave()));
    connect(saveEdges, SIGNAL(clicked()), this, SLOT(saveEdgesFile()));
    connect(openMetrics, SIGNAL(clicked()), this, SLOT(openMetricsDialog()));
    connect(changeAgent, SIGNAL(clicked()), this, SLOT(openAgentDialog()));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(openFile);
    topLayout->addWidget(sepSelector);
    topLayout->addWidget(importFile);

    QVBoxLayout *granLayout = new QVBoxLayout;
    granLayout->addWidget(granLabel);
    granLayout->addWidget(chooseGranularity);
    granLayout->addWidget(slide);
    granLayout->setContentsMargins(QMargins(11,11,15,11));

    QFrame *sepGranBound = new QFrame();
    sepGranBound->setFrameShape(QFrame::VLine);

    QVBoxLayout *monitorLabels = new QVBoxLayout;
    monitorLabels->addWidget(upperMonLabel);
    monitorLabels->addWidget(lowerMonLabel);
    monitorLabels->setContentsMargins(QMargins(11,11,0,11));
    QVBoxLayout *monitorLayout = new QVBoxLayout;
    monitorLayout->addWidget(monitorUpper);
    monitorLayout->addWidget(monitorLower);
    monitorLayout->setContentsMargins(QMargins(11,11,11,11));
    QHBoxLayout *midMidLayout = new QHBoxLayout;
    midMidLayout->addLayout(granLayout);
    midMidLayout->addWidget(sepGranBound);
    midMidLayout->addLayout(monitorLabels);
    midMidLayout->addLayout(monitorLayout);
    midMidLayout->addWidget(chooseLowerBound);
    midMidLayout->addWidget(chooseUpperBound);

    QVBoxLayout *middleLayout = new QVBoxLayout;
    middleLayout->addWidget(networkSelector);
    QHBoxLayout *agentLayout = new QHBoxLayout;
    agentLayout->addWidget(agentLabel);
    agentLayout->addWidget(currentAgent);
    agentLayout->addWidget(changeAgent);
    agentLayout->setContentsMargins(QMargins(11, 15, 15, 30));
    middleLayout->addLayout(agentLayout);
    middleLayout->addLayout(midMidLayout);
    middleLayout->addWidget(goNetwork);

    QVBoxLayout *lowerMiddleLayout = new QVBoxLayout;
    lowerMiddleLayout->addWidget(goEdges);
    lowerMiddleLayout->addWidget(saveEdges);
    lowerMiddleLayout->addWidget(openMetrics);

    QHBoxLayout *lowerLayout = new QHBoxLayout;
    lowerLayout->addWidget(exitButton);

    QFrame *topLine = new QFrame();
    topLine->setFrameShape(QFrame::HLine);

    QFrame *lowerLine = new QFrame();
    lowerLine->setFrameShape(QFrame::HLine);

    QFrame *sepEdges = new QFrame();
    sepEdges->setFrameShape(QFrame::HLine);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(topLabel);
    topLayout->setContentsMargins(QMargins(15,15,15,15));
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(topLine);
    mainLayout->addWidget(middleLabel);
    middleLayout->setContentsMargins(QMargins(15,15,15,15));
    mainLayout->addLayout(middleLayout);
    mainLayout->addWidget(sepEdges);
    mainLayout->addWidget(lowerLabel);
    lowerMiddleLayout->setContentsMargins(QMargins(15,15,15,15));
    mainLayout->addLayout(lowerMiddleLayout);
    mainLayout->addWidget(lowerLine);
    lowerLayout->setContentsMargins(QMargins(15,15,15,15));
    mainLayout->addLayout(lowerLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Dynamic Networks"));
    setFixedHeight(sizeHint().height());

}

// Private slots

void MainDialog::getFile() 
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"),"","Comma Delimited Files(*.csv *.txt)");
    if(file.isNull() == false) {
	fileName = file;
    }
}

void MainDialog::setSep(const QString &selection)
{
    if(selection == "tab") sep = "\t";
    else sep = selection;
}

void MainDialog::setNetworkType(const QString &selection)
{
    networkType = selection;
    if(networkType == "Ego Network - Dynamic" || networkType == "Ego Network - Static") {
	ActorSelectionDialog *actorSelectionDialog = new ActorSelectionDialog(0, nameList);
	actorSelectionDialog->exec();
	selectedAgent = actorSelectionDialog->GetSelection();
	delete actorSelectionDialog;
	currentAgent->setText(selectedAgent);
    } else if(networkType == "Whole Network - Dynamic" || networkType == "Partial Network - Static"){
	selectedAgent = "NA";
	currentAgent->setText("NA");	
	changeAgent->setEnabled(false);
    } else if(networkType == "Two Mode Network - Dynamic") {
	goEdges->setEnabled(true);
    }

}
 
void MainDialog::enableNetwork()
{
    networkSelector->setEnabled(!fileName.isEmpty() && !sep.isEmpty());
}
	
	
void MainDialog::fireFileSend()
{
    emit sendFile(fileName, sep);
}
       
void MainDialog::calculateNetwork()
{
    if(networkType == "Whole Network - Dynamic" || networkType == "Ego Network - Dynamic") {
	delete matCollection;
	matCollection = new MatCollection(inputTable, curGranularity, slide->isChecked());
    }
    if(networkType == "Partial Network - Static" || networkType == "Ego Network - Static") {
	if(upperBound <= lowerBound) {
	    QMessageBox *warning = new QMessageBox;
	    warning->setIcon(QMessageBox::Critical);
	    warning->setText(tr("Selected bounds are illegal!"));
	    warning->exec();
	} else {
	    delete matCollection;
	    matCollection = new MatCollection(inputTable, lowerBound, upperBound, true);
	}
    }
}

void MainDialog::enableCalc()
{
    goNetwork->setEnabled(!networkType.isEmpty() && networkType != "Two Mode Network - Dynamic");
    if(networkType == "Ego Network - Dynamic" || networkType == "Ego Network - Static") {
	changeAgent->setEnabled(true);
    }
    if(networkType == "Two Mode Network - Dynamic") {
	goEdges->setEnabled(true);
	saveEdges->setEnabled(false);
	openMetrics->setEnabled(false);
    } else {
	goEdges->setEnabled(false);    
	saveEdges->setEnabled(false);
	openMetrics->setEnabled(false);
    }
}

void MainDialog::getDetails()
{
    tableHeader = inputTable->GetHeader();
    nameList = inputTable->GetRowNames();
    maxGranularity = tableHeader.size();
    chooseGranularity->setRange(1, maxGranularity);
    chooseGranularity->setValue(1);
    chooseLowerBound->setRange(1, maxGranularity);
    chooseUpperBound->setRange(1, maxGranularity);
    chooseLowerBound->setValue(1);
    chooseUpperBound->setValue(maxGranularity);
    monitorLower->setRange(1, maxGranularity);
    monitorUpper->setRange(1, maxGranularity);
    monitorUpper->setValue(maxGranularity);
}

void MainDialog::setGranularity(int value)
{
    curGranularity = value;
}

void MainDialog::resetFileImport()
{
    networkSelector->setCurrentIndex(0);
    networkSelector->setEnabled(false);
    chooseGranularity->setEnabled(false);
    chooseLowerBound->setEnabled(false);
    chooseUpperBound->setEnabled(false);
    monitorLower->setEnabled(false);
    monitorUpper->setEnabled(false);
    goNetwork->setEnabled(false);
    goEdges->setEnabled(false);
    saveEdges->setEnabled(false);
    openMetrics->setEnabled(false);
    currentAgent->setText("NA");
    selectedAgent = "NA";
    changeAgent->setEnabled(false);
    slide->setEnabled(false);
}

void MainDialog::setLowerBound(int value)
{
    lowerBound = value;
}

void MainDialog::setUpperBound(int value)
{
    upperBound = value;
}

void MainDialog::chooseGranBound(const QString &selection)
{
    if(selection == "Whole Network - Dynamic" || selection == "Ego Network - Dynamic") {
	chooseGranularity->setEnabled(true);
	chooseLowerBound->setEnabled(false);
	chooseUpperBound->setEnabled(false);
	monitorLower->setEnabled(false);
	monitorUpper->setEnabled(false);
	chooseLowerBound->setValue(1);
	chooseUpperBound->setValue(1);
	chooseGranularity->setValue(1);
	slide->setEnabled(true);
	slide->setCheckState(Qt::Unchecked);
	
    } else if(selection == "Partial Network - Static" || selection == "Ego Network - Static") {
	chooseGranularity->setEnabled(false);
	chooseGranularity->setValue(1);
	chooseLowerBound->setValue(1);
	chooseUpperBound->setValue(maxGranularity);
	chooseLowerBound->setEnabled(true);
	chooseUpperBound->setEnabled(true);
	monitorLower->setEnabled(true);
	monitorUpper->setEnabled(true);
	slide->setEnabled(false);
	slide->setCheckState(Qt::Unchecked);
    } else if(networkType == "Two Mode Network - Dynamic") {
	chooseGranularity->setEnabled(false);
	chooseGranularity->setValue(1);
	chooseLowerBound->setValue(1);
	chooseUpperBound->setValue(maxGranularity);
	chooseLowerBound->setEnabled(false);
	chooseUpperBound->setEnabled(false);
	monitorLower->setEnabled(false);
	monitorUpper->setEnabled(false);
	slide->setEnabled(false);
	slide->setCheckState(Qt::Unchecked);
	currentAgent->setText("NA");
	selectedAgent = "NA";
	changeAgent->setEnabled(false);
    } else if(networkType == "-Select a network type-") {
	chooseGranularity->setEnabled(false);
	chooseGranularity->setValue(1);
	chooseLowerBound->setValue(1);
	chooseUpperBound->setValue(maxGranularity);
	chooseLowerBound->setEnabled(false);
	chooseUpperBound->setEnabled(false);
	monitorLower->setEnabled(false);
	monitorUpper->setEnabled(false);
	slide->setEnabled(false);
	slide->setCheckState(Qt::Unchecked);
	currentAgent->setText("NA");
	selectedAgent = "NA";
	changeAgent->setEnabled(false);
	goNetwork->setEnabled(false);
    }
}

void MainDialog::findEdges() 
{
    if(networkType == "Whole Network - Dynamic" || networkType == "Partial Network - Static") {
	std::string type = networkType.toStdString();
	delete edgeFinder;
	edgeFinder = new EdgeFinder(matCollection, type, slide->isChecked());
    }else if(networkType == "Ego Network - Dynamic" || networkType == "Ego Network - Static") {
	std::string type = networkType.toStdString();
	std::string agent = selectedAgent.toStdString();
	delete edgeFinder;
	edgeFinder = new EdgeFinder(matCollection, type, agent, slide->isChecked()); 
    } else if(networkType == "Two Mode Network - Dynamic") {
	delete twoModeEdges;
	twoModeEdges = new TwoModeEdges(inputTable);
    }
}

void MainDialog::enableEdges() 
{
    if(networkType == "Partial Network - Static" || networkType == "Ego Network - Static") {
	if(upperBound > lowerBound) {
	    goEdges->setEnabled(true);
	    saveEdges->setEnabled(false);
	}
    } else {
	goEdges->setEnabled(true);
	saveEdges->setEnabled(false);
    }
}

void MainDialog::enableMetrics()
{
    if(networkType == "Partial Network - Static" || networkType == "Ego Network - Static") {
	if(upperBound > lowerBound) {
	    openMetrics->setEnabled(true);
	}
    } else {
	openMetrics->setEnabled(true);
    }
}

void MainDialog::enableSave()
{
    saveEdges->setEnabled(true);
}

void MainDialog::saveEdgesFile()
{    
    QString QsaveFile = QFileDialog::getSaveFileName(this, tr("Save File"),"", "Comma Delimited Files (*.csv *.txt)");
    std::string saveFile = QsaveFile.toStdString();
    std::string stdSep = sep.toStdString();
    if(networkType == "Whole Network - Dynamic" || networkType == "Ego Network - Dynamic") {
	std::string type = networkType.toStdString();
	CsvOutput(edgeFinder, type, saveFile, stdSep);
    }
    if(networkType == "Partial Network - Static" || networkType == "Ego Network - Static") {
	std::string type = networkType.toStdString();
	CsvOutput(edgeFinder, type, saveFile, stdSep);
    }
    if(networkType == "Two Mode Network - Dynamic") {
	CsvOutput(twoModeEdges, saveFile, stdSep);
    }
}

void MainDialog::openMetricsDialog()
{
    if(networkType == "Ego Network - Dynamic" || networkType == "Ego Network - Static") {
	MetricsDialog *metricsDialog = new MetricsDialog(0, matCollection, networkType, selectedAgent, sep);
	metricsDialog->exec();
    }
}

void MainDialog::openAgentDialog()
{
    ActorSelectionDialog *actorSelectionDialog = new ActorSelectionDialog(0, nameList);
    actorSelectionDialog->exec();

    selectedAgent = actorSelectionDialog->GetSelection();
    delete actorSelectionDialog;
    currentAgent->setText(selectedAgent);
}

void MainDialog::closing()
{
    delete inputTable;
    delete matCollection;
    delete edgeFinder;
    delete twoModeEdges;
}




