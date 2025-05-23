package com.tm.tests.models.chat.messages;

import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.fields.GeoField;
import api.ttt.db.modeler.model.fields.MField;
import api.ttt.db.modeler.model.fields.TextField;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.TMS;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;
import com.tm.tests.models.chat.massagers.Messager;
import com.tm.tests.models.chat.messagins.Messaging;


public class Message extends TModel<Message> {
    public MField<Messaging> messaging = new MField<Messaging>(Messaging.class);
    public MField<Messager> creator = new MField<Messager>(Messager.class);
    public TextField content = new TextField();
    public GeoField loc = new GeoField();


    public static final TMSerial<Message> serial = new TMSerial<Message>(Message.class);
    public static final TMS<Message> tms = initialize(Message.class, serial);
}
