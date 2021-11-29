#ifndef WINDOW_H
#define WINDOW_H

#include "filewidget.h"
#include "colorwidget.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Window;}
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

public slots:
    void navigateFileForm();
    void navigateColorForm();

private:
    Ui::Window *ui;
    ColorWidget *m_colorForm;
    FileWidget  *m_fileForm;
};
#endif // WINDOW_H
