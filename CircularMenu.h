#pragma once
/**
  *
  * @file CircularMenu
  * @author Listening
  * @brief 自定义控件，绘制圆形菜单
  * @version 1.0.2
  * @date 2022-03-30
  *
  * @copyright Copyright (c) 2022
  */
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CircularMenu; }
QT_END_NAMESPACE

//TODO:按钮悬浮时的变化
class CircularMenu : public QWidget
{
    Q_OBJECT

public:
    CircularMenu(QWidget *parent = nullptr);
    ~CircularMenu();
    /**
     * @brief SetCirleRadius 设置圆的半径
     * @param radius
     */
    void SetCircleRadius(const float radius);
    /**
     * @brief SetCenterCircleRadius 设置中心按钮圆的半径
     * @param radius
     */
    void SetCenterCircleRadius(const float radius);
    /**
     * @brief SetCircleSpacing 设置圆与外圆环的间隔
     * @param spacing
     */
    void SetCircleSpacing(const float spacing);
    /**
     * @brief SetCircleRadius 设置圆的半径参数
     * @param centerRadius 中心圆按钮的半径
     * @param circleRadius 圆的半径
     * @param ringRadius 圆环的半径
     */
    void SetAllCircleRadius(float centerRadius,float circleRadius,float ringRadius);
    /**
     * @brief SetIconScale 设置图标的缩放比例，默认填满圆环
     * @param scale 范围 0 < sacle <= 1
     */
    void SetImageScale(const float scale = 1.0);
    /**
     * @brief ProcessButtonClicked 处理触发按钮按下事件
     * @param BtnID
     */
    void ProcessButtonClicked(int BtnID);
private:
    /**
     * @brief DrawCircle 画圆
     * @param painter
     */
    void DrawCircle(QPainter* painter);
    /**
     * @brief DrawPie 画弧形区域
     * @param painter
     */
    void DrawPie(QPainter* painter);
    /**
     * @brief DrawImage 将图标画上去
     * @param painter
     */
    void DrawImage(QPainter* painter);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void BtnClicked(int id);

private:
    Ui::CircularMenu *ui;
    float smallCircleRadius;//小圆半径
    float centerCircleRadius;//中心小圆半径
//    float bigCircleRadius;//大圆半径 等于小圆加间隔
    int circleSpacing;//大小圆之间的间隔
    float iconScale;//图标缩放比例
    bool mousePressed;//鼠标按下标志位
    int areaIndex;//区域索引
    QList<QPainterPath> arcPathList;//区域索引：0为center，1为right-up
    QVector<QPixmap> directionImg;
};
