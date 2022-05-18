#include "logindialog.h"
#include "ui_logindialog.h"
int loginlength;
QString loginpass="", logindots="";

LoginDialog::LoginDialog(QWidget *parent, QString n, QString p) :
    QDialog(parent),
    ui(new Ui::LoginDialog), name(n), password(p)
{
    ui->setupUi(this);
    ui->lineEdit->setText(n);
    ui->lineEdit_2->setText(p);
    loginlength = 0;
    loginpass = ""; logindots = "";
}

QString LoginDialog::GetName(){
    name = ui->lineEdit->text();
    return name;
}

QString LoginDialog::GetPassword(){
    password = loginpass;
    return password;
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_lineEdit_2_textEdited(const QString &arg1)
{
    if(loginlength<ui->lineEdit_2->text().length()){
        loginpass+=ui->lineEdit_2->text().back();
        logindots+="•";
        loginlength++;
    }else{
        loginlength--;
        loginpass.resize(loginlength);
        logindots.resize(loginlength);
        //ui->lineEdit->setText(dots);
    }
    ui->lineEdit_2->setText(logindots);
}

void LoginDialog::on_HnSBtn_pressed(){
    ui->lineEdit_2->setText(loginpass);
}

void LoginDialog::on_HnSBtn_released(){
    ui->lineEdit_2->setText(logindots);
}
