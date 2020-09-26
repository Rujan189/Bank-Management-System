#include "createclient.h"
#include "ui_createclient.h"

#include <QApplication>
#include <QProcess>

#include <QSqlQuery>
#include <QStatusBar>
#include <QMessageBox>
CreateClient::CreateClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateClient)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

}

CreateClient::~CreateClient()
{
    delete ui;
}

void CreateClient::on_pushButton_prDetails_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void CreateClient::on_pushButton_bnAcc_n_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void CreateClient::on_pushButton_bnAcc_b_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void CreateClient::on_pushButton_sec_create_clicked()
{

        QString lname = ui->lineEdit_lname_2->text(); //1

        QString fname = ui->lineEdit_fname_2->text(); //2
        QString dob = ui->lineEdit_dob_2->text();//3
        QString nationality = ui->lineEdit_nationality_2->text();//4
        QString gender = ui->lineEdit_gender_2->text();//5
        QString acct = ui->lineEdit_acct_2->text();//6
        QString email = ui->lineEdit_email_2->text();//7
        QString usrt = ui->lineEdit_usrt_2->text();//8
        QString mob = ui->lineEdit_mob_2->text();//9
        QString address = ui->lineEdit_address_2->text();//10
        QString sq = ui->lineEdit_sq_2->text();//11
        QString ans = ui->lineEdit_ans->text();//12
        QString username_crcl = ui->lineEdit_username_crcl->text();
        QString password_crcl = ui->lineEdit_password_crcl->text();


        mw.connOpen();

        if(!mw.connOpen())
            qDebug()<<("Cannot Connect to Database");
        else
            qDebug()<<("Database Connected");

   QSqlQuery qry;
   qry.prepare("insert into Clients(Last_Name, First_Name, Username, Password, DOB, Nationality, Gender, Account_type, Email_ID, User_Type, Mobile_no, Address, Security_Question, Answer) values('"+lname+"', '"+fname+"','"+username_crcl+"','"+password_crcl+"' ,'"+dob+"', '"+nationality+"', '"+gender+"', '"+acct+"', '"+email+"', '"+usrt+"', '"+mob+"', '"+address+"', '"+sq+"', '"+ans.toUpper()+"')");

   if(qry.exec())
   {
       QMessageBox::information(this, tr("Status"), "Account created!\nYou can login after restarting the application.");
       mw.connClose();
       this->hide();

       qApp->quit();
       QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
       mw.close();
   }
   else{
       QMessageBox::critical(this, tr("Error"), qry.lastError().text());
   }

}

void CreateClient::on_pushButton_sec_b_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
