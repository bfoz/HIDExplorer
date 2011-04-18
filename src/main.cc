/*  HID Explorer
    A cross-platform interface for discovering and inspecting HID devices

    Copyright 2010 Brandon Fosdick <bfoz@bfoz.net> (BSD License)
*/

#include <QApplication>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTabWidget>

#include <hid.h>

#include "delegate.h"
#include "ElementsWidget.h"
#include "HIDDetailWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Delegate* delegate = new Delegate;

    delegate->devices = HID::find();

    delegate->listWidget = new QListWidget;
    HID::device_list::iterator i = delegate->devices.begin();
    for(; i != delegate->devices.end(); ++i)
    {
	QListWidgetItem* newItem = new QListWidgetItem((*i)->product().c_str());
	delegate->listWidget->addItem(newItem);
    }
    QObject::connect(delegate->listWidget, SIGNAL(clicked(const QModelIndex&)), delegate, SLOT(clicked(const QModelIndex&)));

    delegate->detailWidget = new HID::DetailWidget;
    delegate->elementsWidget = new HID::ElementsWidget;

    QTabWidget* tabs = new QTabWidget;
    tabs->addTab(delegate->detailWidget, "Info");
    tabs->addTab(delegate->elementsWidget, "Elements");

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(delegate->listWidget);
    hbox->addWidget(tabs);

    QWidget* widget = new QWidget;
    widget->setLayout(hbox);
    widget->show();

    return app.exec();
}
