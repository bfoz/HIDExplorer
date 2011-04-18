#include <QHeaderView>

#include "ElementsWidget.h"

HID::ElementsWidget::ElementsWidget(QWidget* parent) : QTreeWidget(parent), _device(NULL)
{
    QStringList strings;
    strings.append("Name");
    strings.append("Report ID");
    strings.append("Usage");
    strings.append("Logical Min");
    strings.append("Logical Max");
    strings.append("Physical Min");
    strings.append("Physical Max");
    setHeaderLabels(strings);

    header()->setResizeMode(QHeaderView::ResizeToContents);
}

void addElementTree(HID::elements_type& elements, QTreeWidgetItem *const item)
{
    HID::elements_type::iterator i = elements.begin();
    for(; i != elements.end(); ++i)
    {
	QStringList strings;

	strings.append(QString((*i)->name().c_str()));
	strings.append(QString("%1").arg((*i)->reportID()));
	strings.append(QString("%1").arg((*i)->usage()));
	if( !(*i)->isCollection() )
	{
	    strings.append(QString("%1").arg((*i)->logicalRange().first));
	    strings.append(QString("%1").arg((*i)->logicalRange().second));
	    strings.append(QString("%1").arg((*i)->physicalRange().first));
	    strings.append(QString("%1").arg((*i)->physicalRange().second));
	}

	QTreeWidgetItem *const child = new QTreeWidgetItem(strings);
	item->addChild(child);

    	if( (*i)->isCollection() )
	    addElementTree((*i)->children(), child);
    }
}

void HID::ElementsWidget::refresh()
{
    if( !_device )
	return;

    clear();
    addElementTree(_device->elements(), invisibleRootItem());
}

void HID::ElementsWidget::setDevice(HID::device_type* device)
{
    _device = device;
    refresh();
}
