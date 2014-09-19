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
#include "MatCollection.h"

MatCollection::MatCollection(InputTable *table, int frame, bool userSlide)
    : mainTable(table), frameSize(frame), slide(userSlide) 
{
    begin = 1;
    total = mainTable->GetCols() - frame + 1;
    collection = FillCollection();
}

MatCollection::MatCollection(InputTable *table, int userBeg, int userEnd, bool userSlide) 
    : mainTable(table), begin(userBeg), slide(userSlide)
{
    total = (userEnd - userBeg + 1);
    frameSize = 1; 
    collection = FillCollection();
}


std::vector<MatrixMulti> MatCollection::FillCollection() 
{
  int beg = begin;
  int end = beg + frameSize - 1;
  std::vector<MatrixMulti> tempcol;
  int finish = 0;
  if(slide) {
      finish = total;
  } else {
      int temp = mainTable->GetCols();
      if((temp % frameSize) > 0) {
	  finish = temp / frameSize + 1;
      } else {
	  finish = temp / frameSize;
      }
  }
  loadProgress = new ProgressBar(0, 1, finish);
  loadProgress->setAttribute(Qt::WA_DeleteOnClose);
  loadProgress->setModal(true);
  loadProgress->show();
  for(int i = 0; i != finish; ++i) {
      MatrixMulti temp(mainTable, beg, end); 
      tempcol.push_back(temp);
      if(slide) {
	  beg++;
	  end++;
      } else {
	  beg = beg + frameSize;
	  if(!((end + frameSize) > (total + frameSize - 1))) {
	      end = end + frameSize;
	  } else {
	      end = total + frameSize - 1;
	  }
	  
      }   
      loadProgress->setProgress(i + 1);
  }
  loadProgress->close();
  delete loadProgress;
  return tempcol;
}

const std::vector<MatrixMulti> MatCollection::GetCollection() 
{
  return collection;
}

const std::vector<std::string> MatCollection::GetCollRows() 
{
  return mainTable->GetRowNames();
}

const std::vector<std::string> MatCollection::GetColNames() 
{
  return mainTable->GetHeader();
}

bool MatCollection::IsSlide() 
{
    return slide;
}

int MatCollection::GetFrameSize() 
{
  return frameSize;
}

int MatCollection::GetTotal() 
{
  return total;
}

int MatCollection::GetBegin() 
{
  return begin;
}

