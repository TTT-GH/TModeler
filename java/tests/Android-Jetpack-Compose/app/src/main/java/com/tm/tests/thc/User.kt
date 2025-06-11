package com.tm.tests.thc

import api.ttt.db.modeler.model.serializers.TMSerial
import api.ttt.db.modeler.thc.field.SecureFloatField
import api.ttt.db.modeler.thc.field.SecureIntField
import api.ttt.db.modeler.thc.field.SecureTextField
import api.ttt.db.modeler.thc.model.TNode

class User : TNode<User?>() {
    var name = SecureTextField()
    var age = SecureIntField()
    var height = SecureFloatField()

    companion object {
        val serial = TMSerial(User::class.java)
        val tms = initialize(User::class.java, serial)
    }
}
