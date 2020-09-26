#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "createclient.h"
#include <QPixmap>
#include <QCursor>
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    this->setGeometry(500,250,1099,687);
    this->setFixedSize(this->width(),this->height());

    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);

   QPixmap pic(":/img/ui/img/undraw_setup_wizard_r6mr.svg");
   ui->label_imge->setPixmap(pic.scaled(ui->label_imge->width(),ui->label_imge->height(),Qt::KeepAspectRatio));

   QPixmap avatar(":/img/ui/img/user.svg");
   ui->label_log->setPixmap(avatar.scaled(ui->label_log->width(),ui->label_log->height(),Qt::KeepAspectRatio));

   QPixmap menu_pic(":/img/ui/img/undraw_mobile_user_7oqo.svg");
   ui->label_menu_pic->setPixmap(menu_pic.scaled(ui->label_menu_pic->width(), ui->label_menu_pic->height(), Qt::KeepAspectRatio));

    connect(this, SIGNAL(menu_win()), this, SLOT(on_menu_win_Emitted()));
    connect(this, SIGNAL(check_passwd()), this, SLOT(on_check_passwd_emitted()));
    connect(this, SIGNAL(profile_menu()),this, SLOT(on_profile_menu_emitted()));
    connect(this, SIGNAL(deposit_menu()),this, SLOT(on_deposit_menu_emitted()));
    connect(this, SIGNAL(withdraw_menu()),this, SLOT(on_withdraw_menu_emitted()));
    connect(this, SIGNAL(transfer_menu()),this, SLOT(on_transfer_menu_emitted()));
    connect(this, SIGNAL(pswd_menu()),this, SLOT(on_pswd_menu_emitted()));
    connect(this, SIGNAL(staff_menu()),this, SLOT(on_staff_menu_emitted()));
    connect(this, SIGNAL(login()),this, SLOT(on_login_emitted()));


   if(!connOpen())
       ui->statusbar->showMessage("Not Connected to Db");
   else
       ui->statusbar->showMessage("Connected..");



}

MainWindow::~MainWindow()
{
    delete ui;
}


//------------slots implementation--------------------//
void MainWindow::on_menu_win_Emitted()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_check_passwd_emitted()
{
    QString new_p = ui->lineEdit_ch_new->text();
    QString re_p = ui->lineEdit_ch_new_retype->text();
         if(new_p==re_p)
         {
             ui->label_password_match->setVisible(false);

         }
         else{
             ui->label_password_match->setVisible(true);
         }
}

void MainWindow::on_profile_menu_emitted()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(0);
    connOpen();
       QSqlQuery qry;
    QString chk_name = ui->lineEdit_usrnam->text();
    qry.prepare("select * from Clients where Username='"+chk_name+"'");

    if(qry.exec())
    {
        while (qry.next())
        {

ui->lineEdit_accn_2->setText(qry.value(0).toString());
    ui->lineEdit_lname_2->setText(qry.value(1).toString());
    ui->lineEdit_fname_2->setText(qry.value(2).toString());
    ui->lineEdit_dob_2->setText(qry.value(6).toString());
    ui->lineEdit_nationality_2->setText(qry.value(7).toString());
    ui->lineEdit_gender_2->setText(qry.value(8).toString());
    ui->lineEdit_acct_2->setText(qry.value(9).toString());
    ui->lineEdit_email_2->setText(qry.value(10).toString());
    ui->lineEdit_usrt_2->setText(qry.value(11).toString());
    ui->lineEdit_mob_2->setText(qry.value(12).toString());
    ui->lineEdit_address_2->setText(qry.value(13).toString());
    ui->lineEdit_sq_2->setText(qry.value(14).toString());
}
    }
    else
        QMessageBox::warning(this, tr("Error"),qry.lastError().text());
}

void MainWindow::on_deposit_menu_emitted()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(1);

    bool ok;
    QString usrname = ui->lineEdit_usrnam->text();
connOpen();
    QSqlQuery qry;
    qry.prepare("select * from Clients where Username='"+usrname+"'");

    if(qry.exec())
    {
        while (qry.next())
        {

    ui->label_show_name->setText(qry.value(2).toString() +" " +qry.value(1).toString());
    auto abc = qry.value(3);
    long abc_num = abc.toUInt(&ok);
    ui->label_show_balance_11->setText(QString::number(abc_num,10));
    ui->label_show_accn->setText(qry.value(0).toString());
    connClose();

}
    }
    else
        QMessageBox::warning(this, tr("Error"),qry.lastError().text());


}

