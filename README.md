# IoT Environmental Monitor

## Developer 1: MQTT Broker & Python Listener (Completed)
- **Broker:** Mosquitto on port `1883` (`allow_anonymous true`)
- **Topic:** `room/#` (ESP32 publishes to `room/environment`)
- **Payload Format:** `{"temp": 24.5, "air_quality": 180}`
- **Alert Thresholds:** `temp > 30.0°C`, `air_quality > 400`

### Run Listener
```bash
python3 listener.py

