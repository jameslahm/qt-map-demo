#include "mainwindow.h"
#include "map.h"
#include"dock.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    switchScene(MainWindow::Scene::START);
    setAcceptDrops(true);
}

void MainWindow::switchScene(Scene s){
    scene=s;
    if(scene==Scene::GAME){
        QString s="map.json";
        Map* m=new Map(s,Map::State::IDLE);
        Util::RemoveLayout(centralWidget());
        QPushButton* returnBack=new QPushButton("Return");
        connect(returnBack,&QPushButton::clicked,[=](){this->switchScene(Scene::START);});
        returnBack->setParent(m);
        returnBack->setGeometry(this->width()-110,10,100,50);
        returnBack->show();
        setCentralWidget(m);
    }
    if(scene==Scene::EDIT){
        QString s="map.json";
        Map* m=new Map(s,Map::State::EDIT);
        Util::RemoveLayout(centralWidget());
        QPushButton* returnBack=new QPushButton("Return");
        connect(returnBack,&QPushButton::clicked,[=](){this->switchScene(Scene::START);});
        returnBack->setParent(m);
        returnBack->setGeometry(this->width()-110,10,100,50);
        returnBack->show();
        setCentralWidget(m);

        dock=new Dock("Widget",this);
        addDockWidget(Qt::BottomDockWidgetArea,dock);

        connect(dock,&Dock::save,m,&Map::save);
    }
    if(scene==Scene::START){
        qDebug()<<"Start"<<endl;
        QPushButton* startGame=new QPushButton("Start Game");
        QPushButton* editMap = new QPushButton("Edit Map");
        connect(startGame,&QPushButton::clicked,[=](){this->switchScene(Scene::GAME);});
        connect(editMap,&QPushButton::clicked,[=](){this->switchScene(Scene::EDIT);});
        QVBoxLayout* layout=new QVBoxLayout();
        layout->addWidget(startGame);
        layout->addWidget(editMap);
        QWidget* w=new QWidget();
        setCentralWidget(w);
        w->setLayout(layout);
        if(dock) removeDockWidget(dock);
    }

}

void MainWindow::centerAndResize() {
    // get the dimension available on this screen
    QSize availableSize = qApp->primaryScreen()->geometry().size();
    int width = availableSize.width();
    int height = availableSize.height();
    qDebug() << "Available dimensions " << width << "x" << height;
    width *= 0.9; // 100% of the screen size
    height *= 0.9; // 100% of the screen size
    qDebug() << "Computed dimensions " << width << "x" << height;
    QSize newSize( width, height );

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            newSize,
            qApp->primaryScreen()->geometry()
        )
    );
}

MainWindow::~MainWindow()
{

}
