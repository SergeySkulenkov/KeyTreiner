#include "data.h"
#include "database.h"
#include <QDebug>
Data::Data() {}


bool Data::restoreDb()
{
    DataBase db;
    APP_MSG error = db.restoreDataBase();
    if(error == DB_IS_EXISTS){
        qInfo() << "База данных уже существует";
    }else if(error != DB_OK){
        qWarning() << "Не удалось создать базу данных";
        return false;
    }
    return true;
}
