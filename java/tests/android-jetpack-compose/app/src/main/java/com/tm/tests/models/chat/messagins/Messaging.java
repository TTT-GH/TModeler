package com.tm.tests.models.chat.messagins;

import android.annotation.SuppressLint;
import android.graphics.Color;

import com.tm.tests.models.chat.massagers.Messager;
import com.tm.tests.models.chat.messages.Message;
import com.tm.tests.models.utils.TMedia;

import org.jetbrains.annotations.NotNull;

import java.time.LocalDateTime;

import api.ttt.db.modeler.field.CharField;
import api.ttt.db.modeler.field.ListField;
import api.ttt.db.modeler.field.ModelField;
import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.Tlist;
import api.ttt.db.modeler.ms.Tms;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;

public class Messaging extends TModel<Messaging> {
    public CharField name = new CharField(100);
    public ModelField<MessagingType> typ = new ModelField<MessagingType>(MessagingType.class);
    public ListField<TMedia> photos = new ListField<TMedia>(TMedia.class);
    public ModelField<Message> message = new ModelField<Message>(Message.class);


    public static final TMSerial<Messaging> serial = new TMSerial<Messaging>(Messaging.class);
    public static final Tms<Messaging> tms = initialize(Messaging.class, serial);


    ///----------------------------------------------------------------------------------

    @Override
    public TServerInfos onSync() {
        return super.onSync().with(
                "im/messagings/",
                null,
                ()->{}
        );
    }

    @NotNull
    public Tlist<Messager> members() {
        return null;
    }

    ///----------------------------------------------------------------------------------

}
