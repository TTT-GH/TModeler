from django.shortcuts import render

from .models import *
from .serializers import *

from TModeler.views.core import *
from TModeler.registers.core import *

class UserAPIView(TAPIView):
    model = User
    serializer = UserSerializer
    register.register(model, serializer)




class MessagerAPIView(TAPIView):
    model = Messager
    serializer = MessagerSerializer
    register.register(model, serializer)

class ChanelContextAPIView(TAPIView):
    model = ChanelContext
    serializer = ChanelContextSerializer
    register.register(model, serializer)

class MessagerRoleAPIView(TAPIView):
    model = MessagerRole
    serializer = MessagerRoleSerializer
    register.register(model, serializer)

class MessagingTypeAPIView(TAPIView):
    model = MessagingType
    serializer = MessagingTypeSerializer
    register.register(model, serializer)

class MessagingMemberAPIView(TAPIView):
    model = MessagingMember
    serializer = MessagingMemberSerializer
    register.register(model, serializer)

class ChanelTypeAPIView(TAPIView):
    model = ChanelType
    serializer = ChanelTypeSerializer
    register.register(model, serializer)

class ChanelEditorAPIView(TAPIView):
    model = ChanelEditor
    serializer = ChanelEditorSerializer
    register.register(model, serializer)

class ChanelAPIView(TAPIView):
    model = Chanel
    serializer = ChanelSerializer
    register.register(model, serializer)

class MessagingAPIView(TAPIView):
    model = Messaging
    serializer = MessagingSerializer
    register.register(model, serializer)

class MessageAPIView(TAPIView):
    model = Message
    serializer = MessageSerializer
    register.register(model, serializer)