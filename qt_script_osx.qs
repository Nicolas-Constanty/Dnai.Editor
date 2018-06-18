// https://stackoverflow.com/a/34032216/78204

function Controller() {
    installer.autoRejectMessageBoxes();
    installer.installationFinished.connect(function() {
        gui.clickButton(buttons.NextButton);
    })
}

Controller.prototype.WelcomePageCallback = function() {
    gui.clickButton(buttons.NextButton, 3000);
}

Controller.prototype.CredentialsPageCallback = function() {
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.IntroductionPageCallback = function() {
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.TargetDirectoryPageCallback = function()
{
    gui.currentPageWidget().TargetDirectoryLineEdit.setText(installer.value("HomeDir") + "/Qt");
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.ComponentSelectionPageCallback = function() {
    var widget = gui.currentPageWidget();

    // widget.selectAll();
    widget.deselectAll();

    widget.selectComponent("qt.qt5.5101.clang_64")
    // widget.selectComponent("qt.qt5.5101.doc")
    // widget.selectComponent("qt.qt5.5101.examples")
    // widget.selectComponent("qt.qt5.5101.qtcharts")
    // widget.selectComponent("qt.qt5.5101.qtcharts.clang_64")
    // widget.selectComponent("qt.qt5.5101.qtdatavis3d")
    // widget.selectComponent("qt.qt5.5101.qtdatavis3d.clang_64")
    // widget.selectComponent("qt.qt5.5101.qtnetworkauth")
    // widget.selectComponent("qt.qt5.5101.qtnetworkauth.clang_64")
    // widget.selectComponent("qt.qt5.5101.qtpurchasing")
    // widget.selectComponent("qt.qt5.5101.qtpurchasing.clang_64")
    // widget.selectComponent("qt.qt5.5101.qtremoteobjects")
    // widget.selectComponent("qt.qt5.5101.qtremoteobjects.clang_64")
    // widget.selectComponent("qt.qt5.5101.qtscript")
    // widget.selectComponent("qt.qt5.5101.qtspeech")
    // widget.selectComponent("qt.qt5.5101.qtspeech.clang_64")
    // widget.selectComponent("qt.qt5.5101.qtvirtualkeyboard")
    // widget.selectComponent("qt.qt5.5101.qtvirtualkeyboard.clang_64")
    // widget.selectComponent("qt.qt5.5101.qtwebengine")
    // widget.selectComponent("qt.qt5.5101.qtwebengine.clang_64")
    // widget.selectComponent("qt.qt5.5101.src")
    // widget.selectComponent("qt.tools.qtcreator")

    gui.clickButton(buttons.NextButton);
}

Controller.prototype.LicenseAgreementPageCallback = function() {
    gui.currentPageWidget().AcceptLicenseRadioButton.setChecked(true);
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.StartMenuDirectoryPageCallback = function() {
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.ReadyForInstallationPageCallback = function()
{
    gui.clickButton(buttons.NextButton);
}

Controller.prototype.FinishedPageCallback = function() {
var checkBoxForm = gui.currentPageWidget().LaunchQtCreatorCheckBoxForm
if (checkBoxForm && checkBoxForm.launchQtCreatorCheckBox) {
    checkBoxForm.launchQtCreatorCheckBox.checked = false;
}
    gui.clickButton(buttons.FinishButton);
}
