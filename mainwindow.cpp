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
    dialog.setFileMode(QFileDialog::ExistingFiles);

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
    int increment = 1;
    foreach(QString sFileName, originalFileNames)
    {
        QFileInfo fInfo(sFileName);
        imageRenamePreview.append(fInfo.fileName() + " -> ");

        sFileName.replace( fInfo.baseName(), renamePattern);
        sFileName.replace( "#", QString::number(increment));

        fInfo.setFile(sFileName);
        imageRenamePreview.append(fInfo.fileName());
        imageRenamePreview.append("\n");

        increment++;
    }
    ui->label_renamePreview->setText(imageRenamePreview);
}

QString MainWindow::getRenamePattern()
{
    // Was thinking to do something clever here.
    // Probably not needed
    QString renamePattern = ui->lineEdit_renamePattern->text();
    return renamePattern;
}
