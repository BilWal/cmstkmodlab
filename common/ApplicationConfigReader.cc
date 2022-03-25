/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//               Copyright (C) 2011-2017 - The DESY CMS Group                  //
//                           All rights reserved                               //
//                                                                             //
//      The CMStkModLab source code is licensed under the GNU GPL v3.0.        //
//      You have the right to modify and/or redistribute this source code      //
//      under the terms specified in the license, which may be found online    //
//      at http://www.gnu.org/licenses or at License.txt.                      //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <sstream>
#include <iomanip>

#include <QMessageBox>

#include "ApplicationConfigReader.h"

ApplicationConfigReader::ApplicationConfigReader( const std::string & inputFileName )
{
  inputFileName_ = std::string( inputFileName );
}

ApplicationConfigReader::~ApplicationConfigReader()
{
}

void ApplicationConfigReader::fill(ApplicationConfig::storage_t &keyvalueMap,
    ApplicationConfig::configfile_t &configFileKeyMap)
{
  std::ifstream file(inputFileName_.c_str(), std::ios::in);

  if (!file.good()) {
    std::cerr << " [ApplicationConfigReader::openAndCheckFile] ** ERROR: failed to open file: " << inputFileName_ << "." << std::endl;

    QMessageBox::critical(0, tr("[ApplicationConfigReader::fill]"),
        QString("Failed to open configuration file: \"%1\". No chance!").arg(QString(inputFileName_.c_str())),
        QMessageBox::Abort
    );

    throw; // must abort
  }

  std::string Key;
  std::string Value;
  std::vector<std::string> Values;
  std::string buffer;

  while (std::getline(file, buffer)) {
    // ignore all characters after (and including) hashtag
    if (buffer.find("#") != std::string::npos) {
      buffer = buffer.substr(0, buffer.find("#"));
    }

    if (buffer.empty()) continue;

    std::istringstream iss(buffer.c_str(), std::istringstream::in);
    iss >> Key;
    Values.clear();
    while (iss >> std::quoted(Value)) {
      Values.push_back(Value);
    }
    keyvalueMap[Key] = Values;
    configFileKeyMap.insert({ inputFileName_, Key });
  }

  file.close();
}
