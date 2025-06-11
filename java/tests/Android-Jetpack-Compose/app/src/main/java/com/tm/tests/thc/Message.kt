package com.tm.tests.thc

import api.ttt.db.modeler.field.ModelField
import api.ttt.db.modeler.model.base.TModel
import api.ttt.db.modeler.model.serializers.TMSerial
import api.ttt.db.modeler.thc.field.SecureTextField

class Message : TModel<Message?>() {
    var content = SecureTextField()
    var creator = ModelField(
        User::class.java
    )
    var notice = ModelField(
        User::class.java
    )

    companion object {
        val serial = TMSerial(Message::class.java)
        val tms = initialize(
            Message::class.java, serial
        )
    }
}
