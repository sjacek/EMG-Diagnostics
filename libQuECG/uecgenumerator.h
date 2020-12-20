#ifndef UECGENUMERATOR_H
#define UECGENUMERATOR_H

class UecgEnumerator : public QObject
{
    Q_OBJECT
    Q_LOGGING_CATEGORY(cat, typeid(this).name())
public:
    explicit UecgEnumerator(QObject *parent = nullptr);

private:
    QextSerialEnumerator serialEnumerator;

Q_SIGNALS:
    void deviceDiscovered(const QextPortInfo &info);
    void deviceRemoved(const QextPortInfo &info);

};

#endif // UECGENUMERATOR_H
