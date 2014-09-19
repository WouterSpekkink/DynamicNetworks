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
#ifndef ACTORSELECTIONDIALOG_H
#define ACTORSELECTIONDIALOG_H

#include <QDialog>
#include <vector>
#include <string>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>

class ActorSelectionDialog : public QDialog {

    Q_OBJECT

public:
    
ActorSelectionDialog(QWidget *parent = 0, std::vector<std::string> nameList = std::vector<std::string>());
    
    QString GetSelection();

    ~ActorSelectionDialog() {};
			      
			     

private slots:
    void setSelection(const QString &chosen);

private:
    std::vector<std::string> choiceList;
    QComboBox *choice;
    QLabel *message;
    QPushButton *choose;
    QString selection;
};
#endif
