#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings save(QApplication::applicationDirPath().append("/").append("settings.ina"),QSettings::IniFormat);

    save.beginGroup("General");
    ui->pushButton_imageSaveDirectory->setText(save.value("SaveDirectory", "Save Images Directory (Click Here)").toString());
    ui->lineEdit_renamePattern->setText(save.value("RenamePattern", "Madoka_#").toString());
    save.endGroup();
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
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOptions(QFileDialog::ShowDirsOnly);

    if (dialog.exec())
        ui->pushButton_imageSaveDirectory->setText(dialog.selectedFiles().first());

    QSettings save(QApplication::applicationDirPath().append("/").append("settings.ina"),QSettings::IniFormat);

    save.beginGroup("General");
    save.setValue("SaveDirectory", ui->pushButton_imageSaveDirectory->text());
    save.endGroup();
}

void MainWindow::on_pushButton_renameImages_clicked()
{
    ui->pushButton_renameImages->setText("Renaming Images....");
    for( int i = 0; i < originalFileNames.size(); i++)
    {
        QFile sFile(originalFileNames.at(i));
        sFile.rename(ui->pushButton_imageSaveDirectory->text().append("/").append(convertedFileNames.at(i)));
    }
    ui->pushButton_renameImages->setText("Finished Renaming!");
    QTimer::singleShot(3000, this, SLOT(reset_pushButton_renameImages()));
}

void MainWindow::renameImages()
{

    convertedFileNames.clear();
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

//        convertedFileNames.append(sFileName); // full link
        convertedFileNames.append(fInfo.fileName()); // only file name
        increment++;
    }
    ui->plainTextEdit_renamePreview->setPlainText(imageRenamePreview);
}

QString MainWindow::getRenamePattern()
{
    // Was thinking to do something clever here.
    // Probably not needed
    QString renamePattern = ui->lineEdit_renamePattern->text();
    return renamePattern;
}

void MainWindow::on_lineEdit_renamePattern_textChanged(const QString &arg1)
{
    QSettings save(QApplication::applicationDirPath().append("/").append("settings.ina"),QSettings::IniFormat);

    save.beginGroup("General");
    save.setValue("RenamePattern", arg1);
    save.endGroup();

    renameImages();
}

void MainWindow::reset_pushButton_renameImages()
{
    ui->pushButton_renameImages->setText("Rename Images");
    ui->plainTextEdit_renamePreview->clear();
}
