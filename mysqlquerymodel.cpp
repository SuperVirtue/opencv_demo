#include "mysqlquerymodel.h"


MySqlQueryModel::MySqlQueryModel(QObject *parent) : QSqlQueryModel(parent)
{

}

Qt::ItemFlags MySqlQueryModel::flags(const QModelIndex &index) const{

    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if(index.column()==5)
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool MySqlQueryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() < 5 || index.column() > 5)
            return false;
        QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 3);
        QDateTime time_id = data(primaryKeyIndex).toDateTime();
        QString id=time_id.toString("yyyy-MM-dd hh:mm:ss");
        clear();
        bool ok=false;
        if (index.column() == 5)
            ok = setRemarks(id, value.toString());
        refresh();
        return ok;
}

void MySqlQueryModel::setCurrentSqlStr(QString sql_str)
{
    current_sql_str=sql_str;
}

bool MySqlQueryModel::setRemarks(QString id, QString remarks)
{
    QSqlQuery query;
    QString update_sql_str="update employee_information.employee_attendance_record set remarks ='"+remarks+"' where Attendance_time ='"+id+"';";
    bool ok = query.exec(update_sql_str);
    return ok;
}

void MySqlQueryModel::refresh()
{
    if(!current_sql_str.isEmpty()){
        setQuery(current_sql_str);
        setHeaderData(0,Qt::Horizontal, "工号");
        setHeaderData(1,Qt::Horizontal, "部门");
        setHeaderData(2,Qt::Horizontal, "姓名");
        setHeaderData(3,Qt::Horizontal, "打卡时间");
        setHeaderData(4,Qt::Horizontal, "状态");
        setHeaderData(5,Qt::Horizontal, "备注");
    }
}

QVariant MySqlQueryModel::data(const QModelIndex &item, int role) const{
    QVariant value = QSqlQueryModel::data(item,role);
    QVariant value_ = QSqlQueryModel::data(item,Qt::DisplayRole);
    if(role==Qt::ForegroundRole&&value_.toString() == "异常打卡"){
        return QColor(Qt::red);
    }
    return value;
}
