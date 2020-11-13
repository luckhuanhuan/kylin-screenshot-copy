/*
 *
 * Copyright: 2010-2011 Razor team
 *            2020 KylinSoft Co., Ltd.
 * Authors:
 *   huanhuan zhang <zhanghuanhuan@cs2c.com.cn.com>
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 */
#include "font_options2.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#define SHADOW_WIDTH  5     //小三角的阴影宽度
#define TRIANGLE_WIDTH  20    //小三角的宽度
#define TRIANGLE_HEIGHT 10    //小三角的高度
#define BORDER_RADIUS 10       //窗口边角弧度
Font_Options2::Font_Options2(QWidget *parent)
    : QWidget(parent)
    , m_startx(5)
    , m_triangleWidth(TRIANGLE_WIDTH)
    , m_triangleHeight(TRIANGLE_HEIGHT)
    , radius(6)
    ,Delete(false)
    ,Underline(false)
    ,bold(false)
    ,italic(false)
{
    context.style_settings = new QGSettings("org.ukui.style");
    context.style_name = context.style_settings->get("style-name").toString();
    setCursor(Qt::ArrowCursor);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //设置阴影边框
    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0,0);
    shadowEffect->setColor(Qt::gray);
    shadowEffect->setBlurRadius(BORDER_RADIUS);
    this->setGraphicsEffect(shadowEffect);
    this->setMouseTracking(true);
    Start_x  = 161;
    Start_y = 20;
     for (int i=0;i<4;i++)
     {
          m_colorAreaList.append(QRect(Start_x,Start_y,14,14));
          Start_x += 24;
     }
     Start_x  = 161;
     Start_y = 41;
     for (int i=4;i<8;i++)
     {
          m_colorAreaList.append(QRect(Start_x,Start_y,14,14));
          Start_x += 24;
     }
     context.style_settings = new QGSettings("org.ukui.style");
     context.style_name = context.style_settings->get("style-name").toString();
}
void Font_Options2::setStartPos(double startX)
{
    m_startx = startX;
}
void Font_Options2::setTriangleInfo(double width, double height)
{
    m_triangleWidth = width;
    m_triangleHeight = height;
}
void Font_Options2::setCenterWidget(QWidget *widget)
{
    Font_type = new  QFontComboBox(this);
    Font_type->setCurrentFont(QFont("华文黑体"));
    Font_type->setGeometry(12,16,90,18);
    Font_type->setStyleSheet("font:10px;");
    Font_size = new  QSpinBox(this);
    Font_size->setGeometry(107,16,36,18);
    Font_size->setStyleSheet("font:10px;");
    Font_size->setValue(2);
    delete_btn = new QPushButton(this);
    delete_btn->setGeometry(12,41,32,18);
    Underline_btn= new QPushButton(this);
    Underline_btn->setGeometry(46,41,33,18);
    bold_btn = new QPushButton(this);
    bold_btn->setGeometry(79,41,32,18);
    Italic_btn = new QPushButton(this);
    Italic_btn->setGeometry(111,41,32,18);
    if((context.style_name.compare("ukui-white")==0) || (context.style_name.compare("ukui-default")==0) || (context.style_name.compare("ukui-light")==0))
    {
        delete_btn->setStyleSheet("QPushButton{border-image:url"
                            "(:/img/material/white/delete.png)}");
        Underline_btn->setStyleSheet("QPushButton{border-image:url"
                                 "(:/img/material/dark-theme/underline.png)}");

        bold_btn->setStyleSheet("QPushButton{border-image:url"
                            "(:/img/material/white/bold.png)}");
        Italic_btn->setStyleSheet("QPushButton{border-image:url"
                              "(:/img/material/dark-theme/italic.png)}");
    }
    else if((context.style_name.compare("ukui-dark")==0) || (context.style_name.compare("ukui-black")==0)){
        delete_btn->setStyleSheet("QPushButton{border-image:url"
                            "(:/img/material/white/delete.png)}");
        Underline_btn->setStyleSheet("QPushButton{border-image:url"
                                 "(:/img/material/dark-theme/underline.png)}");

        bold_btn->setStyleSheet("QPushButton{border-image:url"
                            "(:/img/material/white/bold.png)}");
        Italic_btn->setStyleSheet("QPushButton{border-image:url"
                              "(:/img/material/dark-theme/italic.png)}");
    }
    delete_btn->setToolTip(tr("StrikeOut"));
    Underline_btn->setToolTip(tr("Underline"));
    bold_btn->setToolTip(tr("Bold"));
    Italic_btn->setToolTip(tr("Italic"));
    connect(Font_size,SIGNAL(valueChanged(int)),
            this,SLOT(font_size_change(int)));
    connect(Font_type,SIGNAL(currentFontChanged(QFont)),
            this,SLOT(font_type_change(QFont)));
    connect(delete_btn,&QPushButton::clicked,
            this,&Font_Options2::font_delete_selete);
    connect(Underline_btn,&QPushButton::clicked,
            this,&Font_Options2::font_underline_selete);
    connect(Italic_btn,&QPushButton::clicked,
            this,&Font_Options2::font_italic_selete);
    connect(bold_btn,&QPushButton::clicked,
            this,&Font_Options2::font_bold_selete);

}
void Font_Options2::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    //
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startx,height()- m_triangleHeight);
    trianglePolygon << QPoint(m_startx+m_triangleWidth/2,height());
    trianglePolygon << QPoint(m_startx + m_triangleWidth,height()-m_triangleHeight);
    QPainterPath drawPath;
    /*drawPath.addRoundRect(QRect(SHADOW_WIDTH , m_triangleHeight + SHADOW_WIDTH ,
                                width()-SHADOW_WIDTH *2 ,height() -SHADOW_WIDTH *2 -m_triangleHeight),
                         BORDER_RADIUS,BORDER_RADIUS);*/
    drawPath.addRoundRect(QRect(SHADOW_WIDTH,SHADOW_WIDTH,width()-SHADOW_WIDTH *2,height()- m_triangleHeight - SHADOW_WIDTH),
                                           BORDER_RADIUS,BORDER_RADIUS);
    drawPath.addPolygon(trianglePolygon);
    if((context.style_name.compare("ukui-white")==0) || (context.style_name.compare("ukui-default")==0) || (context.style_name.compare("ukui-light")==0)){
        painter.setBrush(QColor(225,225,225,180));
        painter.drawPath(drawPath);
    }
    else if((context.style_name.compare("ukui-dark")==0) || (context.style_name.compare("ukui-black")==0)){
        painter.setBrush(QColor(25,25,25,180));
        painter.drawPath(drawPath);
    }
    painter.setBrush(QColor(25,25,25));
    painter.drawRect(150,30,1,14);
    for (int i =0;i<8;i++)
    {
        QRect rect = m_colorAreaList.at(i);
        QColor color1 =  m_colorList.at(i);
        if (color == color1){
             Rect_h= rect.height()+4;
             Rect_w = rect.width()+4;
             painter.setBrush(QColor(255,255,255));
             painter.drawRect(QRect(rect.x()-2,rect.y()-2,Rect_h,Rect_w));
        }
        painter.setBrush(color1);
        painter.drawRect(m_colorAreaList.at(i));
    }
    if (bold){
        bold_btn->setStyleSheet("QPushButton{border-image:url"
                               "(:/img/material/black/bold_active.png)}");
    }
    else {
        if((context.style_name.compare("ukui-white")==0) || (context.style_name.compare("ukui-default")==0) || (context.style_name.compare("ukui-light")==0))
            bold_btn->setStyleSheet("QPushButton{border-image:url"
                                  "(:/img/material/white/bold.png)}");
        else if((context.style_name.compare("ukui-dark")==0) || (context.style_name.compare("ukui-black")==0)){
            bold_btn->setStyleSheet("QPushButton{border-image:url"
                                  "(:/img/material/dark-theme/bold.png)}");
        }
    }
    if (Delete)
    {
        delete_btn->setStyleSheet("QPushButton{border-image:url"
                               "(:/img/material/black/delete_active.png)}");
    }
    else {
        if((context.style_name.compare("ukui-white")==0) || (context.style_name.compare("ukui-default")==0) || (context.style_name.compare("ukui-light")==0))
            delete_btn->setStyleSheet("QPushButton{border-image:url"
                                  "(:/img/material/white/delete.png)}");
        else if((context.style_name.compare("ukui-dark")==0) || (context.style_name.compare("ukui-black")==0)){
            delete_btn->setStyleSheet("QPushButton{border-image:url"
                                  "(:/img/material/dark-theme/delete.png)}");
        }
    }
    if (italic)
        Italic_btn->setStyleSheet("QPushButton{border-image:url"
                                  "(:/img/material/black/italic_active.png)}");
    else {
        if((context.style_name.compare("ukui-white")==0) || (context.style_name.compare("ukui-default")==0) || (context.style_name.compare("ukui-light")==0))
            Italic_btn->setStyleSheet("QPushButton{border-image:url"
                                  "(:/img/material/white/italic.png)}");
        else if((context.style_name.compare("ukui-dark")==0) || (context.style_name.compare("ukui-black")==0)){
            Italic_btn->setStyleSheet("QPushButton{border-image:url"
                                  "(:/img/material/dark-theme/italic.png)}");
        }
    }
    if (Underline)
    {
         Underline_btn->setStyleSheet("QPushButton{border-image:url"
                                  "(:/img/material/black/underline_active.png)}");
     }
    else {
        if((context.style_name.compare("ukui-white")==0) || (context.style_name.compare("ukui-default")==0)|| (context.style_name.compare("ukui-light")==0))
            Underline_btn->setStyleSheet("QPushButton{border-image:url"
                                 "(:/img/material/white/underline.png)}");
        else if((context.style_name.compare("ukui-dark")==0) || (context.style_name.compare("ukui-black")==0)){
            Underline_btn->setStyleSheet("QPushButton{border-image:url"
                                 "(:/img/material/dark-theme/underline.png)}");
        }
    }
}
void Font_Options2::mousePressEvent(QMouseEvent *e)
{
    for (int i = 0; i < 8; i++) {
        if (m_colorAreaList.at(i).contains(e->pos())) {
            color = m_colorList.at(i);
            emit colorSelected(color);
            update();
            break;
         }
    }
}
void  Font_Options2::font_size_change(int i)
{
    qDebug()<<"text font thickness changed";
    emit font_size_Selete(i);
}
void  Font_Options2::font_type_change(QFont font)
{
    qDebug()<<"text font family changed" <<font ;
    emit font_type_Selete(font);
}
void Font_Options2::font_bold_selete()
{
    bold = !bold;
    if (bold)
        bold_btn->setStyleSheet("QPushButton{border-image:url"
                               "(:/img/material/black/bold_active.png)}");
    else {
        if((context.style_name.compare("ukui-white")==0) || (context.style_name.compare("ukui-default")==0) || (context.style_name.compare("ukui-light")==0))
            bold_btn->setStyleSheet("QPushButton{border-image:url"
                               "(:/img/material/white/bold.png)}");
        else if((context.style_name.compare("ukui-dark")==0) || (context.style_name.compare("ukui-black")==0)){
            bold_btn->setStyleSheet("QPushButton{border-image:url"
                               "(:/img/material/dark-theme/bold.png)}");
        }
    }
    emit font_bold_change(bold);
}
void Font_Options2::font_delete_selete()
{
    Delete = !Delete;
    if (Delete)
         delete_btn->setStyleSheet("QPushButton{border-image:url"
                               "(:/img/material/black/delete_active.png)}");
    else {
        if((context.style_name.compare("ukui-white")==0) || (context.style_name.compare("ukui-default")==0)|| (context.style_name.compare("ukui-light")==0))
            delete_btn->setStyleSheet("QPushButton{border-image:url"
                              "(:/img/material/white/delete.png)}");
        else if((context.style_name.compare("ukui-dark")==0) || (context.style_name.compare("ukui-black")==0)){
            delete_btn->setStyleSheet("QPushButton{border-image:url"
                              "(:/img/material/dark-theme/delete.png)}");
        }
    }
    emit font_delete_change(Delete);
}
void Font_Options2::font_underline_selete()
{
    Underline = !Underline;
    if (Underline)
         Underline_btn->setStyleSheet("QPushButton{border-image:url"
                              "(:/img/material/black/underline_active.png)}");
    else {
        if((context.style_name.compare("ukui-white")==0) || (context.style_name.compare("ukui-default")==0)|| (context.style_name.compare("ukui-light")==0))
            Underline_btn->setStyleSheet("QPushButton{border-image:url"
                              "(:/img/material/white/underline.png)}");
        else if((context.style_name.compare("ukui-dark")==0) || (context.style_name.compare("ukui-black")==0)){
            Underline_btn->setStyleSheet("QPushButton{border-image:url"
                              "(:/img/material/dark-theme/underline.png)}");
        }
    }
    emit font_underline_change(Underline);
}
void Font_Options2::font_italic_selete()
{italic = !italic;
    if (italic)
         Italic_btn->setStyleSheet("QPushButton{border-image:url"
                              "(:/img/material/black/italic_active.png)}");
    else {
        if((context.style_name.compare("ukui-white")==0) || (context.style_name.compare("ukui-default")==0)|| (context.style_name.compare("ukui-light")==0))
            Italic_btn->setStyleSheet("QPushButton{border-image:url"
                              "(:/img/material/white/italic.png)}");
        else if((context.style_name.compare("ukui-dark")==0) || (context.style_name.compare("ukui-black")==0)){
            Italic_btn->setStyleSheet("QPushButton{border-image:url"
                              "(:/img/material/dark-theme/italic.png)}");
        }
    }
    emit font_italic_change(italic);
}
