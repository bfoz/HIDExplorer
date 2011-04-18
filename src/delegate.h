#ifndef	_DELEGATE_H
#define	_DELEGATE_H

#include <QObject>

#include <hid.h>

class QListWidget;
class QModelIndex;

namespace HID
{
    class DetailWidget;
    class ElementsWidget;
}

class Delegate : public QObject
{
    Q_OBJECT

public:
    HID::DetailWidget*	detailWidget;
    HID::ElementsWidget*    elementsWidget;
    HID::device_list	devices;
    QListWidget*    listWidget;

public slots:
    void clicked(const QModelIndex& index);
};

#endif	// _DELEGATE_H
