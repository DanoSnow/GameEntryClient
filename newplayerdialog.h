#ifndef NEWPLAYERDIALOG_H
#define NEWPLAYERDIALOG_H

#include <QDialog>
#include "gameentry.h"

namespace Ui {
class NewPlayerDialog;
}

class NewPlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPlayerDialog(QWidget *parent = nullptr, GameEntry p=GameEntry());
    GameEntry GetPlayer();
    QString GetConfirmation();
    ~NewPlayerDialog();

private slots:
    void on_lineEdit_2_textEdited(const QString &arg1);
    void on_lineEdit_3_textEdited(const QString &arg1);
    void on_HnSBtn_pressed();
    void on_HnSBtn_released();
    void on_HnSBtn_2_pressed();
    void on_HnSBtn_2_released();

private:
    Ui::NewPlayerDialog *ui;
    GameEntry player;
};

#endif // NEWPLAYERDIALOG_H
