#include "tunergui.h"
#include "ui_tunergui.h"

TunerGUI::TunerGUI(QWidget *parent) : QWidget(parent), ui(new Ui::TunerGUI), object(NULL)
{
    ui->setupUi(this);

    object = new LAUAudioObject();
    object->setWindowSize(1024);

    fftObject = new LAUFFTObject();
    fftObject->setWindow(LAUFFTObject::WindowOne);
    fftObject->setWindowSize(1024);

    rawWidget = new LAUPlotWidget(LAUPlotWidget::StyleRaw);
    rawWidget->setWindowSize(1024);
    ui->rawAudioGroupBox->layout()->addWidget(rawWidget);

    psdWidget = new LAUPlotWidget(LAUPlotWidget::StylePSD);
    psdWidget->setWindowSize(1024);
    ui->psdAudioGroupBox->layout()->addWidget(psdWidget);

    connect(object, SIGNAL(emitUpdateBuffer(float *, int)), rawWidget, SLOT(onUpdateBuffer(float *, int)));
    connect(rawWidget, SIGNAL(emitUpdateBuffer(float *, int)), fftObject, SLOT(onUpdateBuffer(float *, int)));
    connect(fftObject, SIGNAL(emitUpdateBuffer(float *, int)), psdWidget, SLOT(onUpdateBuffer(float *, int)));
    connect(psdWidget, SIGNAL(emitUpdateBuffer(float *, int)), this, SLOT(onUpdateBuffer(float *, int)));
}

TunerGUI::~TunerGUI()
{
    delete ui;
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
    qDebug() << "LOVE IT" << samples;
}

float TunerGUI::getPitch()
{

}
