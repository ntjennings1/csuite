#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "obj/caesar.h"
#include "obj/transposition.h"

#include <QDebug>
#include <QApplication>
#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->cipherchoice->addItem("Select a cipher ...");
    ui->cipherchoice->addItem("Caesar");
    ui->cipherchoice->addItem("Transposition");
    ui->cipherchoice->addItem("Vigenere");
    connect(ui->cipherchoice, &QComboBox::currentTextChanged, this, &MainWindow::onComboboxSelection);

    connect(ui->closebutton, &QPushButton::clicked, this, &MainWindow::onClosebuttonClicked);
    connect(ui->resetbutton, &QPushButton::clicked, this, &MainWindow::onResetbuttonClicked);
    connect(ui->reversebutton, &QPushButton::clicked, this, &MainWindow::onReversebuttonClicked);
    connect(ui->startbutton, &QPushButton::clicked, this, &MainWindow::onStartbuttonClicked);
    connect(qApp, &QApplication::focusChanged, this, &MainWindow::onFocusChanged);

    this->setDirection("f");
    this->config("start");
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string MainWindow::getDirection()
{
    return this->direction;
}

void MainWindow::setDirection(std::string direction)
{
    this->direction = direction;
}

std::string MainWindow::getCipher()
{
    return this->cipher;
}

void MainWindow::setCipher(std::string cipher)
{
    this->cipher = cipher;
}

std::string MainWindow::getPtext()
{
    return this->ptext;
}

void MainWindow::setPtext(std::string ptext)
{
    this->ptext = ptext;
}

std::string MainWindow::getCtext()
{
    return this->ctext;
}

void MainWindow::setCtext(std::string ctext)
{
    this->ctext = ctext;
}

std::string MainWindow::getKey()
{
    return this->key;
}

void MainWindow::setKey(std::string key)
{
    this->key = key;
}

void MainWindow::throw_exec(std::string type)
{

    if (type == "close")
    {
        qDebug() << "Error closing CSuite.\n";
        //this->onResetbuttonClicked();
    }
    else if (type == "reset")
    {
        qDebug() << "Error reseting CSuite.\n";
        //this->onResetbuttonClicked();
    }
    else if (type == "caesar")
    {
        qDebug() << "Error running Caesar cipher.\n";
        //this->onResetbuttonClicked();
    }
    else if (type == "trans")
    {
        qDebug() << "Error running transposition cipher.\n";
    }

}

void MainWindow::onFocusChanged()
{
    if (ui->ptextedit->hasFocus())
    {
        std::string ctemp = ui->ctextedit->toPlainText().toStdString();
        std::string ptemp = ui->ptextedit->toPlainText().toStdString();
        std::string ktemp = ui->keyedit->toPlainText().toStdString();

        if ((ptemp == "Plaintext  displays here ..." || ptemp == "Enter plaintext here ...") || ptemp.length() < 1)
        {
            ui->ptextedit->setPlainText("");
        }
        if (ctemp == "")
        {
            if (this->getDirection() == "f")
            {
                ui->ctextedit->setPlainText("Ciphertext displays here ...");
            }
            if (this->getDirection() == "b")
            {
                ui->ctextedit->setPlainText("Enter ciphertext here ...");
            }
        }
        if (ktemp == "")
        {
            ui->keyedit->setPlainText("Enter cipher key ...");
        }
    }
    else if (ui->ctextedit->hasFocus())
    {
        std::string ctemp = ui->ctextedit->toPlainText().toStdString();
        std::string ptemp = ui->ptextedit->toPlainText().toStdString();
        std::string ktemp = ui->keyedit->toPlainText().toStdString();

        if ((ctemp == "Ciphertext displays here ..." || ctemp == "Enter ciphertext here ...") || ctemp.length() < 1)
        {
            ui->ctextedit->setPlainText("");
        }
        if (ptemp == "")
        {
            if (this->getDirection() == "f")
            {
                ui->ptextedit->setPlainText("Enter plaintext here ...");
            }
            else if (this->getDirection() == "b")
            {
                ui->ptextedit->setPlainText("Plaintext displays here ...");
            }
        }
        if (ktemp == "")
        {
            ui->keyedit->setPlainText("Enter cipher key ...");
        }
    }
    else if (ui->keyedit->hasFocus())
    {
        std::string ctemp = ui->ctextedit->toPlainText().toStdString();
        std::string ptemp = ui->ptextedit->toPlainText().toStdString();
        std::string ktemp = ui->keyedit->toPlainText().toStdString();

        if (ktemp == "Enter cipher key ..." || ktemp.length() < 1)
        {
            ui->keyedit->setPlainText("");
        }
        if (ptemp == "")
        {
            if (this->getDirection() == "f")
            {
                ui->ptextedit->setPlainText("Enter plaintext here ...");
            }
            if (this->getDirection() == "b")
            {
                ui->ptextedit->setPlainText("Plaintext displays here ...");
            }
        }
        if (ctemp == "")
        {
            if (this->getDirection() == "f")
            {
                ui->ctextedit->setPlainText("Ciphertext displays here ...");
            }
            if (this->getDirection() == "b")
            {
                ui->ctextedit->setPlainText("Enter ciphertext here ...");
            }
        }
    }
}

void MainWindow::onClosebuttonClicked()
{
    try
    {
        delete ui;
        close();
    }
    catch (const exception &e)
    {
        this->throw_exec("close");
    }
}

void MainWindow::reset()
{
    try
    {
        this->setDirection("f");
        this->config("start");
        this->clear_entries(this->getDirection());
    }
    catch (const exception &e)
    {
        this->throw_exec("reset");
    }
}

