#include "soundplugin.h"

using namespace dtb;
using namespace dtb::sound;
using namespace dtb::widgets;

SoundPlugin::SoundPlugin()
{
    m_soundItem = new SoundItem;
}

const QString SoundPlugin::pluginName() const
{
    return "sound";
}

void SoundPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    SoundApplet * applet = qobject_cast<SoundApplet *>(m_soundItem->popupApplet());

    connect(applet, &SoundApplet::requestHidePopup, this, [=] {
        m_proxyInter->requestHidePopup();
    });

    m_proxyInter->addItem(this, "");
}

int SoundPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *SoundPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_soundItem;
}

QWidget *SoundPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_soundItem->popupApplet();
}

const QString SoundPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return "deepin-sound";
}

void SoundPlugin::popupShow()
{
    SoundApplet * applet = qobject_cast<SoundApplet *>(m_soundItem->popupApplet());
    applet->showAni();
}

void SoundPlugin::popupHide()
{
    SoundApplet * applet = qobject_cast<SoundApplet *>(m_soundItem->popupApplet());
    applet->hideAni();
}
