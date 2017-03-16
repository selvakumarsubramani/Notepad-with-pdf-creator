/**
  * @file mynotepad.cpp - contains class member functions of mynotepad class
  */

#include <QtPrintSupport/qprinter.h>
#include <QPrintDialog>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QDialog>
#include <QPainter>
#include <QIcon>
#include <QShortcut>
#include <QObject>

#include "mynotepad.h"
#include "ui_mynotepad.h"

#define PDF_EXTENSION                   ".pdf"
#define CURRENT_INDEX_1                 0
#define CURRENT_INDEX_2                 1
#define CURRENT_INDEX_3                 2
#define SETHIDDEN_MENUBAR_FALSE         0
#define SETHIDDEN_MENUBAR_TRUE          1
#define HIDE_PUSHBUTTON_TRUE            1
#define HIDE_PUSHBUTTON_FALSE           0
#define NO_PDF_PRINT_OPERATION_TEXT     "PDF(text) file not printed"
#define NO_PDF_PRINT_OPERATION_IMAGE    "PDF(image) file not printed"
#define INVALID_FILE_FORMAT             "Invalid file format"
#define IMAGE_PREVIEW                   "Image Preview"
#define WINDOW_ICON_PATH                ":/Icon/Images/12_Apps_pidgin_icon.png"
#define WINDOW_TITLE                    "SkyBird Software"
#define MEMORYERROR                     "Error while Dynamic Memory Allocation"

MyNotePad::MyNotePad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyNotePad)
{
    ui->setupUi(this);
    setWindowTitle(WINDOW_TITLE);
    setWindowIcon(QIcon(WINDOW_ICON_PATH));
    setWindowFlags(Qt::FramelessWindowHint);

    ui->stackedWidget->setCurrentIndex(CURRENT_INDEX_1);
    ui->menuBar->setHidden(SETHIDDEN_MENUBAR_TRUE);
    ui->mainToolBar->setHidden(SETHIDDEN_MENUBAR_TRUE);
    ui->statusBar->setHidden(SETHIDDEN_MENUBAR_TRUE);

    QShortcut *pShortcut_TextEditor = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_T),this);
    if (pShortcut_TextEditor)
    {
        connect(pShortcut_TextEditor, SIGNAL(activated()), this, SLOT(on_btn_text_editor_clicked()));
    }

    QShortcut *pShortcut_ImagetoPDF = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O),this);
    if (pShortcut_ImagetoPDF)
    {
        connect(pShortcut_ImagetoPDF,SIGNAL(activated()),this,SLOT(on_btn_image_converter_clicked()));
    }
}

MyNotePad::~MyNotePad()
{
    delete ui;
}

void MyNotePad::on_btn_text_editor_clicked()
{
    ui->stackedWidget->setCurrentIndex(CURRENT_INDEX_2);
    ui->menuBar->setHidden(SETHIDDEN_MENUBAR_FALSE);
    ui->mainToolBar->setHidden(SETHIDDEN_MENUBAR_FALSE);
}

void MyNotePad::on_btn_image_converter_clicked()
{
    ui->stackedWidget->setCurrentIndex(CURRENT_INDEX_3);
    ui->menuBar->setHidden(SETHIDDEN_MENUBAR_TRUE);
    ui->btn_save_as_pdf->setEnabled(HIDE_PUSHBUTTON_FALSE);
    ui->btn_remove_image->setEnabled(HIDE_PUSHBUTTON_FALSE);
}

void MyNotePad::on_actionNew_triggered()
{
    m_FileName = "";
    ui->txt_pad->setPlainText("");
}

void MyNotePad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            m_FileName = fileName;
            QTextStream in(&file);
            QString fileContent = in.readAll();
            file.close();
            ui->txt_pad->setPlainText(fileContent);
        }
    }
}

void MyNotePad::on_actionSave_triggered()
{
    if (m_FileName.isEmpty())
    {
        QString fileName =  QFileDialog::getSaveFileName(this);
        m_FileName = fileName;
    }

    QFile file(m_FileName);
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&file);
        out << ui->txt_pad->toPlainText();
        file.flush();
        file.close();
    }
}