void MainWindow::onResetbuttonClicked()
{

    this->reset();
    ui->cipherchoice->setCurrentIndex(0);

}

void MainWindow::onComboboxSelection()
{
    std::string choice = ui->cipherchoice->currentText().toStdString();

    if (choice == "Select a cipher ...")
    {
        this->reset();
    }
    else if (choice == "Caesar")
    {
        this->reset();
        this->setCipher("caesar");
        this->config("cipher");
    }
    else if (choice == "Transposition")
    {
        this->reset();
        this->setCipher("trans");
        this->config("cipher");
    }
}

void MainWindow::onReversebuttonClicked()
{
    if (this->getDirection() == "f")
    {
        this->setDirection("b");
        ui->ptextedit->setReadOnly(true);
        ui->ctextedit->setReadOnly(false);
    }
    else
    {
        this->setDirection("f");
        ui->ptextedit->setReadOnly(false);
        ui->ctextedit->setReadOnly(true);
    }

    this->clear_entries(this->getDirection());

}

void MainWindow::onStartbuttonClicked()
{
    if (this->getCipher() == "caesar")
    {
        try
        {
            if (this->getDirection() == "f")
            {
                std::string pt = ui->ptextedit->toPlainText().toStdString();
                int k = ui->keyedit->toPlainText().toInt();

                Caesar *caesar = new Caesar(pt, k);
                caesar->eval();
                caesar->stage();
                caesar->encrypt();

                ui->ctextedit->setPlainText(QString::fromStdString(caesar->getCiphertext()));
                delete caesar;
            }
            else if (this->getDirection() == "b")
            {
                std::string pt = ui->ctextedit->toPlainText().toStdString();
                int k = ui->keyedit->toPlainText().toInt();

                Caesar *caesar = new Caesar(pt, k);
                caesar->eval();
                caesar->stage();
                caesar->decrypt();

                ui->ptextedit->setPlainText(QString::fromStdString(caesar->getCiphertext()));
                delete caesar;
            }

            ui->startbutton->setDisabled(true);
            ui->resetbutton->setDisabled(false);
            ui->reversebutton->setDisabled(true);
            ui->closebutton->setDisabled(false);

            ui->ptextedit->setReadOnly(true);
            ui->ctextedit->setReadOnly(true);
            ui->keyedit->setReadOnly(true);

        }
        catch (const exception &e)
        {
            this->throw_exec("caesar");
        }
    }
    else if (this->getCipher() == "trans")
    {
        try
        {
            if (this->getDirection() == "f")
            {
                std::string pt = ui->ptextedit->toPlainText().toStdString();
                std::string k = ui->keyedit->toPlainText().toStdString();

                Transposition *transposition = new Transposition(k, pt);
                transposition->eval();
                transposition->stage();
                transposition->encrypt();

                ui->ctextedit->setPlainText(QString::fromStdString(transposition->getCiphertext()));
                delete transposition;
            }
            else if (this->getDirection() == "b")
            {
                std::string pt = ui->ctextedit->toPlainText().toStdString();
                std::string k = ui->keyedit->toPlainText().toStdString();

                Transposition *transposition = new Transposition(k, pt);
                transposition->eval();
                transposition->stage();
                transposition->decrypt();

                ui->ptextedit->setPlainText(QString::fromStdString(transposition->getCiphertext()));
                delete transposition;
            }

            ui->startbutton->setDisabled(true);
            ui->resetbutton->setDisabled(false);
            ui->reversebutton->setDisabled(true);
            ui->closebutton->setDisabled(false);

            ui->ptextedit->setReadOnly(true);
            ui->ctextedit->setReadOnly(true);
            ui->keyedit->setReadOnly(true);

        }
        catch (const exception &e)
        {
            this->throw_exec("trans");
        }
    }
}

void MainWindow::clear_entries(std::string type)
{
    if (type == "f")
    {
        ui->ptextedit->setPlainText("Enter plaintext here ...");
        ui->ctextedit->setPlainText("Ciphertext displays here ...");
        ui->keyedit->setPlainText("Enter cipher key ...");
    }
    if (type == "b")
    {
        ui->ptextedit->setPlainText("Plaintext displays here ...");
        ui->ctextedit->setPlainText("Enter ciphertext here ...");
        ui->keyedit->setPlainText("Enter cipher key ...");
    }

    this->setPtext("");
    this->setCtext("");
    this->setKey("");
}

void MainWindow::config(std::string type)
{
    if (type == "start")
    {

        ui->startbutton->setDisabled(true);
        ui->resetbutton->setDisabled(true);
        ui->reversebutton->setDisabled(true);
        ui->closebutton->setDisabled(false);

        ui->ptextedit->setReadOnly(true);
        ui->ctextedit->setReadOnly(true);
        ui->keyedit->setReadOnly(true);

        ui->ptextedit->setPlainText("Enter plaintext here ...");
        ui->ctextedit->setPlainText("Ciphertext displays here ...");
        ui->typelabel->setText("Type");

    }
    else if (type == "cipher")
    {


        ui->startbutton->setDisabled(false);
        ui->resetbutton->setDisabled(false);
        ui->reversebutton->setDisabled(false);
        ui->closebutton->setDisabled(false);

        ui->ptextedit->setReadOnly(false);
        ui->ctextedit->setReadOnly(true);
        ui->keyedit->setReadOnly(false);

        if (this->getCipher() == "caesar")
        {
            ui->typelabel->setText("int");
        }
        else if (this->getCipher() == "trans")
        {
            ui->typelabel->setText("string");
        }
    }
}