void MainWindow::on_transfer_menu_emitted()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(2);

     QString usrname = ui->lineEdit_usrnam->text();

     connOpen();

     QSqlQuery qry;
     qry.prepare("select * from Clients where Username='"+usrname+"'");

     if(qry.exec())
     {
       while (qry.next())
         {
             ui->label_show_name_3->setText(qry.value(2).toString() +" " +qry.value(1).toString());
             ui->label_show_accn_2->setText(qry.value(0).toString());
             ui->label_show_balance_4->setText(qry.value(3).toString());

         }
       }

       QSqlQueryModel* model = new QSqlQueryModel();
       QSqlQuery *pqry = new QSqlQuery(clientsDb);

       pqry->prepare("select Account_No from Clients");
       pqry->exec();
       model->setQuery(*pqry);
       ui->comboBox->setModel(model);


}

void MainWindow::on_withdraw_menu_emitted()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(3);


    QString usrname = ui->lineEdit_usrnam->text();
connOpen();
    QSqlQuery qry;
    qry.prepare("select * from Clients where Username='"+usrname+"'");

    if(qry.exec())
    {
        while (qry.next())
        {

    ui->label_show_name_4->setText(qry.value(2).toString() +" " +qry.value(1).toString());


    ui->label_show_balance_6->setText(qry.value(3).toString());
    ui->label_show_accn_3->setText(qry.value(0).toString());
    connClose();

        }
    }
}

void MainWindow::on_pswd_menu_emitted()
{
    ui->label_password_match->setVisible(false);
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setCurrentIndex(4);


}

void MainWindow::on_staff_menu_emitted()
{
    ui->stackedWidget->setCurrentIndex(3);
    QSqlQueryModel *model = new QSqlQueryModel();

    connOpen();
    QSqlQuery* qry = new QSqlQuery(clientsDb);

    qry->prepare("select * from Clients");

    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    connClose();
}

void MainWindow::on_login_emitted()
{
    QString usrname = ui->lineEdit_usrnam->text();
    QString passwd = ui->lineEdit_passwrd->text();

    if(!clientsDb.isOpen()){
        qDebug()<<"Failed to open database";
        return;
    }

    connOpen();
    QSqlQuery qry, qry1;
    qry.prepare("select * from Clients where Username='"+usrname+"' and Password='"+passwd+"'");
    if(qry.exec())
    {
        int count = 0;
        while(qry.next())
        {
            count++;
            if(qry.value(11).toString() == "Client"){
                ui->pushButton_staff_win->setEnabled(false);
                ui->pushButton_staff_win->setStyleSheet("QPushButton{background-color: lightgray;}");
                ui->pushButton_staff_win->setToolTip("This window is available only for staffs");

            }

        if(count==1)
        {ui->statusbar->showMessage("username and password is correct");

        connClose();
        ui->stackedWidget->setCurrentIndex(1);

        }
        if(count>1)
        {ui->statusbar->showMessage("username and password is duplicate");}
        if(count<1)
        {ui->statusbar->showMessage("username and password is incorrect");}
    }
    }
}


//---------------------------------------------------------------//

void MainWindow::on_pushButton_clicked()
{
    emit menu_win();
}

void MainWindow::on_pushButton_5_clicked()
{
    emit menu_win();
}

void MainWindow::on_pushButton_login_clicked()
{
    emit login();
    /*QString usrname = ui->lineEdit_usrnam->text();
    QString passwd = ui->lineEdit_passwrd->text();

    if(!clientsDb.isOpen()){
        qDebug()<<"Failed to open database";
        return;
    }

    connOpen();
    QSqlQuery qry, qry1;
    qry.prepare("select * from Clients where Username='"+usrname+"' and Password='"+passwd+"'");
    if(qry.exec())
    {
        int count = 0;
        while(qry.next())
        {
            count++;
            if(qry.value(11).toString() == "Client"){
                ui->pushButton_staff_win->setEnabled(false);
                ui->pushButton_staff_win->setStyleSheet("QPushButton{background-color: lightgray;}");
                ui->pushButton_staff_win->setToolTip("This window is available only for staffs");

            }

        if(count==1)
        {ui->statusbar->showMessage("username and password is correct");

        connClose();
        ui->stackedWidget->setCurrentIndex(1);

        }
        if(count>1)
        {ui->statusbar->showMessage("username and password is duplicate");}
        if(count<1)
        {ui->statusbar->showMessage("username and password is incorrect");}
    }
    }*/
}



