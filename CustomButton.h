#include <QtWidgets/QWidget>

#include <QPoint>
#include "qmath.h"

enum QUADRANT_NUM {
    QUADRANT_UP,
    QUADRANT_LEFT,
    QUADRANT_DOWN,
    QUADRANT_RIGHT,
    QUADRANT_NO_DEFINE,
};

class CustomButton : public QWidget
{
    Q_OBJECT

public:
    CustomButton(QWidget* parent = NULL);
    // 设置弧长及半径;
    void setRadiusValue(int radius);
    void setArcLength(int arcLength);
    void drawRotatedText(QPainter *painter, float degrees, int x, int y, const QString &text);

    QPixmap getPixmap(const int ping);
    QColor getColor(const int ping);
    int getLineNum(const int ping);
    QPixmap getSignalPixmap(const QColor &color,const int lineNum);//获取信号位图

	void setBeginDegree(int degree);

    //void enterEvent(QEvent *);
private:
     // 初始化按钮;
    void initButton();
    // 绘制按钮; 
    void paintEvent(QPaintEvent *);
    // 添加圆弧;
    void addArc(int x, int y, int startAngle, int angleLength, QRgb color);
//    void addArc(qreal startAngle, qreal angleLength, QRgb color);

    // 鼠标事件;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    // 鼠标离开事件;
//    void leaveEvent(QEvent *event);
    int analysisAngle(int x,int y);

signals:
    // 鼠标点击;
    void signalButtonClicked(int buttonId);
    // 鼠标松开;
    void signalButtonReleased(int buttonId);
private:
    // 弧长及半径;
    int m_radius, m_arcLength;

    // 圆弧路径;
    QList<QPainterPath> m_arcPathList;
    QList<QPainterPath> m_textPathList;
    // 圆弧颜色;
    QList<QBrush> m_colorList;
    // 当前鼠标按钮/进入 按钮的索引;
    int m_pressIndex, m_enterIndex;
    // 鼠标事件标志位;
    bool m_isMousePressed;
    bool m_isMouseEntered;

    QUADRANT_NUM mCurWorkRegion;

    QPoint mCenterRound;
    QPixmap mDegreePixmap;

    QString mStrUp;
    QString mStrLeft;
    QString mStrDown;
    QString mStrRight;

	bool m_bTextModeEn;

};










