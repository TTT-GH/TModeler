package com.tm.tests.models.chat.chanels;

import api.ttt.db.modeler.core.operations.Top;
import api.ttt.db.modeler.field.CharField;
import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.Tms;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;

public class ChanelType extends TModel<ChanelType> {
    CharField title = new CharField(100).unique(true);
    CharField description = new CharField(100);


    public static final TMSerial<ChanelType> serial = new TMSerial<ChanelType>(ChanelType.class);
    public static final Tms<ChanelType> tms = initialize(ChanelType.class, serial);


    ///----------------------------------------------------------------------------------

    @Override
    public TServerInfos onSync() {
        return super.onSync().with(
                "im/chanels/types/",
                null,
                ()->{}
        );
    }

    ///----------------------------------------------------------------------------------



    ////-------------------------------------------------------------------------



    private static ChanelType mainType;
    private static ChanelType lambdaType;
    private static ChanelType defaultType; //all post-chanels are default type

    /**- into a context, an user can get only one chanel of this type*/
    public static ChanelType mainType() {
        if(mainType!=null)
            return mainType;

        mainType = ChanelType.tms.builder()
                .filter(Top.eq(attr("title"), "MAIN"))
                .build()
                .first();
        if(mainType==null){
            mainType = new ChanelType().init();
            mainType.title.set("MAIN");
            mainType.save();
        }
        return mainType;
    }

    /**- into a context, an user can get only one chanel of this type*/
    public static ChanelType lambdaType() {
        if(lambdaType!=null)
            return lambdaType;

        lambdaType = ChanelType.tms.builder()
                .filter(Top.eq(attr("title"), "LAMBDA"))
                .build()
                .first();
        if(lambdaType==null){
            lambdaType = new ChanelType().init();
            lambdaType.title.set("LAMBDA");
            lambdaType.save();
        }
        return lambdaType;
    }

    /**- into a context, an user can get several chanels of this type*/
    public static ChanelType defaultType() {
        if(defaultType!=null)
            return defaultType;

        defaultType = ChanelType.tms.builder()
                .filter(Top.eq(attr("title"), "DEFAULT"))
                .build()
                .first();
        if(defaultType==null){
            defaultType = new ChanelType().init();
            defaultType.title.set("DEFAULT");
            defaultType.save();
        }
        return defaultType;
    }
}
