#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QIODevice>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

#include <Item.h>

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

size_t print_table(const vector<Item>& data, QTextStream& ost)
{
    Item::print_table_head(ost);
    for (const Item& item : data)
    {
        item.print_table_row(ost);
    }
    return 0;
}

size_t load_txt(vector<Item>& data, std::istream& ist)
{
    int amount = 0;
    string buff;
    while (getline(ist, buff))
    {
        amount++;
    }
    ist.clear();
    ist.seekg(0, ios_base::beg);
    for (int i = 0; i < amount; i++)
    {
        Item item;
        item.load_txt(ist);
        data.push_back(item);
    }
    return amount;
}

size_t load_bin(vector<Item>& data, std::istream& ist)
{
    int amount = 0;
    for (;!ist.eof();)
    {
        Item user;
        user.load_bin(ist);
        if (!user.GetLast_name().empty())
        {
            data.push_back(user);
            amount++;
        }
    }
    return amount;
}

size_t save_bin(const vector<Item>& data, ostream& ost)
{
    for (const Item& item : data) {
        item.save_bin(ost);
    }
    return 0;
}

bool comparator(const Item& item1, const Item& item2)
{
    return (item1.GetKurs() > item2.GetKurs());
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->modeButtonGroup->setId(ui->mode1RadioButton, 1);
    ui->modeButtonGroup->setId(ui->mode2RadioButton, 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_execPushButton_clicked()
{
    QMessageBox::information(this, tr("The run button is clicked"), tr("The selected mode %1").arg(ui->modeButtonGroup->checkedId()));
    QString out_text;
    QTextStream ost(&out_text, QIODevice::WriteOnly);
    ost << tr("Text file: ") << ui->textFileLineEdit->text() << "\n"
        << tr("Binary file: ") << ui->binFileLineEdit->text() << "\n"
        << tr("Mode: ") << ui->modeButtonGroup->checkedId() << "\n";

    vector<Item> buffer_data;

    if(ui->modeButtonGroup->checkedId() == 1) {
        ifstream ist(ui->textFileLineEdit->text().toUtf8().constData());
        ofstream out(ui->binFileLineEdit->text().toUtf8().constData(), ios::binary);

        load_txt(buffer_data, ist);

        print_table(buffer_data, ost);
        ui->outTextEdit->setPlainText(out_text);

        sort(buffer_data.begin(), buffer_data.end(), comparator);
        save_bin(buffer_data, out);

        buffer_data.clear();
        ist.close();
        out.close();

    }
    else if(ui->modeButtonGroup->checkedId() == 2) {
        ifstream in(ui->binFileLineEdit->text().toUtf8().constData(), ios::binary);

        load_bin(buffer_data, in);
        print_table(buffer_data, ost);
        ui->outTextEdit->setPlainText(out_text);

        buffer_data.clear();
        in.close();
    }
}
