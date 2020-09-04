#include "mainwindow.h"
#include "map.h"
#include"dock.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    setAcceptDrops(true);
}

void MainWindow::switchScene(Scene s){
    scene=s;
    if(scene==Scene::GAME){
        QString s="map.json";
        Map* m=new Map(s,Map::State::IDLE);
        Util::RemoveLayout(centralWidget());
        setCentralWidget(m);
    }
    if(scene==Scene::EDIT){
        QString s="map.json";
        Map* m=new Map(s,Map::State::EDIT);
        Util::RemoveLayout(centralWidget());
        setCentralWidget(m);

        Dock *dock=new Dock("Widget",this);
        addDockWidget(Qt::BottomDockWidgetArea,dock);

        connect(dock,&Dock::save,m,&Map::save);
    }
}

void MainWindow::centerAndResize() {
    // get the dimension available on this screen
    QSize availableSize = qApp->desktop()->availableGeometry().size();
    int width = availableSize.width();
    int height = availableSize.height();
    qDebug() << "Available dimensions " << width << "x" << height;
    width *= 0.9; // 90% of the screen size
    height *= 0.9; // 90% of the screen size
    qDebug() << "Computed dimensions " << width << "x" << height;
    QSize newSize( width, height );

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            newSize,
            qApp->desktop()->availableGeometry()
        )
    );
}

MainWindow::~MainWindow()
{

}
