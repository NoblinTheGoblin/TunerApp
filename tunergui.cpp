#include "tunergui.h"
#include "ui_tunergui.h"

TunerGUI::TunerGUI(QWidget *parent) : QWidget(parent), ui(new Ui::TunerGUI), object(NULL), fftObject(NULL), rawWidget(NULL), psdWidget(NULL)
{
    ui->setupUi(this);

    object = new LAUAudioObject();
    object->setWindowSize(1024);

    fftObject = new LAUFFTObject();
    fftObject->setWindow(LAUFFTObject::Hamming);
    fftObject->setWindowSize(1024);

    rawWidget = new LAUPlotWidget(LAUPlotWidget::StyleRaw);
    rawWidget->setMinimumHeight(200);
    rawWidget->setWindowSize(1024);
    ui->rawAudioGroupBox->setAutoFillBackground(true);
    ui->rawAudioGroupBox->layout()->addWidget(rawWidget);

    psdWidget = new LAUPlotWidget(LAUPlotWidget::StylePSD);
    psdWidget->setMinimumHeight(200);
    psdWidget->setWindowSize(1024);
    ui->psdAudioGroupBox->layout()->addWidget(psdWidget);

    // CONNECT ALL OUR OBJECTS IN ORDER OF EXECUTION
    connect(object, SIGNAL(emitUpdateBuffer(float *, int)), rawWidget, SLOT(onUpdateBuffer(float *, int)));
    connect(rawWidget, SIGNAL(emitUpdateBuffer(float *, int)), fftObject, SLOT(onUpdateBuffer(float *, int)));
    connect(fftObject, SIGNAL(emitUpdateBuffer(float *, int)), psdWidget, SLOT(onUpdateBuffer(float *, int)));
    connect(psdWidget, SIGNAL(emitUpdateBuffer(float *, int)), this, SLOT(onUpdateBuffer(float *, int)));

    // CALL THESE SLOTS SO THAT WE KNOW OUR OBJECTS MATCH THE CURRENT USER INTERFACE SETTINGS
    on_windowFunctionComboBox_currentIndexChanged(ui->windowFunctionComboBox->currentText());
    on_windowSizeComboBox_currentIndexChanged(ui->windowSizeComboBox->currentText());
}

TunerGUI::~TunerGUI()
{
    // DELETE THE UI AND ANY WIDGETS INSIDE ITS LAYOUTS LIKE THE PLOTTING WIDGETS
    delete ui;

    // MAKE SURE WE DELETE THE AUDIO OBJECT LAST SINCE IT CONTROLS THE DATA BUFFERS
    delete fftObject;
    delete object;
}

void TunerGUI::on_windowFunctionComboBox_currentIndexChanged(QString string)
{
    if (string == QString("Rectangular")) {
        fftObject->setWindow(LAUFFTObject::Rectangular);
    } else if (string == QString("Hann")) {
        fftObject->setWindow(LAUFFTObject::Hann);
    } else if (string == QString("Hamming")) {
        fftObject->setWindow(LAUFFTObject::Hamming);
    }
}

void TunerGUI::on_windowSizeComboBox_currentIndexChanged(QString string)
{
    bool okay = false;
    int val = string.toInt(&okay);
    if (okay) {
        object->setWindowSize(val);
        fftObject->setWindowSize(val);
        rawWidget->setWindowSize(val);
        psdWidget->setWindowSize(val);
    }
}

void TunerGUI::onUpdateBuffer(float *buffer, int samples)
{
    qDebug() << "LOVE IT" << samples;
}
