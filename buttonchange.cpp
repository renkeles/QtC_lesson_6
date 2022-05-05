#include "buttonchange.h"
#include "ui_buttonchange.h"

buttonChange::buttonChange(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::buttonChange)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/image/png/image/logo/2944881_bug_seo_user_virus_icon.png"));

    ui->radioButton_ctrl_n->setChecked(true);
    ui->radioButton_ctrl_o->setChecked(true);
    ui->radioButton_ctrl_s->setChecked(true);
    ui->radioButton_ctrl_q->setChecked(true);

    setDefaultLanguage();
}

buttonChange::~buttonChange()
{
    delete ui;
}

bool buttonChange::getCheckOpen()
{
    return ui->radioButton_ctrl_o->isChecked();
}

bool buttonChange::getCheckSave()
{
    return ui->radioButton_ctrl_s->isChecked();
}

bool buttonChange::getCheckNew()
{
    return ui->radioButton_ctrl_n->isChecked();
}

bool buttonChange::getCheckQuit()
{
    return ui->radioButton_ctrl_q->isChecked();
}

void buttonChange::setDefaultLanguage()
{
    this->setWindowTitle(tr("Кнопки"));

    ui->labelCreate->setText(tr("Создать"));
    ui->labelOpen->setText(tr("Открыть"));
    ui->labelSave->setText(tr("Сохранить"));
    ui->labelQuit->setText(tr("Выход"));
}

void buttonChange::setLanguage(Language::CodeLanguage code)
{
    if(Language::CodeLanguage::en == code)
    {
        qtranslator.load(":/language/qm/QtLanguage_en.qm");
        qApp->installTranslator(&qtranslator);
        ui->retranslateUi(this);
    }else
    {
        qtranslator.load(":/language/qm/QtLanguage_ru.qm");
        qApp->installTranslator(&qtranslator);
        ui->retranslateUi(this);
    }
}
