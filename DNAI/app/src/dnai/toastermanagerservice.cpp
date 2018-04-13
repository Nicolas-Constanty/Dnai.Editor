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

Toast *ToasterManagerService::createToast(QString const &text, std::function<void ()> func) {
    QQmlComponent component(dnai::App::getEngineInstance(), "qrc:/resources/Components/Toast.qml");

    QQuickItem *obj = qobject_cast<QQuickItem*>(component.beginCreate(dnai::App::getEngineInstance()->rootContext()));
    obj->setProperty("yMargins", getYposition());
    obj->setProperty("textValue", text);
    obj->setParentItem(dnai::Editor::instance().mainView());

    Toast *toast = new Toast(obj, this, func);

    QObject::connect(toast->item(), SIGNAL(enterToast()),
                     toast, SLOT(onEnterToast()));
    QObject::connect(toast->item(), SIGNAL(exitToast()),
                     toast, SLOT(onExitToast()));
    QObject::connect(toast->item(), SIGNAL(clickToast()),
                     toast, SLOT(onClickToast()));

    component.completeCreate();

    m_list.append(toast);

    return toast;
}

void ToasterManagerService::notifyInformation(QString const &text, std::function<void ()> func) {
    Toast *toast = createToast(text, func);
    toast->item()->setProperty("backgroundColor", "#00BFFF");
}

void ToasterManagerService::notifyError(QString const &text, std::function<void ()> func) {
    Toast *toast = createToast(text, func);
    toast->item()->setProperty("backgroundColor", "#FF3333");
}

void ToasterManagerService::notifyWarning(QString const &text, std::function<void ()> func) {
    Toast *toast = createToast(text, func);
    toast->item()->setProperty("backgroundColor", "orange");
}

void ToasterManagerService::notifySuccess(QString const &text, std::function<void ()> func) {
    Toast *toast = createToast(text, func);
    toast->item()->setProperty("backgroundColor", "#4C9900");
}
