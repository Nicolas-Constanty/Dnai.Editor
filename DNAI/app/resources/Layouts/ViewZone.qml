import QtQuick 2.0
import QtQuick.Controls 2.3

Rectangle {
    id: rootItem
    default property alias _contentChildren: _content.data
    property alias content: _content
    property int splitvalue: -1
    property Item prev: null
    property Item next: null
    property Splitter s: null
    clip: true

    function appendNextV()
    {
        var n = createbjects(rootItem.parent, "ViewZone.qml")
        n.anchors.top = n.parent.top
        n.anchors.bottom = n.parent.bottom
        n.color = "green"
        n.next = rootItem.next
        if (rootItem.next != null)
            rootItem.next.prev = n
        n.prev = rootItem
        rootItem.next = n
        var s
        if (n.prev !== null)
        {
            s = createbjects(rootItem.parent, "Splitter.qml")
            s.width = 17
            s.anchors.top = s.parent.top
            s.anchors.bottom = s.parent.bottom
            s.isVertical = true
            if (n.prev.s === null)
            {
                s.x = n.prev.x + n.prev.width / 2 - s.width / 2
                n.prev.s = s

                n.anchors.left = n.prev.s.horizontalCenter
                n.anchors.right = (n.next !== null && n.next.s !== null) ? n.next.s.horizontalCenter : rootItem.parent.right
                n.prev.anchors.right = n.prev.s.horizontalCenter
                n.prev.color = "green"
            }
            else
            {
                // c1  c2 => c1  c3  c2
                //   s1        s1  s2
                n.s = s
                n.s.x = n.prev.s.x
                n.prev.s.x = n.prev.x + n.prev.width / 2 - s.width / 2
                //c1
                n.prev.anchors.right = n.prev.s.horizontalCenter
                //c2
                n.anchors.left = n.prev.s.horizontalCenter
                n.anchors.right = n.s.horizontalCenter
                //c3
                n.next.anchors.left = n.s.horizontalCenter
            }
            for (var i = 0; i < _content.children.length; i++)
            {
                if (_content.children[i] !== undefined)
                    _content.children[i].parent = n.content
            }
        }
    }
/*



  C1 -> C2  -> C3 -> C4
   S1


  */
    function appendPrevV()
    {
        var n = createbjects(rootItem.parent, "ViewZone.qml")
        n.anchors.top = n.parent.top
        n.anchors.bottom = n.parent.bottom
        n.color = "green"
        n.prev = rootItem.prev
        if (rootItem.prev != null)
            rootItem.prev.next = n
        n.next = rootItem
        rootItem.prev = n
        var s
        if (n.next !== null)
        {
            s = createbjects(rootItem.parent, "Splitter.qml")
            s.width = 17
            s.anchors.top = s.parent.top
            s.anchors.bottom = s.parent.bottom
            s.isVertical = true
            if (n.prev && n.prev.s === null)
            {
                s.x = n.prev.x + n.prev.width / 2 - s.width / 2
                n.prev.s = s

                n.anchors.left = (n.prev.prev !== null && n.prev.prev.s !== null) ? n.prev.prev.s.horizontalCenter : rootItem.parent.left
                n.anchors.right = n.prev.s.horizontalCenter
            }
            else
            {

                // c1  c2 => c3  c1  c2
                //   s1        s1  s2
                s.x = s.x = n.next.x + n.next.width / 2 - s.width / 2
                n.s = s
                //c1
                n.next.anchors.left = n.s.horizontalCenter
                //c2
                n.anchors.left = (n.prev !== null && n.prev.s !== null) ? n.prev.s.horizontalCenter : rootItem.parent.left
                n.anchors.right = n.s.horizontalCenter
            }
            for (var i = 0; i < _content.children.length; i++)
            {
                if (_content.children[i] !== undefined)
                    _content.children[i].parent = n.content
            }
        }
    }

    function appendNextH()
    {
        var n = createbjects(rootItem.parent, "ViewZone.qml")
        n.anchors.left = n.parent.left
        n.anchors.right = n.parent.right
        n.color = "green"
        n.next = rootItem.next
        if (rootItem.next != null)
            rootItem.next.prev = n
        n.prev = rootItem
        rootItem.next = n
        var s
        if (n.prev !== null)
        {
            s = createbjects(rootItem.parent, "Splitter.qml")
            s.height = 17
            s.anchors.left = s.parent.left
            s.anchors.right = s.parent.right
            s.isVertical = false
            if (n.prev.s === null)
            {
                s.y = n.prev.y + n.prev.height / 2 - s.height / 2
                n.prev.s = s

                n.anchors.top = n.prev.s.verticalCenter
                n.anchors.bottom = (n.next !== null && n.next.s !== null) ? n.next.s.verticalCenter : rootItem.parent.bottom
                n.prev.anchors.bottom = n.prev.s.verticalCenter
                n.prev.color = "green"
            }
            else
            {
                // c1  c2 => c1  c3  c2
                //   s1        s1  s2
                n.s = s
                n.s.y = n.prev.s.y
                n.prev.s.y = n.prev.y + n.prev.height / 2 - s.height / 2
                //c1
                n.prev.anchors.bottom = n.prev.s.verticalCenter
                //c2
                n.anchors.top = n.prev.s.verticalCenter
                n.anchors.bottom = n.s.verticalCenter
                //c3
                n.next.anchors.top = n.s.verticalCenter
            }
            for (var i = 0; i < _content.children.length; i++)
            {
                if (_content.children[i] !== undefined)
                    _content.children[i].parent = n.content
            }
        }
    }

    function appendPrevH()
    {
        var n = createbjects(rootItem.parent, "ViewZone.qml")
        n.anchors.left = n.parent.left
        n.anchors.right = n.parent.right
        n.color = "green"
        n.prev = rootItem.prev
        if (rootItem.prev != null)
            rootItem.prev.next = n
        n.next = rootItem
        rootItem.prev = n
        var s
        if (n.next !== null)
        {
            s = createbjects(rootItem.parent, "Splitter.qml")
            s.height = 17
            s.anchors.right = s.parent.right
            s.anchors.left = s.parent.left
            s.isVertical = false
            if (n.prev && n.prev.s === null)
            {
                s.y = n.prev.y + n.prev.height / 2 - s.height / 2
                n.prev.s = s

                n.anchors.top = (n.prev.prev !== null && n.prev.prev.s !== null) ? n.prev.prev.s.verticalCenter : rootItem.parent.top
                n.anchors.bottom = n.prev.s.verticalCenter
            }
            else
            {

                // c1  c2 => c3  c1  c2
                //   s1        s1  s2
                s.y = s.y = n.next.y + n.next.height / 2 - s.height / 2
                n.s = s
                //c1
                n.next.anchors.top = n.s.verticalCenter
                //c2
                n.anchors.top = (n.prev !== null && n.prev.s !== null) ? n.prev.s.verticalCenter : rootItem.parent.top
                n.anchors.bottom = n.s.verticalCenter
            }
            for (var i = 0; i < _content.children.length; i++)
            {
                if (_content.children[i] !== undefined)
                    _content.children[i].parent = n.content
            }
        }
    }

    function createbjects(parentItem, path) {
        var comp = Qt.createComponent(path);
        var view = comp.createObject(parentItem, {});

        if (view === null) {
            // Error Handling
            console.log("Error creating object");
        }
        return view
    }
    function split(direction, w, h)
    {
        if (direction === 0)
            splitLeft(w, h)
        else if (direction === 1)
            splitRight(w, h)
        else if (direction === 2)
            splitTop(w, h)
        else if (direction === 3)
            splitBottom(w, h)
    }

    function splitVertical(w)
    {
        var v1 = createbjects(rootItem, "ViewZone.qml")
        var v2 = createbjects(rootItem, "ViewZone.qml")
        var splitter = createbjects(rootItem, "Splitter.qml")

        splitter.width = 17
        splitter.anchors.top = splitter.parent.top
        splitter.anchors.bottom = splitter.parent.bottom
        splitter.x = w / 2 - splitter.width / 2
        splitter.isVertical = true

        v1.anchors.top = v1.parent.top
        v1.anchors.bottom = v1.parent.bottom
        v1.anchors.left = v1.parent.left
        v1.anchors.right = splitter.horizontalCenter
        v1.s = splitter
        v1.next = v2
        v1.color = "yellow"

        v2.anchors.top = v2.parent.top
        v2.anchors.bottom = v2.parent.bottom
        v2.anchors.left = splitter.horizontalCenter
        v2.anchors.right = v2.parent.right
        v2.color = "gray"
        v2.prev = v1
        rootItem.splitvalue = 1
        return [v1, v2]
    }

    function splitHorizontal(h)
    {
        var v1 = createbjects(rootItem, "ViewZone.qml")
        var v2 = createbjects(rootItem, "ViewZone.qml")
        var splitter = createbjects(rootItem, "Splitter.qml")

        splitter.height = 17
        splitter.anchors.right = splitter.parent.right
        splitter.anchors.left = splitter.parent.left
        splitter.y = h / 2 - splitter.height / 2
        splitter.isVertical = false

        v1.anchors.right = v1.parent.right
        v1.anchors.left = v1.parent.left
        v1.anchors.top = v1.parent.top
        v1.anchors.bottom = splitter.verticalCenter
        v1.s = splitter
        v1.next = v2
        v1.color = "gray"

        v2.anchors.right = v2.parent.right
        v2.anchors.left = v2.parent.left
        v2.anchors.top = splitter.verticalCenter
        v2.anchors.bottom = v2.parent.bottom
        v2.prev = v1
        v2.color = "gray"
        rootItem.splitvalue = 2
        return [v1, v2]
    }

//    function appendLeft()
//    {

//    }

    function splitLeft(w, h)
    {
        if (rootItem.parent.splitvalue !== 1)
        {
            var tab = splitVertical(w)
            for (var i = 0; i < _content.children.length; i++)
            {
                if (_content.children[i] !== undefined)
                    _content.children[i].parent = tab[0].content
            }
        }
        else
            appendPrevV()
    }

    function splitRight(w, h)
    {
        if (rootItem.parent.splitvalue !== 1)
        {
            var tab = splitVertical(w)
            for (var i = 0; i < _content.children.length; i++)
            {
                if (_content.children[i] !== undefined)
                    _content.children[i].parent = tab[1].content
            }
        }
        else
            appendNextV()
    }

    function splitTop(w, h)
    {
        if (rootItem.parent.splitvalue !== 2)
        {
            var tab = splitHorizontal(h)
            for (var i = 0; i < _content.children.length; i++)
            {
                if (_content.children[i] !== undefined)
                    _content.children[i].parent = tab[0].content
            }
        }
        else
            appendPrevH()
    }

    function splitBottom(w, h)
    {
        if (rootItem.parent.splitvalue !== 2)
        {
            var tab = splitHorizontal(h)
            for (var i = 0; i < _content.children.length; i++)
            {
                if (_content.children[i] !== undefined)
                    _content.children[i].parent = tab[1].content
            }
        }
        else
            appendNextH()
    }
    MouseArea {
        id: ma
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            if(mouse.button & Qt.RightButton) {
                contextMenu.popup()
            }
        }
    }
    Menu {
        id: contextMenu
        MenuItem {
            text: "SplitLeft"
            onClicked: {
//                appendNextV()
                split(0, rootItem.width, rootItem.height)
            }
        }
        MenuItem {
            text: "SplitRight"
            onClicked: {
                split(1, rootItem.width, rootItem.height)
            }
        }
        MenuItem {
            text: "SplitTop"
            onClicked: {
                split(2, rootItem.width, rootItem.height)
            }
        }
        MenuItem {
            text: "SplitBottom"
            onClicked: {
                split(3, rootItem.width, rootItem.height)
            }
        }
    }
    Item {
        id: _content
        anchors.fill: parent
    }

    onXChanged: {
        if (rootItem.prev !== null && rootItem.prev.s !== null)
        {
            var rp = rootItem.prev;

            rp.s.updateMinX(rp.x)
            rp.s.updateMaxX((rootItem.next !== null && rootItem.s !== null) ? rootItem.next.x : rootItem.parent.width)
        }
    }

    onYChanged: {
        if (rootItem.prev !== null && rootItem.prev.s !== null)
        {
            var rp = rootItem.prev;

            rp.s.updateMinY(rp.y)
            rp.s.updateMaxY((rootItem.next !== null && rootItem.s !== null) ? rootItem.next.y : rootItem.parent.height)
        }
    }

}
