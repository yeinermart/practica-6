#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "cuerpo.h"
#include <fstream>
#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sistema1_clicked();
    void on_sistema2_clicked();
    void on_finalizar_clicked();
    void movimiento1();
    void movimiento2();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *escena;

    //sistema 1
    Cuerpo *bola1;
    Cuerpo *bola2;
    Cuerpo *bola3;

    Cuerpo *bola1_auxiliar;
    Cuerpo *bola3_auxiliar;

    QTimer *timer1;
 //   fstream sistema1; //archivo

    //sistema 2
    Cuerpo *bol1;
    Cuerpo *bol2;
    Cuerpo *bol3;
    Cuerpo *bol4;
    Cuerpo *bol5;

    Cuerpo *bol2_auxiliar;
    Cuerpo *bol3_auxiliar;
    Cuerpo *bol4_auxiliar;
    Cuerpo *bol5_auxiliar;
    QTimer *timer2;
};
#endif // MAINWINDOW_H
