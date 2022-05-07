#include "CircularMenu.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QMatrix>
#include <QtMath>
#include <QDebug>

#define qcout qDebug() << "[" << __func__ << __LINE__ << "]"

class CircularMenuPrivate
{
    Q_DECLARE_PUBLIC(CircularMenu)
public:
    CircularMenuPrivate(CircularMenu *q);
    virtual ~CircularMenuPrivate() = default;

private:
    /**
     * @brief DrawCircle 画圆
     * @param painter
     */
    void DrawCircle(QPainter *painter);
    /**
     * @brief DrawPie 画弧形区域
     * @param painter
     */
    void DrawPie(QPainter *painter);
    /**
     * @brief DrawImage 将图标画上去
     * @param painter
     */
    void DrawImage(QPainter *painter);

private:
    CircularMenu *const q_ptr;

    float smallCircleRadius;         //小圆半径
    float centerCircleRadius;        //中心小圆半径
                                     //    float bigCircleRadius;//大圆半径 等于小圆加间隔
    float circleSpacing;             //大小圆之间的间隔
    float iconScale;                 //图标缩放比例
    bool mousePressed;               //鼠标按下标志位
    int areaIndex;                   //区域索引
    QList<QPainterPath> arcPathList; //区域索引：0为center，1为right-up
    QColor bgColor;
    QColor pressColor;
};

CircularMenuPrivate::CircularMenuPrivate(CircularMenu *q)
    : q_ptr(q), smallCircleRadius(200), centerCircleRadius(20), circleSpacing(10), iconScale(0.5), mousePressed(false), bgColor(Qt::transparent), pressColor(Qt::white)
{
}

CircularMenu::CircularMenu(QWidget *parent)
    : QWidget(parent), d_ptr(new CircularMenuPrivate(this))
{
    //    for(int i = 0; i < 9; ++i){
    //        QString imagePath = QString(":/%1").arg(i);
    //        QPixmap dImg(imagePath);
    //        directionImg.push_back(dImg);
    //    }

    connect(this, &CircularMenu::BtnClicked, this, &CircularMenu::ProcessButtonClicked);
}

CircularMenu::~CircularMenu()
{
}

void CircularMenu::SetCircleRadius(const float radius)
{
    Q_D(CircularMenu);
    d->smallCircleRadius = radius;
}

void CircularMenu::SetCenterCircleRadius(const float radius)
{
    Q_D(CircularMenu);
    d->centerCircleRadius = radius;
}

void CircularMenu::SetCircleSpacing(const float spacing)
{
    Q_D(CircularMenu);
    d->circleSpacing = spacing;
}

void CircularMenu::SetAllCircleRadius(float centerRadius, float circleRadius, float ringRadius)
{
    SetCenterCircleRadius(centerRadius);
    SetCircleRadius(circleRadius);
    SetCircleSpacing(circleRadius + ringRadius);
}

void CircularMenu::SetImageScale(const float scale)
{
    Q_D(CircularMenu);
    if (scale == 1 || scale == 0)
        return;
    d->iconScale = scale;
}

void CircularMenu::SetBackgroundColor(const QColor &bg)
{
    Q_D(CircularMenu);
    d->bgColor = bg;
}

void CircularMenu::SetBtnPressColor(const QColor &c)
{
    Q_D(CircularMenu);
    d->pressColor = c;
}

void CircularMenuPrivate::DrawCircle(QPainter *painter)
{
    // save() restore()一对。保存 ，恢复 QPainter 的状态，类似栈的入栈出栈
    painter->save();
    QPainterPath path;
    painter->setPen(QPen(Qt::SolidLine));

    auto bigCircleRadius = smallCircleRadius + circleSpacing;
    //绘制圆环的两个圆
    painter->drawEllipse(QPointF(0, 0), bigCircleRadius, bigCircleRadius);
    painter->drawEllipse(QPointF(0, 0), smallCircleRadius, smallCircleRadius);

    //中心按钮圆
    QPainterPath centerCirclePath;
    centerCirclePath.addEllipse(QPointF(0, 0), centerCircleRadius * 1.382, centerCircleRadius * 1.382);
    arcPathList.append(centerCirclePath);

    painter->restore();
}

void CircularMenuPrivate::DrawPie(QPainter *painter)
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
    QRectF rectangle(-smallCircleRadius, -smallCircleRadius, smallCircleRadius * 2, smallCircleRadius * 2);

    // Startangle和Spanangle必须为16倍数，即全圈等于5760（16 * 360）。
    //在指定开始角度和偏移角度时，以3点钟为0度，正值表示逆时针方向，而负值表示顺时针方向。
    //    for (float angle = 22.5*16; angle<360*16;) {
    //        painter->drawPie(rectangle, angle, angle + 45*16);
    //        angle += 45*16;
    //        qDebug()<<"angle"<<angle/16;
    //    }
    //    painter->drawPie(rectangle, startAngle, spanAngle);

    float angle = 22.5;
    auto circleHeight = smallCircleRadius - centerCircleRadius * 1.382;
    for (int i = 0; i < 8; i++)
    {
        QPainterPath path;
        path.arcTo(rectangle, angle, 45);
        angle += 45;
        //        painter->setPen(QColor("#3d84a8"));
        QPainterPath subPath;
        // QRect.adjusted(int xp1, int yp1, int xp2, int yp2)
        // xp1为相对于原始矩形左上角x坐标的偏移值，yp1为相对于原始矩形左上角y坐标的偏移值，负值表示在矩形外，正值表示在矩形内；
        // xp2和yp2分别是相对于右下角x坐标和y坐标的偏移值，负值表示在矩形内，正值表示在矩形外
        subPath.addEllipse(rectangle.adjusted(circleHeight, circleHeight, -circleHeight, -circleHeight));

        // path为扇形 subPath为椭圆 减去可得圆弧
        path -= subPath;
        arcPathList.append(path);
        painter->drawPath(path);
    }

    painter->restore();
}

