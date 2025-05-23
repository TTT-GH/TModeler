package com.tm.tests.models.chat.chanels;

import api.ttt.db.modeler.model.base.TModel;
import api.ttt.db.modeler.model.fields.MField;
import api.ttt.db.modeler.model.serializers.TMSerial;
import api.ttt.db.modeler.ms.TMS;
import api.ttt.db.modeler.synchronizer.utils.TServerInfos;
import com.tm.tests.models.chat.massagers.Messager;
import com.tm.tests.models.chat.massagers.MessagerRole;

/**
 * LE chiffrement des chaines se fait ici:
 * DONNEES ULTRA PUBLIQUES-PRIVEES
 * Liste les editor d'une chaine. ceux qui ont le droit d'exercer au nom de la chaine
 * */
public class ChanelEditor extends TModel<ChanelEditor> {
    public MField<Chanel> chanel = new MField<Chanel>(Chanel.class);
    public MField<Messager> messager = new MField<Messager>(Messager.class);
    public MField<MessagerRole> role = new MField<MessagerRole>(MessagerRole.class);


    public static final TMSerial<ChanelEditor> serial = new TMSerial<ChanelEditor>(ChanelEditor.class);
    public static final TMS<ChanelEditor> tms = initialize(ChanelEditor.class, serial);
}
