/**
 * @file - mynotepad.h contains MyNotePad class */

#ifndef MYNOTEPAD_H
#define MYNOTEPAD_H

#include <QMainWindow>
#include <QPixmap>

#include "mydialog.h"

namespace Ui {
class MyNotePad;
}

class MyNotePad : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyNotePad(QWidget *parent = 0);
    ~MyNotePad();

private slots:
    /**
     * @brief on_btn_text_editor_clicked - user choose the text editor
     */
    void on_btn_text_editor_clicked();

    /**
     * @brief on_btn_image_converter_clicked - user choose the image to pdf converter
     */
    void on_btn_image_converter_clicked();

    /**
     * @brief on_actionNew_triggered - create new text document
     */
    void on_actionNew_triggered();

    /**
     * @brief on_actionOpen_triggered - open the existing text document
     */
    void on_actionOpen_triggered();

    /**
     * @brief on_actionSave_triggered - save the text document
     */
    void on_actionSave_triggered();

    /**
     * @brief on_actionSave_As_triggered - save as the text document
     */
    void on_actionSave_As_triggered();

    /**
     * @brief on_actionCut_triggered - cut the text content
     */
    void on_actionCut_triggered();

    /**
     * @brief on_actionCopy_triggered - copy the text content
     */
    void on_actionCopy_triggered();

    /**
     * @brief on_actionPaste_triggered - paste the text content
     */
    void on_actionPaste_triggered();

    /**
     * @brief on_actionUndo_triggered - undo the text content
     */
    void on_actionUndo_triggered();

    /**
     * @brief on_actionRedo_triggered - redo the text content
     */
    void on_actionRedo_triggered();

    /**
     * @brief on_actionBack_to_Index_triggered - back to home widget
     */
    void on_actionBack_to_Index_triggered();

    /**
     * @brief on_actionPrint_as_PDF_triggered - save as pdf file
     */
    void on_actionPrint_as_PDF_triggered();

    /**
     * @brief on_btn_back_clicked - back to home widget
     */
    void on_btn_back_clicked();

    /**
     * @brief on_btn_open_clicked - open the existing image file
     */
    void on_btn_open_clicked();

    /**
     * @brief on_btn_save_as_pdf_clicked - save as pdf file
     */
    void on_btn_save_as_pdf_clicked();

    /**
     * @brief on_btn_remove_image_clicked - remove the loaded file from label
     */
    void on_btn_remove_image_clicked();

private:
    Ui::MyNotePad *ui;
    QString m_FileName; ///< store the filename
    QPixmap m_PixMap;   ///< to set height and width of the image for priting purpose
};

#endif // MYNOTEPAD_H