void CircularMenuPrivate::DrawImage(QPainter *painter)
{
    painter->save();
    auto scaleFactor = smallCircleRadius / 2 * iconScale;
    auto xPoint = smallCircleRadius / sqrt(2);
    auto point = QPoint(-xPoint, -xPoint);

    //    painter->drawPoint(QPoint(-smallRadius / sqrt(2), -smallRadius / sqrt(2)));
    //    painter->drawLine(QPoint(0,0),QPoint(x, y));

    //    //方案一：分别计算对应坐标点,计算矩形图片在扇形中等分弧的坐标
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

    //方案三：通过指定图片自身旋转后再进行绘制
    QPixmap pUpImg(":/resources/up-one.png");
    QMatrix matrix;
    matrix.translate(pUpImg.width() / 2.0, pUpImg.height() / 2.0);
    matrix.rotate(-45);
    matrix.translate(-pUpImg.width() / 2.0, -pUpImg.height() / 2.0);
    pUpImg = pUpImg.transformed(matrix, Qt::SmoothTransformation);
    for (int i = 0; i < 360;)
    {
        //旋转坐标轴
        painter->rotate(i);
        painter->drawPixmap(QRect(point, QSize(scaleFactor, scaleFactor)),
                            pUpImg.scaled(QSize(scaleFactor, scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        i += 45;
    }
    // 中心按钮图标
    QPixmap pCenterImg(":/0");
    painter->drawPixmap(QRect(QPoint(-scaleFactor / 2, -scaleFactor / 2), QSize(scaleFactor, scaleFactor)),
                        pCenterImg.scaled(QSize(scaleFactor, scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    painter->restore();
}

// TODO:add corresponding func()
void CircularMenu::ProcessButtonClicked(int BtnID)
{
    switch (BtnID)
    {
    case 0:
        qcout << QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 1:
        qcout << QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 2:
        qcout << QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 3:
        qcout << QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 4:
        qcout << QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 5:
        qcout << QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 6:
        qcout << QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 7:
        qcout << QString("BtnID %1 clicked").arg(BtnID);
        break;
    case 8:
        qcout << QString("BtnID %1 clicked").arg(BtnID);
        break;
    }
}

void CircularMenu::paintEvent(QPaintEvent *event)
{
    Q_D(CircularMenu);
    Q_UNUSED(event)
    qcout << "enter paintEvent";
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform);
    QPointF center(width() / 2.0, height() / 2.0);
    painter.translate(center);
    //    painter.rotate(22.5);
    //背景设为透明，可为其他颜色
    painter.setBrush(d->bgColor);
    d->DrawCircle(&painter);
    d->DrawPie(&painter);
    d->DrawImage(&painter);
    //    painter.translate(0,0);

    //鼠标按下后绘制按下效果
    if (d->mousePressed)
    {
        painter.save();
        // painter.setPen(Qt::gray);
        painter.setBrush(d->pressColor);
        painter.drawPath(d->arcPathList[d->areaIndex]);
        painter.restore();
    }
}

void CircularMenu::mousePressEvent(QMouseEvent *event)
{
    Q_D(CircularMenu);
    QPoint mousePressPoint = event->pos();

    //因进行了原点的偏移，故坐标点也需要偏移
    // x>>1 位运算，等效x/2
    QPoint translatePoint = mousePressPoint - QPoint(width() >> 1, height() >> 1);

    qcout << "pos" << mousePressPoint << "trans pos" << translatePoint;

    for (int i = 0; i < d->arcPathList.count(); i++)
    {
        if (d->arcPathList[i].contains(translatePoint))
        {
            qcout << "area i = " << i;
            d->mousePressed = true;
            d->areaIndex = i;
            //更新绘制，实现鼠标按下效果
            update();
            emit BtnClicked(i);
            break;
        }
    }
}

void CircularMenu::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(CircularMenu);
    Q_UNUSED(event)
    d->mousePressed = false;
    //更新绘制，实现鼠标松开效果
    update();
}

void CircularMenu::resizeEvent(QResizeEvent *event)
{
    Q_D(CircularMenu);
    Q_UNUSED(event)
    qcout << "enter resizeEvent";
    d->arcPathList.clear();
    auto width = size().width();
    auto height = size().height();

    auto diameter = width > height ? height : width;
    auto radius = diameter / 2;
    d->smallCircleRadius = 0.816 * radius;
    d->circleSpacing = 0.1 * radius;
    d->centerCircleRadius = 0.15 * radius;
}
