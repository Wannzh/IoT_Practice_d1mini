# ESP8266 WEMOS - Kontrol LED via MQTT

Proyek IoT untuk mengontrol LED menggunakan papan development **WEMOS D1 Mini** (berbasis ESP8266) melalui protokol **MQTT**. Proyek ini dikembangkan dengan PlatformIO dan Arduino framework.

## 📋 Daftar Isi
- [Fitur](#fitur)
- [Spesifikasi Hardware](#spesifikasi-hardware)
- [Instalasi](#instalasi)
- [Konfigurasi](#konfigurasi)
- [Penggunaan](#penggunaan)
- [Struktur Proyek](#struktur-proyek)

## ✨ Fitur

- ✅ Koneksi WiFi otomatis ke jaringan lokal
- ✅ Integrasi MQTT untuk kontrol jarak jauh
- ✅ Dua channel LED (LED Hijau & LED Merah)
- ✅ Publish status LED ke broker MQTT
- ✅ Subscribe ke topic kontrol untuk menerima perintah
- ✅ Serial monitoring untuk debugging

## 🔧 Spesifikasi Hardware

| Komponen | Spesifikasi |
|----------|------------|
| **Papan** | WEMOS D1 Mini (ESP8266) |
| **Flash** | 4MB |
| **RAM** | 160KB |
| **GPIO** | 11 pin digital |
| **LED 1** | D2 (GPIO4) - LED Hijau |
| **LED 2** | D1 (GPIO5) - LED Merah |
| **Serial** | 115200 baud |

## 📥 Instalasi

### Prasyarat
- [PlatformIO IDE](https://platformio.org/) atau extension untuk VS Code
- Python 3.6+
- USB cable untuk WEMOS D1 Mini

### Langkah Instalasi

1. **Clone atau download proyek ini**
   ```bash
   git clone <repository-url>
   cd ESP8266-WEMOS
   ```

2. **Install dependencies**
   ```bash
   platformio lib install
   ```

3. **Build proyek**
   ```bash
   platformio run
   ```

4. **Upload ke board**
   ```bash
   platformio run --target upload
   ```

## ⚙️ Konfigurasi

Edit file `src/main.cpp` dan ubah konfigurasi berikut sesuai kebutuhan:

### WiFi Configuration
```cpp
const char *ssid = "ssid wifi sendiri";
const char *password = "password wifi sendiri";
```

### MQTT Configuration
```cpp
const char *mqtt_server = "server mqtt";
const int mqtt_port = 1883;  // ganti dengan port MQTT Anda
const char *mqtt_user = "username mqtt";
const char *mqtt_pass = "password mqtt";
```

### MQTT Topics
```cpp
const char *TOPIC_CONTROL = "esp8266/led";    // Subscribe
const char *TOPIC_STATUS = "esp8266/status";  // Publish
const char *TOPIC_STATE = "esp8266/state";    // Publish
```

## 📡 Penggunaan

### Kontrol LED via MQTT

**Publish pesan ke topic `esp8266/led`:**

```
Payload: {"green": 1, "red": 0}   // LED Hijau ON, Merah OFF
Payload: {"green": 0, "red": 1}   // LED Hijau OFF, Merah ON
Payload: {"green": 1, "red": 1}   // Kedua LED ON
```

### Monitoring

Buka Serial Monitor untuk melihat status koneksi:
```bash
platformio device monitor --speed 115200
```

Atau gunakan extension PlatformIO di VS Code dengan membuka Serial Monitor.

## 📁 Struktur Proyek

```
ESP8266-WEMOS/
├── platformio.ini          # Konfigurasi PlatformIO
├── README.md              # Dokumentasi proyek (file ini)
├── src/
│   └── main.cpp          # Kode utama ESP8266
├── include/
│   └── README            # Folder untuk header files
├── lib/
│   └── README            # Folder untuk custom libraries
└── test/
    └── README            # Folder untuk test files
```

## 🔗 Dependencies

- **PubSubClient** v2.8.0+ - MQTT client library
- **ESP8266WiFi** - Built-in WiFi library (Arduino Framework)
- **Arduino** - Arduino core for ESP8266

## 🐛 Troubleshooting

### WiFi tidak terkoneksi
- Pastikan SSID dan password WiFi benar
- Periksa signal WiFi di lokasi board
- Cek baud rate serial (115200)

### MQTT tidak terkoneksi
- Verifikasi broker MQTT aktif dan accessible
- Pastikan hostname/IP MQTT server benar
- Periksa username dan password MQTT
- Pastikan port MQTT sesuai (default: 1883)

### LED tidak menyala
- Periksa koneksi kabel LED ke pin D1 dan D2
- Verifikasi polaritas LED (anoda/katoda)
- Test dengan mengirim perintah MQTT

## 📝 Lisensi

Proyek ini dibuat untuk keperluan akademis (Model Simulasi - Semester 5).

## 📧 Kontak

Untuk pertanyaan atau saran, silakan hubungi pengembang proyek.

---

**Last Updated:** 17 Januari 2026
