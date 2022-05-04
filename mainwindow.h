#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aboutprogram.h"
#include "buttonchange.h"
#include "language.h"
#include <QTranslator>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private slots:
    void on_open_triggered();

    void on_openReadOnly_triggered();

    void on_save_triggered();

    void on_exit_triggered();

    void on_create_triggered();

    void on_aboutProgram_triggered();

    void on_buttons_triggered();

    void on_treeViewShow_triggered();

    void on_dark_triggered();

    void on_light_triggered();

    void on_russian_triggered();

    void on_english_triggered();

    void on_treeFileView_doubleClicked(const QModelIndex &index);

    void on_print_triggered();

private:
    Ui::MainWindow *ui;
    aboutProgram *aboutPr;
    buttonChange *btnCh;
    QTranslator qtranslator;
    QFileSystemModel *model;

    int counter;

    void setDefaultLanguage();

};
#endif // MAINWINDOW_H
