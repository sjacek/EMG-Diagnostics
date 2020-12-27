#include "uecgenumerator.h"

UecgEnumerator::UecgEnumerator(QObject *parent)
    : QObject(parent)
    , serialEnumerator(this)
{
    serialEnumerator.setUpNotifications();
    connect(&serialEnumerator, &QextSerialEnumerator::deviceDiscovered, [=](const QextPortInfo& port)
    {
        qCDebug(cat) << "******************** deviceDiscovered:"
                     << "enumName" << port.enumName << "friendName" << port.friendName << "physName" << port.physName
                     << "portName" << port.portName << "productID" << port.productID << "vendorID" << port.vendorID;

        if ((port.productID == PRODUCT_ID) && (port.vendorID == VENDOR_ID))
            emit deviceDiscovered(port);
    });
    connect(&serialEnumerator, &QextSerialEnumerator::deviceRemoved,  [=](const QextPortInfo& port)
    {
        qCDebug(cat) << "******************** deviceRemoved:"
                     << "enumName" << port.enumName << "friendName" << port.friendName << "physName" << port.physName
                     << "portName" << port.portName << "productID" << port.productID << "vendorID" << port.vendorID;
        if ((port.productID == PRODUCT_ID) && (port.vendorID == VENDOR_ID))
            emit deviceRemoved(port);
    });
}
