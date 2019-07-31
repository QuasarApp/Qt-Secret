import QtQuick 2.0
import QtQuick.Controls 2.12

Button {

    id: btn

    property string source: "../images/cpy.png"
    implicitWidth: 46
    implicitHeight: 46

    icon.source: btn.source
}
