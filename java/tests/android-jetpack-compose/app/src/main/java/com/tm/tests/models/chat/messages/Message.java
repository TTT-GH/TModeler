package com.tm.tests.models.chat.messages;

import com.tm.tests.models.chat.massagers.Messager;
import com.tm.tests.models.chat.messagins.Messaging;

import api.ttt.db.modeler.field.GeoField;
import api.ttt.db.modeler.field.ModelField;
import api.ttt.db.modeler.field.TextField;
import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.Tms;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;


public class Message extends TModel<Message> {
    public ModelField<Messaging> messaging = new ModelField<Messaging>(Messaging.class);
    public ModelField<Messager> creator = new ModelField<Messager>(Messager.class);
    public TextField content = new TextField();
    public GeoField loc = new GeoField();


    public static final TMSerial<Message> serial = new TMSerial<Message>(Message.class); // montre moi un moyen d'acceder à ces 2 var static sans avoir à redire ca manuellement pour chaque Model
    public static final Tms<Message> tms = initialize(Message.class, serial);


    ///----------------------------------------------------------------------------------

    @Override
    public TServerInfos onSync() {
        return super.onSync().with(
                "im/messages/",
                null,
                ()->{}
        );
    }

    ///----------------------------------------------------------------------------------
}
