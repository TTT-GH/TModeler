package com.tm.tests.models.chat.massagers;

import android.graphics.Color;

import com.tm.tests.models.utils.TMedia;

import org.jetbrains.annotations.NotNull;

import api.ttt.db.modeler.field.CharField;
import api.ttt.db.modeler.field.ModelField;
import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.Tms;
import api.ttt.db.modeler.synchronizer.interfaces.TSyncCallback;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;

/**
 * Objet global qui represente celui qui gere une messagerie, il est unique par utilisateur
 * */
public class Messager extends TModel<Messager> {
    public CharField phone = new CharField(100).unique(true);
    public CharField name = new CharField(100);
    public ModelField<TMedia> photo = new ModelField<TMedia>(TMedia.class);


    public static final TMSerial<Messager> serial = new TMSerial<Messager>(Messager.class);
    public static final Tms<Messager> tms = initialize(Messager.class, serial);


    ///----------------------------------------------------------------------------------
    // dédié a la sync du Messager
    @Override
    public TServerInfos onSync() {
        return super.onSync().with(
                "im/messagers/",
                null,
                ()->{}
        );
    }

    ///----------------------------------------------------------------------------------

    ///----------------------------------------------------------------------------------


    public boolean isActive(){
        return false;
    }


    public String name(){
        return name.get();
    }

    public String photo(){
        try {
            return photo.get().image.path();
        }catch (Exception e){
            return null;
        }
    }
}
