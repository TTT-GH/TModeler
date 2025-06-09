package com.tm.tests._launcher;

import android.app.Application;

import com.tm.tests.models.chat.chanels.Chanel;
import com.tm.tests.models.chat.chanels.ChanelContext;
import com.tm.tests.models.chat.chanels.ChanelEditor;
import com.tm.tests.models.chat.massagers.Messager;
import com.tm.tests.models.chat.massagers.MessagerRole;
import com.tm.tests.models.chat.messages.Message;
import com.tm.tests.models.chat.messagins.Messaging;
import com.tm.tests.models.chat.messagins.MessagingMember;
import com.tm.tests.models.chat.messagins.MessagingType;

import java.util.List;

import api.ttt.db.modeler.db.Tdb;
import api.ttt.db.modeler.modeler.TModeler;
import api.ttt.db.modeler.modeler.TModelerCallback;
import api.ttt.db.modeler.synchronizer.TSyncMaster;
import api.ttt.db.modeler.synchronizer.interfaces.TSyncCallback;

public class App extends Application {

    @Override
    public void onCreate() {
        super.onCreate();

        initTmodeler();
    }

    private void initTmodeler() {
        TModeler.initialize(this, new TModelerCallback() {
            @Override
            public List<Tdb> onLoadBases(List<Tdb> bases) {
                bases.add(Tdb.connect("FirstTdb"));
                return bases;
            }
            // ici on peut ajouter des paramettres specific de synchronisation
            @Override
            public String onLoadServerHost() {
                return "http://192.168.236.174:8000";
            }
            @Override
            public String onLoadBaseUrl() { return "api";}
            @Override
            public String onLoadVersion() { return "v1";}
            @Override
            public String onLoadMediaHost() { return "media";}
            @Override
            public String onLoadMediaTmpDir() { return "tmp";}

            @Override
            public String onLoadMediaDir(String dir) {
                return super.onLoadMediaDir(dir);
            }

            @Override
            public void onServerAccessChange(boolean connected) {
                if(connected){
                    TSyncMaster.listener(new TSyncCallback(){
                        // pluysieur =s fenetre disponible pour suivre l'auto synchronisation des models autorisé

                        @Override
                        public void syncDone() {
                            // quand tous les model sont sync
                        }
                    }).sync(1000); // période de synchronisation
                }
            }
            @Override
            public void onPrepareSync() {
                /// tres important ici, il sagit d'une fonction du TM (TModeler) dont le role est de communiquer au TSM des changement survenu dans les models de données
                Chanel.tms.commit();
                ChanelContext.tms.commit();
                ChanelEditor.tms.commit();
                //
                Messager.tms.commit();
                MessagerRole.tms.commit();
                //
                Message.tms.commit();
                //
                Messaging.tms.commit();
                MessagingMember.tms.commit();
                MessagingType.tms.commit();
            }
        });
    }
}
