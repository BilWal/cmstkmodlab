/////////////////////////////////////////////////////////////////////////////////
//                                                                             //
//               Copyright (C) 2011-2022 - The DESY CMS Group                  //
//                           All rights reserved                               //
//                                                                             //
//      The CMStkModLab source code is licensed under the GNU GPL v3.0.        //
//      You have the right to modify and/or redistribute this source code      //
//      under the terms specified in the license, which may be found online    //
//      at http://www.gnu.org/licenses or at License.txt.                      //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <QtGlobal>

#include <nqlogger.h>
#include <ApplicationConfig.h>

#include "ApplicationConfigItemModel.h"

ApplicationConfigItemModel::ApplicationConfigItemModel(bool readOnly, QObject *parent)
  : QAbstractTableModel(parent),
    isReadOnly_(readOnly)
{
  NQLog("ApplicationConfigItemModel", NQLog::Debug) << "ApplicationConfigItemModel(QObject *parent)";

  ApplicationConfig* config = ApplicationConfig::instance();

  connect(config, SIGNAL(structureChanged()),
      this, SLOT(structureChanged()));

  structureChanged();
}

void ApplicationConfigItemModel::structureChanged()
{
  NQLog("ApplicationConfigItemModel", NQLog::Debug) << "structureChanged()";

  ApplicationConfig* config = ApplicationConfig::instance();

  keys_.clear();

  for (ApplicationConfig::storage_t::const_iterator it=config->getKeyValueMap().begin();
      it!=config->getKeyValueMap().end();
      ++it) {
    std::string key = it->first;

    std::size_t idx = 0;
    for (auto & s : it->second) {
      keys_.push_back(std::make_pair(key, idx));
      idx++;
    }
  }

  emit keysChanged();
}

int ApplicationConfigItemModel::rowCount(const QModelIndex & parent) const
{
  return keys_.size();
}

int ApplicationConfigItemModel::columnCount(const QModelIndex & parent) const
{
  return 3;
}

QVariant ApplicationConfigItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    if (section==0) {
      return QString("Key");
    } else if (section==1) {
      return QString("Index");
    } else {
      return QString("Value");
    }
  }
  return QVariant();
}

QVariant ApplicationConfigItemModel::data(const QModelIndex &index, int role) const
{
  ApplicationConfig* config = ApplicationConfig::instance();

  if (role == Qt::DisplayRole) {

    if (index.column()==0) {

      return keys_[index.row()].first.c_str();

    } else if (index.column()==1) {

      return QVariant((unsigned int)keys_[index.row()].second);

    }

    std::string key = keys_[index.row()].first;
    std::size_t idx = keys_[index.row()].second;

    return QString(config->getValueByIndex(key, idx).c_str());
  }

  if (role == Qt::TextAlignmentRole) {

    if (index.column()==1) {

      return int(Qt::AlignCenter | Qt::AlignVCenter);

    } else {

      return int(Qt::AlignLeft | Qt::AlignVCenter);

    }
  }

  if (role == Qt::EditRole) {
    std::string key = keys_[index.row()].first;
    std::size_t idx = keys_[index.row()].second;

    return QString(config->getValueByIndex(key, idx).c_str());
  }

  return QVariant();
}

bool ApplicationConfigItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  ApplicationConfig* config = ApplicationConfig::instance();

  if (role == Qt::EditRole) {

#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
    if (!checkIndex(index))
      return false;
#endif
    
    std::string key = keys_[index.row()].first;
    std::size_t idx = keys_[index.row()].second;

    std::string oldValue = config->getValueByIndex(key, idx);
    std::string newValue = value.toString().toStdString();

    if (newValue!=oldValue) {
      config->setValueByIndex(key, idx, newValue);
    }

    return true;
  }
  return false;
}

Qt::ItemFlags ApplicationConfigItemModel::flags(const QModelIndex &index) const
{
  if (!isReadOnly_ && index.column()==2) {
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
  }

  return QAbstractTableModel::flags(index);
}
