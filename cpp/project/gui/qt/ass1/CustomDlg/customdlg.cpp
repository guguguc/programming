#include "customdlg.h"
#include "ui_customdlg.h"
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>

#define FONT_SIZE 40
#define LETTER_SPACE 7

CustomDlg::CustomDlg(const QString &strNumber, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CustomDlg)
{
    ui->setupUi(this);
    m_pWdt = new CustomWdt(strNumber);
    ui->layout->addWidget(m_pWdt);
    resize(600, 200);
}

CustomDlg::~CustomDlg()
{
    delete ui;
}

void CustomDlg::setMask(int left, int right)
{
    m_pWdt->setMask(left, right);
}

CustomWdt::CustomWdt(const QString &strNumber, QWidget *parent)
    : QWidget(parent)
    , m_strNumber(strNumber)
    , m_leftIndex(0)
    , m_rightIndex(0)
{
}

void CustomWdt::setMask(int left, int right)
{
    m_leftIndex = left;
    m_rightIndex = right;
    m_left = size().width();
    int szNumber = m_strNumber.size();
    int szLabel = FONT_SIZE * szNumber + LETTER_SPACE * (szNumber - 1);
    m_left -= szLabel;
    m_left /= 2;
    qInfo() << m_left;
    m_right = m_left + szLabel;
    update();
}

void CustomWdt::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QFont font("Arial");
    font.setPixelSize(FONT_SIZE);
    font.setLetterSpacing(QFont::AbsoluteSpacing, LETTER_SPACE);
    painter.setFont(font);
    QString strDisp(m_strNumber);
    for (int i = m_leftIndex; i < m_rightIndex; ++i)
        strDisp[i] = '*';
    QFontMetrics fm(font);
    int pixelWidth = fm.horizontalAdvance(m_strNumber);
    double left = (double)(width() - pixelWidth) * 0.5;
    painter.drawText(rect(), Qt::AlignCenter, strDisp);
    painter.fillRect(left, 0, pixelWidth, 10, Qt::gray);
    QWidget::paintEvent(e);
}

void CustomWdt::mousePressEvent(QMouseEvent *e)
{
    e->ignore();
}

void CustomWdt::mouseMoveEvent(QMouseEvent *e)
{

}

void CustomWdt::mouseReleaseEvent(QMouseEvent *e)
{

}
/*
bool CustomWdt::isAccept() const
{
    return true;
}
*/
