package com.tm.tests.models.chat.messagins;

import com.tm.tests.models.chat.messages.Message;
import com.tm.tests.models.utils.TMedia;

import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.fields.CharField;
import api.ttt.db.modeler.model.fields.LField;
import api.ttt.db.modeler.model.fields.MField;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.TMS;

public class Messaging extends TModel<Messaging> {
    public CharField name = new CharField(100);
    public MField<MessagingType> typ = new MField<MessagingType>(MessagingType.class);
    public LField<TMedia> photos = new LField<TMedia>(TMedia.class);
    public MField<Message> message = new MField<Message>(Message.class);


    public static final TMSerial<Messaging> serial = new TMSerial<Messaging>(Messaging.class);
    public static final TMS<Messaging> tms = initialize(Messaging.class, serial);
}