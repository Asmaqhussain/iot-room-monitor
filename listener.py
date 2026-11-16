import json
from datetime import datetime
import paho.mqtt.client as mqtt

BROKER_IP = "broker.hivemq.com"
PORT = 1883
TOPIC = "asmaq/iot/room/#"

TEMP_THRESHOLD = 30.0
GAS_THRESHOLD = 400

def on_connect(client, userdata, flags, reason_code, properties):
    print(f"[INFO] Connected to MQTT Broker (Code: {reason_code})")
    client.subscribe(TOPIC)
    print(f"[INFO] Subscribed to topic: {TOPIC}\n")

def on_message(client, userdata, msg):
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    payload_str = msg.payload.decode("utf-8")
    print(f"[{timestamp}] {msg.topic} -> {payload_str}")

    try:
        data = json.loads(payload_str)
        temp = float(data.get("temp", 0))
        gas = float(data.get("air_quality", 0))

        if temp > TEMP_THRESHOLD:
            print(f"  🚨 ALERT: High temperature detected ({temp}°C)!")
        if gas > GAS_THRESHOLD:
            print(f"  🚨 ALERT: Hazardous gas level detected ({gas})!")

        with open("telemetry_log.txt", "a") as log_file:
            log_file.write(f"[{timestamp}] {msg.topic} | {payload_str}\n")

    except (json.JSONDecodeError, ValueError):
        print("  ⚠️ Warning: Received invalid JSON format.")

client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_message = on_message

client.connect(BROKER_IP, PORT, 60)
client.loop_forever()
