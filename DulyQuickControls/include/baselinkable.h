#ifndef BASELINKABLE_H
#define BASELINKABLE_H

#include "ilinkable.h"

namespace duly_gui {
	class BaseLinkable : public ALinkable
	{
	public:
		explicit BaseLinkable(QQuickItem *parent);
		~BaseLinkable();

		/**
		* \brief Connect linkable together, create a link, and keep a reference on the visual curve
		* \param linkable
		* \param curve
		* \return Link *
		*/
		virtual Link *connect(ALinkable *linkable, BezierCurve *curve) override;

		/**
		* \brief Break a link between linkable
		* \param linkable
		*/
		virtual void unlink(ALinkable *linkable) override;

		/**
		* \brief Break all the links between linkable
		*/
		virtual void unlinkAll() override;

		/**
		* \brief Add a link
		* \param l
		*/
		virtual void addLink(Link *l) override;

		/**
		* \brief Remove a link
		* \param l
		*/
		virtual void removeLink(Link *l) override;

		/**
		* \brief is linkable is actually
		* \return bool
		*/
		bool isLink() override;

		/**
		* \brief return the link between this and linkable
		* \param linkable
		* \return Link *
		*/
		Link *getLink(ALinkable *linkable) const override;

		QQuickItem *parent() const { return m_parent; }

	protected:
		QQuickItem *m_parent;
	};

}

#endif // BASELINKABLE_H