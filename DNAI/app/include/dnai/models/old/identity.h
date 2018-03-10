#ifndef MODEL_IDENTITY_H
#define MODEL_IDENTITY_H

#include "imodel.h"

namespace dnai {
namespace models {
class Identity: virtual public IModel
{
public:
	explicit Identity(QString const &);
    virtual ~Identity() = default;

    QString linked_uid() const;
    void setLinked_uid(const QString &linked_uid);

private:
    QString m_linked_uid;

    // IModel interface
public:
	void serialize(QJsonObject &) const override;
	void declare() const override;
	const QList<QString>& editableProperties() override;

    // IClone interface
private:
	virtual IClone *clone() const override;
protected:
	const static QList<QString> m_editableProperties;

};
}
}

#endif // MODEL_IDENTITY_H
