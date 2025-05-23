import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import models 1.0

ApplicationWindow {
    width: 720
    height: 600
    visible: true
    title: qsTr("Client Manager")

    ClientViewModel {
        id: clientModel

        onErrorOccurred: {
            errorDialog.text = message
            errorDialog.visible = true
        }

        onCountChanged: {
            console.log("Nombre d'éléments changé :", clientModel.count)
            mutationDialog.text = message
            mutationDialog.visible = true
        }

        onDataChanged: {
            console.log("Les données ont changé entre", topLeft.row, "et", bottomRight.row)
            updateDialog.text = message
            updateDialog.visible = true
        }
    }

    MessageDialog {
        id: mutationDialog
        title: "Mutation"
        text: "Une erreur est survenue."
        buttons: MessageDialog.Ok
        visible: false
        onAccepted: visible = false
    }

    MessageDialog {
        id: updateDialog
        title: "Update"
        text: "Une erreur est survenue."
        buttons: MessageDialog.Ok
        visible: false
        onAccepted: visible = false
    }

    MessageDialog {
        id: errorDialog
        title: "Erreur"
        text: "Une erreur est survenue."
        buttons: MessageDialog.Ok
        visible: false
        onAccepted: visible = false
    }

    Column {
        spacing: 10
        anchors.fill: parent
        anchors.margins: 20

        Text {
            text: "Total clients: " + clientModel.count()
            font.bold: true
        }

        ListView {
            id: listView
            height: 400
            width: parent.width
            model: clientModel

            delegate: Rectangle {
                width: listView.width
                height: 40
                color: index % 2 === 0 ? "#e0e0e0" : "#f0f0f0"

                property var item: clientModel.get(index)

                Row {
                    spacing: 10
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        text: item.data.name + " (" + item.data.email + ")"
                        font.bold: index === listView.currentIndex
                    }

                    Button {
                        text: "Edit"
                        onClicked: {
                            nameInput.text = item.data.name
                            emailInput.text = item.data.email
                            selectedIndex = index
                        }
                    }

                    Button {
                        text: "Delete"
                        onClicked: {
                            clientModel.remove(index)
                        }
                    }
                }
            }
        }

        Row {
            spacing: 10

            TextField {
                id: nameInput
                placeholderText: "Name"
                width: 150
            }

            TextField {
                id: emailInput
                placeholderText: "Email"
                width: 200
            }

            Button {
                text: "Add"
                onClicked: {
                    clientModel.create({
                        "name": nameInput.text,
                        "email": emailInput.text
                    })
                    nameInput.text = ""
                    emailInput.text = ""
                }
            }

            Button {
                text: "Update"
                enabled: selectedIndex >= 0
                onClicked: {
                    let item = clientModel.get(selectedIndex)
                    let current = item.data
                    current.name = nameInput.text
                    current.email = emailInput.text
                    item.data = current
                    nameInput.text = ""
                    emailInput.text = ""
                    selectedIndex = -1
                }
            }
        }

        Row {
            spacing: 10

            Button {
                text: "Refresh"
                onClicked: clientModel.refresh()
            }

            Button {
                text: "Count"
                onClicked: console.log("Number of clients:", clientModel.count())
            }

            Button {
                text: "Filtrer par nom = 'Alice'"
                onClicked: clientModel.filter("name", "Alice")
            }

            Button {
                text: "Annuler filtre"
                onClicked: clientModel.filter("", "")
            }

            Button {
                text: "Load more (offset 0, limit 2)"
                onClicked: clientModel.loadMore(0, 2)
            }

            Button {
                text: "Load more (offset 2, limit 2)"
                onClicked: clientModel.loadMore(2, 2)
            }
        }
    }

    property int selectedIndex: -1
}
