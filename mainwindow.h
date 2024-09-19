#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QIcon>
#include <QInputDialog>
#include <QMessageBox>
#include <QListWidget>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QPushButton* ad;
    QPushButton* ed;
    QPushButton* del;
    QIcon ad_icon;
    QIcon ed_icon;
    QIcon del_icon;
    QListWidget* listOfAddresses;
    QStringList addresses;
private:
    void saveInFile(const QString& name);
    void loadFromFile(const QString& name);
    void clickedAd();
    void clickedEd();
    void clickedDel();
    virtual void resizeEvent(QResizeEvent* event) override;
    void resizeComponents();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
