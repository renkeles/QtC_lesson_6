#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QTextStream"
#include "buttonchange.h"
#include <QDebug>
#include <QMdiSubWindow>
#include <QSizePolicy>
#include <QPlainTextEdit>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    counter = 0;

    this->setWindowIcon(QIcon(":/image/png/2944881_bug_seo_user_virus_icon.png"));
    ui->setupUi(this);
    aboutPr = new aboutProgram;
    btnCh = new buttonChange;

    aboutPr->setModal(true);
    btnCh->setModal(true);

    ui->treeViewShow->setChecked(true);

    //Templates Qt Style Sheets https://qss-stock.devsecstudio.com/

    QFile styleSheetFile(":/style/qss/Integrid.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    qApp->setStyleSheet(styleSheet);

    setDefaultLanguage();
    MainWindow::on_russian_triggered();

    model = new QFileSystemModel;
    model->setRootPath("");

    QStringList filters;
    filters << "*.txt" << "*.ini" << "*.json" << "*.h";

    model->setNameFilters(filters);
    model->setNameFilterDisables(false);

    ui->treeFileView->setModel(model);

    ui->treeFileView->setColumnWidth(0,200);

    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    MainWindow::on_create_triggered();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete aboutPr;
    delete btnCh;
}

void MainWindow::on_open_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    if(filename.length())
    {
        QFile file(filename);
        if(file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            QTextStream stream(&file);
            QMdiSubWindow *subW = new QMdiSubWindow;
            subW->setWindowIcon(QIcon(":/image/png/2944881_bug_seo_user_virus_icon.png"));
            subW->setWindowTitle(filename);
            subW->resize(300,200);
            QPlainTextEdit *pte = new QPlainTextEdit;
            pte->setPlainText(stream.readAll());
            pte->setReadOnly(false);
            subW->setWidget(pte);
            subW->setAttribute(Qt::WA_DeleteOnClose);
            ui->mdiArea->addSubWindow(subW);
            subW->showMaximized();
            subW->show();
            file.close();
        }
    }
}

void MainWindow::on_openReadOnly_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    if(filename.length())
    {
        QFile file(filename);
        if(file.open(QFile::ReadOnly))
        {
            QTextStream stream(&file);
            QMdiSubWindow *subW = new QMdiSubWindow;
            subW->setWindowIcon(QIcon(":/image/png/2944881_bug_seo_user_virus_icon.png"));
            subW->setWindowTitle(filename);
            subW->resize(300,200);
            QPlainTextEdit *pte = new QPlainTextEdit;
            pte->setPlainText(stream.readAll());
            pte->setReadOnly(true);
            subW->setWidget(pte);
            subW->setAttribute(Qt::WA_DeleteOnClose);
            ui->mdiArea->addSubWindow(subW);
            subW->showMaximized();
            subW->show();
            file.close();
        }
    }
}

void MainWindow::on_save_triggered()
{
    QString filename = QFileDialog::getSaveFileName();
        if(filename.length())
        {
            QFile file(filename);
            if(file.open(QFile::WriteOnly | QFile::NewOnly))
            {
                QTextStream stream(&file);
                QPlainTextEdit *pte = qobject_cast<QPlainTextEdit*>(ui->mdiArea->currentSubWindow()->widget());
                stream << pte->toPlainText();
                file.close();
            }
        }
}

void MainWindow::on_exit_triggered()
{
    exit(0);
}

void MainWindow::on_create_triggered()
{
    QMdiSubWindow *subW = new QMdiSubWindow;
    subW->setWindowIcon(QIcon(":/image/png/2944881_bug_seo_user_virus_icon.png"));
    subW->setWindowTitle("Документ " + QString::number(counter));
    ++counter;
    subW->resize(300,200);
    subW->setWidget(new QPlainTextEdit);
    subW->setAttribute(Qt::WA_DeleteOnClose);

    ui->mdiArea->addSubWindow(subW);

    subW->showMaximized();
    subW->show();
}

void MainWindow::on_aboutProgram_triggered()
{
    aboutPr->show();
}

void MainWindow::on_buttons_triggered()
{
    btnCh->show();
}

void MainWindow::on_treeViewShow_triggered()
{
    if(!ui->treeViewShow->isChecked())
    {
        ui->treeFileView->hide();
    }else
    {
        ui->treeFileView->show();
    }
}

