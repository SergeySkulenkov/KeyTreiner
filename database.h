#ifndef DATABASE_H
#define DATABASE_H

enum APP_MSG{
    DB_IS_EXISTS,
    DB_OK,
    NOT_CREATE_DB,
    NOT_CREATE_TABLE_USER
};

class DataBase
{
public:
    DataBase();
    APP_MSG restoreDataBase();
};

#endif // DATABASE_H
