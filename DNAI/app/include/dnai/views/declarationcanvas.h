#ifndef DECLARATIONCANVAS_H
#define DECLARATIONCANVAS_H

#include "canvasnode.h"
#include "dnai/models/class.h"
#include "dnai/models/context.h"
#include "dnai/models/function.h"

namespace dnai {
namespace views {
class DeclarationCanvas : public CanvasNode
{
    Q_OBJECT
public:
	explicit DeclarationCanvas(QQuickItem *parent = nullptr);
    static void CreateClass(const models::Class* cl, const bool recursif);
    static void CreateContext(const models::Context *cl, const bool recursif);
	static void CreateFunction(const models::Function *cl);
	static void CreateVariable(const models::Variable *cl);

private:
	static void initComponents();
	static void registerComponent(const QString& path);

private:
	static QList<QQmlComponent *> components;
};
}
}

#endif // DECLARATIONCANVAS_H
