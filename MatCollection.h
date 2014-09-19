
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
#ifndef MATCOLLECTION_H
#define MATCOLLECTION_H

#include "MatrixMulti.h"
#include <QObject>
#include "ProgressBar.h"

class MatCollection : public QObject {

    Q_OBJECT

public:
       
    MatCollection() {}

    MatCollection(InputTable *table, int frame, bool userSlide);
    MatCollection(InputTable *table, int userBeg, int userEnd, bool userSlide);

    ~MatCollection() {}

    const std::vector<MatrixMulti> GetCollection();
    const std::vector<std::string> GetCollRows();
    const std::vector<std::string> GetColNames();
    bool IsSlide();
    int GetFrameSize();
    int GetTotal();
    int GetBegin();

private:
    int frameSize;
    InputTable *mainTable;
    std::vector<MatrixMulti> collection;
    int begin;
    int total;
    ProgressBar *loadProgress;
    bool slide;
      
    std::vector<MatrixMulti> FillCollection();
    
};


#endif