void MainWindow::on_pushButton_profile_clicked()
{
    emit profile_menu();

}


void MainWindow::on_pushButton_signup_clicked()
{
   CreateClient crcl;
   crcl.setModal(true);
   crcl.exec();

}

void MainWindow::on_pushButton_upd8_clicked()
{
        QString chk_name = ui->lineEdit_usrnam->text();
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
    //QString sq = ui->lineEdit_sq_2->text();//11
    //QString ans = ui->lineEdit_ans->text();//12

    connOpen();
    QSqlQuery qry;
    qry.prepare("update Clients set Last_Name = '"+lname+"', First_Name = '"+fname+"', DOB = '"+dob+"', Nationality = '"+nationality+"', Gender = '"+gender+"', Account_type = '"+acct+"', Email_ID = '"+email+"', User_Type = '"+usrt+"', Mobile_no = '"+mob+"', Address = '"+address+"' where Username='"+chk_name+"'");

    if(qry.exec())
    {
        QMessageBox::information(this, tr("Status"), "Changes Saved!");
        connClose();

    }
    else{
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }


}

void MainWindow::on_pushButton_deposit_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_4_clicked()
{
    emit deposit_menu();



}

void MainWindow::on_pushButton_depos_clicked()
{
    QString chk_name = ui->lineEdit_usrnam->text();

    bool ok;
    QString txt = ui->label_show_balance_11->text();

    long txt_num = txt.toULong(&ok, 10);

    QString dep_txt = ui->lineEdit_deposit_3->text();
    long dep_txt_num = dep_txt.toULong(&ok, 10);

    txt_num += dep_txt_num;
   QString final_txt = QString::number(txt_num,10);

    connOpen();
    QSqlQuery qry;
    qry.prepare("update Clients set Balance='"+final_txt+"' where Username='"+chk_name+"'");
    if(qry.exec())
    {
        QMessageBox::information(this, tr("Status"), "Amount Deposited");
        ui->label_show_balance_11   ->setText(final_txt);
        //connClose();
    }
    else
        QMessageBox::warning(this, tr("Error"), qry.lastError().text());
}

//deposit clicked
void MainWindow::on_pushButton_2_clicked()
{
    emit transfer_menu();


}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    const QString *accn = &arg1;

    connOpen();

    QSqlQuery qry;
    qry.prepare("select * from Clients where Account_No='"+(*accn)+"'");

    if(qry.exec())
    {
        while (qry.next()) {

            ui->label_show_balance_5->setText(qry.value(3).toString());
                   }
            }
    else
    {
        QMessageBox::warning(this, tr("Error"), qry.lastError().text());
    }


}

void MainWindow::on_pushButton_transfer_2_clicked()
{
    QString chk_name = ui->lineEdit_usrnam->text();

    //deducting amt from available balane
    bool ok;
    QString txt = ui->label_show_balance_4->text();
    long txt_num = txt.toULong(&ok, 10);

    QString tr_txt = ui->lineEdit_transfer_amt_2->text();
    long tr_txt_num = tr_txt.toULong(&ok, 10);

    txt_num -= tr_txt_num;
   QString final_txt = QString::number(txt_num,10);
//-------------------------------------------------------------//
   connOpen();

   QSqlQuery qry, qry1;

   //adding the remanant amt to db
   qry.prepare("update Clients set Balance='"+final_txt+"' where Username='"+chk_name+"'");
   if(qry.exec())
   {
        ui->label_show_balance_4->setText(final_txt);
        //connClose();
   }
   else
       QMessageBox::warning(this, tr("Error"), qry.lastError().text());
//-----------------------------------------------------------------------------------------------------//

    //adding the transferred amt to credit acc
   QString txt1 = ui->label_show_balance_5->text();
   long txt1_num = txt1.toULong(&ok, 10);
   txt1_num += tr_txt_num;
  QString final_txt1 = QString::number(txt1_num,10);

  QString comb = ui->comboBox->currentText() ;

  //transferring........
  qry1.prepare("update Clients set Balance='"+final_txt1+"' where Account_No='"+comb+"'");
  if(qry1.exec())
  {
      QMessageBox::information(this, "Status", "Money Transferred!!");
      ui->label_show_balance_5->setText(final_txt1);
      ui->lineEdit_transfer_amt_2->setText("0");

  }
  else
    QMessageBox::warning(this, tr("Error"), qry1.lastError().text());

}
//------------------------------------------------------------------------//

