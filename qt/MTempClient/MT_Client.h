#ifndef MT_CLIENT_H
#define MT_CLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QHostInfo>

class MT_Client : public QObject{

        Q_OBJECT
        Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
        Q_PROPERTY(quint16 port READ port WRITE setPort NOTIFY portChanged)

    public:
        explicit MT_Client(QObject *parent = 0);
        ~MT_Client();
        QString address() const;
        quint16 port() const;


    signals:
        void addressChanged(QString newAddress);
        void portChanged(quint16 newPort);
        void connected();
        void disconnected();
        void error();

    public slots:
        Q_INVOKABLE bool connectToHost();
        Q_INVOKABLE bool disconnectFromHost();
                    bool setAddress(const QString & addr);
                    bool setPort(const quint16 & port);
    private slots:
        void connectedBouncer();
        void diconnectedBouncer();

    private:
        QTcpSocket * m_sock;
        QString      m_addr;
        quint16      m_port;
};

#endif // MT_CLIENT_H
