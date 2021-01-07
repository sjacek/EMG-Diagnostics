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

        if ((port.productID == PRODUCT_CP210X_UART_BRIDGE) && (port.vendorID == VENDOR_SILICON_LABS))
            emit deviceDiscovered(port);
    });
    connect(&serialEnumerator, &QextSerialEnumerator::deviceRemoved,  [=](const QextPortInfo& port)
    {
        qCDebug(cat) << "******************** deviceRemoved:"
                     << "enumName" << port.enumName << "friendName" << port.friendName << "physName" << port.physName
                     << "portName" << port.portName << "productID" << port.productID << "vendorID" << port.vendorID;
        if ((port.productID == PRODUCT_CP210X_UART_BRIDGE) && (port.vendorID == VENDOR_SILICON_LABS))
            emit deviceRemoved(port);
    });
}
