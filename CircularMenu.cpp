#include "CircularMenu.h"
#include "ui_CircularMenu.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QtMath>

 #define qcout qDebug()<<"["<<__func__<<__LINE__<<"]"

//暂时赋初值
CircularMenu::CircularMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CircularMenu)
    ,smallCircleRadius(200)
    ,centerCircleRadius(20)
    ,circleSpacing(10)
    ,iconScale(0.5)
    ,mousePressed(false)
{
    ui->setupUi(this);
    for(int i = 0; i < 9; ++i){
        QString imagePath = QString(":/%1").arg(i);
        QPixmap dImg(imagePath);
        directionImg.push_back(dImg);
    }


//    CustomButton* c = new CustomButton(this);
//    c->resize(200,200);
    connect(this,&CircularMenu::BtnClicked,this,&CircularMenu::ProcessButtonClicked);
}

CircularMenu::~CircularMenu()
{
    delete ui;
}

void CircularMenu::SetCircleRadius(const float radius)
{
    smallCircleRadius = radius;
}

void CircularMenu::SetCenterCircleRadius(const float radius)
{
    centerCircleRadius = radius;
}

void CircularMenu::SetCircleSpacing(const float spacing)
{
    circleSpacing = spacing;
}

void CircularMenu::SetAllCircleRadius(float centerRadius, float circleRadius, float ringRadius)
{
    SetCenterCircleRadius(centerRadius);
    SetCircleRadius(circleRadius);
    SetCircleSpacing(circleRadius + ringRadius);
}

void CircularMenu::SetIconScale(const float scale)
{
    if(scale == 1 || scale == 0)
        return;
    iconScale = scale;
}

void CircularMenu::DrawCircle(QPainter *painter)
{
    // save() restore()一对。保存 ，恢复 QPainter 的状态，类似基于栈的撤销
    painter->save();
    QPainterPath path;
    painter->setPen(QPen(Qt::SolidLine));
//    painter->setBrush(QBrush(Qt::red));

    auto bigCircleRadius = smallCircleRadius + circleSpacing;
    //绘制圆。
    painter->drawEllipse(QPointF(0, 0), bigCircleRadius, bigCircleRadius);
    painter->drawEllipse(QPointF(0, 0), smallCircleRadius, smallCircleRadius);
//    painter->drawEllipse(QPointF(0, 0), centerCircleRadius, centerCircleRadius);
    QPainterPath centerCirclePath;
    centerCirclePath.addEllipse(QPointF(0, 0), centerCircleRadius, centerCircleRadius);
    arcPathList.append(centerCirclePath);
//    QBrush outCircleBrush((Qt::red));
//    painter->fillPath(path, outCircleBrush);
    painter->restore();
}

void CircularMenu::DrawPie(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    //设置圆形渐变
    //构造一个简单的径向渐变，其中心位于（x，y）和指定的半径。
//    QRadialGradient radial(0, 0, bigCircleRadius);
//    radial.setColorAt(0, QColor("#e3fdfd"));
//    radial.setColorAt(1, QColor("#71c9ce"));
//    painter->setBrush(radial);

    //设置一个矩形区域，开始角度，和偏移角度。
    //即QRect(x,y,width,height)
    QRectF rectangle(-smallCircleRadius, -smallCircleRadius, smallCircleRadius*2, smallCircleRadius*2);

    //Startangle和Spanangle必须为16倍数，即全圈等于5760（16 * 360）。
    //在指定开始角度和偏移角度时，以3点钟为0度，正值表示逆时针方向，而负值表示顺时针方向。 
//    for (float angle = 22.5*16; angle<360*16;) {
//        painter->drawPie(rectangle, angle, angle + 45*16);
//        angle += 45*16;
//        qDebug()<<"angle"<<angle/16;
//    }
    //    painter->drawPie(rectangle, startAngle, spanAngle);

    float angle = 22.5;
    auto circleHeight = smallCircleRadius - centerCircleRadius;
    for (int i = 0; i < 8; i++) {
        QPainterPath path;
        path.arcTo(rectangle, angle, 45);
        angle += 45;
//        painter->setPen(QColor("#3d84a8"));
        QPainterPath subPath;
        //TODO：圆弧高度暂定为固定数值
        subPath.addEllipse(rectangle.adjusted(circleHeight, circleHeight, -circleHeight, -circleHeight));
        // path为扇形 subPath为椭圆 减去可得圆弧
        path -= subPath;
        arcPathList.append(path);
        painter->drawPath(path);
    }

    painter->restore();
}

