/**
 * @file - mydialog.h contains MyDialog class */

#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    QString m_FileName; ///< store the filename
    ~MyDialog();

private slots:
    /**
     * @brief on_btn_ok_clicked - accept the filename and close the dialog
     */
    void on_btn_ok_clicked();

    void on_btn_close_clicked();

private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
