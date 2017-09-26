#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>
#include <QSGSimpleRectNode>
#include <QtMath>
#include <algorithm>
#include <QSettings>

#include "output.h"
#include "input.h"
#include "link.h"

const std::shared_ptr<Link> &InputBackend::Connect(ALinkable *linkable)
{
	const auto li = dynamic_cast<OutputBackend *>(linkable);
    if (li != nullptr && li->GetType() == GetType())
    {
        auto l = GetLink(linkable);
        if (l.get() == nullptr)
        {
            m_links.Clear();
            l = std::make_shared<Link>(this, linkable);
            m_links.Add(l);
            linkable->AddLink(l);
            return l;
        }
        //TODO INSERT DEBUG "Link already exist"
        return l;
    }
}

Input::Input(QQuickItem *parent) :
    IO(parent)
{

}

void Input::refreshBackendIO()
{
//    if (m_io)
//    {
//        qDebug() << "Hey";

//        delete m_io;
//    }
//    qDebug() << "Ho";
    m_io = new InputBackend(m_type);
}
