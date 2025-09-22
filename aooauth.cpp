#include "aooauth.h"

#include <QDesktopServices>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>
#include <QUrlQuery>

AOOAuth::AOOAuth(const QHostAddress &bind_addr, int port, QObject *parent)
    : QObject{parent}
    , m_oauth(new QOAuth2AuthorizationCodeFlow(this))
    , m_handler(new QOAuthHttpServerReplyHandler(bind_addr, port, this))
    , m_networkManager(new QNetworkAccessManager(this))
{
    qDebug() << "Created AOOAuth Instance";
    m_oauth->setReplyHandler(m_handler);
}

QString AOOAuth::token() const
{
    return m_oauth->token();
}

AOOAuth::~AOOAuth() {}

void AOOAuth::setAuthorizationUrl(const QUrl &url)
{
    m_authorization_url = url;
}

void AOOAuth::setTokenUrl(const QUrl &url)
{
    m_token_url = url;
}

void AOOAuth::setRevocationUrl(const QUrl &url)
{
    m_revoke_url = url;
}

void AOOAuth::setClientId(const QString &id)
{
    m_client_id = id;
}

void AOOAuth::requestToken()
{
    m_oauth->setAuthorizationUrl(m_authorization_url);
    m_oauth->setAccessTokenUrl(m_token_url);
    m_oauth->setClientIdentifier(m_client_id);
    m_oauth->setScope("identify");

    connect(m_oauth, &QAbstractOAuth::authorizeWithBrowser, &QDesktopServices::openUrl);
    connect(m_oauth, &QAbstractOAuth::granted, this, [this]() {
        qDebug() << "OAuth granted! Token:" << m_oauth->token();
        m_handler->close();
        emit authenticated();
    });

    connect(m_oauth, &QAbstractOAuth::requestFailed, this, [this](QAbstractOAuth::Error error) {
        qDebug() << QVariant::fromValue(error).toString();
    });

    if (m_handler->isListening()) {
        qDebug() << "Starting OAuth on port" << m_handler->port();
        m_oauth->grant();
    } else {
        qDebug() << "Failed to start server on port" << m_handler->port();
        emit authenticationFailed();
    }
}
