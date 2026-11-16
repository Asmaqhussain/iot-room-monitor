# IoT Environmental Monitor

An end-to-end IoT monitoring pipeline using a simulated ESP32 sensor node in Wokwi, a public MQTT broker, and a Python telemetry listener running on an Ubuntu VM.

## MQTT Broker & Telemetry Stream
* **Broker:** `broker.hivemq.com` on port `1883`
* **Publish Topic:** `asmaq/iot/room/environment`
* **Subscribe Topic:** `asmaq/iot/room/#`
* **Payload Format:** `{"temp": 24.5, "air_quality": 180.0}`
* **Alert Thresholds:**
  * Temperature: `temp > 30.0°C`
  * Hazardous Gas / Air Quality: `air_quality > 400`

## Repository Structure
* `listener.py` — Python (`paho-mqtt`) subscriber running on the Ubuntu VM that receives real-time JSON telemetry, prints threshold alerts, and logs data.
* `telemetry_log.txt` — Timestamped log file storing incoming sensor readings.
* `esp32_sensor/sketch.ino` — ESP32 firmware reading temperature (DHT22) and air quality (Potentiometer) and publishing every 3 seconds.
* `esp32_sensor/diagram.json` — Wokwi circuit wiring layout (DHT22 on GPIO `15`, Potentiometer on GPIO `34`).

## Quick Start for Team Members
1. **Subscribe to the Live Data Stream:** Connect any MQTT client, dashboard, or database consumer to `broker.hivemq.com:1883` and subscribe to `asmaq/iot/room/#`.
2. **Run the Python Listener Locally:**
   ```bash
   pip install paho-mqtt
   python3 listener.py
