#include "scoredialog.h"
#include "ui_scoredialog.h"

ScoreDialog::ScoreDialog(QWidget *parent, int s) :
    QDialog(parent),
    ui(new Ui::ScoreDialog), score(s)
{
    ui->setupUi(this);
}

int ScoreDialog::GetScore(){
    score = ui->spinBox->value();
    return score;
}

ScoreDialog::~ScoreDialog()
{
    delete ui;
}
