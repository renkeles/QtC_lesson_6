#ifndef BUTTONCHANGE_H
#define BUTTONCHANGE_H

#include <QDialog>
#include <QTranslator>
#include "language.h"

namespace Ui {
class buttonChange;
}

class buttonChange : public QDialog
{
    Q_OBJECT

public:
    explicit buttonChange(QDialog *parent = nullptr);
    ~buttonChange();
    bool getCheckOpen();
    bool getCheckSave();
    bool getCheckNew();
    bool getCheckQuit();

    void setLanguage(Language::CodeLanguage code);
private:
    Ui::buttonChange *ui;
    QTranslator qtranslator;
    void setDefaultLanguage();

};

#endif // BUTTONCHANGE_H
