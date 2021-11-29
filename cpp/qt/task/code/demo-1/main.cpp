#include "main.h"
#include "ui_main.h"

#include <QtWidgets>
#include <QtCore>

Main::Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main)
{
    ui->setupUi(this);
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
}

Main::~Main()
{
    delete ui;
}

void Main::on_pushButton_clicked()
{
    QString p1, p2, p3;
    // 至少一个大写字母, 至少一个小写字母，至少一个数字
    p1 = "^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])[A-Za-z0-9]{6,}$";
    p2 = "^[0-9]{11,11}$";
    bool ret1 = checkValidation(ui->lineEdit->text(), p1);
    bool ret2 = checkValidation(ui->lineEdit_2->text(), p2);
    if (!ret1) {
        ui->label_4->show();
    } else {
        ui->label_4->hide();
    }
    if (!ret2) {
        ui->label_5->show();
    } else {
        ui->label_5->hide();
    }
    if (ret1 && ret2)
    {
        openFileDialog();
    }
}

void Main::on_pushButton_2_clicked()
{
    this->close();
}

bool Main::checkValidation(const QString &str,
                           const QString &pattern) const
{
    QRegularExpression re(pattern);
    auto match = re.match(str);
    return match.hasMatch();
}

void Main::openFileDialog()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("save as"),
                                                    "",
                                                    tr("json file (*.json)"));
    QJsonObject data({ {"username", ui->lineEdit->text()},
                       {"password", ui->lineEdit_2->text()},
                       {"email", ui->lineEdit_3->text()}});
    bool ret = saveJson(filename, data);
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

bool Main::saveJson(const QString &filename, const QJsonObject &data)
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

void testRe()
{
    QRegularExpression re("a pattern");
    auto match = re.match("sd a pattern");
    if (match.hasMatch()) {
        qDebug() << "match!\n"
                 << "pos: " << match.capturedStart();
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Main ui;
    ui.show();
    return app.exec();
}
