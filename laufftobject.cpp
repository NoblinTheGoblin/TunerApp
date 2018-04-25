#include "laufftobject.h"

LAUFFTObject::LAUFFTObject(int smpls, Window wnd, QObject *parent) : QObject(parent), windowSize(smpls), window(wnd)
{
    dBuffer = (double *)malloc(LAUFFTOBJECTMAXWINDOWSIZE * sizeof(double));
    memset(dBuffer, LAUFFTOBJECTMAXWINDOWSIZE * sizeof(double), 0);

    wBuffer = (double *)malloc(LAUFFTOBJECTMAXWINDOWSIZE * sizeof(double));
    memset(wBuffer, LAUFFTOBJECTMAXWINDOWSIZE * sizeof(double), 0);
}

LAUFFTObject::~LAUFFTObject()
{
    if (dBuffer) {
        free(dBuffer);
    }

    if (wBuffer) {
        free(wBuffer);
    }
}

void LAUFFTObject::setWindow(Window wnd)
{
    // STORE THE WINDOW FUNCTION NAME
    window = wnd;

    // STORE THE CURRENT WINDOW IN THE WINDOW BUFFER
    if (window == WindowOne) {
        for (int n = 0; n < windowSize; n++) {
            wBuffer[n] = 1.0;
        }
    } else if (window == WindowTwo) {
        for (int n = 0; n < windowSize; n++) {
            wBuffer[n] = 1.0;
        }
    } else if (window == WindowThree) {
        for (int n = 0; n < windowSize; n++) {
            wBuffer[n] = 1.0;
        }
    }
}

void LAUFFTObject::setWindowSize(int val)
{
    // SAVE THE NEW WINDOW SIZE HERE
    windowSize = val;

    // NOW CALL THE WINDOW FUNCTION SO THAT WE HAVE THE NEW SIZED WINDOW
    setWindow(window);
}

void LAUFFTObject::onUpdateBuffer(float *buffer, int samples)
{
    // COPY THE CURRENT WINDOW INTO OUR DATA BUFFER
    for (int n = 0; n < qMin(samples, windowSize); n++) {
        dBuffer[n] = (double)buffer[n] * wBuffer[n];
    }

    // CALCULATE THE FFT INPLACE
    // CALCULATE THE FFT INPLACE
    // CALCULATE THE FFT INPLACE

    // COPY THE FFT COEFFICIENTS BACK TO OUR BUFFER
    for (int n = 0; n < qMin(samples, windowSize); n++) {
        buffer[n] = (float)dBuffer[n];
    }

    emit emitUpdateBuffer(buffer, samples);
}

