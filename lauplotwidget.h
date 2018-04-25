#ifndef LAUPLOTWIDGET_H
#define LAUPLOTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "qcustomplot.h"

#define LAUPLOTWIDGETMAXWINDOWSIZE 4096

class LAUPlotWidget : public QWidget
{
    Q_OBJECT

public:
    enum Style { StyleRaw, StylePSD };
    explicit LAUPlotWidget(Style stl = StyleRaw, QWidget *parent = nullptr);

    void setWindowSize(int val)
    {
        windowSize = val;
    }

public slots:
    void onUpdateBuffer(float *buffer, int samples);

private:
    Style style;
    QCustomPlot *plot;
    QVector<double> x, y;
    int windowSize;

signals:
    void emitUpdateBuffer(float *buffer, int samples);
};

#endif // LAUPLOTWIDGET_H
