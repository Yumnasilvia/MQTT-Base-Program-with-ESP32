import paho.mqtt.client as mqtt

TOPIC_SUB = 'sensor/data'
IP_BROKER = "IP_BROKER" # IP JETSON NANO (SERVER)
PORT = 1883

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe(TOPIC_SUB)

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(IP_BROKER, PORT, 60)

client.loop_forever()
