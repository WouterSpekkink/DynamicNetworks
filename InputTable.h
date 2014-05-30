#ifndef INPUTTABLE_H
#define INPUTTABLE_H

#include <QObject>
#include <string>
#include <vector>

class InputTable : public QObject {

    Q_OBJECT

public:
    InputTable(QWidget *parent = 0); 

    void ReadFile(const std::string &file, const char &delim);
    int GetRows();
    int GetCols();
    const std::vector<std::string> GetHeader();
    const std::vector<std::string> GetRowNames();
    const std::vector<std::vector <short> > GetRowData();

    ~InputTable() {}

signals:
    void importFinished();

private slots:
void readData(const QString &fileName, const QString &sep);
    
private:
    std::vector<std::string> header; // This will hold the header of the file
    std::vector<std::string> rowNames; // This will hold the row names
    std::vector<std::vector <short> > rowData; // This will hold the numerical data row-wise
    int nrow;
    int ncol;
  };
#endif
