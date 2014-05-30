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
