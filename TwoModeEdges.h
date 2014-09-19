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

    const std::vector<std::vector <short> > GetEdges();
    const std::vector<std::string> GetNames();
    const std::vector<std::string> GetIntervals();
    const std::vector<std::string> GetHeader();

private:
    InputTable *mainTable;
    std::vector<std::vector <short> > edges;
    std::vector<std::string> namesTrans;
    std::vector<std::string> header;
    std::vector<std::string> intervalTrans;
    std::vector<std::vector <short> > rowData;
    ProgressBar *loadProgress;
    
    std::vector<std::string> CalcIntervals();
    std::vector<std::vector <short> > CalcEdges();
};

#endif
