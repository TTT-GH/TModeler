package com.tm.tests.models.chat.massagers;

import api.ttt.db.modeler.core.operations.Top;
import api.ttt.db.modeler.field.CharField;
import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.Tms;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;

public class MessagerRole extends TModel<MessagerRole> {
    CharField title = new CharField(100).unique(true);
    CharField description = new CharField(100);


    public static final TMSerial<MessagerRole> serial = new TMSerial<MessagerRole>(MessagerRole.class);
    public static final Tms<MessagerRole> tms = initialize(MessagerRole.class, serial);


    ///----------------------------------------------------------------------------------

    @Override
    public TServerInfos onSync() {
        return super.onSync().with(
                "im/messagers/roles/",
                null,
                ()->{}
        );
    }

    ///----------------------------------------------------------------------------------


    ///----------------------------------------------------------------------------------------------

    private static MessagerRole creator;
    private static MessagerRole messager;
    private static MessagerRole admin;
    public static MessagerRole creator() {
        if(creator!=null)
            return creator;

        creator = MessagerRole.tms.builder().filter(Top.eq(attr("title"), "CREATOR")).build().first();
        if(creator==null){
            creator = new MessagerRole().init();
            creator.title.set("CREATOR");
            creator.save();
        }
        return creator;
    }

    public static MessagerRole messager() {
        if(messager!=null)
            return messager;

        messager = MessagerRole.tms.builder().filter(Top.eq(attr("title"), "MESSAGER")).build().first();
        if(messager==null){
            messager = new MessagerRole().init();
            messager.title.set("MESSAGER");
            messager.save();
        }
        return messager;
    }

    public static MessagerRole admin() {
        if(admin!=null)
            return admin;

        admin = MessagerRole.tms.builder().filter(Top.eq(attr("title"), "ADMIN")).build().first();
        if(admin==null){
            admin = new MessagerRole().init();
            admin.title.set("ADMIN");
            admin.save();
        }
        return admin;
    }
}
