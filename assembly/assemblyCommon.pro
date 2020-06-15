ARCHITECTURE=Linux
USEFAKEDEVICES="X1"
NOUEYE="X1"

LIBS += -L/home/ntonon/Postdoc/PS_Assembly/code/cmstkmodlab/devices/lib -lTkModLabLang
LIBS += -L/home/ntonon/Postdoc/PS_Assembly/code/cmstkmodlab/devices/lib -lTkModLabConrad
LIBS += -L/home/ntonon/Postdoc/PS_Assembly/code/cmstkmodlab/devices/lib -lTkModLabArduino
LIBS += -L/home/ntonon/Postdoc/PS_Assembly/code/cmstkmodlab/devices/lib -lTkModLabKeyence
LIBS += -L/home/ntonon/Postdoc/PS_Assembly/code/cmstkmodlab/common -lCommon

QMAKE_CXXFLAGS += -pthread -std=c++1z -m64 -I/home/ntonon/Documents/Programmes/myBuild_root-6.18.04_c++17/include
LIBS += -L/home/ntonon/Documents/Programmes/myBuild_root-6.18.04_c++17/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic

equals(USEFAKEDEVICES,"X1") {
  NOUEYE="X1"
}

macx {
  NOUEYE="X1"
  CONFIG+=x86_64
  
  #QMAKE_CXXFLAGS += -stdlib=libc++

  #QMAKE_MAC_SDK = macosx10.11
  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11
  #LIBS += -framework AppKit
  #LIBS += -framework QuartzCore
  #LIBS += -framework QTKit
  #LIBS += -framework Cocoa
}

equals(NOUEYE,"X0") {
  LIBS += -lueye_api
}

CONFIG += link_pkgconfig
PKGCONFIG += opencv

QMAKE = qmake-qt4

QMAKE_CXXFLAGS += -std=c++17

macx {
  QMAKE_CXXFLAGS += -DAPPLICATIONVERSIONSTR=\\\"unknown\\\"
}
else {
  QMAKE_CXXFLAGS += -DAPPLICATIONVERSIONSTR=\\\"`git describe --dirty --always --tags`\\\"
}

DEFINES +=  USE_FAKEIO NOUEYE
equals(NOUEYE,"X1") {
  DEFINES += NOUEYE
}

QT += core gui xml network script svg
greaterThan(QT_MAJOR_VERSION, 4) {
  QT += widgets
} 

TARGET = AssemblyCommon
TEMPLATE = lib

macx {
  QMAKE_POST_LINK = install_name_tool -change libCommon.1.dylib /home/ntonon/Postdoc/PS_Assembly/code/cmstkmodlab/common/libCommon.1.dylib $(TARGET)
}

DEPENDPATH += /home/ntonon/Postdoc/PS_Assembly/code/cmstkmodlab/common
INCLUDEPATH += .
INCLUDEPATH += ..
INCLUDEPATH += /home/ntonon/Postdoc/PS_Assembly/code/cmstkmodlab
INCLUDEPATH += /home/ntonon/Postdoc/PS_Assembly/code/cmstkmodlab/common

greaterThan(QT_MAJOR_VERSION, 4) {
  cache()
}

