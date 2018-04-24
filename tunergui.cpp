#include "tunergui.h"
#include "ui_tunergui.h"

TunerGUI::TunerGUI(QWidget *parent) : QWidget(parent), ui(new Ui::TunerGUI), object(NULL)
{
    ui->setupUi(this);

    object = new LAUAudioObject();
    object->setWindowSize(1024);
    connect(object, SIGNAL(emitBuffer(float *, int)), this, SLOT(onUpdateBuffer(float *, int)));
}

TunerGUI::~TunerGUI()
{
    delete ui;
}

void TunerGUI::setupPlot()
{
    ui->InputGraph->addGraph();
    ui->PSDGraph->addGraph();

    ui->InputGraph->xAxis->setRange(0, 1025);
    ui->InputGraph->yAxis->setRange(-2, 2);

    ui->PSDGraph->xAxis->setRange(0, 1024);
    ui->PSDGraph->yAxis->setRange(0, 3);


    QVector<double> time(1024);

    for (int i = 0; i < 1024; i++) {
        time[i] = i;
    }

    //ui->InputGraph->graph(0)->setData(time, windowedData);
}

void TunerGUI::plotPSD()
{
    vector<double> windowedBuffer;
    windowedBuffer.assign((double *)windowedInput, (double *)windowedInput + 1024);
    windowedData.fromStdVector(windowedBuffer);

    //qDebug() << windowed[windowSize/2-1];

    //ui->PSDGraph->graph(0)->setData(time, PSD);
}

QVector<float> TunerGUI::getFFT()
{
    float *outputBuffer;
    float *PSD;

    fftw_plan p;

    p = fftw_plan_r2r_1d(1024, (double *)windowedInput, (double *)FFTdata, FFTW_R2HC, FFTW_ESTIMATE);

    fftw_execute(p);

    //for(int i = 0; i < (1024/2 + 1); i++){
    //PSD[i] = (outputBuffer[i]*outputBuffer[i] + outputBuffer[1024/2 +1 -i] * outputBuffer[1024/2 +1 -i]);
    //}

}

float *TunerGUI::getWindowFunc()
{
    int windowSize = 1024;

    for (int i = 0; i < windowSize; i++) {
        windowedInput[i] = 0.5 * (1 - qCos((i * 2 * M_PI) / 1023)) * (double)inputBuffer[i];
    }
}

void TunerGUI::onUpdateBuffer(float *buffer, int samples)
{
    inputBuffer = buffer;
    samplesFromMic = samples;

    setupPlot();
    ui->InputGraph->replot();
}

float TunerGUI::getPitch()
{

}
