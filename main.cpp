#include <QCoreApplication>
#include <QtSql>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString serverName = "(localdb)\\Projects";
    QString dbName = "test";

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();

    QString dsn = QString("Driver={SQL Server Native Client 11.0};Server=%1;Database=%2;Uid=odbc;Pwd=odbc;").arg(serverName).arg(dbName);
    db.setDatabaseName(dsn);

    if (db.open()) {
        qDebug() << "Opened!";
        // create a query to investigate a table in the SQL Server (user odbc has the sysadmin role!)
        QSqlQuery qry;
        if (qry.exec("SELECT * FROM [test].[dbo].[people]")) {
            while (qry.next()) {
                qDebug() << qry.value(0).toInt() << " " << qry.value(1).toString() << " " << qry.value(2).toString();
            }
        } else {
           qDebug() << "Error: " << db.lastError().text();
        }
        qDebug() << "Closing...";
        db.close();
    } else {
        qDebug() << "Error: " << db.lastError().text();
    }

    return a.exec();
}
