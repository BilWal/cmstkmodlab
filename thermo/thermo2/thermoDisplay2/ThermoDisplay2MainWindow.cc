/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//               Copyright (C) 2011-2019 - The DESY CMS Group                  //
//                           All rights reserved                               //
//                                                                             //
//      The CMStkModLab source code is licensed under the GNU GPL v3.0.        //
//      You have the right to modify and/or redistribute this source code      //
//      under the terms specified in the license, which may be found online    //
//      at http://www.gnu.org/licenses or at License.txt.                      //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

#include <QApplication>
#include <QGroupBox>
#include <QToolBar>
#include <QToolButton>
#include <QFileDialog>
#include <QVBoxLayout>

#include <nqlogger.h>

#include "ApplicationConfig.h"

#include "ThermoDisplay2MainWindow.h"

ThermoDisplay2MainWindow::ThermoDisplay2MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  ApplicationConfig* config = ApplicationConfig::instance();

  tabWidget_ = new QTabWidget(this);

  QToolBar *toolBar = new QToolBar(this);

  QToolButton * btnClear = new QToolButton(toolBar);
  btnClear->setText("Clear");
  btnClear->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
  connect(btnClear, SIGNAL(clicked()), this, SLOT(clearData()));
  toolBar->addWidget(btnClear);

  QToolButton * btnSavePlots = new QToolButton(toolBar);
  btnSavePlots->setText("Save Plots");
  btnSavePlots->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
  connect(btnSavePlots, SIGNAL(clicked()), this, SLOT(savePlots()));
  toolBar->addWidget(btnSavePlots);

  addToolBar(toolBar);

  QWidget *w;
  QVBoxLayout *layout;

  w = new QWidget(tabWidget_);
  layout = new QVBoxLayout(w);

  ChillerTSChart_ = new ThermoDisplay2TemperatureStateChart();

  ChillerTBathSeries_ = new ThermoDisplay2LineSeries();
  ChillerTBathSeries_->setName("Bath");
  ChillerTSChart_->addSeries(ChillerTBathSeries_);

  ChillerTReturnSeries_ = new ThermoDisplay2LineSeries();
  ChillerTReturnSeries_->setName("Return");
  ChillerTSChart_->addSeries(ChillerTReturnSeries_);

  ChillerTCWISeries_ = new ThermoDisplay2LineSeries();
  ChillerTCWISeries_->setName("CW Inlet");
  ChillerTSChart_->addSeries(ChillerTCWISeries_);

  ChillerTCWOSeries_ = new ThermoDisplay2LineSeries();
  ChillerTCWOSeries_->setName("CW Outlet");
  ChillerTSChart_->addSeries(ChillerTCWOSeries_);

  ChillerSTCSeries_ = new ThermoDisplay2LineSeries();
  ChillerSTCSeries_->setName("T Control");
  ChillerTSChart_->addStateSeries(ChillerSTCSeries_);

  ChillerSCSeries_ = new ThermoDisplay2LineSeries();
  ChillerSCSeries_->setName("Circulator");
  ChillerTSChart_->addStateSeries(ChillerSCSeries_);

  ChillerTSChartView_ = new ThermoDisplay2TemperatureStateChartView(ChillerTSChart_);
  ChillerTSChartView_->setRenderHint(QPainter::Antialiasing);
  ChillerTSChartView_->setMinimumSize(800, 300);
  layout->addWidget(ChillerTSChartView_);

  ChillerTSChart_->connectMarkers();
  ChillerTSChart_->updateLegend();

  ChillerPPChart_ = new ThermoDisplay2PowerPressureChart();

  ChillerPowerSeries_ = new ThermoDisplay2LineSeries();
  ChillerPowerSeries_->setName("Power");
  ChillerPPChart_->addPowerSeries(ChillerPowerSeries_);

  ChillerPressureSeries_ = new ThermoDisplay2LineSeries();
  ChillerPressureSeries_->setName("Pressure");
  ChillerPPChart_->addPressureSeries(ChillerPressureSeries_);

  ChillerPPChartView_ = new ThermoDisplay2PowerPressureChartView(ChillerPPChart_);
  ChillerPPChartView_->setRenderHint(QPainter::Antialiasing);
  ChillerPPChartView_->setMinimumSize(800, 300);
  layout->addWidget(ChillerPPChartView_);

  ChillerPPChart_->connectMarkers();
  ChillerPPChart_->updateLegend();

  tabWidget_->addTab(w, "Chiller");

  w = new QWidget(tabWidget_);
  layout = new QVBoxLayout(w);

  VacuumPressureSeries_ = new ThermoDisplay2LineSeries();
  VacuumPressureSeries_->setName("pressure");

  VacuumPressureChart_ = new ThermoDisplay2PressureChart();
  VacuumPressureChart_->addSeries(VacuumPressureSeries_);

  VacuumChartView_ = new ThermoDisplay2PressureChartView(VacuumPressureChart_);
  VacuumChartView_->setRenderHint(QPainter::Antialiasing);
  VacuumChartView_->setMinimumSize(800, 300);
  layout->addWidget(VacuumChartView_);

  VacuumPressureChart_->connectMarkers();
  VacuumPressureChart_->updateLegend();

  tabWidget_->addTab(w, "Vacuum");

  w = new QWidget(tabWidget_);
  layout = new QVBoxLayout(w);

  U1Series_ = new ThermoDisplay2LineSeries();
  U1Series_->setName("U1");
  U2Series_ = new ThermoDisplay2LineSeries();
  U2Series_->setName("U2");
  U3Series_ = new ThermoDisplay2LineSeries();
  U3Series_->setName("U3");

  UChart_ = new ThermoDisplay2VoltageChart();
  UChart_->addSeries(U1Series_);
  UChart_->addSeries(U2Series_);
  UChart_->addSeries(U3Series_);

  UChartView_ = new ThermoDisplay2VoltageChartView(UChart_);
  UChartView_->setRenderHint(QPainter::Antialiasing);
  UChartView_->setMinimumSize(800, 300);
  layout->addWidget(UChartView_);
  UChart_->connectMarkers();
  UChart_->updateLegend();

  I1Series_ = new ThermoDisplay2LineSeries();
  I1Series_->setName("I1");
  I2Series_ = new ThermoDisplay2LineSeries();
  I2Series_->setName("I2");
  I3Series_ = new ThermoDisplay2LineSeries();
  I3Series_->setName("I3");

  IChart_ = new ThermoDisplay2CurrentChart();
  IChart_->addSeries(I1Series_);
  IChart_->addSeries(I2Series_);
  IChart_->addSeries(I3Series_);

  IChartView_ = new ThermoDisplay2CurrentChartView(IChart_);
  IChartView_->setRenderHint(QPainter::Antialiasing);
  IChartView_->setMinimumSize(800, 300);
  layout->addWidget(IChartView_);
  IChart_->connectMarkers();
  IChart_->updateLegend();

  tabWidget_->addTab(w, "Power");

  w = new QWidget(tabWidget_);
  layout = new QVBoxLayout(w);

  for (unsigned int card = 0;card<2;++card) {

    TChart_[card] = new ThermoDisplay2TemperatureChart();

    for (unsigned int channel = 0;channel<10;++channel) {
      unsigned int sensor = (card+1)*100 + channel + 1;
      TSeries_[card][channel] = new ThermoDisplay2LineSeries();
      TSeries_[card][channel]->setName(QString("T%1").arg(sensor));

      TChart_[card]->addSeries(TSeries_[card][channel]);
    }

    TChartView_[card] = new ThermoDisplay2TemperatureChartView(TChart_[card]);
    TChartView_[card]->setRenderHint(QPainter::Antialiasing);
    TChartView_[card]->setMinimumSize(800, 300);
    layout->addWidget(TChartView_[card]);
    TChart_[card]->connectMarkers();
    TChart_[card]->updateLegend();
  }

  tabWidget_->addTab(w, "Temperature");

  client_ = new ThermoDAQ2Client(config->getValue<unsigned int>("ServerPort"));
  reader_ = new ThermoDAQ2NetworkReader(this);

  QObject::connect(client_, SIGNAL(handleMessage(QString&)),
                   reader_, SLOT(run(QString&)));
  QObject::connect(reader_, SIGNAL(finished()),
                   this, SLOT(updateInfo()));

  setCentralWidget(tabWidget_);

  /*
  QPalette pal = palette();
  QColor color = pal.color(QPalette::Window);
  if (color.lightnessF()<0.4) {
    ChillerTSChart_->setTheme(QChart::ChartThemeDark);
    UChart_->setTheme(QChart::ChartThemeDark);
    IChart_->setTheme(QChart::ChartThemeDark);
    TChart_[0]->setTheme(QChart::ChartThemeDark);
    TChart_[1]->setTheme(QChart::ChartThemeDark);
  }
  */

  requestData();

  timer_ = new QTimer(this);
  connect(timer_, SIGNAL(timeout()),
          this, SLOT(requestData()));
  timer_->setSingleShot(false);
  timer_->start(5000);
}

