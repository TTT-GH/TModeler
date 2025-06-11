from .models import *
from TModeler.serializers.core import *

class UserSerializer(TSerializer):
    class Meta:
        model = User
        fields = '__all__'

        
class MessagerSerializer(TSerializer):
    class Meta:
        model = Messager
        fields = '__all__'

class ChanelContextSerializer(TSerializer):
    class Meta:
        model = ChanelContext
        fields = '__all__'

class MessagerRoleSerializer(TSerializer):
    class Meta:
        model = MessagerRole
        fields = '__all__'

class MessagingTypeSerializer(TSerializer):
    class Meta:
        model = MessagingType
        fields = '__all__'

class MessagingMemberSerializer(TSerializer):
    class Meta:
        model = MessagingMember
        fields = '__all__'

class ChanelTypeSerializer(TSerializer):
    class Meta:
        model = ChanelType
        fields = '__all__'

class ChanelEditorSerializer(TSerializer):
    class Meta:
        model = ChanelEditor
        fields = '__all__'

class ChanelSerializer(TSerializer):
    class Meta:
        model = Chanel
        fields = '__all__'

class MessagingSerializer(TSerializer):
    class Meta:
        model = Messaging
        fields = '__all__'

class MessageSerializer(TSerializer):
    class Meta:
        model = Message
        fields = '__all__'
        