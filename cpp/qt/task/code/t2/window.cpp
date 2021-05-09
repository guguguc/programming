#include "window.h"
#include "ui_window.h"
#include "ui_file.h"
#include "ui_color.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);

    m_colorForm = new ColorWidget();
    m_fileForm = new FileWidget();

    ui->stackedWidget->addWidget(m_colorForm);
    ui->stackedWidget->addWidget(m_fileForm);

    connect(ui->btColor, &QPushButton::clicked, this, &Window::navigateColorForm);
    connect(ui->btFile, &QPushButton::clicked, this, &Window::navigateFileForm);
}

Window::~Window()
{
    delete ui;
}

