#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("practica_6")); //titulo de la ventana
    escena = new QGraphicsScene; // x/2  y/2  x y
    ui->graphicsView->setScene(escena); //establesco la escena
    escena->setSceneRect(-500,-250,1000,500);  //las dimensiones de la escena
    ui->graphicsView->setBackgroundBrush(Qt::black); //color de fondo

    //sistema 1
    // px , py, vx, vy, masa, imagen, radio
    bola1= new Cuerpo(0,-7000,2,0,70,1,120); //cuerpo 1
    bola2= new Cuerpo(0,0,0,0,70000,2,300); //cuerpo 2    central
    bola3= new Cuerpo(4000,5000,-1.6,1.2,25,3,100); //cuerpo 3
/*
    sistema1.open("sistema1",ios::out); //codigo para abrir el archivo o crear
    if(sistema1.fail()){
        cout<<"no se pudo abrir sistema1";
        exit(1);
    }
    sistema1<<"0 -7000 0 0 4000 5000"<<endl;
    */

    timer1 = new QTimer;
    connect(timer1,SIGNAL(timeout()),this,SLOT(movimiento1()));

    //sistema 2- px py vx vy masa bolaescogida radio
    bol1= new Cuerpo(0,0,0,0,50000,4,200);  //cuerpo 1    central
    bol2= new Cuerpo(-5000,0,0,-2,70,5,70+30);  //cuerpo 2 --le sumo 30 al radio para que
    bol3= new Cuerpo(5000,0,0,2,70,5,70+30);  //cuerpo 3   --los planetas o bolas no queden
    bol4= new Cuerpo(0,-5000,2,0,70,5,70+30);  //cuerpo 4  --tan pequeños
    bol5= new Cuerpo(0,5000,-2,0,70,5,70+30);  //cuerpo 5  --si el radio*2=resultado/20=tamaño
                                                         //-- en pixeles de la imagen ancho-alto
    timer2 = new QTimer;
    connect(timer2,SIGNAL(timeout()),this,SLOT(movimiento2()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sistema1_clicked()
{

    timer1->start(1); //1ms velocida de refrescamiento
/*
    bola2->setPos(0,0);  //prueba para verificar si aparecen las bolas o planetas
    escena->addItem(bola2);
    bola1->setPos(-600,0);
    escena->addItem(bola1);
    bola3->setPos(200,100);
    escena->addItem(bola3);
    */
}

void MainWindow::on_sistema2_clicked()
{
    timer2->start(1);
    /*
    bol1->setPos(0,0);     // prueba para probar si estan ahi
    escena->addItem(bol1);
    bol2->setPos(0,-300);
    escena->addItem(bol2);
    bol3->setPos(0,300);
    escena->addItem(bol3);
    bol4->setPos(600,0);
    escena->addItem(bol4);
    bol5->setPos(200,200);
    escena->addItem(bol5);
    */
}

void MainWindow::on_finalizar_clicked()
{
    timer1->stop();
    timer2->stop();
    escena->removeItem(bola2);
    escena->removeItem(bola1);
    escena->removeItem(bola3);

    escena->removeItem(bol1);
    escena->removeItem(bol2);
    escena->removeItem(bol3);
    escena->removeItem(bol4);
    escena->removeItem(bol5);
}

void MainWindow::movimiento1()
{
    //cuerpo 1
    double cuerpo1_Ax; //aceleracion en x del planeta 1
    double cuerpo1_Ay; //aceleracion en y del planeta 1

    double radio12; //distancia del planeta 1 al 2
    double teta12; //angulo del planeta 1 al planeta 2

    double radio13; //distancia del planeta 1 al 3
    double teta13; //angulo del planeta 1 al planeta 3

    double cuer1_pos_x;
    double cuer1_pos_y;

    //cuerpo 2
    double cuerpo2_Ax; //aceleracion en x del planeta 2
    double cuerpo2_Ay; //aceleracion en y del planeta 2

    double radio21; //distancia del planeta 2 al 1
    double teta21; //angulo del planeta 2 al planeta 1

    double radio23; //distancia del planeta 2 al 3
    double teta23; //angulo del planeta 2 al planeta 3

    double cuer2_pos_x;
    double cuer2_pos_y;

    //cuerpo 3
    double cuerpo3_Ax; //aceleracion en x del planeta 3
    double cuerpo3_Ay; //aceleracion en y del planeta 3

    double radio32; //distancia del planeta 3 al 2
    double teta32; //angulo del planeta 3 al planeta 2

    double radio31; //distancia del planeta 3 al 1
    double teta31; //angulo del planeta 3 al planeta 1

    double cuer3_pos_x; //posicion del cuerpo x y
    double cuer3_pos_y;

    double escala_x=40;  //escalo para q se vean dentro de la escena
    double escala_y=30;

    // aceleracion cuerpo 1 del cuerpo 2 y 3.
    //actualizacion posicion cuerpo 1

    //distancia del cuerpo 1 al cuerpo 2
    radio12= sqrt(pow(bola2->getpx()-bola1->getpx(),2) + pow(bola2->getpy()-bola1->getpy(),2));
    //angulo del cuerpo 1 al cuerpo 2
    teta12 = atan2(bola2->getpy()-bola1->getpy(),bola2->getpx()-bola1->getpx());

    //distancia del cuerpo 1 al cuerpo 3
    radio13= sqrt(pow(bola3->getpx()-bola1->getpx(),2) + pow(bola3->getpy()-bola1->getpy(),2));
    //angulo del cuerpo 1 al cuerpo 3
    teta13 = atan2(bola3->getpy()-bola1->getpy(),bola3->getpx()-bola1->getpx());

    //aceleraciones del cuerpo 1 por el cuerpo 2 y 3
    cuerpo1_Ax=(bola2->getmasa())*pow(radio12,-2)*cos(teta12)+(bola3->getmasa())*pow(radio13,-2)*cos(teta13);
    cuerpo1_Ay=(bola2->getmasa())*pow(radio12,-2)*sin(teta12)+(bola3->getmasa())*pow(radio13,-2)*sin(teta13);

    bola1->Actul_posi(cuerpo1_Ax, cuerpo1_Ay);

    cuer1_pos_x=bola1->getpx();
    cuer1_pos_y=bola1->getpy();
    bola1->setPos(cuer1_pos_x/escala_x,cuer1_pos_y/escala_y);
    escena->addItem(bola1);

//----------------------------------------------------------------------------------
    // aceleracion cuerpo 2 del cuerpo 1 y 3.
    //actualizacion posicion cuerpo 2

    //distancia del cuerpo 2 al cuerpo 1
    radio21= sqrt(pow(bola1->getpx()-bola2->getpx(),2) + pow(bola1->getpy()-bola2->getpy(),2));
    //angulo del cuerpo 2 al cuerpo 1
    teta21 = atan2(bola1->getpy()-bola2->getpy(),bola1->getpx()-bola2->getpx());

    //distancia del cuerpo 2 al cuerpo 3
    radio23= sqrt(pow(bola3->getpx()-bola2->getpx(),2) + pow(bola3->getpy()-bola2->getpy(),2));
    //angulo del cuerpo 2 al cuerpo 3
    teta23 = atan2(bola3->getpy()-bola2->getpy(),bola3->getpx()-bola2->getpx());

    //aceleraciones del cuerpo 2 al cuerpo 2 y 1
    cuerpo2_Ax=(bola1->getmasa())*pow(radio21,-2)*cos(teta21)+(bola3->getmasa())*pow(radio23,-2)*cos(teta23);
    cuerpo2_Ay=(bola2->getmasa())*pow(radio21,-2)*sin(teta21)+(bola3->getmasa())*pow(radio23,-2)*sin(teta23);

    bola2->Actul_posi(cuerpo2_Ax, cuerpo2_Ay);

    cuer2_pos_x=bola2->getpx();
    cuer2_pos_y=bola2->getpy();
    bola2->setPos(cuer2_pos_x/escala_x,cuer2_pos_y/escala_y);
    escena->addItem(bola2);

 //-----------------------------------------------------------------------------------------

    // aceleracion cuerpo 3 del cuerpo 2 y 1.
    //actualizacion posicion cuerpo 3

    //distancia del cuerpo 3 al cuerpo 1
    radio31= sqrt(pow(bola1->getpx()-bola3->getpx(),2) + pow(bola1->getpy()-bola3->getpy(),2));
    //angulo del cuerpo 3 al cuerpo 1
    teta31 = atan2(bola1->getpy()-bola3->getpy(),bola1->getpx()-bola3->getpx());

    //distancia del cuerpo 3 al cuerpo 2
    radio32= sqrt(pow(bola2->getpx()-bola3->getpx(),2) + pow(bola2->getpy()-bola3->getpy(),2));
    //angulo del cuerpo 3 al cuerpo 2
    teta32 = atan2(bola2->getpy()-bola3->getpy(),bola2->getpx()-bola3->getpx());

    //aceleraciones cuerpo 3 por el cuerpo 2 y 1
    cuerpo3_Ax=(bola2->getmasa())*pow(radio32,-2)*cos(teta32)+(bola1->getmasa())*pow(radio31,-2)*cos(teta31);
    cuerpo3_Ay=(bola2->getmasa())*pow(radio32,-2)*sin(teta32)+(bola1->getmasa())*pow(radio31,-2)*sin(teta31);

    bola3->Actul_posi(cuerpo3_Ax, cuerpo3_Ay);

    cuer3_pos_x=bola3->getpx();
    cuer3_pos_y=bola3->getpy();
    bola3->setPos(cuer3_pos_x/escala_x,cuer3_pos_y/escala_y);
    escena->addItem(bola3);

}

void MainWindow::movimiento2()
{
                            //sistema 2
    //cuerpo 1
    double cuerp1_Ax; //aceleracion en x del planeta 1
    double cuerp1_Ay; //aceleracion en y del planeta 1

    double radi12; //distancia del planeta 1 al 2
    double tet12; //angulo del planeta 1 al planeta 2

    double radi13; //distancia del planeta 1 al 3
    double tet13; //angulo del planeta 1 al planeta 3

    double radi14; //distancia del planeta 1 al 4
    double tet14;  //angulo del planeta 1 al 4

    double radi15; //distancia del planeta 1 al 5
    double tet15;    //angulo del planeta 1 al 5

    double cuer1_posi_x; //posiciones x y
    double cuer1_posi_y;

    //cuerpo 2 -----------------------------------------------------------------
    double cuerp2_Ax; //aceleracion en x del planeta 2
    double cuerp2_Ay; //aceleracion en y del planeta 2

    double radi21; //distancia del planeta 2 al 1
    double tet21; //angulo del planeta 2 al planeta 1

    double radi23; //distancia del planeta 2 al 3
    double tet23; //angulo del planeta 2 al planeta 3

    double radi24; //distancia del planeta 2 al 4
    double tet24; //angulo del planeta 2 al planeta 4

    double radi25; //distancia del planeta 2 al 5
    double tet25; //angulo del planeta 2 al planeta 5

    double cuer2_posi_x;  //posicion del planeta 2 x y
    double cuer2_posi_y;

    //cuerpo 3 -------------------------------------------------------------------
    double cuerp3_Ax; //aceleracion en x del planeta 3
    double cuerp3_Ay; //aceleracion en y del planeta 3

    double radi31; //distancia del planeta 3 al 1
    double tet31; //angulo del planeta 3 al planeta 1

    double radi32; //distancia del planeta 3 al 2
    double tet32; //angulo del planeta 3 al planeta 2

    double radi34; //distancia del planeta 3 al 4
    double tet34; //angulo del planeta 3 al planeta 4

    double radi35; //distancia del planeta 3 al 5
    double tet35; //angulo del planeta 3 al planeta 5

    double cuer3_posi_x;
    double cuer3_posi_y;

    //cuerpo 4 ----------------------------------------------------------------------------
    double cuerp4_Ax; //aceleracion en x del planeta 4
    double cuerp4_Ay; //aceleracion en y del planeta 4

    double radi41; //distancia del planeta 4 al 1
    double tet41; //angulo del planeta 4 al planeta 1

    double radi42; //distancia del planeta 4 al 2
    double tet42; //angulo del planeta 4 al planeta 2

    double radi43; //distancia del planeta 4 al 3
    double tet43; //angulo del planeta 4 al planeta 3

    double radi45; //distancia del planeta 4 al 5
    double tet45; //angulo del planeta 4 al planeta 5

    double cuer4_posi_x;  //posiciones del planeta 4
    double cuer4_posi_y;

    //cuerpo 5 --------------------------------------------------------------------------
    double cuerp5_Ax; //aceleracion en x del planeta 5
    double cuerp5_Ay; //aceleracion en y del planeta 5

    double radi51; //distancia del planeta 5 al 1
    double tet51; //angulo del planeta 5 al planeta 1

    double radi52; //distancia del planeta 5 al 2
    double tet52; //angulo del planeta 5 al planeta 2

    double radi53; //distancia del planeta 5 al 3
    double tet53; //angulo del planeta 5 al planeta 3

    double radi54; //distancia del planeta 5 al 4
    double tet54; //angulo del planeta 5 al planeta 4

    double cuer5_posi_x;  //posiciones del planeta 5
    double cuer5_posi_y;

//---------------------------------------------------------------------------------------

    double escal_x=40;  //escalo para q se vean dentro de la escena
    double escal_y=30;
//----------------------------------------------------------------------------------

    // aceleracion cuerpo 1 del cuerpo 2, 3, 4, 5.
    //actualizacion posicion cuerpo 1

    //distancia del cuerpo 1 al cuerpo 2
    radi12= sqrt(pow(bol2->getpx()-bol1->getpx(),2) + pow(bol2->getpy()-bol1->getpy(),2));
    //angulo del cuerpo 1 al cuerpo 2
    tet12 = atan2(bol2->getpy()-bol1->getpy(),bol2->getpx()-bol1->getpx());

    //distancia del cuerpo 1 al cuerpo 3
    radi13= sqrt(pow(bol3->getpx()-bol1->getpx(),2) + pow(bol3->getpy()-bol1->getpy(),2));
    //angulo del cuerpo 1 al cuerpo 3
    tet13 = atan2(bol3->getpy()-bol1->getpy(),bol3->getpx()-bol1->getpx());

    //distancia del cuerpo 1 al cuerpo 4
    radi14= sqrt(pow(bol4->getpx()-bol1->getpx(),2) + pow(bol4->getpy()-bol1->getpy(),2));
    //angulo del cuerpo 1 al cuerpo 4
    tet14 = atan2(bol4->getpy()-bol1->getpy(),bol4->getpx()-bol1->getpx());

    //distancia del cuerpo 1 al cuerpo 5
    radi15= sqrt(pow(bol5->getpx()-bol1->getpx(),2) + pow(bol5->getpy()-bol1->getpy(),2));
    //angulo del cuerpo 1 al cuerpo 5  --- aqui voy ***********
    tet15 = atan2(bol5->getpy()-bol1->getpy(),bol5->getpx()-bol1->getpx());

    //aceleraciones del cuerpo 1 por el cuerpo 2, 3, 4, 5
    cuerp1_Ax=(bol2->getmasa())*pow(radi12,-2)*cos(tet12)+(bol3->getmasa())*pow(radi13,-2)*cos(tet13)+(bol4->getmasa())*pow(radi14,-2)*cos(tet14)+(bol5->getmasa())*pow(radi15,-2)*cos(tet15);
    cuerp1_Ay=(bol2->getmasa())*pow(radi12,-2)*sin(tet12)+(bol3->getmasa())*pow(radi13,-2)*sin(tet13)+(bol4->getmasa())*pow(radi14,-2)*sin(tet14)+(bol5->getmasa())*pow(radi15,-2)*sin(tet15);

    bol1->Actul_posi(cuerp1_Ax, cuerp1_Ay);

    cuer1_posi_x=bol1->getpx();
    cuer1_posi_y=bol1->getpy();
    bol1->setPos(cuer1_posi_x/escal_x,cuer1_posi_y/escal_y);
    escena->addItem(bol1);

    //------------------------------------------------------------------------------

    // aceleracion cuerpo 2 del cuerpo 1, 3, 4, 5.
    //actualizacion posicion cuerpo 2

    //distancia del cuerpo 2 al cuerpo 1
    radi21= sqrt(pow(bol1->getpx()-bol2->getpx(),2) + pow(bol1->getpy()-bol2->getpy(),2));
    //angulo del cuerpo 2 al cuerpo 1
    tet21 = atan2(bol1->getpy()-bol2->getpy(),bol1->getpx()-bol2->getpx());

    //distancia del cuerpo 2 al cuerpo 3
    radi23= sqrt(pow(bol3->getpx()-bol2->getpx(),2) + pow(bol3->getpy()-bol2->getpy(),2));
    //angulo del cuerpo 2 al cuerpo 3
    tet23 = atan2(bol3->getpy()-bol2->getpy(),bol3->getpx()-bol2->getpx());

    //distancia del cuerpo 2 al cuerpo 4
    radi24= sqrt(pow(bol4->getpx()-bol2->getpx(),2) + pow(bol4->getpy()-bol2->getpy(),2));
    //angulo del cuerpo 2 al cuerpo 4
    tet24 = atan2(bol4->getpy()-bol2->getpy(),bol4->getpx()-bol2->getpx());

    //distancia del cuerpo 2 al cuerpo 5
    radi25= sqrt(pow(bol5->getpx()-bol2->getpx(),2) + pow(bol5->getpy()-bol2->getpy(),2));
    //angulo del cuerpo 2 al cuerpo 5
    tet25 = atan2(bol5->getpy()-bol2->getpy(),bol5->getpx()-bol2->getpx());

    //aceleraciones del cuerpo 2 por el cuerpo 1, 3, 4, 5
    cuerp2_Ax=(bol1->getmasa())*pow(radi21,-2)*cos(tet21)+(bol3->getmasa())*pow(radi23,-2)*cos(tet23)+(bol4->getmasa())*pow(radi24,-2)*cos(tet24)+(bol5->getmasa())*pow(radi25,-2)*cos(tet25);
    cuerp2_Ay=(bol1->getmasa())*pow(radi21,-2)*sin(tet21)+(bol3->getmasa())*pow(radi23,-2)*sin(tet23)+(bol4->getmasa())*pow(radi24,-2)*sin(tet24)+(bol5->getmasa())*pow(radi25,-2)*sin(tet25);

    bol2->Actul_posi(cuerp2_Ax, cuerp2_Ay);

    cuer2_posi_x=bol2->getpx();
    cuer2_posi_y=bol2->getpy();
    bol2->setPos(cuer2_posi_x/escal_x,cuer2_posi_y/escal_y);
    escena->addItem(bol2);

    //------------------------------------------------------------------------------

    // aceleracion cuerpo 3 del cuerpo 1, 2, 4, 5.
    //actualizacion posicion cuerpo 3

    //distancia del cuerpo 3 al cuerpo 1
    radi31= sqrt(pow(bol1->getpx()-bol3->getpx(),2) + pow(bol1->getpy()-bol3->getpy(),2));
    //angulo del cuerpo 3 al cuerpo 1
    tet31 = atan2(bol1->getpy()-bol3->getpy(),bol1->getpx()-bol3->getpx());

    //distancia del cuerpo 3 al cuerpo 2
    radi32= sqrt(pow(bol2->getpx()-bol3->getpx(),2) + pow(bol2->getpy()-bol3->getpy(),2));
    //angulo del cuerpo 3 al cuerpo 2
    tet32 = atan2(bol2->getpy()-bol3->getpy(),bol2->getpx()-bol3->getpx());

    //distancia del cuerpo 3 al cuerpo 4
    radi34= sqrt(pow(bol4->getpx()-bol3->getpx(),2) + pow(bol4->getpy()-bol3->getpy(),2));
    //angulo del cuerpo 3 al cuerpo 4
    tet34 = atan2(bol4->getpy()-bol3->getpy(),bol4->getpx()-bol3->getpx());

    //distancia del cuerpo 3 al cuerpo 5
    radi35= sqrt(pow(bol5->getpx()-bol3->getpx(),2) + pow(bol5->getpy()-bol3->getpy(),2));
    //angulo del cuerpo 3 al cuerpo 5
    tet35 = atan2(bol5->getpy()-bol3->getpy(),bol5->getpx()-bol3->getpx());

    //aceleraciones del cuerpo 3 por el cuerpo 1, 2, 4, 5
    cuerp3_Ax=(bol1->getmasa())*pow(radi31,-2)*cos(tet31)+(bol2->getmasa())*pow(radi32,-2)*cos(tet32)+(bol4->getmasa())*pow(radi34,-2)*cos(tet34)+(bol5->getmasa())*pow(radi35,-2)*cos(tet35);
    cuerp3_Ay=(bol1->getmasa())*pow(radi31,-2)*sin(tet31)+(bol2->getmasa())*pow(radi32,-2)*sin(tet32)+(bol4->getmasa())*pow(radi34,-2)*sin(tet34)+(bol5->getmasa())*pow(radi35,-2)*sin(tet35);

    bol3->Actul_posi(cuerp3_Ax, cuerp3_Ay);

    cuer3_posi_x=bol3->getpx();
    cuer3_posi_y=bol3->getpy();
    bol3->setPos(cuer3_posi_x/escal_x,cuer3_posi_y/escal_y);
    escena->addItem(bol3);

    //------------------------------------------------------------------------------

    // aceleracion cuerpo 4 del cuerpo 1, 2, 3, 5.
    //actualizacion posicion cuerpo 4

    //distancia del cuerpo 4 al cuerpo 1
    radi41= sqrt(pow(bol1->getpx()-bol4->getpx(),2) + pow(bol1->getpy()-bol4->getpy(),2));
    //angulo del cuerpo 4 al cuerpo 1
    tet41 = atan2(bol1->getpy()-bol4->getpy(),bol1->getpx()-bol4->getpx());

    //distancia del cuerpo 4 al cuerpo 2
    radi42= sqrt(pow(bol2->getpx()-bol4->getpx(),2) + pow(bol2->getpy()-bol4->getpy(),2));
    //angulo del cuerpo 4 al cuerpo 2
    tet42 = atan2(bol2->getpy()-bol4->getpy(),bol2->getpx()-bol4->getpx());

    //distancia del cuerpo 4 al cuerpo 3
    radi43= sqrt(pow(bol3->getpx()-bol4->getpx(),2) + pow(bol3->getpy()-bol4->getpy(),2));
    //angulo del cuerpo 4 al cuerpo 3
    tet43 = atan2(bol3->getpy()-bol4->getpy(),bol3->getpx()-bol4->getpx());

    //distancia del cuerpo 4 al cuerpo 5
    radi45= sqrt(pow(bol5->getpx()-bol4->getpx(),2) + pow(bol5->getpy()-bol4->getpy(),2));
    //angulo del cuerpo 4 al cuerpo 5
    tet45 = atan2(bol5->getpy()-bol4->getpy(),bol5->getpx()-bol4->getpx());

    //aceleraciones del cuerpo 4 por el cuerpo 1, 2, 3, 5
    cuerp4_Ax=(bol1->getmasa())*pow(radi41,-2)*cos(tet41)+(bol2->getmasa())*pow(radi42,-2)*cos(tet42)+(bol3->getmasa())*pow(radi43,-2)*cos(tet43)+(bol5->getmasa())*pow(radi45,-2)*cos(tet45);
    cuerp4_Ay=(bol1->getmasa())*pow(radi41,-2)*sin(tet41)+(bol2->getmasa())*pow(radi42,-2)*sin(tet42)+(bol3->getmasa())*pow(radi43,-2)*sin(tet43)+(bol5->getmasa())*pow(radi45,-2)*sin(tet45);

    bol4->Actul_posi(cuerp4_Ax, cuerp4_Ay);

    cuer4_posi_x=bol4->getpx();
    cuer4_posi_y=bol4->getpy();
    bol4->setPos(cuer4_posi_x/escal_x,cuer4_posi_y/escal_y);
    escena->addItem(bol4);

    //------------------------------------------------------------------------------

    // aceleracion cuerpo 5 del cuerpo 1, 2, 3, 4.
    //actualizacion posicion cuerpo 5

    //distancia del cuerpo 5 al cuerpo 1
    radi51= sqrt(pow(bol1->getpx()-bol5->getpx(),2) + pow(bol1->getpy()-bol5->getpy(),2));
    //angulo del cuerpo 5 al cuerpo 1
    tet51 = atan2(bol1->getpy()-bol5->getpy(),bol1->getpx()-bol5->getpx());

    //distancia del cuerpo 5 al cuerpo 2
    radi52= sqrt(pow(bol2->getpx()-bol5->getpx(),2) + pow(bol2->getpy()-bol5->getpy(),2));
    //angulo del cuerpo 5 al cuerpo 2
    tet52 = atan2(bol2->getpy()-bol5->getpy(),bol2->getpx()-bol5->getpx());

    //distancia del cuerpo 5 al cuerpo 3
    radi53= sqrt(pow(bol3->getpx()-bol5->getpx(),2) + pow(bol3->getpy()-bol5->getpy(),2));
    //angulo del cuerpo 5 al cuerpo 3
    tet53 = atan2(bol3->getpy()-bol5->getpy(),bol3->getpx()-bol5->getpx());

    //distancia del cuerpo 5 al cuerpo 4
    radi54= sqrt(pow(bol4->getpx()-bol5->getpx(),2) + pow(bol4->getpy()-bol5->getpy(),2));
    //angulo del cuerpo 5 al cuerpo 4
    tet54 = atan2(bol4->getpy()-bol5->getpy(),bol4->getpx()-bol5->getpx());

    //aceleraciones del cuerpo 5 por el cuerpo 1, 2, 3, 4
    cuerp5_Ax=(bol1->getmasa())*pow(radi51,-2)*cos(tet51)+(bol2->getmasa())*pow(radi52,-2)*cos(tet52)+(bol3->getmasa())*pow(radi53,-2)*cos(tet53)+(bol4->getmasa())*pow(radi54,-2)*cos(tet54);
    cuerp5_Ay=(bol1->getmasa())*pow(radi51,-2)*sin(tet51)+(bol2->getmasa())*pow(radi52,-2)*sin(tet52)+(bol3->getmasa())*pow(radi53,-2)*sin(tet53)+(bol4->getmasa())*pow(radi54,-2)*sin(tet54);

    bol5->Actul_posi(cuerp5_Ax, cuerp5_Ay);

    cuer5_posi_x=bol5->getpx();
    cuer5_posi_y=bol5->getpy();
    bol5->setPos(cuer5_posi_x/escal_x,cuer5_posi_y/escal_y);
    escena->addItem(bol5);


}

