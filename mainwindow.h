#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include "newplayerdialog.h"
#include "logindialog.h"
#include "scoredialog.h"
#include "gameentry.h"
#include "exceptions.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void GetRanking(const QString data);
    ~MainWindow();

private slots:
    void ClientConnected();
    void ClientReadyRead();
    void on_startBtn_clicked();
    void Stop();
    void on_loginBtn_clicked();
    void on_newPlayerBtn_clicked();
    void on_rankingBtn_clicked();
    void on_exitBtn_clicked();
    void on_playBtn_clicked();
    void on_scoresBtn_clicked();
    void on_matchBtn_clicked();
    void on_backBtn_clicked();
    void on_rejected();

private:
    Ui::MainWindow *ui;
    QTcpSocket socket;
    QTimer timer;
};

#endif // MAINWINDOW_H
