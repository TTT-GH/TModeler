package com.tm.tests.models.chat.chanels;

import api.ttt.db.modeler.core.operations.Top;
import api.ttt.db.modeler.field.CharField;
import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.Tms;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;

public class ChanelContext extends TModel<ChanelContext> {
    public CharField route = new CharField(255).unique(true);
    public CharField description = new CharField(100);


    public static final TMSerial<ChanelContext> serial = new TMSerial<ChanelContext>(ChanelContext.class);
    public static final Tms<ChanelContext> tms = initialize(ChanelContext.class, serial);


    ///----------------------------------------------------------------------------------

    @Override
    public TServerInfos onSync() {
        return super.onSync().with(
                "im/chanels/contexts/",
                null,
                ()->{}
        );
    }

    ///----------------------------------------------------------------------------------


    public static ChanelContext get(String route) {
        ChanelContext context = ChanelContext.tms.builder().filter(Top.eq(attr("route"), route)).build().first();
        if(context==null){
            context = new ChanelContext().init();
            context.route.set(route);
            context.save();
        }
        return context;
    }
}
