#
# Copyright (C) 2018-2020 QuasarApp.
# Distributed under the lgplv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

unix:exec = $$PWD/tests/build/release/Qt-SecretTest
win32:exec = $$PWD/tests/build/release/Qt-SecretTest.exe

QT_DIR = $$[QT_HOST_BINS]

win32:QMAKE_BIN = $$QT_DIR/qmake.exe

contains(QMAKE_HOST.os, Linux):{
    DEPLOYER=cqtdeployer
    QMAKE_BIN = $$QT_DIR/qmake

} else {
    DEPLOYER=$$(cqtdeployer)
}


!android:deployTest.commands = $$DEPLOYER -bin $$exec clear -qmake $$QMAKE_BIN -targetDir $$PWD/deployTests -libDir $$PWD -recursiveDepth 5

unix:!android:testRSA.commands = $$PWD/deployTests/Qt-SecretTest.sh
win32:testRSA.commands = $$PWD/deployTests/Qt-SecretTest.exe


test.depends += deployTest
test.depends += testRSA


QMAKE_EXTRA_TARGETS += \
    deployTest \
    testRSA \
    test
