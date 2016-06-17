#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_imageSelect_clicked();

    void on_pushButton_imageSaveDirectory_clicked();

    void on_pushButton_renameImages_clicked();

    void renameImages();

    QString getRenamePattern();

private:
    Ui::MainWindow *ui;
    QStringList originalFileNames;
    QStringList convertedFileNames;
};

#endif // MAINWINDOW_H
