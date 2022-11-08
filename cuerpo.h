#ifndef CUERPO_H
#define CUERPO_H
#include <QGraphicsItem>  //base para todos los elementos gráficos
#include <QPainter> //realiza pintura de bajo nivel en widgets y otros dispositivos de pintura
#include <math.h>    //operaciones matemáticas básicas
#include <string.h>
#include <QPixmap>

using namespace std;

#define dt 1
#define G 1

class Cuerpo: public QGraphicsItem
{
private:
    double px;  //posicion en x
    double py;  //posicion en y
    double vx;  //velocidad en x
    double vy;  //velocidad en y
    double ax;  //aceleracion en x
    double ay;  //aceleracion en y
    int masa;     //masa
    int radio;    //radio del objeto
    QPixmap *pixmap;  //mapa de pixeles donde estara la imagen

public:
    QRectF boundingRect() const;  //crea el rectangulo base
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //lo pinta

    Cuerpo();   //constructor
    Cuerpo(double px_, double py_, double vx_, double vy_, double masa_, int imagen, int radio_); //constructor sobrecargado

    //metodos set: establecer y get:obtener

    void setpx(double x);  //para modificar el valor de px
    void setPy(double y);

    double getpy();   //para q me den el valor de py
    double getpx();
    double getvx();
    double getvy();
    double getmasa();

    void Actul_posi(double Ax, double Ay); //actualiza la posicion -- aceleracion x    y
};

#endif // CUERPO_H
