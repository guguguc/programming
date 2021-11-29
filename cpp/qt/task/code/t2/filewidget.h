#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>
#include <ui_file.h>

QT_BEGIN_NAMESPACE
namespace Ui { class FileWidget; }
QT_END_NAMESPACE

class FileWidget : public QWidget
{
    Q_OBJECT

public:
    FileWidget(QWidget *parent = nullptr);
    ~FileWidget();

private:
    Ui::FileWidget *ui;
};

#endif // FILEWIDGET_H
