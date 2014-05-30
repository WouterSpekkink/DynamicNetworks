#include "MetricsDialog.h"

MetricsDialog::MetricsDialog(QWidget *parent, MatCollection *inputCollection, QString type, QString agent, QString sep)
    : QDialog(parent), collection(inputCollection), networkType(type), ego(agent), Qsep(sep)
{
    metricsFinder = new MetricsFinder();
    message = new QLabel(tr("Choose a metric"));
    metricChoice = new QComboBox;
    metricChoice->addItem(tr("-Choose metric-"));
    if(networkType == "Ego Network - Dynamic") {
	metricChoice->addItem("Involvement");
	metricChoice->addItem("Degree");
    }
    egoMessage = new QLabel("Currently selected node: ");
    egoLabel = new QLabel(ego);
    calculate = new QPushButton(tr("Calculate"));
    save = new QPushButton(tr("Save File"));
    exit = new QPushButton(tr("Exit"));
    save->setEnabled(false);

    connect(metricChoice, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(setMetric(const QString &)));
    connect(calculate, SIGNAL(clicked()), this, SLOT(calculateMetric()));
    connect(save, SIGNAL(clicked()), this, SLOT(saveFile()));
    connect(exit, SIGNAL(clicked()), this, SLOT(close()));
    
    
    QHBoxLayout *labelLayout = new QHBoxLayout;
    labelLayout->addWidget(egoMessage);
    labelLayout->addWidget(egoLabel);
    
    QHBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->addWidget(metricChoice);
    controlLayout->addWidget(calculate);
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(labelLayout);
    mainLayout->addWidget(message);
    mainLayout->addLayout(controlLayout);
    mainLayout->addWidget(save);
    mainLayout->addWidget(exit);

    setLayout(mainLayout);
    setWindowTitle("Metrics");
    setFixedHeight(sizeHint().height());
}

void MetricsDialog::setMetric(const QString &chosen)
{
    metric = chosen;
    save->setEnabled(false);
}

void MetricsDialog::calculateMetric()
{
    /* First we initialize all vectors with data and we delete
       old versions of metricsFinder.*/
    delete metricsFinder;
    
    // Then we can start filling some of them.
    if(metric == "Involvement") {
	metricsFinder = new MetricsFinder(collection, ego, collection->IsSlide());
	metricsFinder->CalcInvolvement();
    }
    if(metric == "Degree") {
	metricsFinder = new MetricsFinder(collection, ego, collection->IsSlide());
	metricsFinder->CalcDegree();
    }
    save->setEnabled(true);   
}

void MetricsDialog::saveFile()
{
    QString QsaveFile = QFileDialog::getSaveFileName(this, tr("Save File"), "", "Comma Delimited Files (*.csv *txt)");
    std::string saveFile = QsaveFile.toStdString();
    std::string sep = Qsep.toStdString();
    if(metric == "Involvement") {
	std::string stdMetric = metric.toStdString();
	CsvOutput(metricsFinder, saveFile, sep, stdMetric);
    }
    if(metric == "Degree") {
	std::string stdMetric = metric.toStdString();
	CsvOutput(metricsFinder, saveFile, sep, stdMetric);
    }
}
