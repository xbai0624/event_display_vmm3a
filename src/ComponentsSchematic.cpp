#include "ComponentsSchematic.h"

#include <QVBoxLayout>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QBrush>

#include <iostream>

ComponentsSchematic::ComponentsSchematic(QWidget *parent) : QWidget(parent)
{
    Init();
}

ComponentsSchematic::~ComponentsSchematic()
{
}

void ComponentsSchematic::Init()
{
    graphics_view = new QGraphicsView(this);
    graphics_scene = new QGraphicsScene(this);

    graphics_view->setScene(graphics_scene);

    QGraphicsRectItem *item1 = new QGraphicsRectItem(0, 0, 20, 20);
    item_list.push_back(item1);
    graphics_scene -> addItem(item1);

    // add a log
    //QPixmap logo("./resources/jlab2.jpg");
    //logo = logo.scaled(37.5*2, 172.5*2);
    QPixmap logo("./resources/logo.jpeg");
    logo = logo.scaled(37.5*2, 37.5*2);
    graphics_scene -> addPixmap(logo);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(graphics_view);
}

void ComponentsSchematic::ItemSelected()
{
    //std::cout<<"item selected ..."<<std::endl;
    dynamic_cast<QGraphicsRectItem*>(item_list[0])->setPen(QPen(Qt::red));
    auto rect = item_list[0]->boundingRect();
    graphics_scene->update(rect);
}

void ComponentsSchematic::ItemDeSelected()
{
    //std::cout<<"item deselected..."<<std::endl;
    dynamic_cast<QGraphicsRectItem*>(item_list[0])->setPen(QPen(Qt::black));
    auto rect = item_list[0]->boundingRect();
    graphics_scene->update(rect);
}

void ComponentsSchematic::paintEvent(QPaintEvent* e)
{
}
