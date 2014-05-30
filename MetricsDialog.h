#ifndef METRICSDIALOG_H
#define METRICSDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <vector>
#include "MatCollection.h"
#include "MetricsFinder.h"
#include "CsvOutput.h"

class MetricsDialog : public QDialog {

    Q_OBJECT

public:
    /* This will, at least, be the constructor for the Ego type networks
       I might add other contructors for other types of networks, or
       I'll just add if statements to this one.  */
    MetricsDialog(QWidget *parent = 0, MatCollection *inputCollection = new MatCollection(), QString type = QString(), QString agent = QString(), QString sep = QString());

    ~MetricsDialog() {};

private slots:
    void setMetric(const QString &chosen);
    void calculateMetric();
    void saveFile();

private:
    QString networkType;
    QLabel *message;
    QComboBox *metricChoice;
    QString metric;
    QPushButton *calculate;
    QPushButton *save;
    QPushButton *exit;
    MatCollection *collection;
    MetricsFinder *metricsFinder;
    QString ego;
    QLabel *egoLabel;
    QLabel *egoMessage;
    QString Qsep;
};

#endif
