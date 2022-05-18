#ifndef SCOREDIALOG_H
#define SCOREDIALOG_H

#include <QDialog>

namespace Ui {
class ScoreDialog;
}

class ScoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreDialog(QWidget *parent = nullptr, int s=0);
    int GetScore();
    ~ScoreDialog();

private:
    Ui::ScoreDialog *ui;
    int score;
};

#endif // SCOREDIALOG_H
