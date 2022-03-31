#include "CustomButton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPushButton>
#include <QToolTip>
#include <qmath.h>

CustomButton::CustomButton(QWidget* parent)
    : QWidget(parent)
    , m_pressIndex(0)
    , m_enterIndex(0)
    , m_isMouseEntered(false)
    , m_isMousePressed(false)
    , m_radius(90)
    , m_arcLength(65)
    , mCenterRound(QPoint(0,0))
{
	m_bTextModeEn = false;
	//MouseTracking
	this->setMouseTracking(true);

    //resize(200, 200);

    initButton();

}

//void CustomButton::enterEvent(QEvent *)
//{
//    QToolTip::showText(QPoint(width()/2,height()/2),"dfgsgte",this,QRect());
//}

void CustomButton::setRadiusValue(int radius)
{
    m_radius = radius;
}

void CustomButton::setArcLength(int arcLength)
{
    m_arcLength = arcLength;
}

void CustomButton::drawRotatedText(QPainter *painter, float degrees, int x, int y, const QString &text)
{
    painter->save(); //保存原来坐标系统
    painter->translate(x, y); //平移坐标原点到 x， y
    painter->rotate(degrees); //坐标旋转degrees 度
    painter->drawText(0, 0, text); //在原点绘制文本
    painter->restore(); //回复原来的坐标系统
}
void CustomButton::initButton()
{

    QLinearGradient radialGradient;
    radialGradient.setColorAt(0.0,QColor(62,62,62));
    radialGradient.setColorAt(1.0,QColor(40,40,40));


    addArc(1,0,45, 90, qRgb(38, 38, 38));
    addArc(0,1,135, 90, qRgb(38, 38, 38));
    addArc(-1,0,225, 90, qRgb(38, 38, 38));
    addArc(0,-1,315, 90, qRgb(38, 38, 38));

    // 绘制中心圆;
    QPainterPath centerRoundPath;
    centerRoundPath.addEllipse(QPoint(0, 0), m_radius - m_arcLength+2, m_radius - m_arcLength+2);
    m_arcPathList.append(centerRoundPath);
    m_colorList.append(QColor(17, 17, 17));

    //    QPainterPath centerRoundPath1;
    //    centerRoundPath1.addEllipse(mCenterRound, m_radius - m_arcLength-2, m_radius - m_arcLength-2);
    //    m_arcPathList.append(centerRoundPath1);
    //    m_colorList.append(QColor(38, 40, 46));


//    // 添加文字;
//    QFont font;
//    font.setFamily("Microsoft YaHei");
//    font.setPointSize(14);

//    for (int i = 0; i < m_arcPathList.count(); i++)
//    {
//        QPainterPath painterPath;
//        m_textPathList.append(painterPath);
//    }
    //    m_textPathList[0].addText(QPoint(-30, -55), font, QStringLiteral("小臂上仰"));
    //    m_textPathList[1].addText(QPoint(-70, 10), font, QStringLiteral("手动收线"));
    //    m_textPathList[2].addText(QPoint(-10, 70), font, QStringLiteral("小臂下附"));
    //    m_textPathList[3].addText(QPoint(50, 10), font, QStringLiteral("手动放线"));

//	mStrUp = QStringLiteral("小臂上仰");
//	mStrLeft = QStringLiteral("手动收线");
//	mStrDown = QStringLiteral("小臂下附");
//	mStrRight = QStringLiteral("手动放线");

	/*mStrUp = "Fuck EveryOne";
	mStrLeft = "Fuck You";
	mStrDown = "Fuck Him";
	mStrRight = "Fuck Her";*/

}

