package com.tm.tests

import android.annotation.SuppressLint
import api.ttt.db.modeler.thc.THC
import api.ttt.db.modeler.thc.model.TNodeToken
import com.tm.tests.thc.ChatBox
import com.tm.tests.thc.Message
import com.tm.tests.thc.User
import java.time.LocalDateTime

object Thc {
    @SuppressLint("NewApi")
    fun test() {
        // === 📋 [0] Initialisation des utilisateurs ===
        val u1 = User.tms.all().first()
        val u2 = User.tms.all().second()
        val u3 = User.tms.all()[2]
        val u4 = User.tms.all()[3]
        val u5 = User.tms.all()[4]

        // === 🔐 [1] Message privé : u1 -> u2 ===
        val m1 = Message()
        m1.content.from(u1).to(u2).set("Bonjour User U2")
        m1.save()

        // === 🔁 [2] Changement de token de u1 (nouvelle paire de clés) ===
        val newToken = TNodeToken()
        newToken.generate(u1.token.get()) // basé sur l'ancien
        newToken.save()
        u1.token.set(newToken) // nouvelle clé privée pour u1

        // === 👁️ [3] u2 lit le message de u1 ===
        val received = Message.tms.all().last() // dernier message
        val readContent = received.content.from(u1).to(u2).get()
        assert(readContent == "Bonjour User U2")

        // === 🔁 [4] Transfert du message à u3 (transfert autorisé) ===
        val m1_forwarded = Message()
        val contentForU3 = m1.content.from(u1).to(u2).transfert(u3)
        m1_forwarded.content.set(contentForU3)
        m1_forwarded.save()

        // === ✅ [5] Donnée publique authentifiée : âge de u1 ===
        u1.age.securityLevel(THC.SECURE_LOW)
        u1.age.from(u1).set(24) // signé par u1
        val certifiedAge = u1.age.from(u1).get()
        assert(certifiedAge == 24L)

        // === ⚠️ [6] Tentative d’usurpation : âge modifié par u3 ===
        u1.age.from(u3).set(99) // écrasé par u3
        val badAge = u1.age.from(u3).get()
        assert(
            badAge == null // rejeté car non signé par u1
        )

        // === 💬 [7] Message public de u4 (non privé) ===
        val publicComment = Message()
        publicComment.content.from(u4).set("Bonjour User U1")
        publicComment.save()

        // === 👥 [8] Création d’un groupe avec 5 utilisateurs ===
        val group = ChatBox()
        group.name.set("Group 1")
        group.members.add(u1, u2, u3, u4, u5)
        group.save()

        // === 📢 [9] Message de groupe envoyé par u3 ===
        val groupMsg = Message()
        groupMsg.content.securityLevel(THC.SECURE_MEDIUM)
        groupMsg.content.from(u3).to(group).set("Hi everyone!!")
        groupMsg.save()

        // === 👀 [10] Tous les membres lisent le message de groupe ===
        for (user in group.members) {
            if (groupMsg.content.from(u3).to(group).granted(user)) {
                val content = groupMsg.content.from(u3).to(group).get()
                assert(content == "Hi everyone!!")
            }
        }

        // === 🕒 [11] Lecture horodatée et gestion d'accusé de réception ===
        // gestion via l’état de message (fallback)
        if (groupMsg.content.from(u3).to(group).granted(u4)) {
            val state = groupMsg.state.get()
            state.received(LocalDateTime.now())
            groupMsg.content.from(u3).to(group).get()
            state.read(LocalDateTime.now())
            state.save()
        }

        // === ⛔ [12] Tentative de lecture interdite par u5 ===
        val leakTry = m1.content.from(u1).to(u5).get()
        assert(
            leakTry == null // refusé car non autorisé
        )

        // === 🧠 [13] Transfert refusé sur message non-transférable ===
        val strictMessage = Message()
        strictMessage.content.from(u1).to(u2).set("Donnée ultra sécurisée")
        strictMessage.content.securityLevel(THC.SECURE_HIGH)
        strictMessage.content.transferable(false) // politique stricte
        strictMessage.save()
        val attemptTransfer = strictMessage.content.from(u1).to(u2).transfert(u3)
        assert(
            attemptTransfer == null // transfert bloqué
        )
        println("✅ Tous les cas de figure sont testés avec succès.")
    }
}
