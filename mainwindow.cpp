#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
#include<QMessageBox>
#include<QPointer>
#include<QLabel>

enum process {start, starting, mainMenu};
enum loginButton {login, logout};
enum getting_ranking {name, score, match};
static getting_ranking player;
static process pro;
static loginButton Login;
static bool flag = false;
static int angle = 0, posescaler = 0;
static GameEntry newPlayer, currentPlayer;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(&socket,SIGNAL(connected()),this,SLOT(ClientConnected()));
    connect(&socket,SIGNAL(readyRead()),this,SLOT(ClientReadyRead()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(Stop()));
    ui->label_2->hide();
    ui->loginBtn->hide();
    ui->newPlayerBtn->hide();
    ui->rankingBtn->hide();
    ui->exitBtn->hide();
    ui->playBtn->hide();
    ui->playBtn->setDisabled(true);
    ui->backBtn->hide();
    ui->scoresBtn->hide();
    ui->matchBtn->hide();
    ui->tableWidget->hide();
    pro = start;
    timer.setInterval(500);
    timer.start();
}

void MainWindow::GetRanking(const QString data){
    QList<QPointer<QLabel>> nameList, scoreList, matchList;
    QPointer<QLabel> nameLabel = new QLabel(this), scoreLabel = new QLabel(this),
            matchLabel = new QLabel(this);
    int count = 1, i = 0;
    QString str = data, temp;
    while(count<str.length()){
        temp+=str[count];
        count++;
        if(str[count]=="!"){
            switch(player){
            case name:
                currentPlayer.SetName(temp);
                player = score;
                break;
            case score:
                currentPlayer.SetScore(temp.toInt());
                player = match;
                break;
            case match:
                currentPlayer.SetTimesPlayed(temp.toInt());
                player = match;
                //Updating the cells
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                nameList.append(nameLabel);
                nameList[i] = new QLabel(this);
                nameList[i]->setText(currentPlayer.GetName());
                ui->tableWidget->setCellWidget(i,0,nameList[i]);
                scoreList.append(scoreLabel);
                scoreList[i] = new QLabel(this);
                scoreList[i]->setText(QString::number(currentPlayer.GetScore()));
                ui->tableWidget->setCellWidget(i,1,scoreList[i]);
                matchList.append(matchLabel);
                matchList[i] = new QLabel(this);
                matchList[i]->setText(QString::number(currentPlayer.GetTimesPlayed()));
                ui->tableWidget->setCellWidget(i,2,matchList[i]);
                i++;
                player = name;
                break;
            }
            temp="";
            count++;
        }
    }
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::ClientConnected(){
    ui->statusBar->showMessage("Successfully connected to server",10000);
}

void MainWindow::ClientReadyRead(){
    QTcpSocket* socket = (QTcpSocket*)sender();
    qint64 bytesCount = socket->bytesAvailable();
    QByteArray bytes = socket->read(bytesCount);
    QString data = QString::fromLatin1(bytes);
    //-------------------------------------------------------------------
    //-------------------Check what data I'm asking for------------------
    //-------------------------------------------------------------------
    if(data=="1"){
        QMessageBox::warning(this,"Empty","No players at the list");
    }
    if(data=="2"){
        QMessageBox::warning(this,"Not Found","Player not found");
    }
    if(data=="A"){
        ui->statusBar->showMessage("Player autenticated",10000);
        Login = logout;
        ui->loginBtn->setText("Logout");
        ui->label_3->setText("Welcome");
        ui->playBtn->setDisabled(false);
    }
    if(data[0]=="R"){
        ui->label_2->hide();        //Hiding all widgets that I dont want to see
        ui->label_3->hide();
        ui->loginBtn->hide();
        ui->newPlayerBtn->hide();
        ui->rankingBtn->hide();
        ui->exitBtn->hide();
        ui->playBtn->hide();
        ui->backBtn->show();        //Showing all widgets that I do want to see
        ui->scoresBtn->show();
        ui->matchBtn->show();
        ui->tableWidget->show();
        ui->label_3->setText(data);
        player = name;
        GetRanking(data);
    }
}

void MainWindow::on_startBtn_clicked(){
    pro = starting;
    ui->label->setText("???");
    timer.setInterval(10);
    ui->startBtn->hide();
    ui->label->show();
}

void MainWindow::Stop(){
    switch(pro){
    case start:
        if(flag){
            ui->label->show();
            flag = false;
        }else{
            ui->label->hide();
            flag = true;
        }
        break;
    case starting:
        ui->label->move(205+20*cos(angle*3.14/180),200+20*sin(angle*3.14/180));
        angle+=5;
        posescaler++;
        if(posescaler==500){
            pro = mainMenu;
        }
        break;
    case mainMenu:
        timer.stop();
        ui->label->hide();
        ui->label_2->show();
        ui->loginBtn->show();
        ui->newPlayerBtn->show();
        ui->rankingBtn->show();
        ui->exitBtn->show();
        ui->playBtn->show();
        socket.connectToHost("127.0.0.1",60);
        break;
    }
}

void MainWindow::on_loginBtn_clicked(){
    LoginDialog dialog;
    connect(&dialog,SIGNAL(rejected()),this,SLOT(on_rejected()));
    if(Login==login){
        QString n, p;
        do{
            try{
                if(dialog.exec()){
                    n = dialog.GetName();
                    p = dialog.GetPassword();
                    if(n=="" || p==""){
                        throw(IncompleteParameters());
                    }
                    QString loginData = "L"+n+"!"+p;
                    QByteArray bytes = loginData.toLatin1();
                    socket.write(bytes);
                }
            }
            catch(IncompleteParameters &parameters){
                QMessageBox::warning(this,"Incomplete parameters",parameters.what());
            }
            catch(Rejected &reject){
                QMessageBox::warning(this,"Cancel exit",reject.what());
                return;
            }
        }while(n=="" || p=="");
    }else{
        ui->statusBar->showMessage("Good bye",10000);
        Login = login;
        ui->loginBtn->setText("Login");
        ui->label_3->setText("");
        ui->playBtn->setDisabled(true);
    }
}

void MainWindow::on_newPlayerBtn_clicked(){
    NewPlayerDialog dialog;
    connect(&dialog,SIGNAL(rejected()),this,SLOT(on_rejected()));
    QString confirm;
    do{
        try{
            if(dialog.exec()){
                newPlayer = dialog.GetPlayer();
                confirm = dialog.GetConfirmation();
                if(newPlayer.GetName()=="" || newPlayer.GetPassword()=="" || confirm==""){
                    throw(IncompleteParameters());
                }
                if(newPlayer.GetPassword()!=confirm){
                    throw(WrongConfirm());
                }
                QString data = "n"+newPlayer.GetName()+"!"+QString::number(newPlayer.GetScore())+"!"
                        +QString::number(newPlayer.GetTimesPlayed())+"!"+newPlayer.GetPassword();
                QByteArray bytes = data.toLatin1();
                socket.write(bytes);
            }
        }
        catch(IncompleteParameters &incomplete){
            QMessageBox::warning(this,"Incomplete parameters",incomplete.what());
        }
        catch(WrongConfirm &wrong){
            QMessageBox::warning(this,"Password warning",wrong.what());
        }
        catch(Rejected &reject){
            QMessageBox::warning(this,"Cancel exit",reject.what());
            return;
        }
    }while(newPlayer.GetName()=="" || newPlayer.GetPassword()=="" || confirm=="" || newPlayer.GetPassword()!=confirm);
}

void MainWindow::on_rankingBtn_clicked(){
    QString R = "R";
    QByteArray bytes = R.toLatin1();
    socket.write(bytes);
}

void MainWindow::on_exitBtn_clicked(){
    socket.disconnectFromHost();
    close();
}

void MainWindow::on_playBtn_clicked(){
    ScoreDialog dialog;
    int s;
    if(dialog.exec()){
        s = dialog.GetScore();
        QString data = "S"+QString::number(s);
        QByteArray bytes = data.toLatin1();
        socket.write(bytes);
    }
}

void MainWindow::on_scoresBtn_clicked(){
    QString R = "R";
    QByteArray bytes = R.toLatin1();
    socket.write(bytes);
    for(int i=0;i<=ui->tableWidget->rowCount();i++){
        ui->tableWidget->removeRow(0);
    }
}

void MainWindow::on_matchBtn_clicked(){
    QString R = "r";
    QByteArray bytes = R.toLatin1();
    socket.write(bytes);
    for(int i=0;i<=ui->tableWidget->rowCount();i++){
        ui->tableWidget->removeRow(0);
    }
}

void MainWindow::on_backBtn_clicked(){
    ui->label_2->show();
    ui->label_3->show();
    ui->loginBtn->show();
    ui->newPlayerBtn->show();
    ui->rankingBtn->show();
    ui->exitBtn->show();
    ui->playBtn->show();
    ui->backBtn->hide();
    ui->scoresBtn->hide();
    ui->matchBtn->hide();
    for(int i=0;i<=ui->tableWidget->rowCount();i++){
        ui->tableWidget->removeRow(0);
    }
    ui->tableWidget->hide();
}

void MainWindow::on_rejected(){
    throw(Rejected());
}
