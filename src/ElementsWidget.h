/*  Display the report elements of a Human Interface Device
*/

#ifndef	ELEMENTS_WIDGET_H
#define	ELEMENTS_WIDGET_H

#include <QTreeWidget>

#include <hid.h>

namespace HID
{
    class ElementsWidget;
}

class HID::ElementsWidget : public QTreeWidget
{
    device_type*    _device;

public:
    ElementsWidget(QWidget* parent=NULL);

    void refresh();
    void setDevice(device_type* device);
};

#endif	// ELEMENTS_WIDGET_H
