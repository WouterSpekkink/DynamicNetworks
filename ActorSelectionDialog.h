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
