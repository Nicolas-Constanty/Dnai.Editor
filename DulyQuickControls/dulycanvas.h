#ifndef DULYCANVAS_H
#define DULYCANVAS_H

#include <QColor>
#include <list>
#include <memory>
#include "line.h"
#include "focusmanager.h"
#include "scalableitem.h"

class DulyCanvas : public ScalableItem
{
    Q_OBJECT

    Q_PROPERTY(int gridStep READ gridStep WRITE setGridStep NOTIFY gridStepChanged)
    Q_PROPERTY(int accentGridStep READ accentGridStep WRITE setAccentGridStep NOTIFY accentGridStepChanged)

    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(QColor accentGridColor READ accentGridColor WRITE setAccentGridColor NOTIFY accentGridColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)


public:
	explicit DulyCanvas(QQuickItem *parent = nullptr);
    ~DulyCanvas();

    static DulyCanvas *Instance;
	
	/**
	 * \brief return the focusManager
	 * \return FocusManager &
	 */
	FocusManager &focusManager() { return m_focusManager; }
	
	/**
	 * \brief Override updatePaintNode and draw a beautifull canvas
	 * \return QSGNode * 
	 */
	virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

public:
    int gridStep() const { return m_gridStep; }
    int accentGridStep() const { return m_accentGridStep; }

    QColor gridColor() const { return m_gridColor; }
    QColor accentGridColor() const { return m_accentGridColor; }
    QColor backgroundColor() const { return m_backgroundColor; }

public:
    void setGridStep(int step);
    void setAccentGridStep(int step);
    void setGridColor(const QColor &color);
    void setAccentGridColor(const QColor &color);
    void setBackgroundColor(const QColor & color);
    void setScaleFactor(qreal scale) override;


signals:
    void gridStepChanged(int step);
    void accentGridStepChanged(int step);
    void gridColorChanged(const QColor &color);
    void accentGridColorChanged(const QColor &color);
    void backgroundColorChanged(const QColor &color);

private:
    int m_gridStep;
    int m_accentGridStep;

    QColor m_gridColor;
    QColor m_accentGridColor;
    QColor m_backgroundColor;

private:
    void createGrid();
    FocusManager m_focusManager;
	std::list<QSGGeometryNode *> m_lines;
	QPointF	m_offset;
	QPointF	m_gridOffset;


protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
};

#endif // DULYCANVAS_H
