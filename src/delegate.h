#ifndef	_DELEGATE_H
#define	_DELEGATE_H

#include <QObject>

#include "HIDDetailWidget.h"

class QListWidget;
class QModelIndex;

class Delegate : public QObject
{
    Q_OBJECT

public:
    HID::DetailWidget*	detailWidget;
    HID::device_list	devices;
    QListWidget*    listWidget;

public slots:
    void clicked(const QModelIndex& index);
};

#endif	// _DELEGATE_H
