from django.db import models

from TModeler.fields.core import *
from TModeler.models.core import *

# Create your models here.


class TMedia(TModel):
    desc = models.CharField(max_length=255, null=True, blank=True)
    image = models.ImageField(upload_to="images/", blank=True, null=True)

class User(TModel):
    phone = models.CharField(unique=True, max_length=20, default=None, blank=True, null=True)
    email = models.EmailField(unique=True, default=None, blank=True, null=True)
    password = models.CharField(max_length=128, default=None, blank=True, null=True)
    username = models.CharField(max_length=50, default=None, blank=True, null=True)
    first_name = models.CharField(max_length=50, default=None, blank=True, null=True)
    last_name = models.CharField(max_length=50, default=None, blank=True, null=True)
    dob = models.DateField(default=None, blank=True, null=True)
    sex = models.IntegerField(default=0, blank=True, null=True)

class Messager(TModel):
    phone = models.CharField(unique=True, max_length=20, default=None, null=True, blank=True)
    name = models.CharField(max_length=255, null=True, blank=True)
    photo = models.ForeignKey(TMedia, on_delete=models.SET_NULL, null=True, blank=True)

class ChanelContext(TModel):
    route = models.CharField(max_length=255, null=True, blank=True)
    description = models.CharField(max_length=255, null=True, blank=True)

class MessagerRole(TModel):
    title = models.CharField(max_length=255, null=True, blank=True)
    description = models.CharField(max_length=255, null=True, blank=True)

class MessagingType(TModel):
    title = models.CharField(max_length=255, null=True, blank=True)
    description = models.CharField(max_length=255, null=True, blank=True)

class MessagingMember(TModel):
    messager = models.ForeignKey(Messager, on_delete=models.SET_NULL, null=True, blank=True)
    role = models.ForeignKey(MessagerRole, on_delete=models.SET_NULL, null=True, blank=True)
    messaging = models.ForeignKey('Messaging', on_delete=models.SET_NULL, null=True, blank=True)

class ChanelType(TModel):
    title = models.CharField(max_length=255, null=True, blank=True)
    description = models.CharField(max_length=255, null=True, blank=True)

class ChanelEditor(TModel):
    messager = models.ForeignKey(Messager, on_delete=models.SET_NULL, null=True, blank=True)
    role = models.ForeignKey(MessagerRole, on_delete=models.SET_NULL, null=True, blank=True)
    chanel = models.ForeignKey('Chanel', on_delete=models.SET_NULL, null=True, blank=True)

class Chanel(TModel):
    name = models.CharField(max_length=255, null=True, blank=True)
    context = models.ForeignKey(ChanelContext, on_delete=models.SET_NULL, null=True, blank=True)
    typ = models.ForeignKey(ChanelType, on_delete=models.SET_NULL, null=True, blank=True)
    pv_messagings = models.ManyToManyField('Messaging', related_name='pv_messaging', symmetrical=False, blank=True, default=dict)
    pb_messagings = models.ManyToManyField('Messaging', related_name='pb_messaging', symmetrical=False, blank=True, default=dict)
    sub_chanels = models.ManyToManyField('Chanel', related_name='subs', symmetrical=False, blank=True, default=dict)

class Messaging(TModel):
    name = models.CharField(max_length=255, null=True, blank=True)
    typ = models.ForeignKey(MessagingType, on_delete=models.SET_NULL, null=True, blank=True)
    photos = models.ManyToManyField(TMedia, symmetrical=False, blank=True, default=dict)
    message = models.ForeignKey('Message', on_delete=models.SET_NULL, null=True, blank=True, related_name='ref_message')

class Message(TModel):
    content = models.TextField(null=True, blank=True)
    loc = models.CharField(max_length=255, null=True, blank=True)
    creator = models.ForeignKey(Messager, on_delete=models.SET_NULL, null=True, blank=True)
    messaging = models.ForeignKey(Messaging, on_delete=models.SET_NULL, null=True, blank=True, related_name='parent')