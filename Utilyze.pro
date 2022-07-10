
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT += qml quick bluetooth positioning
SOURCES += \
    Sources/bluetoothbaseclass.cpp \
    Sources/connectionhandler.cpp \
    Sources/devicefinder.cpp \
    Sources/devicehandler.cpp \
    Sources/deviceinfo.cpp \
    Sources/main.cpp

RESOURCES += qml.qrc \
    images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
ios {
    QMAKE_INFO_PLIST = $$files($$PWD/ios/Info.plist)
    ios_icon.files = $$files($$PWD/ios/AppIcon*.png)
    QMAKE_BUNDLE_DATA += ios_icon
}
macos: QMAKE_INFO_PLIST = $$files($$PWD/ios/Info.qmake.macos.plist)

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Headers/bluetoothbaseclass.h \
    Headers/connectionhandler.h \
    Headers/devicefinder.h \
    Headers/devicehandler.h \
    Headers/deviceinfo.h \
    Headers/roomnet.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,x86) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
