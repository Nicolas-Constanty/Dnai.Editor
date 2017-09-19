#ifndef DULYCANVAS_H
#define DULYCANVAS_H

#include <QQuickItem>
#include <QColor>
#include <list>
#include <memory>
#include "line.h"

class DulyCanvas : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(int gridStep READ gridStep WRITE setGridStep NOTIFY gridStepChanged)
    Q_PROPERTY(int accentGridStep READ accentGridStep WRITE setAccentGridStep NOTIFY accentGridStepChanged)
    Q_PROPERTY(double scaleFactor READ scaleFactor WRITE setScaleFactor NOTIFY scaleFactorChanged)

    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(QColor accentGridColor READ accentGridColor WRITE setAccentGridColor NOTIFY accentGridColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)


public:
    DulyCanvas(QQuickItem *parent = 0);
    ~DulyCanvas();

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    int gridStep() const { return m_gridStep; }
    int accentGridStep() const { return m_accentGridStep; }
    QColor gridColor() const { return m_gridColor; }
    QColor accentGridColor() const { return m_accentGridColor; }
    QColor backgroundColor() const { return m_backgroundColor; }
    double scaleFactor() const { return m_scaleFactor; }


    void setGridStep(int step);
    void setAccentGridStep(int step);
    void setGridColor(const QColor &color);
    void setAccentGridColor(const QColor &color);
    void setBackgroundColor(const QColor & color);
    void setScaleFactor(double scale);

signals:
    void gridStepChanged(int step);
    void accentGridStepChanged(int step);
    void gridColorChanged(const QColor &color);
    void accentGridColorChanged(const QColor &color);
    void backgroundColorChanged(const QColor &color);
    void scaleFactorChanged(double scale);

private:
    int m_gridStep;
    int m_accentGridStep;
    QColor m_gridColor;
    QColor m_accentGridColor;
    QColor m_backgroundColor;
    double m_scaleFactor;

    void CreateGrid();
    std::list<QSGGeometryNode *> m_lines;
};

#endif // DULYCANVAS_H
