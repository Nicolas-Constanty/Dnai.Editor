#ifndef RESOURCESNODE_H
#define RESOURCESNODE_H

#include <QObject>

class DulyResources  : public QObject
{
   Q_OBJECT
   public:
	explicit DulyResources(QObject *parent = nullptr) : QObject(parent) {}
    ~DulyResources() {}
	/**
     * \brief define all the handle type by the application
     */
    enum IOType
    {
        Int,
        String,
        Bool,
        Count //Get the size of enum, must be at the end all the time!
    };
    Q_ENUM(IOType)

	enum FlowType
	{
		Enter,
		Exit
    };
	Q_ENUM(FlowType)
};



#endif // RESOURCESNODE_H
