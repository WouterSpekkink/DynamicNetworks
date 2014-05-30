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
