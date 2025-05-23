package com.tm.tests.models.chat.messagins;

import api.ttt.db.modeler.base.operations.Top;
import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.fields.CharField;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.TMS;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;

public class MessagingType extends TModel<MessagingType> {
    CharField title = new CharField(100).unique(true);
    CharField description = new CharField(100);


    public static final TMSerial<MessagingType> serial = new TMSerial<MessagingType>(MessagingType.class);
    public static final TMS<MessagingType> tms = initialize(MessagingType.class, serial);


    ///----------------------------------------------------------------------------------

    @Override
    public TServerInfos onSync() {
        return super.onSync().with(
                "im/messagings/types/",
                null,
                ()->{}
        );
    }

    ///----------------------------------------------------------------------------------



    ////-------------------------------------------------------------------------



    private static MessagingType privateType;
    private static MessagingType publicType;
    public static MessagingType privateType() {
        if(privateType!=null)
            return privateType;

        privateType = MessagingType.tms.builder()
                .filter(Top.eq(attr("title"), "PRIVATE"))
                .build()
                .first();
        if(privateType==null){
            privateType = new MessagingType().init();
            privateType.title.set("PRIVATE");
            privateType.save();
        }
        return privateType;
    }

    public static MessagingType publicType() {
        if(publicType!=null)
            return publicType;

        publicType = MessagingType.tms.builder()
                .filter(Top.eq(attr("title"), "PUBLIC"))
                .build()
                .first();
        if(publicType==null){
            publicType = new MessagingType().init();
            publicType.title.set("PUBLIC");
            publicType.save();
        }
        return publicType;
    }
}
