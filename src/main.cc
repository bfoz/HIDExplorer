/*  HID Explorer
    A cross-platform interface for discovering and inspecting HID devices

    Copyright 2010 Brandon Fosdick <bfoz@bfoz.net> (BSD License)
*/

#include <QApplication>
#include <QListWidget>

#include <hid.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    HID::device_list devices = HID::find();

    QListWidget* listWidget = new QListWidget;
    HID::device_list::iterator i = devices.begin();
    for(; i != devices.end(); ++i)
    {
	QListWidgetItem* newItem = new QListWidgetItem((*i)->product().c_str());
	listWidget->addItem(newItem);

	listWidget->show();
    }

    return app.exec();
}
