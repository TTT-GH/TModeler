package com.tm.tests._launcher;

import android.app.Application;

import java.util.List;

import api.ttt.db.modeler.db.TModeler;
import api.ttt.db.modeler.db.Tdb;
import api.ttt.db.modeler.db.TModelerCallback;
import api.ttt.db.modeler.synchronizer.TSyncMaster;
import com.tm.tests.models.chat.chanels.Chanel;
import com.tm.tests.models.chat.chanels.ChanelContext;
import com.tm.tests.models.chat.chanels.ChanelEditor;
import com.tm.tests.models.chat.chanels.ChanelType;
import com.tm.tests.models.chat.massagers.Messager;
import com.tm.tests.models.chat.massagers.MessagerRole;
import com.tm.tests.models.chat.messages.Message;
import com.tm.tests.models.chat.messagins.Messaging;
import com.tm.tests.models.chat.messagins.MessagingMember;
import com.tm.tests.models.chat.messagins.MessagingType;

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
            @Override
            public String onLoadServerHost() {/// - Notify network security config
                //return "http://spoozy.app/tgps";
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
                /*
                if(!MainActivity.log("Server Connected "+connected))
                    TModeler.serverLink.offline();
                if(connected)
                    TSyncMaster.listener(MainActivity.syncListener()).sync(1000);*/
            }
            @Override
            public void onPrepareSync() {
                Chanel.tms.commit();
                ChanelContext.tms.commit();
                ChanelEditor.tms.commit();
                ChanelType.tms.commit();
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
