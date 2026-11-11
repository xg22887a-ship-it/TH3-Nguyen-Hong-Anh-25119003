# TH3-Nguyen-Hong-Anh-25119003

---

## Nguyễn Hồng Anh - 25119003 - Thực hành 3 - Thí nghiệm 2

Minh chứng và code ở trong các folders tương ứng của mỗi bài !

### TH3 · Tầng mạng trên ESP32 — Nhóm3

#### Bài 1 · Wi-Fi: Access Point và Station

**SSID nhóm đã đặt:** nhom3 (pass `password123`)

| **Ví dụ** | **Kết quả** |
| --- | --- |
| VD1 · Access Point | IP của AP: **192.168.4.1** — điện thoại quét thấy SSID nhom3 |
| VD2 · Station | Nối vào router (2,4 GHz), IP nhận được: **192.168.0.101** (gateway 192.168.0.1) |

[serial_monitor_vd2](bai_1/vd2_station/minh_chung/serial_vd2.jpg) · [serial_monitor_vd1](bai_1/vd1_access_point/minh_chung/serial_vd1.jpg)

#### Bài 2 · BLE: ESP32 làm server

| **Yêu cầu** | **Kết quả** |
| --- | --- |
| Tên thiết bị BLE | nhom3 — nRF Connect quét thấy và kết nối được |
| Giá trị đặc tính | MSSV 25119003 — đọc được trên nRF Connect |
| `PROPERTY_WRITE` | Ghi cho hôn miếng → đọc lại thấy giá trị mới |

Log Serial: `Dien thoai DOC: MSSV 25119003` → `Dien thoai GHI gia tri moi: Hihi chao cau` → `Dien thoai DOC: Hihi chao cau`.

#### Bài 3 · ESP-NOW: hai kit nói trực tiếp

*(Chưa làm — cần 2 kit ESP32.)*

#### Bài 4 · HTTP: web server điều khiển LED

LED → GPIO 2. ESP32 làm Station, web server cổng 80 tại [**http://192.168.0.101**](http://192.168.0.101), các route `/`, `/on`, `/off`, `/toggle`. Trang hiển thị rõ **LED đang BẬT / LED đang TẮT**; bấm nút trên điện thoại cùng mạng → LED đổi trạng thái.

#### Bài 5 · MQTT: publish/subscribe

Broker `test.mosquitto.org:1883`, client id `esp32-nhom3-<MAC>` (khác nhau cho mỗi kit).

| **Topic** | **Vai trò** | **Kết quả** |
| --- | --- | --- |
| `bica/th3/nhom3` | ESP32 publish số đếm mỗi 2 s | App MQTT nhận số đếm tăng dần |
| `bica/th3/nhom3/led` | ESP32 subscribe lệnh LED | Publish `1` → LED bật, `0` → LED tắt |
