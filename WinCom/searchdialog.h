#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QTextBrowser>
#include <QDialog>
#include <QtCore>

namespace Ui {
    class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SearchDialog(QTextBrowser *textBrowser, QWidget *parent = 0);
    ~SearchDialog();
    void findNext();
    void findPrevious();
    Ui::SearchDialog *ui;

private slots:
    void on_findNextBtn_clicked();

    void on_cancelBtn_clicked();

private:
    QTextBrowser *_textBrowser;
};

#endif // SEARCHDIALOG_H