# Input
HEADERS += AssemblyVUEyeCamera.h \
           AssemblyVUEyeModel.h \
           AssemblyUEyeWidget.h \
           AssemblyUEyeCameraWidget.h \
           AssemblyUEyeCameraThread.h \
           AssemblyUEyeView.h \
           AssemblyUEyeSnapShooter.h \
           AssemblyZFocusFinder.h \
           AssemblyImageController.h \
           AssemblyImageView.h \
           AssemblyThresholder.h \
           AssemblyThresholderView.h \
           AssemblyObjectFinderPatRec.h \
           AssemblyObjectFinderPatRecWidget.h \
           AssemblyObjectFinderPatRecView.h \
           AssemblyObjectFinderPatRecThread.h \
           AssemblyObjectAligner.h \
           AssemblyObjectAlignerView.h \
           AssemblyAssembly.h \
           AssemblyAssemblyView.h \
           AssemblyMultiPickupTester.h \
           AssemblyMultiPickupTesterWidget.h \
           AssemblyPositionsRegistryWidget.h \
           AssemblyToolboxView.h \
           AssemblySmartMotionManager.h \
           AssemblyParameters.h \
           AssemblyParametersView.h \
           AssemblyVacuumWidget.h \
           AssemblyMotionWidgets.h \
           AssemblyHardwareControlView.h \
           AssemblyLogFileController.h \
           AssemblyLogFileView.h \
           ConradManager.h \
           LStepExpressModel.h \
           LStepExpressMotion.h \
           LStepExpressMotionManager.h \
           LStepExpressMotionView.h \
           LStepExpressMotionThread.h \
           LStepExpressWidget.h \
           LStepExpressJoystickWidget.h \
           LStepExpressSettings.h \
           LStepExpressSettingsWidget.h \
           LStepExpressMeasurement.h \
           LStepExpressMeasurementWidget.h \
           LStepExpressMeasurementTable.h \
           LStepExpressPositionWidget.h \
           LStepExpressStatusWindow.h \
           LaserModel.h \
           LaserThread.h \
           LaserWidget.h \
           LaserControlsWidget.h \
           AssemblyUtilities.h

equals(NOUEYE,"X0") {
HEADERS += AssemblyUEyeCamera.h \
           AssemblyUEyeModel.h
} else {
HEADERS += AssemblyUEyeFakeCamera.h \
           AssemblyUEyeFakeModel.h
}

SOURCES += AssemblyVUEyeCamera.cc \
           AssemblyVUEyeModel.cc \
           AssemblyUEyeWidget.cc \
           AssemblyUEyeCameraWidget.cc \
           AssemblyUEyeCameraThread.cc \
           AssemblyUEyeView.cc \
           AssemblyUEyeSnapShooter.cc \
           AssemblyZFocusFinder.cc \
           AssemblyImageController.cc \
           AssemblyImageView.cc \
           AssemblyThresholder.cc \
           AssemblyThresholderView.cc \
           AssemblyObjectFinderPatRec.cc \
           AssemblyObjectFinderPatRecWidget.cc \
           AssemblyObjectFinderPatRecView.cc \
           AssemblyObjectFinderPatRecThread.cc \
           AssemblyObjectAligner.cc \
           AssemblyObjectAlignerView.cc \
           AssemblyAssembly.cc \
           AssemblyAssemblyView.cc \
           AssemblyMultiPickupTester.cc \
           AssemblyMultiPickupTesterWidget.cc \
           AssemblyPositionsRegistryWidget.cc \
           AssemblyToolboxView.cc \
           AssemblySmartMotionManager.cc \
           AssemblyParameters.cc \
           AssemblyParametersView.cc \
           AssemblyVacuumWidget.cc \
           AssemblyMotionWidgets.cc \
           AssemblyHardwareControlView.cc \
           AssemblyLogFileController.cc \
           AssemblyLogFileView.cc \
           ConradManager.cc \
           LStepExpressModel.cc \
           LStepExpressMotion.cc \
           LStepExpressMotionManager.cc \
           LStepExpressMotionView.cc \
           LStepExpressMotionThread.cc \
           LStepExpressWidget.cc \
           LStepExpressJoystickWidget.cc \
           LStepExpressSettings.cc \
           LStepExpressSettingsWidget.cc \
           LStepExpressMeasurement.cc \
           LStepExpressMeasurementWidget.cc \
           LStepExpressMeasurementTable.cc \
           LStepExpressPositionWidget.cc \
           LStepExpressStatusWindow.cc \
           LaserModel.cc \
           LaserWidget.cc \
           LaserThread.cc \
           LaserControlsWidget.cc \
           AssemblyUtilities.cc

equals(NOUEYE,"X0") {
SOURCES += AssemblyUEyeCamera.cc \
           AssemblyUEyeModel.cc
} else {
SOURCES += AssemblyUEyeFakeCamera.cc \
           AssemblyUEyeFakeModel.cc
}
