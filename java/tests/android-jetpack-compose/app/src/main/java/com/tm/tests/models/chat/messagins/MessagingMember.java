package com.tm.tests.models.chat.messagins;

import com.tm.tests.models.chat.massagers.Messager;
import com.tm.tests.models.chat.massagers.MessagerRole;

import api.ttt.db.modeler.field.ModelField;
import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.Tms;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;

/**
 * LE chiffrement des conversations se fait ici:
 * DONNEES ULTRA PUBLIQUES-PRIVEES
 * Liste ceux qui ont le droit d'echanger dans une conversation
 * */
public class MessagingMember extends TModel<MessagingMember> {
    public ModelField<Messaging> messaging = new ModelField<Messaging>(Messaging.class);
    public ModelField<Messager> messager = new ModelField<Messager>(Messager.class);
    public ModelField<MessagerRole> role = new ModelField<MessagerRole>(MessagerRole.class);


    public static final TMSerial<MessagingMember> serial = new TMSerial<MessagingMember>(MessagingMember.class);
    public static final Tms<MessagingMember> tms = initialize(MessagingMember.class, serial);


    ///----------------------------------------------------------------------------------

    @Override
    public TServerInfos onSync() {
        return super.onSync().with(
                "im/messagings/members/",
                null,
                ()->{}
        );
    }

    ///----------------------------------------------------------------------------------
}
