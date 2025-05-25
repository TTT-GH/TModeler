package com.tm.tests.models.chat.chanels;

import com.tm.tests.models.chat.massagers.Messager;
import com.tm.tests.models.chat.massagers.MessagerRole;

import api.ttt.db.modeler.field.ModelField;
import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.Tms;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;

/**
 * LE chiffrement des chaines se fait ici:
 * DONNEES ULTRA PUBLIQUES-PRIVEES
 * Liste les editor d'une chaine. ceux qui ont le droit d'exercer au nom de la chaine
 * */
public class ChanelEditor extends TModel<ChanelEditor> {
    public ModelField<Chanel> chanel = new ModelField<Chanel>(Chanel.class);
    public ModelField<Messager> messager = new ModelField<Messager>(Messager.class);
    public ModelField<MessagerRole> role = new ModelField<MessagerRole>(MessagerRole.class);


    public static final TMSerial<ChanelEditor> serial = new TMSerial<ChanelEditor>(ChanelEditor.class);
    public static final Tms<ChanelEditor> tms = initialize(ChanelEditor.class, serial);


    ///----------------------------------------------------------------------------------

    @Override
    public TServerInfos onSync() {
        return super.onSync().with(
                "im/chanels/editors/",
                null,
                ()->{}
        );
    }

    ///----------------------------------------------------------------------------------
}
