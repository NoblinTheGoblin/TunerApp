#ifndef TUNERGUI_H
#define TUNERGUI_H

#include <QDebug>
#include <QWidget>
#include <QVector>
#include <vector>
#include <math.h>
#include <fftw3.h>
#include "lauaudioobject.h"

using namespace std;

namespace Ui
{
    class TunerGUI;
}

class TunerGUI : public QWidget
{
    Q_OBJECT

public:
    explicit TunerGUI(QWidget *parent = 0);
    ~TunerGUI();

    void setupPlot();
    void plotPSD();
    QVector<float> getFFT();
    float *getWindowFunc();
    float getPitch();

public slots:
    void onUpdateBuffer(float *buffer, int samples);

protected:
    void showEvent(QShowEvent *)
    {
        if (object && object->isValid()) {
            object->onStart();
        }
    }

private:
    Ui::TunerGUI *ui;
    LAUAudioObject *object;
    float *inputBuffer;
    int samplesFromMic;
    double *FFTdata;
    double *windowedInput;
    QVector<double> windowedData;
    QVector<float> PSDdata;
    float frequency;
};

#endif // TUNERGUI_H
