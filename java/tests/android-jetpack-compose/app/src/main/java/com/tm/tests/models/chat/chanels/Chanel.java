package com.tm.tests.models.chat.chanels;

import com.tm.tests.models.chat.messagins.Messaging;

import api.ttt.db.modeler.field.CharField;
import api.ttt.db.modeler.field.ListField;
import api.ttt.db.modeler.field.ModelField;
import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.Tms;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;

/**
 * It is just a way to order messagings, by grouping
 * */
public class Chanel extends TModel<Chanel> {
    public CharField name = new CharField(100);
    public ModelField<ChanelContext> context = new ModelField<ChanelContext>(ChanelContext.class);
    public ModelField<ChanelType> typ = new ModelField<ChanelType>(ChanelType.class);
    public ListField<Messaging> pv_messagings = new ListField<Messaging>(Messaging.class);
    public ListField<Messaging> pb_messagings = new ListField<Messaging>(Messaging.class);
    public ListField<Chanel> sub_chanels = new ListField<Chanel>(Chanel.class);


    public static final TMSerial<Chanel> serial = new TMSerial<Chanel>(Chanel.class);
    public static final Tms<Chanel> tms = initialize(Chanel.class, serial);


    ///----------------------------------------------------------------------------------

    @Override
    public TServerInfos onSync() {
        return super.onSync().with(
                "im/chanels/",
                null,
                ()->{
                    /*
                    XApp.run(()->{
                        Cb.setClipboard(XApp.context, "Chanel Sync : " + tms.all().serialData());
                    });*/
                }
        );
    }

    ///----------------------------------------------------------------------------------
}
