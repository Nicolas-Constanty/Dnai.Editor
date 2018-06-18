function createCallBack(callback)
{
   var obj =Qt.createQmlObject('import QtQuick 2.0; Item { property var callback: null }', parent);
    obj.callback = callback
    return obj
}