void MainWindow::on_dark_triggered()
{
    QFile styleSheetFile(":/style/qss/Combinear.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::on_light_triggered()
{
    QFile styleSheetFile(":/style/qss/Integrid.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    qApp->setStyleSheet(styleSheet);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(btnCh->getCheckOpen())
    {
        if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_O)
        {
            MainWindow::on_open_triggered();
        }
    }else if(!btnCh->getCheckOpen())
    {
        if (e->key() == Qt::Key_F3)
        {
            MainWindow::on_open_triggered();
        }
    }

    if(btnCh->getCheckNew())
    {
        if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_N)
        {
            MainWindow::on_create_triggered();
        }
    }else if(!btnCh->getCheckNew())
    {
        if (e->key() == Qt::Key_F2)
        {
            MainWindow::on_create_triggered();
        }
    }

    if(btnCh->getCheckSave())
    {
        if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_S)
        {
            MainWindow::on_save_triggered();
        }
    }else if(!btnCh->getCheckSave())
    {
        if (e->key() == Qt::Key_F6)
        {
            MainWindow::on_save_triggered();
        }
    }

    if(btnCh->getCheckQuit())
    {
        if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Q)
        {
            exit(0);
            //qApp->quit();
        }
    }else if(!btnCh->getCheckQuit())
    {
        if (e->key() == Qt::Key_F12)
        {
            exit(0);
        }
    }
}

void MainWindow::setDefaultLanguage()
{
    this->setWindowTitle(tr("Блокнот"));

    ui->file->setTitle(tr("Файл"));
        ui->create->setText(tr("Создать"));
        ui->open->setText(tr("Открыть"));
        ui->openReadOnly->setText(tr("Открыть для чтения"));
        ui->save->setText(tr("Сохранить"));
        ui->print->setText(tr("Печать"));
        ui->exit->setText(tr("Выход"));

    ui->view->setTitle(tr("Вид"));
        ui->treeViewShow->setText(tr("Проводник"));

    ui->options->setTitle(tr("Настройки"));
        ui->control->setTitle(tr("Управление"));
            ui->buttons->setText(tr("Кнопки"));
        ui->language->setTitle(tr("Язык"));
            ui->russian->setText(tr("Русский"));
            ui->english->setText(tr("English"));
        ui->theme->setTitle(tr("Темы"));
            ui->light->setText((tr("Светлая")));
            ui->dark->setText(tr("Тёмная"));

    ui->faq->setTitle(tr("Справка"));
        ui->aboutProgram->setText(tr("О программе"));
}

void MainWindow::on_russian_triggered()
{
    qtranslator.load(":/language/qm/QtLanguage_ru.qm");
    qApp->installTranslator(&qtranslator);
    btnCh->setLanguage(Language::CodeLanguage::ru);
    aboutPr->setLanguage(Language::CodeLanguage::ru);
    ui->retranslateUi(this);
}

void MainWindow::on_english_triggered()
{
    qtranslator.load(":/language/qm/QtLanguage_en.qm");
    qApp->installTranslator(&qtranslator);
    btnCh->setLanguage(Language::CodeLanguage::en);
    aboutPr->setLanguage(Language::CodeLanguage::en);
    ui->retranslateUi(this);
}

void MainWindow::on_treeFileView_doubleClicked(const QModelIndex &index)
{
        QFile file(model->filePath(index));
        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream stream(&file);
            QMdiSubWindow *subW = new QMdiSubWindow;
            subW->setWindowTitle(index.data(Qt::DisplayRole).toString());
            subW->resize(300,200);
            QPlainTextEdit *pte = new QPlainTextEdit;
            pte->setPlainText(stream.readAll());
            pte->setReadOnly(false);
            subW->setWidget(pte);
            subW->setAttribute(Qt::WA_DeleteOnClose);
            ui->mdiArea->addSubWindow(subW);
            subW->showMaximized();
            subW->show();
            file.close();
        }
}


void MainWindow::on_print_triggered()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle(tr("Печать"));
    if (dlg.exec() != QDialog::Accepted)
    return;

    QPlainTextEdit *pte = qobject_cast<QPlainTextEdit*>(ui->mdiArea->currentSubWindow()->widget());
    QString printStr = pte->toPlainText();
    QChar *list = printStr.data();
    QStringList strlst;
    int line = 10, cursor = 0;
    for (bool getst = true;getst;)
    {
        int index = printStr.indexOf("\n", cursor);
        QString s = "";
        if (index == -1)
        {
            getst = false;
            s.append(&list[cursor], printStr.length() - cursor);
        }
        else s.append(&list[cursor], index - cursor);
        cursor = index + 1;
        strlst << s;
    }

    QPainter painter;
    painter.begin(&printer);
    //int w = painter.window().width();
    int h = painter.window().height();
    int amount = strlst.count();
    QFont font = painter.font();
    QFontMetrics fmetrics(font);
    for (int i = 0; i < amount; i++)
    {
        QPointF pf;
        pf.setX(10);
        pf.setY(line);
        painter.drawText(pf, strlst.at(i));
        line += fmetrics.height();
        if (h - line <= fmetrics.height())
        {
            printer.newPage();
            line = 10;
        }
    }
    painter.end();

}

