#include <QFormLayout>

#include "HIDDetailWidget.h"

HID::DetailWidget::DetailWidget(QWidget* parent) : QWidget(parent), _device(NULL)
{
    labelManufacturerString = new QLabel;
    labelPrimaryUsage = new QLabel;
    labelPrimaryUsagePage = new QLabel;
    labelProductID = new QLabel;
    labelProductString = new QLabel;
    labelVendorID = new QLabel;

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow(tr("Product Name"), labelProductString);
    formLayout->addRow(tr("Manufacturer"), labelManufacturerString);
    formLayout->addRow(tr("Primary Usage Page"), labelPrimaryUsagePage);
    formLayout->addRow(tr("Primary Usage"), labelPrimaryUsage);
    formLayout->addRow(tr("Product ID"), labelVendorID);
    formLayout->addRow(tr("Vendor ID"), labelProductID);

    setLayout(formLayout);
}

void HID::DetailWidget::refresh()
{
    if( !_device )
	return;

    labelManufacturerString->setText(_device->manufacturer().c_str());
    labelPrimaryUsage->setNum(_device->usage());
    labelPrimaryUsagePage->setNum(_device->usagePage());
    labelProductString->setText(_device->product().c_str());
    labelVendorID->setNum(_device->vendorID());
    labelProductID->setNum(_device->productID());
}

void HID::DetailWidget::setDevice(HID::device_type* device)
{
    _device = device;
    refresh();
}