void CustomButton::paintEvent(QPaintEvent *)
{

    //m_radius = height()/2;
    //m_arcLength = height()/4;

    QPainter painter(this);
	painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.translate(width()>>1, height()>>1);

	//背景色，分割线颜色
	QColor colorBKG(41, 44, 50);
	QColor colorSPL(32, 149, 216);

    painter.setBrush(colorBKG);
//    painter.drawEllipse(QPoint(0,0), m_radius+8, m_radius+8);

    //背景渐变
//    QLinearGradient linearGradient(0, -m_radius, 0, m_radius);
//    linearGradient.setColorAt(0.0, QColor(60,60,60));
//    linearGradient.setColorAt(0.9, QColor(22, 22, 22));
//    painter.setBrush(QBrush(linearGradient));
//    painter.drawEllipse(QPoint(0, 0), m_radius, m_radius);

    //画扇形分割线
//    int count = 4;
//    for(int i = 0; i < count;i++)
//    {
//        painter.save();
//        painter.rotate(45+90 * i);
//        painter.setPen(QPen(colorBKG, 3, Qt::SolidLine));
//        painter.drawLine(0, 0, 0,m_radius);
//        painter.setPen(QPen(colorSPL, 3, Qt::SolidLine));
//        painter.drawLine(0, 0, 0, m_radius-5);
//        painter.restore();
//    }

    if(m_isMousePressed)
    {
        painter.drawPath(m_arcPathList[1]);

    }

//    painter.setBrush(Qt::red);

//    for (int i = 0; i < m_arcPathList.count(); i++)
//    {
		
//        if (i == m_pressIndex && m_isMousePressed)
//        {
////            painter.setBrush(QColor(255, 255, 255, 120));
//            painter.drawPath(m_arcPathList[i]);

//        }
//        else if (i == m_pressIndex && m_isMouseEntered)
//        {
//            //painter.setBrush(QColor(255, 255, 255, 60));
//            painter.drawPath(m_arcPathList[i]);
//        }
//        painter.setBrush(Qt::white);
//        painter.drawPath(m_textPathList[i]);
//    }

    //painter.setBrush(QColor(38, 40, 46));
    //painter.drawEllipse(mCenterRound, m_radius - m_arcLength-2, m_radius - m_arcLength-2);

//    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
//    QMatrix leftmatrix;
//    if(mCurWorkRegion == QUADRANT_UP){
//        painter.drawPixmap(-30,-50,60,30,mDegreePixmap);
//    }else if(mCurWorkRegion == QUADRANT_LEFT){
//        leftmatrix.rotate(270);
//        mDegreePixmap=mDegreePixmap.transformed(leftmatrix,Qt::SmoothTransformation);
//        painter.drawPixmap(-60,-30,30,60,mDegreePixmap);
//    }else if(mCurWorkRegion == QUADRANT_DOWN){
//        leftmatrix.rotate(180);
//        mDegreePixmap=mDegreePixmap.transformed(leftmatrix,Qt::SmoothTransformation);
//        painter.drawPixmap(-30,25,60,30,mDegreePixmap);

//    }else if(mCurWorkRegion == QUADRANT_RIGHT){
//        leftmatrix.rotate(90);
//        mDegreePixmap=mDegreePixmap.transformed(leftmatrix,Qt::SmoothTransformation);
//        painter.drawPixmap(30,-30,30,60,mDegreePixmap);
//    }

//    QFont font;
//    font.setFamily("Microsoft YaHei");
//    font.setPointSize(12);
//    painter.setFont(font);
//    painter.setPen(Qt::white);

//	//m_bTextModeEn = true;
//	QFontMetrics fm(font);
//	int  rText = 70;

//	int iTotalWidth;
//	int nWidth;
//	//行高空隙去除，-3或-4
//	int nHeight = fm.height() - 4;

//	//上方文字最简单
//	iTotalWidth = fm.width(mStrUp);
//	painter.save();
//	painter.rotate(-90 * iTotalWidth / (rText * M_PI));
//    for(int i = 0;i < mStrUp.size();i++)
//    {
//		//旋转一半，写文字，剩下一半再旋转
//		nWidth = fm.width(mStrUp.at(i));
//		painter.rotate(90 * nWidth / (rText * M_PI));
//		painter.drawText(-nWidth / 2, -1 * rText, mStrUp.at(i));
//		painter.rotate(90 * nWidth / (rText * M_PI));
//    }
//	painter.restore();

//	//右侧文字，中文竖着，英文朝圆外
	
//	painter.save();
//	if (m_bTextModeEn)
//	{
//		iTotalWidth = fm.width(mStrRight);
//		painter.rotate(90 - 90 * iTotalWidth / (rText * M_PI));
//		for (int i = 0; i < mStrRight.size(); i++)
//		{
//			nWidth = fm.width(mStrRight.at(i));
//			painter.rotate(90 * nWidth / (rText * M_PI));
//			painter.drawText(-nWidth / 2, -1 * rText, mStrRight.at(i));
//			painter.rotate(90 * nWidth / (rText * M_PI));
//		}
//	}
//	else
//	{
//		iTotalWidth = nHeight*mStrRight.size();
//		painter.rotate(-90 * iTotalWidth / (rText * M_PI));
//		for (int i = 0; i < mStrRight.size(); i++)
//		{
			
//			painter.rotate(90 * nHeight / (rText * M_PI));
//			//文字左右微调 -5
//			painter.drawText(rText-5, nHeight / 2, mStrRight.at(i));
//			painter.rotate(90 * nHeight / (rText * M_PI));
//		}
//	}
//	painter.restore();

//	//下方文字也简单，大家都一致
//	painter.save();
//	iTotalWidth = fm.width(mStrDown);
//	painter.rotate(90 * iTotalWidth / (rText * M_PI));
//	for (int i = 0; i < mStrDown.size(); i++)
//	{
//		nWidth = fm.width(mStrDown.at(i));
//		painter.rotate(-90 * nWidth / (rText * M_PI));
//		//文字上下微调 -8
//		painter.drawText(-nWidth / 2, rText + nHeight-8, mStrDown.at(i));
//		painter.rotate(-90 * nWidth / (rText * M_PI));
//	}
//	painter.restore();

//	//左侧文字，中文朝上，英文朝内
//	painter.save();
//	if (m_bTextModeEn)
//	{
//		iTotalWidth = fm.width(mStrLeft);
//		painter.rotate(90 + 90 * iTotalWidth / (rText * M_PI));
//		for (int i = 0; i < mStrLeft.size(); i++)
//		{
//			nWidth = fm.width(mStrLeft.at(i));
//			painter.rotate(-90 * nWidth / (rText * M_PI));
//			painter.drawText(-nWidth / 2, rText+nHeight-8, mStrLeft.at(i));
//			painter.rotate(-90 * nWidth / (rText * M_PI));
//		}
//	}
//	else
//	{
//		iTotalWidth = nHeight*mStrLeft.size();
//		painter.rotate(90 * iTotalWidth / (rText * M_PI));
//		for (int i = 0; i < mStrLeft.size(); i++)
//		{
//			painter.rotate(-90 * nHeight / (rText * M_PI));
//			//文字左右微调 -10
//			painter.drawText(-rText-10, nHeight / 2, mStrLeft.at(i));
//			painter.rotate(-90 * nHeight / (rText * M_PI));
//		}
//	}
//	painter.restore();

}

