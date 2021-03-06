#ifndef LAUFFTOBJECT_H
#define LAUFFTOBJECT_H

#include <QObject>
#include <fftw3.h>
#include <math.h>

#define LAUFFTOBJECTMAXWINDOWSIZE 4096

class LAUFFTObject : public QObject
{
    Q_OBJECT

public:
    enum Window { Rectangular, Hann, Hamming };
    explicit LAUFFTObject(int smpls = 512, Window wnd = Rectangular, QObject *parent = nullptr);
    ~LAUFFTObject();

    void setWindow(Window wnd);
    void setWindowSize(int val);

public slots:
    void onUpdateBuffer(float *buffer, int samples);

private:
    Window window;
    int windowSize;
    double *dBuffer;
    double *wBuffer;

signals:
    void emitUpdateBuffer(float *buffer, int samples);

};

#endif // LAUFFTOBJECT_H
