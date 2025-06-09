package com.tm.tests

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler

import api.ttt.db.modeler.ms.Tlist
import com.tm.tests.models.chat.chanels.Chanel
import com.tm.tests.models.chat.chanels.ChanelContext
import com.tm.tests.models.chat.chanels.ChanelEditor
import com.tm.tests.models.chat.chanels.ChanelType
import com.tm.tests.models.chat.massagers.Messager
import com.tm.tests.models.chat.massagers.MessagerRole
import com.tm.tests.models.chat.messages.Message
import com.tm.tests.models.chat.messagins.Messaging
import com.tm.tests.models.chat.messagins.MessagingMember
import com.tm.tests.models.chat.messagins.MessagingType

import com.tm.tests.models.utils.TMedia


class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        testTM();

        Thc.test();
    }

    private fun testTM(){

    }


    private lateinit var handler: Handler

    // Main Messager instance
    private lateinit var messager: Messager
    // Main Chanel instance
    private lateinit var myChanel: Chanel
    // List of Messaging instances
    private lateinit var myMessagings: Tlist<Messaging>
    // List of Message instances
    private lateinit var myMessages: Tlist<Message>

    /**
     * Logs information
     */
    @SuppressLint("NewApi")
    object Log {
        fun d(tag: String, msg: String) {
            val time = java.time.LocalTime.now().toString()
            println("[$time] [$tag] $msg")
        }
    }

    fun testModelCrudOperations() {
        val i = 1 // Or use Random or loop counter

        val messager1 = Messager().init()
        messager1.name.set("User A $i")
        val media = TMedia().init()
        media.description.set("profile pic")
        messager1.photo.set(media)

        val messager2 = Messager().init()
        messager2.name.set("User B $i")

        val messager3 = Messager().init()
        messager3.name.set("User C $i")
        messager3.save()

        val messager4 = Messager().init()
        messager4.name.set("User D $i")
        messager4.save()

        val chanel1 = Chanel().init()
        chanel1.name.set("Main Channel $i")
        chanel1.context.set(ChanelContext.get(""))
        chanel1.typ.set(ChanelType.mainType())
        chanel1.save()

        val chanel2 = Chanel().init()
        chanel2.name.set("Secondary Channel $i")
        chanel2.context.set(ChanelContext.get(""))
        chanel2.typ.set(ChanelType.lambdaType())
        chanel2.save()

        val editor1 = ChanelEditor().init()
        editor1.role.set(MessagerRole.creator())
        editor1.messager.set(messager1)
        editor1.chanel.set(chanel1)

        val editor2 = ChanelEditor().init()
        editor2.role.set(MessagerRole.messager())
        editor2.messager.set(messager2)
        editor2.chanel.set(chanel1)

        editor1.save()
        editor2.save()

        val messaging1 = Messaging().init()
        messaging1.name.set("Private Chat $i")
        messaging1.typ.set(MessagingType.privateType())
        chanel1.pv_messagings.add(messaging1)

        val member1 = MessagingMember().init()
        member1.role.set(MessagerRole.creator())
        member1.messager.set(messager1)
        member1.messaging.set(messaging1)

        val member2 = MessagingMember().init()
        member2.role.set(MessagerRole.admin())
        member2.messager.set(messager2)
        member2.messaging.set(messaging1)

        member1.save()
        member2.save()

        val messaging2 = Messaging().init()
        messaging2.name.set("Public Chat $i")
        messaging2.typ.set(MessagingType.publicType())
        chanel1.pb_messagings.add(messaging2)

        val member3 = MessagingMember().init()
        member3.role.set(MessagerRole.creator())
        member3.messager.set(messager3)
        member3.messaging.set(messaging2)

        val member4 = MessagingMember().init()
        member4.role.set(MessagerRole.admin())
        member4.messager.set(messager4)
        member4.messaging.set(messaging2)

        val member5 = MessagingMember().init()
        member5.role.set(MessagerRole.messager())
        member5.messager.set(messager1)
        member5.messaging.set(messaging2)

        val member6 = MessagingMember().init()
        member6.role.set(MessagerRole.messager())
        member6.messager.set(messager2)
        member6.messaging.set(messaging2)

        member3.save()
        member4.save()
        member5.save()
        member6.save()

        val message1 = Message().init()
        message1.content.set("Hello!!! $i")
        message1.creator.set(messager1)
        message1.messaging.set(messaging2)
        message1.save()

        val message2 = Message().init()
        message2.content.set("How!!! $i")
        message2.creator.set(messager2)
        message2.messaging.set(messaging2)
        message2.save()

        val message3 = Message().init()
        message3.content.set("Fine!!! $i")
        message3.creator.set(messager3)
        message3.messaging.set(messaging2)
        message3.save()

        val message4 = Message().init()
        message4.content.set("Cool!!! $i")
        message4.creator.set(messager4)
        message4.messaging.set(messaging2)
        message4.save()

        // If needed, set global variable or return channel
        val activeMessager = messager1
        val resultChanel = chanel1

        // Add assertions here if you want to validate something
    }

    private fun migrations() {
        listOf(
            Message.tms,
            Messager.tms,
            Messaging.tms,
            Chanel.tms,
            ChanelEditor.tms,
            MessagingMember.tms,
            TMedia.tms
        ).forEach { it.migrate() }
    }

    private fun observers() {
        Message.tms.onSave { keys ->
            //Log.d(this::class.java.simpleName, "onSave...\n${Message.tms.get(keys).data()}")
        }
        Message.tms.onCreate { keys ->
            //Log.d(this::class.java.simpleName, "onCreate...\n${Message.tms.get(keys).data()}")
        }
        Message.tms.onUpdate { keys ->
            //Log.d(this::class.java.simpleName, "onUpdate...\n${Message.tms.get(keys).data()}")
        }
        Message.tms.onDelete { keys ->
            //Log.d(this::class.java.simpleName, "onDelete...\n")
        }
        Message.tms.onModelChange { keys ->
            //Log.d(this::class.java.simpleName, "onModelChange...\n")
        }
    }

    fun filter() {

        // 🔍 1. Messagers dont le nom a au moins deux mots et une majuscule à la 2e lettre
        val messagers = Messager.tms.all().filter { messager ->
            val name = messager.name.get()
            name.split(" ").size >= 2 && name.getOrNull(1)?.isUpperCase() == true
        }
        Log.d("FILTER", "1️⃣ Messagers (2 mots, majuscule 2e lettre):\n" + Messager.data(messagers, Messager.serial))

        // 🔍 2. ChanelEditor où le messager est actif ET le rôle est creator ou admin
        val editors = ChanelEditor.tms.all().filter { editor ->
            val role = editor.role
            val isActive = editor.messager.get().isActive() // à adapter selon ton modèle
            isActive && (role == MessagerRole.creator() || role == MessagerRole.admin())
        }
        Log.d("FILTER", "2️⃣ ChanelEditors actifs (creator/admin):\n" + ChanelEditor.data(editors, ChanelEditor.serial))

        // 🔍 4. MessagingMember dans des Messaging publics avec > 3 membres
        val members = MessagingMember.tms.all().filter { member ->
            val messaging = member.messaging.get()
            messaging.typ == MessagingType.publicType() &&
                    messaging.members().size > 3
        }
        Log.d("FILTER", "4️⃣ Membres dans Messaging publics avec >3 membres:\n" + MessagingMember.data(members, MessagingMember.serial))

        // 🔍 5. Messagings publics contenant au moins un message avec mot-clé spécifique
        val messagingsWithKeywords = Messaging.tms.all().filter { messaging ->
            messaging.typ == MessagingType.publicType() &&
                    Message.tms.all().any { msg ->
                        msg.messaging == messaging &&
                                msg.content.get().contains("urgent", ignoreCase = true)
                    }
        }
        Log.d("FILTER", "5️⃣ Messagings publics avec message 'urgent':\n" + Messaging.data(messagingsWithKeywords, Messaging.serial))
    }

}