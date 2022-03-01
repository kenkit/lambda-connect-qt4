#ifndef _LAMBDA_CONNECT_H_
#define _LAMBDA_CONNECT_H_
#include <functional>
#include <QString>
#include <QObject>

namespace Qt4LambdaConnecter {

class LambdaConnectorHelper: public QObject
{
    Q_OBJECT
public:
    LambdaConnectorHelper(QObject *parent, const char* signal,
                          const std::function<void(int)>& f,
                          Qt::ConnectionType type = Qt::AutoConnection);
    LambdaConnectorHelper(QObject *parent, const char* signal,
                          const std::function<void()>& f,
                          Qt::ConnectionType type = Qt::AutoConnection);
    bool disconnect();
    bool connected();
public slots:
    void trigger();
    void trigger(int i);
private:
    bool m_result;
    const QString m_signal;

    std::function<void(int)> m_lambda;
    std::function<void()> m_lambda1;

};

LambdaConnectorHelper* connect(QObject *sender,
                               const char *signal,
                               const std::function<void()> &lambda,
                               Qt::ConnectionType type = Qt::AutoConnection);

LambdaConnectorHelper* connect(QObject *sender,
                               const char *signal,
                               const std::function<void(int)> &lambda,
                               Qt::ConnectionType type = Qt::AutoConnection);

} // Qt4LambdaConnecter

#endif // _LAMBDA_CONNECT_H_


