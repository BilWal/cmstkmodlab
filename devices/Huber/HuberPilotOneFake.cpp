/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//               Copyright (C) 2011-2020 - The DESY CMS Group                  //
//                           All rights reserved                               //
//                                                                             //
//      The CMStkModLab source code is licensed under the GNU GPL v3.0.        //
//      You have the right to modify and/or redistribute this source code      //
//      under the terms specified in the license, which may be found online    //
//      at http://www.gnu.org/licenses or at License.txt.                      //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>

#include <iostream>
#include <string>

//#####################
// TODO:
// query error codes
//#####################

#include "HuberPilotOneFake.h"

HuberPilotOneFake::HuberPilotOneFake(const ioport_t ioPort)
 : VHuberPilotOne(ioPort)
{
  temperatureSetPoint_ = 20.0;
  externalTemperatureControl_ = false;
  temperatureControlEnabled_ = false;
  circulatorEnabled_ = false;
}

bool HuberPilotOneFake::SetTemperatureSetPoint(const float temperatureSetPoint)
{
  if (temperatureSetPoint_ > PilotOneUpperTempLimit ||
      temperatureSetPoint_ < PilotOneLowerTempLimit ) {
    std::cerr << " [HuberPilotOneFake::SetSetTemperatureSetPointWorkingTemp] ** ERROR: working temp T="
              << temperatureSetPoint_ << " exceeds soft limits." << std::endl;
    std::cerr << "  > (s. HuberPilotOneFake class definition)" << std::endl;
    return false;
  }

  std::cout << " [HuberPilotOneFake::SetTemperatureSetPoint] -- FAKE: Setting temperature setpoint = "
            << temperatureSetPoint << "." << std::endl;

  temperatureSetPoint_ = temperatureSetPoint;

  usleep(10000);

  return true;
}

float HuberPilotOneFake::GetTemperatureSetPoint()
{
  std::cout << " [HuberPilotOneFake::GetTemperatureSetPoint] -- FAKE: Returning T = "
            << temperatureSetPoint_ << std::endl;

  usleep(10000);

  return temperatureSetPoint_;
}

float HuberPilotOneFake::GetBathTemperature()
{
  float temp = temperatureSetPoint_;
  temp += normalDistribution_(randomGenerator_);
  return temp;
}

float HuberPilotOneFake::GetReturnTemperature()
{
  if (circulatorEnabled_) {
    return GetBathTemperature() + 2.0;
  } else {
    return GetBathTemperature();
  }
}

float HuberPilotOneFake::GetPumpPressure()
{
  return 1.3 + normalDistribution_(randomGenerator_);
}

int HuberPilotOneFake::GetPower()
{
  return 500 + 100*normalDistribution_(randomGenerator_);
}

bool HuberPilotOneFake::SetTemperatureControlMode(bool external)
{
  externalTemperatureControl_ = external;
  return true;
}

bool HuberPilotOneFake::GetTemperatureControlMode()
{
  return externalTemperatureControl_;
}

bool HuberPilotOneFake::SetTemperatureControlEnabled(bool enabled)
{
  temperatureControlEnabled_ = enabled;
  return true;
}

bool HuberPilotOneFake::GetTemperatureControlEnabled()
{
  return temperatureControlEnabled_;
}

bool HuberPilotOneFake::SetCirculatorEnabled(bool enabled)
{
  circulatorEnabled_ = enabled;
  return true;
}

bool HuberPilotOneFake::GetCirculatorEnabled()
{
  return circulatorEnabled_;
}

float HuberPilotOneFake::GetCoolingWaterInletTemperature()
{
  return 13.0 + 2.*normalDistribution_(randomGenerator_);
}

float HuberPilotOneFake::GetCoolingWaterOutletTemperature()
{
  float temp = GetCoolingWaterInletTemperature();
  if (temperatureControlEnabled_) temp += 1.0;
  if (circulatorEnabled_) temp += 2.0;
  return temp;
}

void HuberPilotOneFake::Device_Init()
{

}