void MyNotePad::on_actionSave_As_triggered()
{
    QString fileName =  QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty())
    {
        m_FileName = fileName;
        on_actionSave_triggered();
    }
}

void MyNotePad::on_actionCut_triggered()
{
    ui->txt_pad->cut();
}

void MyNotePad::on_actionCopy_triggered()
{
    ui->txt_pad->copy();
}

void MyNotePad::on_actionPaste_triggered()
{
    ui->txt_pad->paste();
}

void MyNotePad::on_actionRedo_triggered()
{
    ui->txt_pad->redo();
}

void MyNotePad::on_actionUndo_triggered()
{
    ui->txt_pad->undo();
}

void MyNotePad::on_actionBack_to_Index_triggered()
{
    ui->stackedWidget->setCurrentIndex(CURRENT_INDEX_1);
    ui->menuBar->setHidden(SETHIDDEN_MENUBAR_TRUE);
    ui->mainToolBar->setHidden(SETHIDDEN_MENUBAR_TRUE);
    ui->txt_pad->clear();
}

void MyNotePad::on_actionPrint_as_PDF_triggered()
{
    QPrinter printer;
    MyDialog dialog;
    dialog.show();
    dialog.exec();
    QString fileName = QString("%1").arg(dialog.m_FileName);

    if (QString::compare(fileName, ""))
    {
        qDebug() << NO_PDF_PRINT_OPERATION_TEXT;
        return;
    }
    else
    {
        fileName.append(PDF_EXTENSION);
        qDebug() << fileName;
        printer.setPageSize(QPrinter::A4);
        printer.setOrientation(QPrinter::Portrait);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        ui->txt_pad->print(&printer);
    }
}

void MyNotePad::on_btn_back_clicked()
{
    ui->lbl_image_preview->clear();
    ui->lbl_image_preview->setText(IMAGE_PREVIEW);
    ui->stackedWidget->setCurrentIndex(CURRENT_INDEX_1);
}

void MyNotePad::on_btn_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        QImage *pImage = new QImage();
        if (pImage)
        {
            if (!(pImage->load(fileName)))
            {
                ui->lbl_image_preview->setText(INVALID_FILE_FORMAT);
                return;
            }
            m_PixMap = QPixmap::fromImage(*pImage);
            ui->lbl_image_preview->setPixmap(m_PixMap.scaled(ui->lbl_image_preview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            delete pImage;
            ui->btn_save_as_pdf->setEnabled(HIDE_PUSHBUTTON_TRUE);
            ui->btn_remove_image->setEnabled(HIDE_PUSHBUTTON_TRUE);
        }
        else
        {
            qDebug() << MEMORYERROR;
        }
    }
}


void MyNotePad::on_btn_save_as_pdf_clicked()
{
    QPrinter printer;
    MyDialog dialog;
    dialog.show();
    dialog.exec();
    QString fileName = QString("%1").arg(dialog.m_FileName);
    if (QString::compare(fileName,""))
    {
        qDebug() << NO_PDF_PRINT_OPERATION_IMAGE;
        return;
    }
    else
    {
        fileName.append(PDF_EXTENSION);
        qDebug() << fileName;
        printer.setPageSize(QPrinter::A4);
        printer.setOrientation(QPrinter::Landscape);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);

        QPainter painter;
        painter.begin(&printer);
        double xscale = (printer.pageRect().width() / double(m_PixMap.width()));
        double yscale = (printer.pageRect().height() / double(m_PixMap.height()));
        double scale = qMin(xscale, yscale);
        painter.translate((printer.paperRect().x() + printer.pageRect().width() / 2),
                          (printer.paperRect().y() + printer.pageRect().height() / 2));
        painter.scale(scale, scale);
        painter.translate((-m_PixMap.width() / 2), (-m_PixMap.height() / 2));
        painter.drawPixmap(0, 0, m_PixMap);
        painter.end();
    }
}

void MyNotePad::on_btn_remove_image_clicked()
{
    ui->lbl_image_preview->clear();
    ui->lbl_image_preview->setText(IMAGE_PREVIEW);
    ui->btn_save_as_pdf->setEnabled(HIDE_PUSHBUTTON_FALSE);
    ui->btn_remove_image->setEnabled(HIDE_PUSHBUTTON_FALSE);
}
