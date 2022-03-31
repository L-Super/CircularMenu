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
    // ���û������뾶;
    void setRadiusValue(int radius);
    void setArcLength(int arcLength);
    void drawRotatedText(QPainter *painter, float degrees, int x, int y, const QString &text);

    QPixmap getPixmap(const int ping);
    QColor getColor(const int ping);
    int getLineNum(const int ping);
    QPixmap getSignalPixmap(const QColor &color,const int lineNum);//��ȡ�ź�λͼ

	void setBeginDegree(int degree);

    //void enterEvent(QEvent *);
private:
     // ��ʼ����ť;
    void initButton();
    // ���ư�ť; 
    void paintEvent(QPaintEvent *);
    // ���Բ��;
    void addArc(int x, int y, int startAngle, int angleLength, QRgb color);
//    void addArc(qreal startAngle, qreal angleLength, QRgb color);

    // ����¼�;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    // ����뿪�¼�;
//    void leaveEvent(QEvent *event);
    int analysisAngle(int x,int y);

signals:
    // �����;
    void signalButtonClicked(int buttonId);
    // ����ɿ�;
    void signalButtonReleased(int buttonId);
private:
    // �������뾶;
    int m_radius, m_arcLength;

    // Բ��·��;
    QList<QPainterPath> m_arcPathList;
    QList<QPainterPath> m_textPathList;
    // Բ����ɫ;
    QList<QBrush> m_colorList;
    // ��ǰ��갴ť/���� ��ť������;
    int m_pressIndex, m_enterIndex;
    // ����¼���־λ;
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