void CustomButton::addArc(int x, int y, int startAngle, int angleLength, QRgb color)
{
    //绘制矩形 m_radius = 90
    //    QRectF(qreal left, qreal top, qreal width, qreal height);
    QRectF rect(-m_radius+x, -m_radius+y, m_radius * 2, m_radius * 2);

    // 设置扇形路径;
    QPainterPath path;
    path.arcTo(rect, startAngle, angleLength);
    QPainterPath subPath;
    // 设置小扇形路径;
    subPath.addEllipse(rect.adjusted(m_arcLength, m_arcLength, -m_arcLength, -m_arcLength));
    // 大扇形减去小扇形得到圆弧;
    path -= subPath;

    m_arcPathList.append(path);

    // 设置圆弧颜色
//    QRadialGradient radialGradient;
//    radialGradient.setCenter(0, 0);
//    radialGradient.setRadius(m_radius);
//    radialGradient.setColorAt(0, color);
//    radialGradient.setColorAt(1.0, color);
//    m_colorList.append(radialGradient);
}

void CustomButton::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePressPoint = event->pos();

    //x>>1 位运算，等效x/2
    QPoint translatePoint = mousePressPoint - QPoint(width() >> 1, height() >> 1);
    qDebug()<<"pos"<<mousePressPoint<<"trans pos"<<translatePoint;
    for (int i = 0; i < m_arcPathList.count(); i++)
    {
        if (m_arcPathList[i].contains(translatePoint) /*|| m_textPathList[i].contains(translatePoint)*/)
        {
            m_pressIndex = i;
            m_isMousePressed = true;
            qDebug()<<"clicked i = "<<i;
            update();
            emit signalButtonClicked(i);
            break;
        }
    }
}

void CustomButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (m_isMousePressed)
    {
        m_isMousePressed = false;
//        mCenterRound = QPoint(0,0);
//        mDegreePixmap = QPixmap(0,0);
//        //qDebug()<<"_________m_pressIndex = "<<m_pressIndex;
//        emit signalButtonReleased(m_pressIndex);
        update();
    }
}

void CustomButton::mouseMoveEvent(QMouseEvent *event)
{
//    if(m_isMousePressed)
//    {
//        mCenterRound = event->pos() - QPoint(width() >> 1, height() >> 1);

//        int x = mCenterRound.x();
//        int y = -mCenterRound.y();
//        int angle = analysisAngle(x,y);

//        if(angle > 45 && angle <= 135 ){
//            mCenterRound.setX(0);
//            mCurWorkRegion = QUADRANT_UP;
//        }else if(angle > 135 && angle <= 225){
//            mCenterRound.setY(0);
//            mCurWorkRegion = QUADRANT_LEFT;
//        }else if(angle > 225 && angle <= 315){
//            mCenterRound.setX(0);
//            mCurWorkRegion = QUADRANT_DOWN;
//        }else{
//            mCenterRound.setY(0);
//            mCurWorkRegion = QUADRANT_RIGHT;
//        }

//        int degree = qSqrt(qPow(x,2)+qPow(y,2));
//        qDebug()<<"degree"<<degree;

//        mDegreePixmap = getPixmap(degree);

//        update();
//    }
}
/*************************************************
Function:       analysisAngle
Description:    获取当前鼠标的度数
Input:          x,y
Return:         int,当前鼠标的度数
*************************************************/
//int CustomButton::analysisAngle(int x,int y)
//{
//    double angle;

//    if(x == 0 && y > 0)
//    {
//        return 90;
//    }
//    else if(x == 0 && y < 0)
//    {
//        return 270;
//    }
//    else if(x >= 0 && y == 0)
//    {
//        return 0;
//    }
//    else if(x < 0 && y == 0)
//    {
//        return 180;
//    }
//    else
//    {
//        angle = atan2(qAbs(y),qAbs(x))/(2*acos(-1))*360;
//        if(x < 0 && y > 0)
//        {
//            angle = 180 - angle;
//        }
//        if(x < 0 && y < 0)
//        {
//            angle += 180;
//        }
//        if(x > 0 && y< 0)
//        {
//            angle = 360 - angle;
//        }
//        return angle;
//    }
//}




//QPixmap CustomButton::getPixmap(const int ping)
//{
//    return getSignalPixmap(QColor(0x5,0x00c7,0xc7),getLineNum(ping));
//}

//QColor CustomButton::getColor(const int ping )
//{
//    if(ping<=10)
//        return QColor(0xea,0x00,0x00);
//    else if(ping<=20)
//        return QColor(0xff,0x00,0x80);
//    else if(ping<=30)
//        return QColor(0xe8,0x00,0xe8);
//    else if(ping<=40)
//        return QColor(0xea,0xc1,0x00);
//    else if(ping<=50)
//        return QColor(0xe1,0xe1,0x00);
//    else if(ping<=60)
//        return QColor(0x9a,0xff,0x02);
//    else if(ping<=70)

//        return QColor(0x00,0xff,0xff);
//    else if(ping<=80)

//        return QColor(0x28,0x94,0xff);
//    else
//        return QColor(0x6a,0x6a,0xff);
//}

//int CustomButton::getLineNum(const int ping)
//{
//    if(ping<=20)
//        return 1;
//    else if(ping<=40)
//        return 2;
//    else if(ping<=60)
//        return 3;
//    else if(ping<=80)
//        return 4;
//    else
//        return 5;
//}
QPixmap CustomButton::getSignalPixmap(const QColor &color,const int linenum)//获取信号位图
{
    QPixmap pixmap(60,30);
//    pixmap.fill(QColor(255,255,255,0));
//    QPainter painter(&pixmap);
//    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
//    painter.setPen(QPen(color,2,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));

//	//30 - i* 5 ，是为了顶部不要被削掉
//    for(int i=1,xpos=0;i<=linenum;++i,++xpos)
//    {
//        painter.drawArc(30 - i * 6, 30 - i * 5, i * 12, i * 10, 53 * 16, 37 * 2 * 16);
//    }
    return pixmap;
}
