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
#include "ProgressBar.h"
#include <QHBoxLayout>

ProgressBar::ProgressBar(QWidget *parent, int min, int max)
    : QDialog(parent), minimum(min), maximum(max)
{
    progress = new QProgressBar;
    progress->setMinimum(minimum);
    progress->setMaximum(maximum);
    QHBoxLayout *barLayout = new QHBoxLayout;
    barLayout->addWidget(progress);
    setLayout(barLayout);
    setWindowTitle(tr("Progress"));
    setFixedHeight(sizeHint().height());
}


void ProgressBar::setProgress(int value) 
{
    progress->setValue(value);
}
