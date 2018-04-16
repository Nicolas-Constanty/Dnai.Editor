#ifndef TOAST_H
#define TOAST_H

#include <QQuickItem>
#include <QObject>
#include <QTimer>

class ToasterManagerService;

class Toast : public QObject {
    Q_OBJECT

public:
    Toast(QQuickItem *item, ToasterManagerService*, std::function<void ()> func);
    ~Toast();
    QQuickItem *item();
    QTimer &timer();

signals:
    void remove(Toast *);

public slots:
    void timeout();
    void onDeleteTimeOut();

public slots:
    void onEnterToast();
    void onExitToast();
    void onClickToast();
    void onRemoveToast();

private:
    int         m_msecDisable;
    QQuickItem  *m_item;
    QTimer      *m_timer;
    ToasterManagerService *m_toasterManager;
    std::function<void ()> m_func;
};

#endif // TOAST_H
