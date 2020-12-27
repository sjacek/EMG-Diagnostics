#ifndef UECGENUMERATOR_H
#define UECGENUMERATOR_H

class UecgEnumerator : public QObject
{
    Q_OBJECT
    Q_LOGGING_CATEGORY(cat, typeid(this).name())
public:
    explicit UecgEnumerator(QObject* parent = nullptr);

    static const int PRODUCT_ID = 0xea60;
    static const int VENDOR_ID = 0x10c4;

private:
    QextSerialEnumerator serialEnumerator;

Q_SIGNALS:
    void deviceDiscovered(const QextPortInfo& info);
    void deviceRemoved(const QextPortInfo& info);

};

#endif // UECGENUMERATOR_H
