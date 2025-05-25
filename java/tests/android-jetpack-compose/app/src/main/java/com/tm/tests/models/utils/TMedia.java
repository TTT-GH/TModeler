package com.tm.tests.models.utils;

import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.field.*;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.Tms;

/**
 * Media federation allow central media control
 * On server we'll setup that on a only application
 * */
public class TMedia extends TModel<TMedia> {
    public CharField description = new CharField(255);
    public ImageField image = new ImageField();
    public ImageField file = new ImageField();


    public static final TMSerial<TMedia> serial = new TMSerial<TMedia>(TMedia.class);//With custom Serial
    public static final Tms<TMedia> tms = initialize(TMedia.class, serial);//With custom Serial
}
