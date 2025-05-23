package com.tm.tests.models.chat.chanels;

import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.fields.CharField;
import api.ttt.db.modeler.model.fields.LField;
import api.ttt.db.modeler.model.fields.MField;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.TMS;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;
import com.tm.tests.models.chat.messagins.Messaging;

/**
 * It is just a way to order messagings, by grouping
 * */
public class Chanel extends TModel<Chanel> {
    public CharField name = new CharField(100);
    public MField<ChanelContext> context = new MField<ChanelContext>(ChanelContext.class);
    public MField<ChanelType> typ = new MField<ChanelType>(ChanelType.class);
    public LField<Messaging> pv_messagings = new LField<Messaging>(Messaging.class);
    public LField<Messaging> pb_messagings = new LField<Messaging>(Messaging.class);
    public LField<Chanel> sub_chanels = new LField<Chanel>(Chanel.class);


    public static final TMSerial<Chanel> serial = new TMSerial<Chanel>(Chanel.class);
    public static final TMS<Chanel> tms = initialize(Chanel.class, serial);
}
