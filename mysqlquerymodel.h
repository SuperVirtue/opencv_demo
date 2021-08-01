#ifndef MYSQLQUERYMODEL_H
#define MYSQLQUERYMODEL_H

#include <QObject>
#include <QSqlQueryModel>
#include <QVariant>
#include <QColor>
#include <QDebug>
#include <QSqlQuery>
#include <QDateTime>
class MySqlQueryModel : public QSqlQueryModel
{
public:
    MySqlQueryModel(QObject *parent);
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    void setCurrentSqlStr(QString sql_str);

private:
    bool setRemarks(QString id,QString remarks);
    void refresh();
    QString current_sql_str;
};

#endif // MYSQLQUERYMODEL_H
