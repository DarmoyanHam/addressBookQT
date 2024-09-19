#include "mainwindow.h"
#include "ui_mainwindow.h"

double percent(double, double);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(0, 0, 700, 700);

    ad_icon = QIcon("C:/Users/darmo/Downloads/add.png");
    ad = new QPushButton("add address", this);
    //ad->setGeometry(100, 100, 200, 100);
    ad->setIcon(ad_icon);
    ad->setIconSize(QSize(50, 50));
    ad->setStyleSheet("background-color: green; color: black;");

    ed_icon = QIcon("C:/Users/darmo/Downloads/edit-button.png");
    ed = new QPushButton("edit address", this);
    //ed->setGeometry(100, 210, 200, 100);
    ed->setIcon(ed_icon);
    ed->setIconSize(QSize(50, 50));
    ed->setStyleSheet("background-color: darkblue; color: black;");

    del_icon = QIcon("C:/Users/darmo/Downloads/close.png");
    del = new QPushButton("delete address", this);
    //del->setGeometry(100, 320, 200, 100);
    del->setIcon(del_icon);
    del->setIconSize(QSize(50, 50));
    del->setStyleSheet("background-color: darkred; color: black;");

    listOfAddresses = new QListWidget(this);
    //listOfAddresses->setGeometry(350, 100, 300, 500);

    resizeComponents();

    loadFromFile("C:/Users/darmo/OneDrive/Desktop/dir/c++/Qt/adress_book/addresses.txt");

    connect(ad, &QPushButton::clicked, this, &MainWindow::clickedAd);
    connect(ed, &QPushButton::clicked, this, &MainWindow::clickedEd);
    connect(del, &QPushButton::clicked, this, &MainWindow::clickedDel);
}

void MainWindow::clickedAd()
{
    QString data = QInputDialog::getText(this, "Add data", "Write new data here");

    if(!data.isEmpty())
    {
        QMessageBox::information(this, "Successfull adding", "Entered data is " + data);
        addresses.append(data);
        listOfAddresses->addItem(data);
        saveInFile("C:/Users/darmo/OneDrive/Desktop/dir/c++/Qt/adress_book/addresses.txt");
    }
    else
    {
        QMessageBox::warning(this, "warning", "You should write something");
    }
}

void MainWindow::clickedEd()
{
    QListWidgetItem* selected = listOfAddresses->currentItem();

    if(selected)
    {
        QString newAddress = QInputDialog::getText(this, "New data", "Write new data here");

        if(!newAddress.isEmpty())
        {
            selected->setText(newAddress);
            int row = listOfAddresses->row(selected);
            addresses[row] = newAddress;
            saveInFile("C:/Users/darmo/OneDrive/Desktop/dir/c++/Qt/adress_book/addresses.txt");
        }
        else
        {
            QMessageBox::warning(this, "warning", "You should write something");
        }
    }
    else
    {
        QMessageBox::warning(this, "warning", "nothing was selected");
    }
}

void MainWindow::clickedDel()
{
    QListWidgetItem* selected = listOfAddresses->currentItem();
    if(selected)
    {
        int row = listOfAddresses->row(selected);
        listOfAddresses->takeItem(row);
        addresses.removeAt(row);
        saveInFile("C:/Users/darmo/OneDrive/Desktop/dir/c++/Qt/adress_book/addresses.txt");
    }
    else
    {
        QMessageBox::warning(this, "warning", "nothing was selected");
    }
}

void MainWindow::saveInFile(const QString &name)
{
    QFile file(name);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for(auto& i : addresses)
        {
            out << i << '\n';
        }

        file.close();
    }
}

void MainWindow::loadFromFile(const QString &name)
{
    QFile file(name);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString address = in.readLine();
            if(!address.isEmpty())
            {
                addresses.append(address);
                listOfAddresses->addItem(address);
            }
        }

        file.close();
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    resizeComponents();
}

void MainWindow::resizeComponents()
{
    int w = this->width();
    int h = this->height();
    ad->setGeometry(percent(w, 5), percent(h, 5), percent(w, 20), percent(h, 15));
    ed->setGeometry(percent(w, 5), percent(h, 25), percent(w, 20), percent(h, 15));
    del->setGeometry(percent(w, 5), percent(h, 45), percent(w, 20), percent(h, 15));

    listOfAddresses->setGeometry(percent(w, 30), percent(h, 5), percent(w, 65), percent(h, 90));
}

double percent(double x, double y)
{
    return x * y / 100;
}



MainWindow::~MainWindow()
{
    saveInFile("C:/Users/darmo/OneDrive/Desktop/dir/c++/Qt/adress_book/addresses.txt");
}

