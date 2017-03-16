/**
  * @file mydialog.cpp - contains class member function of mydialog class
  */

#include <QIcon>

#include "mydialog.h"
#include "ui_mydialog.h"

#define WINDOW_ICON_PATH    ":/Icon/Images/12_Apps_pidgin_icon.png"
#define CONFORMATION        "SaveAs PDF"
#define NOEMPTYSPACE        "Filename should not empty"
#define MAXIMUMLENGTH       256

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    setWindowTitle(CONFORMATION);
    setWindowIcon(QIcon(WINDOW_ICON_PATH));
    setWindowFlags(Qt::FramelessWindowHint);

    ui->txt_input->setMaxLength(MAXIMUMLENGTH);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_btn_ok_clicked()
{
    if (ui->txt_input->text().isEmpty())
    {
        ui->lbl_warning->setText(NOEMPTYSPACE);
    }
    else
    {
        m_FileName = QString("%1").arg(ui->txt_input->text());
        ui->lbl_warning->clear();
        accept();
    }
}

void MyDialog::on_btn_close_clicked()
{
    accept();
}
