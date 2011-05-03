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

void matched(HID::enumerator_type* enumerator, HID::device_type* device, void* context)
{
    Delegate *const delegate = (Delegate*)context;
    QListWidgetItem* newItem = new QListWidgetItem(device->product().c_str());
    delegate->listWidget->addItem(newItem);
}

void removed(HID::enumerator_type* enumerator, HID::device_type* device, void* context)
{
    Delegate *const delegate = (Delegate*)context;
    QList<QListWidgetItem*> items = delegate->listWidget->findItems(device->product().c_str(), Qt::MatchFixedString);

    QList<QListWidgetItem*>::iterator i = items.begin();
    for(; i != items.end(); ++i)
	delegate->listWidget->takeItem(delegate->listWidget->row(*i));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Delegate* delegate = new Delegate;

    delegate->listWidget = new QListWidget;
    QObject::connect(delegate->listWidget, SIGNAL(clicked(const QModelIndex&)), delegate, SLOT(clicked(const QModelIndex&)));

    delegate->detailWidget = new HID::DetailWidget;
    delegate->elementsWidget = new HID::ElementsWidget;

    QTabWidget* tabs = new QTabWidget;
    tabs->addTab(delegate->detailWidget, "Info");
    tabs->addTab(delegate->elementsWidget, "Elements");

    /* Set a larger stretch on the QTabWidget so it will expand to match the
	selected device. But, the layout manager will prefer to take space from
	the list widget instead of expanding the main window. So, set the list
	widget's minimum width to the width of its sizeHint to force the window
	to be expanded.
    */
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(delegate->listWidget);
    hbox->addWidget(tabs, 1);
    const QSize s = delegate->listWidget->sizeHint();
    delegate->listWidget->setMinimumWidth(s.width());

    QWidget* widget = new QWidget;
    widget->setLayout(hbox);
    widget->show();

    // Create a USB HID enumerator to watch for device events and dispatch them accordingly
    HID::enumerator_type* enumerator = HID::enumerator();
    enumerator->setMatchCallback(matched, delegate);
    enumerator->setRemovalCallback(removed, delegate);
    enumerator->start();

    return app.exec();
}