void MainWindow::on_pushButton_3_clicked()
{
    emit withdraw_menu();

}

void MainWindow::on_pushButton_withdr_2_clicked()
{

QString chk_name = ui->lineEdit_usrnam->text();

    bool ok;
    QString txt = ui->label_show_balance_6->text();

    long txt_num = txt.toULong(&ok, 10);

    QString dep_txt = ui->lineEdit_withdraw_2->text();
    long dep_txt_num = dep_txt.toULong(&ok, 10);

    txt_num -= dep_txt_num;
   QString final_txt = QString::number(txt_num,10);

    connOpen();
    QSqlQuery qry;
    qry.prepare("update Clients set Balance='"+final_txt+"' where Username='"+chk_name+"'");
    if(qry.exec())
    {
        QMessageBox::information(this, tr("Status"), "Amount Withdrawn");
        ui->label_show_balance_6->setText(final_txt);
        ui->lineEdit_withdraw_2->setText("0");
        //connClose();
    }
    else
        QMessageBox::warning(this, tr("Error"), qry.lastError().text());
}



void MainWindow::on_pushButton_staff_win_clicked()
{
    emit staff_menu();
}

void MainWindow::on_pushButton_6_clicked()
{
    Forgotpasswd fwp;
    fwp.setModal(true);
    fwp.exec();
}

void MainWindow::on_pushButton_7_clicked()
{
    emit pswd_menu();

}

void MainWindow::on_pushButton_ch_change_psswd_clicked()
{

     QString usrname = ui->lineEdit_usrnam->text();
    QString old = ui->lineEdit_ch_old->text();
    QString new_p = ui->lineEdit_ch_new->text();
    QString re_p = ui->lineEdit_ch_new_retype->text();
    QString db_old;
    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from Clients where Username='"+usrname+"'");
    if(qry.exec())
    {qDebug()<< "qry executed";
        while (qry.next()){
            qDebug()<< "qry next also executed";
            db_old = (qry.value(5).toString());}}

    if (db_old == old){
        if(new_p==re_p)
        {
            ui->label_password_match->setVisible(false);
            QSqlQuery qry1;
            qry1.prepare("update Clients set Password='"+new_p+"' where Username='"+usrname+"'");
            if(qry1.exec()){qDebug()<< "qry1 executed";QMessageBox::information(this, "Status", "Password changed\n Changes will take effect on next login.");}
            connClose();
        }
        else{
            ui->label_password_match->setVisible(true);
        }
    }
}

void MainWindow::on_lineEdit_ch_new_retype_editingFinished()
{
    emit check_passwd();


}

void MainWindow::on_lineEdit_ch_new_editingFinished()
{
    emit check_passwd();
}

