#include "cuerpo.h"

QRectF Cuerpo::boundingRect() const
{
    return QRectF(-radio/20,-radio/20,2*radio/20,2*radio/20);
}

void Cuerpo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-radio/20,-radio/20,*pixmap,0,0,2*radio/20,2*radio/20);
}

Cuerpo::Cuerpo()
{

}

Cuerpo::Cuerpo(double px_, double py_, double vx_, double vy_, double masa_, int imagen, int radio_)
{
    radio=radio_;
    px=px_;
    py=py_;
    vx=vx_;
    vy=vy_;
    masa=masa_;
    setPos(px,py);  //establecer posicion
    if(imagen==1)
        {
            pixmap = new QPixmap(":/imagenes/cuerpo1_2.png");
        }
    if(imagen==2)
        {
            pixmap = new QPixmap(":/imagenes/cuerpo2_1_central.jpg");
        }
    if(imagen==3)
        {
            pixmap = new QPixmap(":/imagenes/cuerpo3_3.jpg");
        }
    if(imagen==4)
        {
            pixmap = new QPixmap(":/imagenes/cuerpo4_4.jpg");
        }
    if(imagen==5)
        {
            pixmap = new QPixmap(":/imagenes/cuerpo5_5.jpg");
        }
}

void Cuerpo::setpx(double x)
{
    px=x;
}

void Cuerpo::setPy(double y)
{
    py=y;
}

double Cuerpo::getpy()
{
    return py;
}

double Cuerpo::getpx()
{
    return px;
}

double Cuerpo::getvx()
{
    return vx;
}

double Cuerpo::getvy()
{
    return vy;
}

double Cuerpo::getmasa()
{
    return masa;
}

void Cuerpo::Actul_posi(double Ax, double Ay)
{
    vx = vx + Ax*dt;   //formula de velocida
    vy = vy + Ay*dt;
    px= px + vx*dt + (0.5)*Ax*(dt*dt); //formula de posicion
    py= py + vy*dt + (0.5)*Ay*(dt*dt);
}
