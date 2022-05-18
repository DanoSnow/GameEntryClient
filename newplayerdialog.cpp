#include "newplayerdialog.h"
#include "ui_newplayerdialog.h"
int newPlength=0, newPlength2=0;
QString newPdots="", newPpass="", newPdots2="", newPpass2="";

NewPlayerDialog::NewPlayerDialog(QWidget *parent, GameEntry G) :
    QDialog(parent),
    ui(new Ui::NewPlayerDialog), player(G)
{
    ui->setupUi(this);
    ui->lineEdit->setText(player.GetName());
    ui->lineEdit_2->setText(player.GetPassword());
    ui->lineEdit_3->setText("");
    newPlength = 0; newPlength2 = 0;
    newPdots = ""; newPpass = ""; newPdots2 = ""; newPpass2 = "";
}

GameEntry NewPlayerDialog::GetPlayer(){
    player.SetName(ui->lineEdit->text());
    player.SetPassword(newPpass);
    return player;
}

QString NewPlayerDialog::GetConfirmation(){
    QString confirmation = newPpass2;
    return confirmation;
}

NewPlayerDialog::~NewPlayerDialog()
{
    delete ui;
}

void NewPlayerDialog::on_lineEdit_2_textEdited(const QString &arg1){
    if(newPlength<ui->lineEdit_2->text().length()){
        newPpass+=ui->lineEdit_2->text().back();
        newPdots+="•";
        newPlength++;
    }else{
        newPlength--;
        newPpass.resize(newPlength);
        newPdots.resize(newPlength);
    }
    ui->lineEdit_2->setText(newPdots);
}

void NewPlayerDialog::on_lineEdit_3_textEdited(const QString &arg1){
    if(newPlength2<ui->lineEdit_3->text().length()){
        newPpass2+=ui->lineEdit_3->text().back();
        newPdots2+="•";
        newPlength2++;
    }else{
        newPlength2--;
        newPpass2.resize(newPlength2);
        newPdots2.resize(newPlength2);
    }
    ui->lineEdit_3->setText(newPdots2);
}

void NewPlayerDialog::on_HnSBtn_pressed(){
    ui->lineEdit_2->setText(newPpass);
}

void NewPlayerDialog::on_HnSBtn_released(){
    ui->lineEdit_2->setText(newPdots);
}

void NewPlayerDialog::on_HnSBtn_2_pressed(){
    ui->lineEdit_3->setText(newPpass2);
}

void NewPlayerDialog::on_HnSBtn_2_released(){
    ui->lineEdit_3->setText(newPdots2);
}
