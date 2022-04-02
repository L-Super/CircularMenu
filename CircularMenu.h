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

class CircularMenuPrivate;
class CircularMenu : public QWidget
{
    Q_OBJECT

public:
    CircularMenu(QWidget *parent = nullptr);
    virtual ~CircularMenu();
    /**
     * @brief SetCirleRadius 设置圆的半径
     * @param radius 半径
     */
    void SetCircleRadius(const float radius);
    /**
     * @brief SetCenterCircleRadius 设置中心按钮圆的半径
     * @param radius 半径
     */
    void SetCenterCircleRadius(const float radius);
    /**
     * @brief SetCircleSpacing 设置圆与外圆环的间隔
     * @param spacing 间隔距离
     */
    void SetCircleSpacing(const float spacing);
    /**
     * @brief SetCircleRadius 设置圆的半径参数
     * @param centerRadius 中心圆按钮的半径
     * @param circleRadius 圆的半径
     * @param ringRadius 圆环的半径
     */
    void SetAllCircleRadius(const float centerRadius, const float circleRadius, const float ringRadius);
    /**
     * @brief SetIconScale 设置图标的缩放比例，默认填满圆环
     * @param scale 范围 0 < sacle <= 1
     */
    void SetImageScale(const float scale = 1.0);
    /**
     * @brief ProcessButtonClicked 处理触发按钮按下事件
     * @param BtnID 对应按钮序号
     */
    void ProcessButtonClicked(int BtnID);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

signals:
    void BtnClicked(int id);

private:
    QScopedPointer<CircularMenuPrivate> d_ptr;
    Q_DECLARE_PRIVATE(CircularMenu)

//    QVector<QPixmap> directionImg;
};
