#include "database.h"
#include "sqlite/sqlite3.h"
#include <QDebug>
#include <QFile>

static void upper(sqlite3_context *context,  int argc, sqlite3_value **argv){
    if( argc != 1 ) return;
    switch(sqlite3_value_type(argv[0]))
    {
    case SQLITE_NULL:
    {
        sqlite3_result_text( context, "NULL", 4, SQLITE_STATIC );
        break;
    }
    case SQLITE_TEXT:
    {
        QString str(reinterpret_cast<const char*>(sqlite3_value_text(argv[0])));
        str = str.toUpper();
        const char* cstr = static_cast<char*>( str.toUtf8().data());
        sqlite3_result_text(context, cstr, str.toUtf8().size() , SQLITE_TRANSIENT);
        break;
    }
    default:
        sqlite3_result_text( context, "NULL", 4, SQLITE_STATIC );
        break;
    }
}

static int localeCompare( void* /*arg*/, int len1, const void* data1,  int len2, const void* data2 )
{
    qDebug() << "localeCopare";
    QString string1 = QString::fromUtf8((char*)data1,len1).toUpper();
    QString string2 = QString::fromUtf8((char*)data2,len2).toUpper();
    qDebug() << string1 << "=?=" << string2;
    return QString::localeAwareCompare( string1, string2 );
}

DataBase::DataBase() {}

void DataBase::restoreDataBase()
{
    if(QFile::exists("example.db")){
        return;
    }
    /* Открываем соединение с БД */
    sqlite3* db;
    if(sqlite3_open("example.db", &db) == SQLITE_OK){
        //Установлено
    }else{
        //Ошибка
        return;
    }

    char *zErrMsg = 0;          //Текст сообщения об ошибке

    /* Создаём таблицу */
    std::string sql = "CREATE TABLE users("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "user_name      TEXT NOT NULL,"
                      "last_point     INTEGER NOT NULL);";

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
        qDebug() << zErrMsg;
        sqlite3_free(zErrMsg);
        return;
    } else {
        qDebug() << "Таблица создана";
    }



    /* Закрываем соединение с БД */
    sqlite3_close(db);
}