void ThermoDisplay2MainWindow::clearData()
{
  ChillerTSChart_->clearData();
  ChillerPPChart_->clearData();
  VacuumPressureChart_->clearData();
  UChart_->clearData();
  IChart_->clearData();
  TChart_[0]->clearData();
  TChart_[1]->clearData();
}

void ThermoDisplay2MainWindow::savePlots()
{
  QDateTime dt = QDateTime::currentDateTime();

  ApplicationConfig* config = ApplicationConfig::instance();

  QString startDir = config->getValue<std::string>("PlotSaveDirectory").c_str();

  QString dir = QFileDialog::getExistingDirectory(this, "Save Directory",
                                                  startDir,
                                                  QFileDialog::ShowDirsOnly);

  if (dir.isEmpty()) return;

  int currentTab = tabWidget_->currentIndex();
  for (int idx=0;idx<4;++idx) {
    if (idx!=currentTab) tabWidget_->setCurrentIndex(idx);
  }
  tabWidget_->setCurrentIndex(currentTab);

  config->setValue("PlotSaveDirectory", dir);
  config->safe(std::string(Config::CMSTkModLabBasePath) + "/thermo/thermo2/thermo2.cfg");

  QApplication::processEvents();

  {
    auto dpr = 2.0*ChillerTSChartView_->devicePixelRatioF();
    QPixmap buffer(ChillerTSChartView_->width() * dpr,
                   ChillerTSChartView_->height() * dpr);
    buffer.fill(Qt::transparent);

    QPainter *painter = new QPainter(&buffer);
    painter->setPen(*(new QColor(255,34,255,255)));
    ChillerTSChartView_->render(painter);

    QFile file(dir + "/" + dt.toString("yyyy-MM-dd-hh-mm-ss") + "_thermo2_chillerTS.png");
    file.open(QIODevice::WriteOnly);
    buffer.save(&file, "PNG");
  }

  QApplication::processEvents();

  {
    auto dpr = 2.0*ChillerPPChartView_->devicePixelRatioF();
    QPixmap buffer(ChillerPPChartView_->width() * dpr,
                   ChillerPPChartView_->height() * dpr);
    buffer.fill(Qt::transparent);

    QPainter *painter = new QPainter(&buffer);
    painter->setPen(*(new QColor(255,34,255,255)));
    ChillerPPChartView_->render(painter);

    QFile file(dir + "/" + dt.toString("yyyy-MM-dd-hh-mm-ss") + "_thermo2_chillerPP.png");
    file.open(QIODevice::WriteOnly);
    buffer.save(&file, "PNG");
  }

  QApplication::processEvents();

  {
    auto dpr = 2.0*VacuumChartView_->devicePixelRatioF();
    QPixmap buffer(VacuumChartView_->width() * dpr,
                   VacuumChartView_->height() * dpr);
    buffer.fill(Qt::transparent);

    QPainter *painter = new QPainter(&buffer);
    VacuumChartView_->render(painter);

    QFile file(dir + "/" + dt.toString("yyyy-MM-dd-hh-mm-ss") + "_thermo2_vacuum.png");
    file.open(QIODevice::WriteOnly);
    buffer.save(&file, "PNG");
  }

  QApplication::processEvents();

  {
    auto dpr = 2.0*UChartView_->devicePixelRatioF();
    QPixmap buffer(UChartView_->width() * dpr,
                   UChartView_->height() * dpr);
    buffer.fill(Qt::transparent);

    QPainter *painter = new QPainter(&buffer);
    painter->setPen(*(new QColor(255,34,255,255)));
    UChartView_->render(painter);

    QFile file(dir + "/" + dt.toString("yyyy-MM-dd-hh-mm-ss") + "_thermo2_voltage.png");
    file.open(QIODevice::WriteOnly);
    buffer.save(&file, "PNG");
  }

  QApplication::processEvents();

  {
    auto dpr = 2.0*IChartView_->devicePixelRatioF();
    QPixmap buffer(IChartView_->width() * dpr,
                   IChartView_->height() * dpr);
    buffer.fill(Qt::transparent);

    QPainter *painter = new QPainter(&buffer);
    painter->setPen(*(new QColor(255,34,255,255)));
    IChartView_->render(painter);

    QFile file(dir + "/" + dt.toString("yyyy-MM-dd-hh-mm-ss") + "_thermo2_current.png");
    file.open(QIODevice::WriteOnly);
    buffer.save(&file, "PNG");
  }

  QApplication::processEvents();

  {
    auto dpr = 2.0*TChartView_[0]->devicePixelRatioF();
    QPixmap buffer(TChartView_[0]->width() * dpr,
                   TChartView_[0]->height() * dpr);
    buffer.fill(Qt::transparent);

    QPainter *painter = new QPainter(&buffer);
    painter->setPen(*(new QColor(255,34,255,255)));
    TChartView_[0]->render(painter);

    QFile file(dir + "/" + dt.toString("yyyy-MM-dd-hh-mm-ss") + "_thermo2_temperatures1.png");
    file.open(QIODevice::WriteOnly);
    buffer.save(&file, "PNG");
  }

  QApplication::processEvents();

  {
    auto dpr = 2.0*TChartView_[1]->devicePixelRatioF();
    QPixmap buffer(TChartView_[1]->width() * dpr,
                   TChartView_[1]->height() * dpr);
    buffer.fill(Qt::transparent);

    QPainter *painter = new QPainter(&buffer);
    painter->setPen(*(new QColor(255,34,255,255)));
    TChartView_[1]->render(painter);

    QFile file(dir + "/" + dt.toString("yyyy-MM-dd-hh-mm-ss") + "_thermo2_temperatures2.png");
    file.open(QIODevice::WriteOnly);
    buffer.save(&file, "PNG");
  }
}

