#include <QListWidget>
#include <QMessageBox>
#include <QModelIndex>

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

// Create a USB HID enumerator to watch for device events and dispatch them accordingly
Delegate::Delegate() : QObject(), enumerator(HID::enumerator())
{
    enumerator->setMatchCallback(matched, this);
    enumerator->setRemovalCallback(removed, this);    
}

void Delegate::clicked(const QModelIndex& index)
{
    HID::device_list::iterator i = enumerator->begin();
    for(ssize_t j=0; (i != enumerator->end()) && (j != index.row()); ++i, ++j){}
    detailWidget->setDevice(*i);
    elementsWidget->setDevice(*i);
}