void MainWindow::on_pushButton_8_clicked()
{
    QString srch_txt = ui->lineEdit->text();
    connOpen();

    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(clientsDb);

    qry->prepare("select * from Clients where First_Name='"+srch_txt+"' or Last_Name='"+srch_txt+"' or Account_No='"+srch_txt+"'");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);





}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

    QString val = ui->tableView->model()->data(index).toString();
    connOpen();

    QSqlQuery qry;
    qry.prepare("select * from Clients where Last_Name = '"+val+"'or First_Name = '"+val+"'or DOB = '"+val+"'or Nationality = '"+val+"'or Gender = '"+val+"'or Account_type = '"+val+"'or Email_ID = '"+val+"'or User_Type = '"+val+"'or Mobile_no = '"+val+"'or Address='"+val+"' or Balance='"+val+"' or Username='"+val+"' or Password='"+val+"' or Security_Question='"+val+"'or Answer='"+val+"'");

    if(qry.exec())
    {
        while(qry.next())
        {
            ui->label_accn_tbl->setText(qry.value(0).toString());
                ui->lineEdit_lname_tbl->setText(qry.value(1).toString());
                ui->lineEdit_fname_tbl->setText(qry.value(2).toString());
                ui->lineEdit_dob_tbl->setText(qry.value(6).toString());
                ui->lineEdit_nationality_tbl->setText(qry.value(7).toString());
                ui->lineEdit_gender_tbl->setText(qry.value(8).toString());
                ui->lineEdit_acct_tbl->setText(qry.value(9).toString());
                ui->lineEdit_email_tbl->setText(qry.value(10).toString());
                ui->lineEdit_usrt_tbl->setText(qry.value(11).toString());
                ui->lineEdit_mob_tbl->setText(qry.value(12).toString());
                ui->lineEdit_address_tbl->setText(qry.value(13).toString());
                ui->lineEdit_sq_tbl->setText(qry.value(14).toString());
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), qry.lastError().text());
    }


}



void MainWindow::on_buttonBox_accepted()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    connOpen();
    QSqlQuery* qry = new QSqlQuery(clientsDb);

    qry->prepare("select * from Clients");

    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    connClose();
}



void MainWindow::on_pushButton_9_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    connOpen();
    QSqlQuery* qry = new QSqlQuery(clientsDb);

    qry->prepare("select * from Clients");

    qry->exec();
    model->setQuery(*qry);
    ui->tableView->setModel(model);
    connClose();
}


void MainWindow::on_pushButton_upd8_tbl_clicked()
{
    QString chk_name = ui->lineEdit_usrnam->text();
    QString lname = ui->lineEdit_lname_tbl->text(); //1
    QString fname = ui->lineEdit_fname_tbl->text(); //2
    QString dob = ui->lineEdit_dob_tbl->text();//3
    QString nationality = ui->lineEdit_nationality_tbl->text();//4
    QString gender = ui->lineEdit_gender_tbl->text();//5
    QString acct = ui->lineEdit_acct_tbl->text();//6
    QString email = ui->lineEdit_email_tbl->text();//7
    QString usrt = ui->lineEdit_usrt_tbl->text();//8
    QString mob = ui->lineEdit_mob_tbl->text();//9
    QString address = ui->lineEdit_address_tbl->text();//10
    QString accn = ui->label_accn_tbl->text();
    //QString sq = ui->lineEdit_sq_2->text();//11
    //QString ans = ui->lineEdit_ans->text();//12

    connOpen();
    QSqlQuery qry;
    qry.prepare("update Clients set Last_Name = '"+lname+"', First_Name = '"+fname+"', DOB = '"+dob+"', Nationality = '"+nationality+"', Gender = '"+gender+"', Account_type = '"+acct+"', Email_ID = '"+email+"', User_Type = '"+usrt+"', Mobile_no = '"+mob+"', Address = '"+address+"' where Account_No='"+accn+"'");

    if(qry.exec())
    {
        QMessageBox::information(this, tr("Status"), "Changes Saved!");
        connClose();

    }
    else{
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }
}

void MainWindow::on_pushButton_profile_4_clicked()
{
    emit profile_menu();
}

void MainWindow::on_pushButton_profile_3_clicked()
{
    emit profile_menu();
}

void MainWindow::on_pushButton_17_clicked()
{
    emit deposit_menu();
}

void MainWindow::on_pushButton_18_clicked()
{
    emit deposit_menu();
}

void MainWindow::on_pushButton_14_clicked()
{
    emit transfer_menu();
}

void MainWindow::on_pushButton_16_clicked()
{
    emit withdraw_menu();
}

void MainWindow::on_pushButton_15_clicked()
{
    emit pswd_menu();
}

void MainWindow::on_pushButton_staff_win_3_clicked()
{
    emit staff_menu();
}

void MainWindow::on_pushButton_19_clicked()
{
    emit transfer_menu();
}

void MainWindow::on_pushButton_20_clicked()
{
    emit withdraw_menu();
}

void MainWindow::on_pushButton_21_clicked()
{
    emit pswd_menu();
}

void MainWindow::on_pushButton_staff_win_4_clicked()
{
    emit staff_menu();
}
