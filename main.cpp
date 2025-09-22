#include <QtGui/QGuiApplication>

#include <QTimer>
#include "AOOAuth.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    AOOAuth *foo = new AOOAuth(QHostAddress::LocalHost, 27016, &a);
    foo->setAuthorizationUrl(QUrl("https://discord.com/api/oauth2/authorize"));
    foo->setTokenUrl(QUrl("https://discord.com/api/oauth2/token"));
    foo->setClientId("1387467051915940131");

    foo->requestToken();

    return a.exec();
}
