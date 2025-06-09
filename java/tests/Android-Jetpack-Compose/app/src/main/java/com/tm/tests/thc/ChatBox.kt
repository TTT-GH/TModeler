package com.tm.tests.thc

import api.ttt.db.modeler.field.ListField
import api.ttt.db.modeler.field.TextField
import api.ttt.db.modeler.thc.model.TNode

class ChatBox : TNode<ChatBox?>() {
    var name = TextField()
    var members = ListField(User::class.java)
}
