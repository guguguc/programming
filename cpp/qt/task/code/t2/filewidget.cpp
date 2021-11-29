#include "filewidget.h"

FileWidget::FileWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileWidget())
{

}

FileWidget::~FileWidget()
{
    delete ui;
}
