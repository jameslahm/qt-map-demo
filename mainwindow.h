#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum Scene {
        START,
        GAME,
        EDIT
    };
    Scene scene;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void centerAndResize();
    void switchScene(Scene s);
};

#endif // MAINWINDOW_H
