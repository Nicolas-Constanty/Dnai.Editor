var component;
var object;
var shape
var parent

function createObjects(path, sh, p) {
    shape = sh
    parent = p
    if (parent == null)
        parent = appWindow
    component = Qt.createComponent("../../" + path);
    if (component.status == Component.Ready)
        finishCreation();
    else
        component.statusChanged.connect(finishCreation);
    return object
}

function finishCreation() {
    if (component.status == Component.Ready) {
        object = component.createObject(parent, shape);
        if (object == null) {
            // Error Handling
            console.info("Error creating object");
        }
        return object
    } else if (component.status == Component.Error) {
        // Error Handling
        console.info("Error loading component:", component.errorString());
    }
    console.info("Fail")
}

function getObject() {
    return object
}
