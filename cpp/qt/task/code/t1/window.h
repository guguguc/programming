#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QDialog
{
    Q_OBJECT

private slots:
    void on_btOk_clicked();
    void on_btCancel_clicked();

private:
    bool checkValidation(const QString &str,const QString &pattern) const;
    inline bool saveJsonFile(const QString &filename, const QJsonObject &data);
    inline void openFileDialog();
    inline void clearFiled();

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private:
    Ui::Window *ui;
};
#endif // WINDOW_H