void ThermoDisplay2MainWindow::requestData()
{
  NQLogDebug("ThermoDisplay2MainWindow") << "requestData()";
  client_->readDAQStatus();
}

void ThermoDisplay2MainWindow::updateInfo()
{
  NQLogDebug("ThermoDisplay2MainWindow") << "updateInfo()";

  const Measurement_t& m = reader_->getMeasurement();

  {
    bool updateLegend = false;

    if (ChillerTBathSeries_->isEnabled()!=m.u525wState_) updateLegend = true;
    ChillerTBathSeries_->setEnabled(m.u525wState_);
    ChillerTReturnSeries_->setEnabled(m.u525wState_);
    ChillerTCWISeries_->setEnabled(m.u525wState_);
    ChillerTCWOSeries_->setEnabled(m.u525wState_);
    ChillerPowerSeries_->setEnabled(m.u525wState_);
    ChillerPressureSeries_->setEnabled(m.u525wState_);
    ChillerSTCSeries_->setEnabled(m.u525wState_);
    ChillerSCSeries_->setEnabled(m.u525wState_);
    ChillerTBathSeries_->append(m.dt.toMSecsSinceEpoch(), m.u525wBathTemperature_);
    ChillerTReturnSeries_->append(m.dt.toMSecsSinceEpoch(), m.u525wReturnTemperature_);
    ChillerTCWISeries_->append(m.dt.toMSecsSinceEpoch(), m.u525wCWInletTemperature_);
    ChillerTCWOSeries_->append(m.dt.toMSecsSinceEpoch(), m.u525wCWOutletTemperature_);
    ChillerPowerSeries_->append(m.dt.toMSecsSinceEpoch(), m.u525wPower_/1000.);
    ChillerPressureSeries_->append(m.dt.toMSecsSinceEpoch(), m.u525wPumpPressure_);
    ChillerSTCSeries_->append(m.dt.toMSecsSinceEpoch(), m.u525wTemperatureControlEnabled_);
    ChillerSCSeries_->append(m.dt.toMSecsSinceEpoch(), m.u525wCirculatorEnabled_);

    if (updateLegend) {
      ChillerTSChart_->updateLegend();
      ChillerPPChart_->updateLegend();
    }
  }

  {
    bool updateLegend = false;

    NQLogDebug("ThermoDisplay2MainWindow") << "updateInfo() " << m.leyboldState_;
    NQLogDebug("ThermoDisplay2MainWindow") << "updateInfo() " << m.leyboldPressure_;

    if (VacuumPressureSeries_->isEnabled()!=m.leyboldState_) updateLegend = true;
    VacuumPressureSeries_->setEnabled(m.leyboldState_);
    VacuumPressureSeries_->append(m.dt.toMSecsSinceEpoch(), m.leyboldPressure_);

    if (updateLegend) {
      VacuumPressureChart_->updateLegend();
    }
  }

  {
    bool updateLegend = false;

    if (U1Series_->isEnabled()!=m.nge103BState[0]) updateLegend = true;
    U1Series_->setEnabled(m.nge103BState[0]);
    I1Series_->setEnabled(m.nge103BState[0]);
    U1Series_->append(m.dt.toMSecsSinceEpoch(), m.nge103BVoltage[0]);
    I1Series_->append(m.dt.toMSecsSinceEpoch(), m.nge103BCurrent[0]);

    if (U2Series_->isEnabled()!=m.nge103BState[1]) updateLegend = true;
    U2Series_->setEnabled(m.nge103BState[1]);
    I2Series_->setEnabled(m.nge103BState[1]);
    U2Series_->append(m.dt.toMSecsSinceEpoch(), m.nge103BVoltage[1]);
    I2Series_->append(m.dt.toMSecsSinceEpoch(), m.nge103BCurrent[1]);

    if (U3Series_->isEnabled()!=m.nge103BState[2]) updateLegend = true;
    U3Series_->setEnabled(m.nge103BState[2]);
    I3Series_->setEnabled(m.nge103BState[2]);
    U3Series_->append(m.dt.toMSecsSinceEpoch(), m.nge103BVoltage[2]);
    I3Series_->append(m.dt.toMSecsSinceEpoch(), m.nge103BCurrent[2]);

    if (updateLegend) {
      UChart_->updateLegend();
      IChart_->updateLegend();
    }
  }

  {
    for (unsigned int card = 0;card<2;++card) {
      bool updateLegend = false;
      for (unsigned int channel = 0;channel<10;++channel) {
        if (TSeries_[card][channel]->isEnabled()!=m.keithleyState[card][channel]) updateLegend = true;
        TSeries_[card][channel]->setEnabled(m.keithleyState[card][channel]);
        TSeries_[card][channel]->append(m.dt.toMSecsSinceEpoch(), m.keithleyTemperature[card][channel]);
      }
      if (updateLegend) TChart_[card]->updateLegend();
    }
  }

  ChillerTSChartView_->refreshAxes();
  ChillerPPChartView_->refreshAxes();
  VacuumChartView_->refreshAxes();
  UChartView_->refreshAxes();
  IChartView_->refreshAxes();
  TChartView_[0]->refreshAxes();
  TChartView_[1]->refreshAxes();
}
