package com.tm.tests.models.chat.messagins;

import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.fields.MField;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.TMS;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;
import com.tm.tests.models.chat.massagers.Messager;
import com.tm.tests.models.chat.massagers.MessagerRole;

/**
 * LE chiffrement des conversations se fait ici:
 * DONNEES ULTRA PUBLIQUES-PRIVEES
 * Liste ceux qui ont le droit d'echanger dans une conversation
 * */
public class MessagingMember extends TModel<MessagingMember> {
    public MField<Messaging> messaging = new MField<Messaging>(Messaging.class);
    public MField<Messager> messager = new MField<Messager>(Messager.class);
    public MField<MessagerRole> role = new MField<MessagerRole>(MessagerRole.class);


    public static final TMSerial<MessagingMember> serial = new TMSerial<MessagingMember>(MessagingMember.class);
    public static final TMS<MessagingMember> tms = initialize(MessagingMember.class, serial);
}
