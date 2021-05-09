#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ColorWidget())
{

}

ColorWidget::~ColorWidget()
{
    delete ui;
}
