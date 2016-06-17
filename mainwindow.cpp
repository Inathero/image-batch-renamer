#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_imageSelect_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);

    originalFileNames.clear();
    if (dialog.exec())
        originalFileNames = dialog.selectedFiles();

    renameImages();
}

void MainWindow::on_pushButton_imageSaveDirectory_clicked()
{

}

void MainWindow::on_pushButton_renameImages_clicked()
{

}

void MainWindow::renameImages()
{
    QString imageRenamePreview;
    QString renamePattern = getRenamePattern();
    foreach(QString sFileName, originalFileNames)
    {
        imageRenamePreview.append(sFileName + " -> ");

    }
}

QString MainWindow::getRenamePattern()
{
    // Was thinking to do something clever here.
    // Probably not needed
    QString renamePattern = ui->lineEdit_renamePattern->text();
    return renamePattern;
}
