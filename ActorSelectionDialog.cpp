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
#include "ActorSelectionDialog.h"

ActorSelectionDialog::ActorSelectionDialog(QWidget *parent, std::vector<std::string> nameList)
    : QDialog(parent), choiceList(nameList)
{
    choice = new QComboBox;
    std::vector<std::string>::iterator it;
    choice->addItem(tr("-Choose a node-"));
    for(it = choiceList.begin(); it != choiceList.end(); it++) {
	std::string currentName = *it;
	QString QcurrentName = QString::fromStdString(currentName);
	choice->addItem(QcurrentName);
    }
    message = new QLabel(tr("Choose a node: "));
    choose = new QPushButton(tr("Choose selected"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *choiceLayout = new QHBoxLayout;
    choiceLayout->addWidget(choice);
    choiceLayout->addWidget(choose);
    mainLayout->addWidget(message);
    mainLayout->addLayout(choiceLayout);
    setLayout(mainLayout);
    setWindowTitle(tr("Node Selection"));
    setFixedHeight(sizeHint().height());

    connect(choice, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(setSelection(const QString &)));
    connect(choose, SIGNAL(clicked()), this, SLOT(close()));
}

QString ActorSelectionDialog::GetSelection()
{
    return selection;
}

void ActorSelectionDialog::setSelection(const QString &chosen)
{
    selection = chosen;
}
