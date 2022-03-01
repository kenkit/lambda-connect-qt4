#include "lambdaconnect.h"

namespace Qt4LambdaConnecter {

LambdaConnectorHelper::LambdaConnectorHelper(QObject *parent,
        const char* signal,
        const std::function<void(int)>& f,
        Qt::ConnectionType type)
    : QObject(parent),
      m_signal(signal),
      m_lambda(f)
{
    m_result = QObject::connect(parent, signal, this, SLOT(trigger(int)), type);
}

LambdaConnectorHelper::LambdaConnectorHelper(QObject *parent,
        const char* signal,
        const std::function<void()>& f,
        Qt::ConnectionType type)
    : QObject(parent),
      m_signal(signal),
      m_lambda1(f)
{
    m_result = QObject::connect(parent, signal, this, SLOT(trigger()), type);
}

void LambdaConnectorHelper::trigger(int i)
{
    m_lambda(i);
}

void LambdaConnectorHelper::trigger()
{
    m_lambda1();
}

bool LambdaConnectorHelper::connected()
{
    return m_result;
}

bool LambdaConnectorHelper::disconnect()
{
    if (m_result)
    {
#if QT_VERSION > QT_VERSION_CHECK(5, 0, 0)
        m_result = QObject::disconnect(parent(),
                                       m_signal.toUtf8().data(),
                                       this,
                                       SLOT(trigger()));
#else
        m_result = QObject::disconnect(parent(),
                                       m_signal.toAscii().data(),
                                       this,
                                       SLOT(trigger()));
#endif
    }
    return m_result;
}

LambdaConnectorHelper* connect(QObject *sender,
                               const char *signal,
                               const std::function<void(int)> &lambda,
                               Qt::ConnectionType type)
{
    return new LambdaConnectorHelper(sender, signal, lambda, type);
}

LambdaConnectorHelper* connect(QObject *sender,
                               const char *signal,
                               const std::function<void()> &lambda,
                               Qt::ConnectionType type)
{
    return new LambdaConnectorHelper(sender, signal, lambda, type);
}

}
