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

#ifndef THERMODISPLAY2MAINWINDOW_H
#define THERMODISPLAY2MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QTabWidget>

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

#include "ThermoDAQ2Client.h"
#include "ThermoDAQ2NetworkReader.h"

#include "ThermoDisplay2ChartView.h"
#include "ThermoDisplay2Chart.h"
#include "ThermoDisplay2LineSeries.h"

QT_CHARTS_USE_NAMESPACE

class ThermoDisplay2MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit ThermoDisplay2MainWindow(QWidget *parent = 0);

public slots:

  void requestData();
  void updateInfo();

  void clearData();
  void savePlots();

protected:

  QTimer* timer_;

  QTabWidget* tabWidget_;

  ThermoDAQ2Client* client_;
  ThermoDAQ2NetworkReader* reader_;

  ThermoDisplay2ChartView *ChillerTSChartView_;
  ThermoDisplay2TemperatureStateChart *ChillerTSChart_;
  ThermoDisplay2LineSeries *ChillerTBathSeries_;
  ThermoDisplay2LineSeries *ChillerTReturnSeries_;
  ThermoDisplay2LineSeries *ChillerTCWISeries_;
  ThermoDisplay2LineSeries *ChillerTCWOSeries_;
  ThermoDisplay2LineSeries *ChillerSTCSeries_;
  ThermoDisplay2LineSeries *ChillerSCSeries_;

  ThermoDisplay2ChartView *ChillerPPChartView_;
  ThermoDisplay2PowerPressureChart *ChillerPPChart_;
  ThermoDisplay2LineSeries *ChillerPowerSeries_;
  ThermoDisplay2LineSeries *ChillerPressureSeries_;

  ThermoDisplay2ChartView *VacuumChartView_;
  ThermoDisplay2PressureChart *VacuumPressureChart_;
  ThermoDisplay2LineSeries *VacuumPressureSeries_;

  ThermoDisplay2ChartView *UChartView_;
  ThermoDisplay2VoltageChart *UChart_;
  ThermoDisplay2LineSeries *U1Series_;
  ThermoDisplay2LineSeries *U2Series_;
  ThermoDisplay2LineSeries *U3Series_;

  ThermoDisplay2ChartView *IChartView_;
  ThermoDisplay2CurrentChart *IChart_;
  ThermoDisplay2LineSeries *I1Series_;
  ThermoDisplay2LineSeries *I2Series_;
  ThermoDisplay2LineSeries *I3Series_;

  ThermoDisplay2ChartView *TChartView_[2];
  ThermoDisplay2TemperatureChart *TChart_[2];
  ThermoDisplay2LineSeries *TSeries_[2][10];
};

#endif // THERMODISPLAY2MAINWINDOW_H
