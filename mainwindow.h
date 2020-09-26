#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>

#include <forgotpasswd.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSqlDatabase clientsDb;

public:
    void connClose()
    {
        clientsDb.close();
        clientsDb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen()
    {
        clientsDb= QSqlDatabase::addDatabase("QSQLITE");
        clientsDb.setDatabaseName("/home/itis/Documents/prac/qt-projects/ytube/bms/lib/data/bms.db");

        if(!clientsDb.open())
        {
            qDebug()<<("Not Connected..");
            return false;
        }
        else
        {
            qDebug() << ("Connected..");
            return true;
        }
    }

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();



    void on_pushButton_profile_clicked();

    void on_pushButton_signup_clicked();

    void on_pushButton_upd8_clicked();

    void on_pushButton_deposit_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_depos_clicked();

    void on_pushButton_2_clicked();



    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_transfer_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_withdr_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_staff_win_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_ch_change_psswd_clicked();

    void on_lineEdit_ch_new_retype_editingFinished();
    void on_pushButton_8_clicked();
    void on_lineEdit_ch_new_editingFinished();

signals:
    void menu_win();
    void check_passwd();
    void profile_menu();
    void deposit_menu();
    void transfer_menu();
    void withdraw_menu();
    void pswd_menu();
    void staff_menu();
    void login();

private slots:
    void on_menu_win_Emitted();
    void on_check_passwd_emitted();
    void on_profile_menu_emitted();
    void on_deposit_menu_emitted();
    void on_transfer_menu_emitted();
    void on_withdraw_menu_emitted();
    void on_pswd_menu_emitted();
    void on_staff_menu_emitted();
    void on_login_emitted();

    void on_tableView_clicked(const QModelIndex &index);

    //void on_tableView_activated(const QModelIndex &index);

    void on_buttonBox_accepted();



    void on_pushButton_9_clicked();

    //void on_pushButton_8_clicked(bool checked);

    void on_pushButton_upd8_tbl_clicked();

    void on_pushButton_profile_4_clicked();

    void on_pushButton_profile_3_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_staff_win_3_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_staff_win_4_clicked();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
