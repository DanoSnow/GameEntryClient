#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr, QString n=QString(), QString p=QString());
    QString GetName();
    QString GetPassword();
    ~LoginDialog();

private slots:
    void on_lineEdit_2_textEdited(const QString &arg1);
    void on_HnSBtn_pressed();
    void on_HnSBtn_released();

private:
    Ui::LoginDialog *ui;
    QString name, password;
};

#endif // LOGINDIALOG_H
