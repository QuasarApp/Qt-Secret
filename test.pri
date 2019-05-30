unix:exec = $$PWD/Stests/build/release/Qt-SecretTest
win32:exec = $$PWD/Stests/build/release/Qt-SecretTest.exe


contains(QMAKE_HOST.os, Linux):{
    DEPLOYER=cqtdeployer
} else {
    DEPLOYER=%cqtdeployer%
}

deployTest.commands = $$DEPLOYER -bin $$exec clear -qmake $$QMAKE_QMAKE -targetDir $$PWD/deployTests -libDir $$PWD -recursiveDepth 5

test.depends = deployTest
unix:test.commands = $$PWD/deployTests/serverTests.sh
win32:test.commands = $$PWD/deployTests/serverTests.exe

QMAKE_EXTRA_TARGETS += \
    deployTest \
    test
