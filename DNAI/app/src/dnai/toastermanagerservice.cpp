#include <QDebug>
#include <QQmlContext>
#include "dnai/app.h"
#include "include/dnai/toastermanagerservice.h"

int ToasterManagerService::getYposition(int absIdx) const {
    int y = 0;
    int idx = 0;

    foreach (Toast *item, m_list) {
        if (idx == absIdx) {
            break;
        }
        y += item->item()->height() + 10;
        idx++;
    }
    return y;
}

void ToasterManagerService::timeout(Toast *toast) {
    m_list.removeOne(toast);
    int idx = 0;

    foreach (Toast *tmp, m_list) {
        tmp->item()->setProperty("yMargins", getYposition(idx));
        idx++;
    }
}

void ToasterManagerService::removeOne(Toast *toast) {
    delete toast;
}

Toast *ToasterManagerService::createToast(QString const &text, std::function<void ()> func) {
    QQmlComponent component(dnai::App::getEngineInstance(), "qrc:/resources/Components/Toast.qml");

    QQuickItem *obj = qobject_cast<QQuickItem*>(component.beginCreate(dnai::App::getEngineInstance()->rootContext()));
    obj->setProperty("yMargins", getYposition());
    obj->setProperty("textValue", text);
    obj->setParentItem(dnai::Editor::instance().mainView());

    Toast *toast = new Toast(obj, this, func);

    QObject::connect(toast->item(), SIGNAL(enterToast()),
                     toast, SLOT(onEnterToast()), Qt::QueuedConnection);
    QObject::connect(toast->item(), SIGNAL(exitToast()),
                     toast, SLOT(onExitToast()),Qt::QueuedConnection);
    QObject::connect(toast->item(), SIGNAL(clickToast()),
                     toast, SLOT(onClickToast()),Qt::QueuedConnection);
    QObject::connect(toast->item(), SIGNAL(removeToast()),
                     toast, SLOT(onRemoveToast()),Qt::QueuedConnection);

    component.completeCreate();

    m_list.append(toast);

    return toast;
}

void ToasterManagerService::notifyInformation(QString const &text, std::function<void ()> func) {
    Toast *toast = createToast(text, func);
    toast->item()->setProperty("backgroundColor", "#00BFFF");
    toast->item()->setProperty("iconsFont", "\uf05a");
    toast->item()->setProperty("colorIconsFont", "white");
}

void ToasterManagerService::notifyError(QString const &text, std::function<void ()> func) {
    Toast *toast = createToast(text, func);
    toast->item()->setProperty("backgroundColor", "#FF3333");
    toast->item()->setProperty("iconsFont", "\uf057");
    toast->item()->setProperty("colorIconsFont", "white");
}

void ToasterManagerService::notifyWarning(QString const &text, std::function<void ()> func) {
    Toast *toast = createToast(text, func);
    toast->item()->setProperty("backgroundColor", "orange");
    toast->item()->setProperty("iconsFont", "\uf06a");
    toast->item()->setProperty("colorIconsFont", "white");
}

void ToasterManagerService::notifySuccess(QString const &text, std::function<void ()> func) {
    Toast *toast = createToast(text, func);
    toast->item()->setProperty("backgroundColor", "#4C9900");
    toast->item()->setProperty("iconsFont", "\uf058");
    toast->item()->setProperty("colorIconsFont", "white");
}
