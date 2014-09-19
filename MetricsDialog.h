/*
 Copyright 2014 Wouter Spekkink
 Authors : Wouter Spekkink <wouter.spekkink@gmail.com>
 Website : http://www.wouterspekkink.org

 This file is part of Dynamic Networks.

 DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.

 Copyright 2014 Wouter Spekkink. All rights reserved.

 Dynamic Networks is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Dynamic Networks is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

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
