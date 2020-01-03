#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include "diskmanager.h"
#include "define.h"
#include "dirmanager.h"
#include <map>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QTableWidget* table = new QTableWidget(BLOCKNUM/4,5); //创建一个表格
    table->setWindowTitle("磁盘查看");
    table->resize(700, 800); //设置表格
    table->setHorizontalHeaderLabels(QStringList()<<""<<"内容1"<<"内容2"<<"内容3"<<"内容4"); //设置行头
    vector<string> all_data = A_Disk.show_all();
    for (int i = 0; i < BLOCKNUM/4; i++)
    {
        table->setVerticalHeaderItem(i, new QTableWidgetItem(""));

        for(int j=4*i;j<4*i+4;j++){
           if(all_data[j]!=""){
               QString data = QString::fromStdString(all_data[j]);
               table->setItem(i,j-4*i+1,new QTableWidgetItem(data));
               table->item(i,j-4*i+1)->setBackgroundColor(QColor(255,255,0));
           }
        }

        QString addr = QString::asprintf("%d~%d 块",4*i, 4*i+3);
        table->setItem(i,0,new QTableWidgetItem(addr));
        table->item(i,0)->setBackgroundColor(QColor(0,0,0));
        table->item(i,0)->setTextColor(QColor(255,255,255));
    }
    table->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    bool isOK1;
    bool isOK2, isOK3;
    QString username = QInputDialog::getText(NULL, "","输入你的用户名",
                                                       QLineEdit::Normal,
                                                       "用户名",
                                                       &isOK3);
    QString name = QInputDialog::getText(NULL, "","输入你的文件名",
                                                       QLineEdit::Normal,
                                                       "文件名",
                                                       &isOK1);
    QString inputdata = QInputDialog::getText(NULL, "","输入你的数据",
                                                       QLineEdit::Normal,
                                                       "数据",
                                                       &isOK2);

    if(isOK1 and isOK2 and isOK3) {
        int lenss = inputdata.toStdString().size();
        QString lens = QString::asprintf("%d",lenss);
        QMessageBox::information(NULL, "filename",
                                       "已经写入<br>你的文件名是: <b>" + name + "</b><br>你的数据是: <b>" + inputdata + "</b><br>你的数据大小为是: <b>" + lens + "</b><br>",
                                       QMessageBox::Yes | QMessageBox::No,
                                       QMessageBox::Yes);

        string filename = name.toStdString();
        string data = inputdata.toStdString();
        string user = username.toStdString();
        Dirs.CreatDir(user, filename, "0");
        A_Disk.CreateFile(filename, data);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QTableWidget* table = new QTableWidget(100,4); //创建一个表格
    table->setWindowTitle("展示目录");
    table->resize(700, 800); //设置表格
    table->setHorizontalHeaderLabels(QStringList()<<"文件名"<<"创建时间"<<"用户名"<<"数据"); //设置行头
    map<string,Dir>::iterator it;
    int i = 0;
    for(it=Dirs.DirMap.begin();it!=Dirs.DirMap.end();it++){
      pair<string,Dir> item=*it;
      QString filename = QString::fromStdString(item.second.FileName);
      QString date = QString::fromStdString(item.second.Date);
      QString owner = QString::fromStdString(item.second.FileOwner);
      QString data = QString::fromStdString(A_Disk.ReadFile(item.second.FileName));

      table->setItem(i,0,new QTableWidgetItem(filename));
      table->item(i,0)->setBackgroundColor(QColor(255,255,0));
      table->setItem(i,1,new QTableWidgetItem(date));
      table->item(i,1)->setBackgroundColor(QColor(255,255,0));
      table->setItem(i,2,new QTableWidgetItem(owner));
      table->item(i,2)->setBackgroundColor(QColor(255,255,0));
      table->setItem(i,3,new QTableWidgetItem(data));
      table->item(i,2)->setBackgroundColor(QColor(255,255,0));
      i++;
    }

    table->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    bool isOK1;

    QMessageBox::StandardButton btn;

    QString name = QInputDialog::getText(NULL, "","输入你要删除的文件",
                                                       QLineEdit::Normal,
                                                       "文件名",
                                                       &isOK1);
    QString inputdata = QString::fromStdString(A_Disk.ReadFile(name.toStdString()));

    if(isOK1) {

        btn = QMessageBox::question(NULL, "",
                                       "确认删除文件: <b>" + name + "</b><br>你的数据是: <b>" + inputdata + "</b><br>",
                                       QMessageBox::Yes | QMessageBox::No,
                                       QMessageBox::No);
        if(btn==QMessageBox::Yes){
            string filename = name.toStdString();
            Dirs.DelFile(name.toStdString());
        } else{
            QMessageBox::information(NULL, "",
                                           "已取消删除",
                                           QMessageBox::Yes | QMessageBox::No,
                                           QMessageBox::No);
        }
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QTableWidget* table = new QTableWidget(16,5); //创建一个表格
    table->setWindowTitle("显示内存");
    table->resize(700, 800); //设置表格
    table->setHorizontalHeaderLabels(QStringList()<<"是否为空"<<"线程 id"<<"文件名"<<"数据长度"<<"数据"); //设置行头


    for(int i=0; i<16; i++) {
      QString qsign = QString::asprintf("%d", Mems.Mem[i].sign);
      QString qid = QString::asprintf("%d", Mems.Mem[i].thread_id);
      QString qfilename = QString::fromStdString(Mems.Mem[i].name);
      QString qdatasize = QString::asprintf("%d", Mems.Mem[i].datasize);
      QString qdata = QString::fromStdString(Mems.Mem[i].message);

      table->setItem(i,0,new QTableWidgetItem(qsign));
      table->item(i,0)->setBackgroundColor(QColor(255,255,0));
      table->setItem(i,1,new QTableWidgetItem(qid));
      table->item(i,1)->setBackgroundColor(QColor(255,255,0));
      table->setItem(i,2,new QTableWidgetItem(qfilename));
      table->item(i,2)->setBackgroundColor(QColor(255,255,0));
      table->setItem(i,3,new QTableWidgetItem(qdatasize));
      table->item(i,2)->setBackgroundColor(QColor(255,255,0));
      table->setItem(i,4,new QTableWidgetItem(qdata));
      table->item(i,2)->setBackgroundColor(QColor(255,255,0));
    }

    table->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    bool isOK1;
    bool isOK2;
    QString qname = QInputDialog::getText(NULL, "","输入你的文件名",
                                                       QLineEdit::Normal,
                                                       "文件名",
                                                       &isOK1);
    QString qtid = QInputDialog::getText(NULL, "","输入你的线程id",
                                                       QLineEdit::Normal,
                                                       "id",
                                                       &isOK2);

    if(isOK1 and isOK2) {
        QMessageBox::information(NULL, "filename",
                                       "已经写入<br>你的文件名是: <b>" + qname + "</b><br>你的线程id是: <b>" + qtid + "</b><br>",
                                       QMessageBox::Yes | QMessageBox::No,
                                       QMessageBox::Yes);

        string filename = qname.toStdString();
        int id = qtid.toInt();
        Mems.Alloc(id, filename);
    }
}
