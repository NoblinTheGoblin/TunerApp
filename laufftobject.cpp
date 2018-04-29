#include "lauplotwidget.h"

LAUPlotWidget::LAUPlotWidget(Style stl, QWidget *parent) : QWidget(parent), style(stl), windowSize(512)
{
    this->setLayout(new QVBoxLayout());
    this->layout()->setContentsMargins(0, 0, 0, 0);

    plot = new QCustomPlot();
    this->layout()->addWidget(plot);

    if (style == StyleRaw) {
        // SET AXES FOR SHOWING DENSITIES
        plot->xAxis->setLabel("Time [n]");
        plot->xAxis2->setVisible(true);
        plot->xAxis->setRange(0, windowSize);
        plot->xAxis2->setRange(0, windowSize);

        plot->yAxis->setLabel("Raw Audio Signal");
        plot->yAxis2->setVisible(true);
        plot->yAxis->setRangeReversed(false);
        plot->yAxis2->setRangeReversed(false);
        plot->yAxis->setRange(-2, 2);
        plot->yAxis2->setRange(-2, 2);
    } else if (style == StylePSD) {
        // SET AXES FOR SHOWING DENSITIES
        plot->xAxis->setLabel("Frequency [k]");
        plot->xAxis2->setVisible(true);
        plot->xAxis->setRange(0, windowSize);
        plot->xAxis2->setRange(0, windowSize);
        plot->xAxis->setScaleType(QCPAxis::stLogarithmic);
        plot->xAxis2->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
        plot->xAxis->setTicker(logTicker);
        plot->xAxis2->setTicker(logTicker);

        plot->yAxis->setLabel("PSD Audio Signal");
        plot->yAxis2->setVisible(true);
        plot->yAxis->setRangeReversed(false);
        plot->yAxis2->setRangeReversed(false);
        plot->yAxis->setRange(-100, 100);
        plot->yAxis2->setRange(-100, 100);
        plot->yAxis->setScaleType(QCPAxis::stLogarithmic);
        plot->yAxis2->setScaleType(QCPAxis::stLogarithmic);
        plot->yAxis->setTicker(logTicker);
        plot->yAxis2->setTicker(logTicker);
    }

    // CREATE THE GRAPH INSIDE THE PLOT OBJECT AND SET THE PEN STYLE
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::red));
    plot->graph(0)->setLineStyle(QCPGraph::lsLine);
}

void LAUPlotWidget::onUpdateBuffer(float *buffer, int samples)
{
    // MAKE SURE WE HAVE AN EXISTING X AND Y VECTOR AND THAT
    // BOTH CAN HOLD THE INCOMING SAMPLES
    if (x.size() != samples) {
        x.resize(samples);
        for (int n = 0; n < samples; n++) {
            x[n] = (double)n;
        }
        plot->xAxis->setRange(0, samples);
        plot->xAxis2->setRange(0, samples);
    }

    if (y.size() != samples) {
        y.resize(samples);
    }

    // COPY THE INCOMING SAMPLES OVER TO OUR DOUBLE VECTOR FOR PLOTTING
    for (int n = 0; n < samples; n++) {
        y[n] = (double)buffer[n];
    }

    // CALL THE PLOT FUNCTION TO DISPLAY ON SCREEN
    plot->graph(0)->setData(x, y);
    plot->replot();

    // EMIT THE BUFFER TO THE NEXT STAGE OF PROCESSING
    emit emitUpdateBuffer(buffer, samples);
}
