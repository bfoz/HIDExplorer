#include <QMessageBox>
#include <QModelIndex>

#include "delegate.h"
#include "ElementsWidget.h"
#include "HIDDetailWidget.h"

void Delegate::clicked(const QModelIndex& index)
{
    HID::device_list::iterator i = devices.begin();
    for(ssize_t j=0; (i != devices.end()) && (j != index.row()); ++i, ++j){}
    detailWidget->setDevice(*i);
    elementsWidget->setDevice(*i);
}
