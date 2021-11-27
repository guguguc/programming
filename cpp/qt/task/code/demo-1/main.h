#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QAbstractButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Main; }
QT_END_NAMESPACE

class Main : public QMainWindow
{
    Q_OBJECT

public:
    Main(QWidget *parent = nullptr);
    ~Main();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    bool checkValidation(const QString &str,
                         const QString &pattern) const;
    void openFileDialog();
    bool saveJson(const QString &filename, const QJsonObject &data);

private:
    Ui::Main *ui;
};
#endif // MAIN_H
