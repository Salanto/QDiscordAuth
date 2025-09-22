#pragma once

#include <QNetworkRequestFactory>
#include <QObject>
#include <qnetworkaccessmanager.h>

class QOAuth2AuthorizationCodeFlow;
class QOAuthHttpServerReplyHandler;

class AOOAuth : public QObject
{
    Q_OBJECT
public:
    explicit AOOAuth(const QHostAddress &bind_addr, int port, QObject *parent = nullptr);
    ~AOOAuth();

signals:
    void authenticated();
    void authenticationFailed();

public:
    void setAuthorizationUrl(const QUrl &url);
    void setTokenUrl(const QUrl &url);
    void setRevocationUrl(const QUrl &url);
    void setClientId(const QString &id);

    void requestToken();
    QString token() const;

private:
    QUrl m_authorization_url;
    QUrl m_token_url;
    QUrl m_revoke_url;
    QString m_client_id;
    QHostAddress m_bind_address;
    int m_bind_port;

    QOAuth2AuthorizationCodeFlow *m_oauth;
    QOAuthHttpServerReplyHandler *m_handler;
    QNetworkAccessManager *m_networkManager;
};
