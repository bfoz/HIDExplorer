/*  A widget that displays the top-level details of a Human Interface Device
*/

#ifndef	HID_DETAIL_WIDGET_H
#define	HID_DETAIL_WIDGET_H

#include <hid.h>

#include <QLabel>

namespace HID
{
    class DetailWidget;
}

class HID::DetailWidget : public QWidget
{
    Q_OBJECT

    device_type*    _device;

    QLabel* labelManufacturerString;
    QLabel* labelPrimaryUsage;
    QLabel* labelPrimaryUsagePage;
    QLabel* labelProductID;
    QLabel* labelProductString;
    QLabel* labelVendorID;

public:
    DetailWidget(QWidget* parent=NULL);

    void refresh();
    void setDevice(device_type* device);
};

#endif	// HID_DETAIL_WIDGET_H
