#include "create2disk.h"
#include "ui_create2disk.h"
#include "diskmanager.h"

Create2disk::Create2disk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create2disk)
{
    ui->setupUi(this);
}

Create2disk::~Create2disk()
{
    delete ui;
}

void Create2disk::on_buttonBox_2_accepted()
{
    QString name=ui->lineEdit->text();
    QString inputdata="";
    ui->textEdit->setPlainText(inputdata);
    string filename = name.toStdString();
    string data = inputdata.toStdString();
    A_Disk.CreateFile(filename, data);
}
