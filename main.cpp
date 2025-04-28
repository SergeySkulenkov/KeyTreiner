#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QElapsedTimer>
#include <QStyleFactory>
#include <QDebug>
#include "data.h"

void loadМodules(QSplashScreen* psplash)
{
    QElapsedTimer time;
    time.start();
    Data data;
    if(!data.restoreDb()){
        qDebug() << "Сообщение от сплеш страницы: Не удалось создать базу данных";
    }
    for (int i = 0; i < 100; ) {
        if (time.elapsed() > 10){
            time.start();
            ++i;
        }
        if(i%10 == 0){
            psplash->showMessage("Loading modules: "+ QString::number(i) + "%",
                                Qt::AlignHCenter | Qt::AlignBottom,
                                Qt::white
                                );
            qApp->processEvents();
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QSplashScreen splash(QPixmap(":/resouurces/splash.jpg"));
    splash.show();
    MainWindow w;
    loadМodules(&splash);
    splash.finish(&w);
    w.show();
    return a.exec();
}
