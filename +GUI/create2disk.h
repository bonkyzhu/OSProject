#ifndef CREATE2DISK_H
#define CREATE2DISK_H

#include <QDialog>

namespace Ui {
class Create2disk;
}

class Create2disk : public QDialog
{
    Q_OBJECT

public:
    explicit Create2disk(QWidget *parent = nullptr);
    ~Create2disk();

private slots:
    void on_buttonBox_2_accepted();

private:
    Ui::Create2disk *ui;
};

#endif // CREATE2DISK_H
