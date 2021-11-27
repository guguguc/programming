#ifndef CUSTOMDLG_H
#define CUSTOMDLG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class CustomDlg; }
QT_END_NAMESPACE

class CustomWdt : public QWidget
{
public:
    CustomWdt(const QString &strNumber, QWidget *parent=nullptr);
    void setMask(int left, int right);
private:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
private:
    QString m_strNumber;
    int m_leftIndex;
    int m_rightIndex;
    int m_left;
    int m_right;
    int m_cur;
};

class CustomDlg : public QDialog
{
    Q_OBJECT

public:
    CustomDlg(const QString &strNumber, QWidget *parent = nullptr);
    void setMask(int left, int right);
    ~CustomDlg();

private:
    Ui::CustomDlg *ui;
    CustomWdt *m_pWdt;
};

#endif // CUSTOMDLG_H
