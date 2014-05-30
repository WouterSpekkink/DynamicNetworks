#ifndef CSVOUTPUT_H
#define CSVOUTPUT_H
#include "MatrixMulti.h"
#include "MatCollection.h"
#include "EdgeFinder.h"
#include "MetricsFinder.h"
#include "TwoModeEdges.h"

bool CsvOutput(MatrixMulti *matrix, std::string filename, std::string sep); //Implementation will write a single adjacency matrix
bool CsvOutput(MatCollection *collection, std::string filename, std::string sep); //Implementation will write collection of matrices
bool CsvOutput(EdgeFinder *edges, std::string networkType, std::string filename, std::string sep); // Implementation will write edges file
bool CsvOutput(MetricsFinder *metrics, std::string filename, std::string sep, std::string metric);
bool CsvOutput(TwoModeEdges *edges, std::string filename, std::string sep);

#endif
