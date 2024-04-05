import paho.mqtt.client as mqtt

#MQTT SETINGS
IP_BROKER = "IP_BROKER" # IP JETSON NANO (SERVER)
USERNAME_BROKER = "MQTTBROKER_USERNAME"
PASS_BROKER = "MQTTBROKER_PASSWORD"
PORT = 1883
TOPIC_SUB = 'sensor/data'

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe(TOPIC_SUB)

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.username_pw_set(USERNAME_BROKER, password=PASS_BROKER)
client.connect(IP_BROKER, PORT, 60)

client.loop_forever()
