#ifndef DOCK_H
#define DOCK_H
#include<QDockWidget>
#include"terrain.h"
#include <QHBoxLayout>
#include<QPushButton>

class Dock:public QDockWidget
{
    Q_OBJECT
public:
    Dock(QString s,QWidget* parent):QDockWidget (s,parent){
        Terrain* t=Terrain::make_terrain("brick",QRect(0,0,50,50));

        QHBoxLayout *layout=new QHBoxLayout();
        layout->addWidget(t);
        t->resize(t->r.width(),t->r.height());
        QWidget* w=new QWidget();

        layout->addStretch();
        QPushButton* saveMap=new QPushButton("Save");
        connect(saveMap,&QPushButton::clicked,[=](){emit this->save();});
        layout->addWidget(saveMap);

        w->setLayout(layout);
//        w->setMinimumHeight(70);
        setWidget(w);

        setAcceptDrops(true);
    }
    void mousePressEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    ~Dock() override {}
signals:
    void save();
};

#endif // DOCK_H
