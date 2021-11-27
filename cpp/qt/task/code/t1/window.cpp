#include "window.h"
#include "ui_window.h"
#include <QtWidgets>


Window::Window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->lbHintUserName->hide();
    ui->lbHintPhoneNumber->hide();
    ui->lbHintMail->hide();
}

void Window::on_btOk_clicked()
{
    QString p1, p2;
    // 至少一个大写字母, 至少一个小写字母，至少一个数字
    p1 = "^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])[A-Za-z0-9]{6,}$";
    p2 = "^[0-9]{11,11}$";
    bool ret1 = checkValidation(ui->leUserName->text(), p1);
    bool ret2 = checkValidation(ui->lePhoneNumber->text(), p2);
    if (!ret1) {
        ui->lbHintUserName->show();
    } else {
        ui->lbHintUserName->hide();
    }
    if (!ret2) {
        ui->lbHintPhoneNumber->show();
    } else {
        ui->lbHintPhoneNumber->hide();
    }
    if (ret1 && ret2)
    {
        openFileDialog();
        clearFiled();
    }
}

void Window::on_btCancel_clicked()
{
    this->close();
}

bool Window::checkValidation(const QString &str,
                           const QString &pattern) const
{
    QRegularExpression re(pattern);
    auto match = re.match(str);
    return match.hasMatch();
}

void Window::openFileDialog()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("save as"),
                                                    "",
                                                    tr("json file (*.json)"));
    QJsonObject data({ {"username", ui->leUserName->text()},
                       {"password", ui->lePhoneNumber->text()},
                       {"email", ui->leMail->text()}});
    bool ret = saveJsonFile(filename, data);
    if (ret)
    {
        QString msg = "写入" + filename + "成功";
        QMessageBox::information(this, tr("提示"), tr(msg.toStdString().c_str()));
    }
    else
    {
        QMessageBox::warning(this, tr("提示"), "写入失败");
    }
}

bool Window::saveJsonFile(const QString &filename, const QJsonObject &data)
{
    QSaveFile file(filename);
    if (!file.open(QSaveFile::WriteOnly))
    {
        QMessageBox::information(this, tr("无法打开文件"), file.errorString());
        return false;
    }
    file.write(QJsonDocument(data).toJson());
    return file.commit();
}

inline void Window::clearFiled()
{
    ui->leUserName->clear();
    ui->lePhoneNumber->clear();
    ui->leMail->clear();
}

Window::~Window()
{
    delete ui;
}

