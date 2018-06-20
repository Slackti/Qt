#include "searchdialog.h"
#include "ui_searchdialog.h"

#include <QTextDocument>
#include <QPalette>
#include <QComboBox>
#include <QDebug>

SearchDialog::SearchDialog(QTextBrowser *textBrowser, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    _textBrowser = textBrowser;

    //Highlight
    QPalette palette = _textBrowser->palette();
    palette.setColor(QPalette::Highlight, palette.color(QPalette::Active,QPalette::Highlight));
    _textBrowser->setPalette(palette);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

//Find next slot
void SearchDialog::findNext()
{
    bool flag = false;
    bool flag1, flag2;// flag3;

    QString str = ui->comboBox->currentText();
    flag1 = ui->allChCheckBox->isChecked();
    flag2 = ui->matchCaseCheckBox->isChecked();
    //flag3 = ui->loopFindCheckBox->isChecked();

    if(ui->radioDownButton->isChecked())
    {
        if(flag1 && !flag2)
        {
            flag = _textBrowser->find(str, QTextDocument::FindWholeWords);
        }
        else if(flag2 && !flag1)
        {
            flag = _textBrowser->find(str, QTextDocument::FindCaseSensitively);
        }
        else if(flag1 && flag2)
        {
            flag = _textBrowser->find(str, QTextDocument::FindWholeWords | QTextDocument::FindCaseSensitively);
        }
        else
        {
            flag = _textBrowser->find(str);
        }
    }
    else if(ui->radioUpButton->isChecked())
    {
        if(flag1 && !flag2)
        {
            flag = _textBrowser->find(str, QTextDocument::FindBackward | QTextDocument::FindWholeWords);
        }
        else if(flag2 && !flag1)
        {
            flag = _textBrowser->find(str, QTextDocument::FindBackward | QTextDocument::FindCaseSensitively);
        }
        else if(flag1 && flag2)
        {
            flag = _textBrowser->find(str, QTextDocument::FindBackward | QTextDocument::FindWholeWords | QTextDocument::FindCaseSensitively);
        }
        else
        {
            flag = _textBrowser->find(str, QTextDocument::FindBackward);
        }
    }

    if(!flag)
    {
        ui->statusLabel->setText(tr("找不到%1").arg(str));
    }
    else
    {
        ui->statusLabel->setText(tr(""));
    }
}

//F4 slot
void SearchDialog::findPrevious()
{
    bool flag = false;
    bool flag1, flag2;//flag3;

    QString str = ui->comboBox->currentText();
    flag1 = ui->allChCheckBox->isChecked();
    flag2 = ui->matchCaseCheckBox->isChecked();
    //flag3 = ui->loopFindCheckBox->isChecked();

    if(ui->radioDownButton->isChecked())
    {
        if(flag1 && !flag2)
        {
            flag = _textBrowser->find(str, QTextDocument::FindBackward | QTextDocument::FindWholeWords);
        }
        else if(flag2 && !flag1)
        {
            flag = _textBrowser->find(str, QTextDocument::FindBackward | QTextDocument::FindCaseSensitively);
        }
        else if(flag1 && flag2)
        {
            flag = _textBrowser->find(str, QTextDocument::FindBackward | QTextDocument::FindWholeWords | QTextDocument::FindCaseSensitively);
        }
        else
        {
            flag = _textBrowser->find(str, QTextDocument::FindBackward);
        }
    }
    else if(ui->radioUpButton->isChecked())
    {
        if(flag1 && !flag2)
        {
            flag = _textBrowser->find(str, QTextDocument::FindWholeWords);
        }
        else if(flag2 && !flag1)
        {
            flag = _textBrowser->find(str, QTextDocument::FindCaseSensitively);
        }
        else if(flag1 && flag2)
        {
            flag = _textBrowser->find(str, QTextDocument::FindWholeWords | QTextDocument::FindCaseSensitively);
        }
        else
        {
            flag = _textBrowser->find(str);
        }
    }

    if(!flag)
    {
        ui->statusLabel->setText(tr("找不到%1").arg(str));
    }
    else
    {
        ui->statusLabel->setText(tr(""));
    }
}

//Find next signal
void SearchDialog::on_findNextBtn_clicked()
{
    findNext();
}

//Close FindDialog
void SearchDialog::on_cancelBtn_clicked()
{
    this->close();
}
