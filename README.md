# Esp32Hole

ESP32 ad blocker based on host list.

## How to install

### Preprocess the hosts file

The first versions uploaded the full hosts file to the SPIFFS. The performance of finding the domain in the full hosts file was really poor, so for the current version the hosts file is preprocessed and stored in smaller files based on the lenght of the domain

```sh
cd utils
gen_block_lists.sh
```

This downloads the hosts file and saves it in different files in the *data* directory

### Upload LittleFS

* Follow the guide [Arduino IDE 2: Install ESP32 LittleFS Uploader (Upload Files to the Filesystem)](https://randomnerdtutorials.com/arduino-ide-2-install-esp32-littlefs/)
* In Arudino IDE go to `F1 -> Upload LittleFS to ESP32`.
* This copies all the `/data` contents next to the `ino` onto the board.

### Usage

* In the `ino` change `wifi_ssid` & `wifi_password` to your wifi credentials.
* Move generated hosts folder next to `ino`
* Upload

### Test

* At the start of the prgram the IP of the ESP is printed.
* `nslookup - <IP>`
* On success

```txt
Domain: notad.com | IP:X.X.X.X
Resolve took 70 ms | Find took 57 ms
```

* On block

```txt
Domain: ad.com | Blocked
Find took 15 ms
```