void CircularMenu::DrawImage(QPainter *painter)
{
    painter->save();
    auto scaleFactor = smallCircleRadius / 2 * iconScale;
    auto xPoint = smallCircleRadius / sqrt(2);
    auto point = QPoint(-xPoint, -xPoint);

//    painter->drawPoint(QPoint(-smallRadius / sqrt(2), -smallRadius / sqrt(2)));
//    painter->drawLine(QPoint(0,0),QPoint(x, y));

//    //方案一：分别计算对应坐标点
//    //up 点(x,y) ...
//    float x = smallRadius/sqrt(5+5*tan(67.5*M_PI/180));
//    float y = sqrt(smallRadius*smallRadius - smallRadius*smallRadius/(5+5*tan(67.5*M_PI/180)));
//    //left-up 点(xx,xx)
//    float xx = smallRadius / sqrt(2);
//    painter->drawPixmap(QRect(QPoint(xx-scaleSize, -xx), QSize(scaleSize, scaleSize)), directionImg.at(1).scaled(QSize(scaleSize,scaleSize)));
//    painter->drawPixmap(QRect(QPoint(-xx, -xx), QSize(scaleSize, scaleSize)), directionImg.at(3).scaled(QSize(scaleSize,scaleSize)));
//    painter->drawPixmap(QRect(QPoint(-xx, xx-scaleSize), QSize(scaleSize, scaleSize)), directionImg.at(5).scaled(QSize(scaleSize,scaleSize)));
//    painter->drawPixmap(QRect(QPoint(xx-scaleSize, xx-scaleSize), QSize(scaleSize, scaleSize)), directionImg.at(8).scaled(QSize(scaleSize,scaleSize)));
//    painter->drawPixmap(QRect(QPoint(x-scaleSize, -y), QSize(scaleSize, scaleSize)), directionImg.at(2).scaled(QSize(scaleSize,scaleSize)));
//    painter->drawPixmap(QRect(QPoint(-y, x-scaleSize), QSize(scaleSize, scaleSize)), directionImg.at(4).scaled(QSize(scaleSize,scaleSize)));
//    painter->drawPixmap(QRect(QPoint(-x, y-scaleSize), QSize(scaleSize, scaleSize)), directionImg.at(6).scaled(QSize(scaleSize,scaleSize)));
//    painter->drawPixmap(QRect(QPoint(y-scaleSize, -x), QSize(scaleSize, scaleSize)), directionImg.at(8).scaled(QSize(scaleSize,scaleSize)));

    //方案二：通过left-up位置的图片直接旋转8次
//    for (int i = 0; i < 360;)
//    {
//        //旋转坐标轴
//        painter->rotate(i);
//        painter->drawPixmap(QRect(point, QSize(scaleFactor, scaleFactor)),
//                            directionImg.at(3).scaled(QSize(scaleFactor,scaleFactor),Qt::KeepAspectRatio, Qt::SmoothTransformation));
//        i += 45;
//    }

    //方案三：通过指定图片进行绘制
    QPixmap pix(":/resources/up-one.png");
    QMatrix matrix;
    matrix.translate(pix.width()/2.0,pix.height()/2);
    matrix.rotate(-45);
    matrix.translate(-pix.width()/2.0, -pix.height()/2);
    pix = pix.transformed(matrix,Qt::SmoothTransformation);
    for (int i = 0; i < 360;)
    {
        //旋转坐标轴
        painter->rotate(i);
        painter->drawPixmap(QRect(point, QSize(scaleFactor, scaleFactor)),
                            pix.scaled(QSize(scaleFactor,scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        i += 45;
    }
    // 中心按钮图标
    painter->drawPixmap(QRect(QPoint(-scaleFactor/2,-scaleFactor/2), QSize(scaleFactor, scaleFactor)),
                        directionImg.at(0).scaled(QSize(scaleFactor,scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    painter->restore();
}

void CircularMenu::MousePressed()
{
    QPainter painter(this);
    painter.setBrush(Qt::gray);
    painter.drawPath(arcPathList[1]);
    update();
}

//TODO:add corresponding func()
void CircularMenu::ProcessButtonClicked(int BtnID)
{
    switch (BtnID)
    {
    case 0:
        qcout<<QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 1:
        qcout<<QString("BtnID %1 clicked").arg(BtnID);

        break;
    case 2:
        qcout<<QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 3:
        qcout<<QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 4:
        qcout<<QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 5:
        qcout<<QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 6:
        qcout<<QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 7:
        qcout<<QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 8:
        qcout<<QString("BtnID %1 clicked").arg(BtnID);
        break;

    }
}

void CircularMenu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform);
    QPointF center(width() / 2.0, height() / 2.0);
    painter.translate(center);
//    painter.rotate(22.5);
    painter.setBrush(Qt::white);
    DrawCircle(&painter);
    DrawPie(&painter);
    DrawImage(&painter);
//    painter.translate(0,0);


    if(mousePressed)
    {
        painter.setBrush(Qt::gray);
        painter.drawPath(arcPathList[1]);
    }

}

void CircularMenu::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePressPoint = event->pos();

    //因进行了原点的偏移，故坐标点也需要偏移
    //x>>1 位运算，等效x/2
    QPoint translatePoint = mousePressPoint - QPoint(width() >> 1, height() >> 1);
    qcout<<"width"<<width()<<">>1"<<(width()>>1);
    qcout<<"pos"<<mousePressPoint<<"trans pos"<<translatePoint;

    for (int i = 0; i < arcPathList.count(); i++)
    {
        if (arcPathList[i].contains(translatePoint))
        {
            qcout<<"area i = "<<i;
            mousePressed = true;

            update();
            emit BtnClicked(i);
            break;
        }
    }
}

//TODO:调用update(）重新绘制，以覆盖按钮按下时的颜色填充操作
void CircularMenu::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressed = false;
    update();
}



