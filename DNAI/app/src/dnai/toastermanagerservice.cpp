#include "dnai/app.h"
#include "include/dnai/toastermanagerservice.h"

/*ToasterManagerService::ToasterManagerService() :
    QObject(0),
    m_engine(dnai::App::getEngineInstance())
{

}*/

void ToasterManagerService::notifyInformation(QString const &text) {
    QQmlComponent component(dnai::App::getEngineInstance(),
            QUrl::fromLocalFile("qrc:/resources/Components/Toast.qml"));
    /*while (!component.isReady()) {

    }*/
    QQuickItem *obj = qobject_cast<QQuickItem*>(component.beginCreate(dnai::App::getEngineInstance()->rootContext()));
    component.completeCreate();

    dnai::App::currentInstance()->processManager()->launchUpdater(dnai::Editor::instance().version(), dnai::App::currentInstance()->settings().currentVersionAPI());
    //QObject *object = component.create();
    /*
     *        const QString path = "qrc:/resources/Components/Node.qml";
        QQmlComponent component(App::getEngineInstance(), path);
        QQuickItem *obj = qobject_cast<QQuickItem*>(component.beginCreate(App::getEngineInstance()->rootContext()));
        QQmlProperty model(obj, "model", App::getEngineInstance());
        model.write(QVariant::fromValue(App::currentInstance()->nodes()->createNode(static_cast<enums::QInstructionID::Instruction_ID>(nodeModel->property("instruction_id").toInt()))));
        const auto view = qvariant_cast<QQuickItem *>(Editor::instance().selectedView()->property("currentView"));
        if (!view)
        {
            throw std::runtime_error("No canvas view found!");
        }
        auto canvas = dynamic_cast<views::CanvasNode *>(view);
        obj->setParentItem(canvas->content());
        component.completeCreate();
     *
    */
//    delete object;
}
