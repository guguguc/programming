#include "main.h"
#include "ui_main.h"

Main::Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main)
{
    ui->setupUi(this);

}

Main::~Main()
{
    delete ui;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Main main;
    main.show();
    return app.exec();
}

