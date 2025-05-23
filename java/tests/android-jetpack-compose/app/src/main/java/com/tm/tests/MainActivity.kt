package com.tm.tests

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import api.ttt.db.modeler.ms.TList
import com.tm.tests.models.chat.chanels.Chanel
import com.tm.tests.models.chat.chanels.ChanelContext
import com.tm.tests.models.chat.chanels.ChanelEditor
import com.tm.tests.models.chat.massagers.Messager
import com.tm.tests.models.chat.massagers.MessagerRole
import com.tm.tests.models.chat.messages.Message
import com.tm.tests.models.chat.messagins.Messaging


import api.ttt.db.modeler.db.TModeler

import api.ttt.db.modeler.db.Tdb

import api.ttt.db.modeler.db.TModelerCallback

import api.ttt.db.modeler.synchronizer.TSyncMaster
import api.ttt.db.utils.T

import com.tm.tests.models.chat.chanels.ChanelType

import com.tm.tests.models.chat.messagins.MessagingMember

import com.tm.tests.models.chat.messagins.MessagingType
import com.tm.tests.models.utils.TMedia


class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        testTM();
    }

    private fun testTM(){

    }


    private lateinit var handler: Handler

    // Main Messager instance
    private lateinit var messager: Messager
    // Main Chanel instance
    private lateinit var myChanel: Chanel
    // List of Messaging instances
    private lateinit var myMessagings: TList<Messaging>
    // List of Message instances
    private lateinit var myMessages: TList<Message>

    /**
     * Creates and logs messaging test data
     */
    private fun chats() {
        baseInit()

        val chanelCount = Chanel.tms.all().count()
        initChat(chanelCount)

        T.Try {
            messager = Messager.tms.all()
                .filter { it.name.get().uppercase().contains("OLIVIER") }
                .first()
        }
        log("-> \n" + (if (::messager.isInitialized) messager.data(messager.serial()) else "NULL"))

        T.Try {
            myChanel = ChanelEditor.tms.all()
                .filter {
                    it.messager == messager &&
                            it.chanel.get().context == ChanelContext.get("") &&
                            it.role == MessagerRole.creator()
                }
                .first().chanel.get()
        }
        log("-> \n" + (if (::myChanel.isInitialized) myChanel.data(myChanel.serial()) else "NULL"))

        T.Try {
            /*myMessagings = Messaging.tms.all().filter {
                it.chanel == myChanel && it.typ == MessagingType.publicType()
            }*/
        }
        log("-> \n" + Messaging.data(myMessagings, Messaging.serial))

        T.Try {
            myMessages = Message.tms.all().filter {
                it.messaging == myMessagings.first()
            }
        }
        log("-> \n" + Message.data(myMessages, Message.serial))
    }

    /**
     * Initializes base static model references
     */
    private fun baseInit() {
        MessagerRole.creator()
        MessagerRole.admin()
        MessagerRole.messager()

        ChanelType.mainType()
        ChanelType.lambdaType()

        ChanelContext.get("")
        ChanelContext.get("")
        ChanelContext.get("")

        MessagingType.privateType()
        MessagingType.publicType()
    }

    /**
     * Logs information
     */
    private fun log(msg: String) {
        //Log.d("TEST", msg)
    }

    /**
     * Creates a test chat instance with several users, channels, messaging groups and messages
     */
    private fun initChat(i: Long): Chanel {
        val messager1 = Messager().init().apply {
            name.set("Olivier Tambo $i")
            photo.set(TMedia().init().apply { description.set("pp") })
        }

        val messager2 = Messager().init().apply { name.set("Michel Tambo $i") }
        val messager3 = Messager().init().apply { name.set("Annie Tambo $i") }.also { it.save() }
        val messager4 = Messager().init().apply { name.set("Gaby Tambo $i") }.also { it.save() }

        val chanel1 = Chanel().init().apply {
            name.set("MAIN Chanel $i")
            context.set(ChanelContext.get(""))
            typ.set(ChanelType.mainType())
            save()
        }

        val chanel2 = Chanel().init().apply {
            name.set("LAMBDA Chanel $i")
            context.set(ChanelContext.get(""))
            typ.set(ChanelType.lambdaType())
            save()
        }

        ChanelEditor().init().apply {
            role.set(MessagerRole.creator())
            this.messager.set(messager1)
            chanel.set(chanel1)
            save()
        }

        ChanelEditor().init().apply {
            role.set(MessagerRole.messager())
            this.messager.set(messager2)
            chanel.set(chanel1)
            save()
        }

        val messaging1 = Messaging().init().apply {
            name.set("PRIVATE Messaging $i")
            typ.set(MessagingType.privateType())
        }
        chanel1.pv_messagings.add(messaging1)

        listOf(
            MessagingMember().init().apply {
                role.set(MessagerRole.creator())
                this.messager.set(messager1)
                messaging.set(messaging1)
            },
            MessagingMember().init().apply {
                role.set(MessagerRole.admin())
                this.messager.set(messager2)
                messaging.set(messaging1)
            }
        ).forEach { it.save() }

        val messaging2 = Messaging().init().apply {
            name.set("PUBLIC Messaging $i")
            typ.set(MessagingType.publicType())
        }
        chanel1.pb_messagings.add(messaging2)

        listOf(
            Triple(MessagerRole.creator(), messager3, messaging2),
            Triple(MessagerRole.admin(), messager4, messaging2),
            Triple(MessagerRole.messager(), messager1, messaging2),
            Triple(MessagerRole.messager(), messager2, messaging2)
        ).map { (role, user, messaging) ->
            MessagingMember().init().apply {
                this.role.set(role)
                this.messager.set(user)
                this.messaging.set(messaging)
                save()
            }
        }

        listOf("Hello!!!", "How!!!", "fine!!!", "cool!!!").forEachIndexed { index, text ->
            Message().init().apply {
                content.set("$text $i")
                //loc.set(LatLng(3.3265, 9.32658))
                creator.set(listOf(messager1, messager2, messager3, messager4)[index])
                messaging.set(messaging2)
                save()
            }
        }

        messager = messager1
        return chanel1
    }

}