# IoT-Data-Logger
The IoT-based data logger employs an ESP32 Dev-Kit microcontroller interfaced with multiple sensors for real-time environmental data acquisition and transmission. The system components include the MQ-135 gas sensor, DHT11 temperature and humidity sensor, TEMT6000 light sensor, BMP180 pressure sensor, a Vero board with jumper cables for connectivity, and a stable power supply.  

Sensor data is collected periodically, with the MQ-135 monitoring air quality, the DHT11 measuring temperature and humidity, the TEMT6000 recording ambient light intensity, and the BMP180 tracking atmospheric pressure and altitude. These sensors generate analog or digital outputs, which are processed by the ESP32.  

The ESP32’s onboard Wi-Fi module enables seamless data transmission. A pre-configured cloud-based script (e.g., Google Apps Script) facilitates data upload to Google Sheets every 10 seconds, ensuring continuous and synchronized logging. The Vero board organizes connections, enhancing system reliability.  

This implementation offers a robust, cost-effective solution for environmental monitoring, with real-time data storage accessible remotely for analysis and decision-making.
