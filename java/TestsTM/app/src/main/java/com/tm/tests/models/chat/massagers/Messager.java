package com.tm.tests.models.chat.massagers;

import android.graphics.Color;

import com.tm.tests.models.utils.TMedia;

import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.fields.CharField;
import api.ttt.db.modeler.model.fields.MField;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.TMS;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;

/**
 * Objet global qui represente celui qui gere une messagerie, il est unique par utilisateur
 * */
public class Messager extends TModel<Messager> {
    public CharField phone = new CharField(100).unique(true);
    public CharField name = new CharField(100);
    public MField<TMedia> photo = new MField<TMedia>(TMedia.class);


    public static final TMSerial<Messager> serial = new TMSerial<Messager>(Messager.class);
    public static final TMS<Messager> tms = initialize(Messager.class, serial);
}
