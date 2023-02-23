#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QNotePad");
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    filename = "";
    ui->textEdit->setPlainText("");
}


void MainWindow::on_actionSuperscript_triggered()
{
    QTextCharFormat format;
    format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
    ui->textEdit->textCursor().mergeCharFormat(format);
}


void MainWindow::on_actionSubscript_triggered()
{
    QTextCharFormat format;
    format.setVerticalAlignment(QTextCharFormat::AlignSubScript);
    ui->textEdit->textCursor().mergeCharFormat(format);
}


void MainWindow::on_actionBold_triggered()
{
    bool isBold = ui->textEdit->textCursor().charFormat().font().bold();
    QTextCharFormat format;
    if(isBold) {
        format.setFontWeight(QFont::Normal);
    } else {
        format.setFontWeight(QFont::Bold);
    }
    ui->textEdit->textCursor().mergeCharFormat(format);
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString file = QFileDialog::getSaveFileName(this, "Open a file");
    if(!file.isEmpty()) {
        filename = file;
        on_actionSave_triggered();
    }
}


void MainWindow::on_actionSave_triggered()
{
    if(QString::compare(filename, QString())) {
        QFile file(filename);
        if(file.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            out.flush();
            file.close();
        }
    } else {
        QMessageBox::information(this, "Invalid file name", "Please enter a valid filename or use the \"Save as\" option if this is a new file.");
    }
}


void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, "Open a file");
    if(!file.isEmpty()) {
        QFile openedFile(file);
        if(openedFile.open(QFile::ReadOnly | QFile::Text)) {
            filename = file;
            QTextStream in(&openedFile);
            QString read_contents = in.readAll();
            openedFile.close();
            ui->textEdit->setPlainText(read_contents);
        }
    }
}


void MainWindow::on_actionNormalize_triggered()
{
    QTextCharFormat format;
    format.setVerticalAlignment(QTextCharFormat::AlignNormal);
    ui->textEdit->textCursor().mergeCharFormat(format);
}


void MainWindow::on_actionAbout_Me_triggered()
{
    aboutMeDialog = new Dialog(this);
    aboutMeDialog->show();
}

