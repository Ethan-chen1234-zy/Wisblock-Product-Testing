#ifdef RAK13101_MODULE

#define POWER_KEY WB_IO5

// 发送 AT 命令并等待响应
String sendAT(String cmd, uint32_t wait_ms = 1000)
{
  Serial1.println(cmd);
  unsigned long t = millis();
  String resp = "";
  while (millis() - t < wait_ms)
  {
    if (Serial1.available())
    {
      resp += (char)Serial1.read();
    }
    delay(1);
  }
  resp.trim();
  Serial.print("[AT CMD] "); Serial.println(cmd);
  Serial.print("[RESP] "); Serial.println(resp);
  return resp;
}

bool test_lte_signal()
{
    Serial.println("---- LTE Signal Test ----");

    //  检查模块网络注册
//    for (int i = 0; i < 5; i++) 
//    {
//      String reg = sendAT("AT+CREG?", 2000);  // 超时 1 秒
//      if (reg.length() == 0)
//      {
//          Serial.println("LTE Signal Test: (No Response on CREG)");
//          return false;  // 未返回立即失败
//      }
//  
//      if ((reg.indexOf(",1") != -1) || (reg.indexOf(",5") != -1))
//      {
//          //Serial.println("Module registered to network.");
//      }
//      else
//      {
//          //Serial.println("LTE Signal Test: (Module not registered)");
//      }
//    }

    //  查询 RSSI，最多 5 次
    const int maxRetries = 10;
    for (int attempt = 1; attempt <= maxRetries; attempt++)
    {
        String resp = sendAT("AT+CSQ", 1500);  // 超时 1.5 秒
        if (resp.length() == 0)
        {
            Serial.println("LTE Signal Test: (No Response on CSQ)");
            return false;  // 未返回立即失败
        }

        if (resp.indexOf("+CSQ:") != -1)
        {
            int colon = resp.indexOf(":");
            int comma = resp.indexOf(",");
            int rssi = resp.substring(colon + 1, comma).toInt();
            Serial.print("Attempt "); Serial.print(attempt); Serial.print(" - RSSI: "); Serial.println(rssi);

            if (rssi >= 5 && rssi <= 31)
            {
                Serial.println("LTE Signal Test: PASS");
                return true;  // 成功立即返回
            }
            else
            {
                Serial.println("LTE Signal Test: (Weak or No Signal)");
            }
        }
        else
        {
            Serial.println("LTE Signal Test: (Invalid Response)");
        }

        if (attempt < maxRetries)
        {
            Serial.println("Retrying LTE signal test...");
            delay(500);  // 小间隔再重试
        }
    }
    return false;
}

// GNSS 测试函数（最长等待 90 秒，每隔 5 秒读取一次）
// 如果 AT+QGPSLOC=2 没有返回值，则立即判定失败
bool test_gnss()
{
    Serial.println("---- GNSS Test (MC20 RMC) ----");

    // 1. 打开 GNSS 电源
    String resp = sendAT("AT+QGNSSC=1", 2000);
    if (resp.indexOf("OK") == -1)
    {
        Serial.println("Failed to start GNSS!");
        return false;
    }

    Serial.println("Waiting GNSS fix (up to 90s)...");

    const int interval = 5000;      // 5 秒轮询
    const int maxTime = 90000;     // 最大等待 90 秒
    int elapsed = 0;
    float lat = 0.0, lon = 0.0;

    while (elapsed < maxTime)
    {
        String loc = sendAT("AT+QGNSSRD=\"NMEA/RMC\"", 3000);

        // 解析 RMC
        if (loc.indexOf("$GNRMC") != -1)
        {
            int start = 0;
            int idx[10];
            int count = 0;
            while ((start = loc.indexOf(",", start)) != -1 && count < 10)
            {
                idx[count++] = start;
                start++;
            }
            if (count >= 7)
            {
                String latStr = loc.substring(idx[2]+1, idx[3]);
                String latDir = loc.substring(idx[3]+1, idx[4]);
                String lonStr = loc.substring(idx[4]+1, idx[5]);
                String lonDir = loc.substring(idx[5]+1, idx[6]);

                float latDeg = latStr.substring(0,2).toFloat() + latStr.substring(2).toFloat()/60.0;
                float lonDeg = lonStr.substring(0,3).toFloat() + lonStr.substring(3).toFloat()/60.0;

                if (latDir == "S") latDeg = -latDeg;
                if (lonDir == "W") lonDeg = -lonDeg;

                lat = latDeg;
                lon = lonDeg;

                if (lat != 0.0 && lon != 0.0)
                {
                    Serial.print("Latitude: "); Serial.println(lat, 6);
                    Serial.print("Longitude: "); Serial.println(lon, 6);
                    Serial.println("GNSS Test: PASS");

                    // 关闭 GNSS
                    sendAT("AT+QGNSSC=0", 1000);
                    return true;
                }
            }
        }

        Serial.println("RMC not ready yet, retrying...");
        delay(interval);
        elapsed += interval;
    }

    sendAT("AT+QGNSSC=0", 1000);
    return false;
}

void RAK13101_test(unsigned long timeout)
{
  Serial1.begin(9600);
  delay(1000);
  Serial1.println("ATI");

  bool moduleSleeps = true;
  time_t time_now = millis();
  //MC20 init
  while ((millis() - time_now) < 6000)
  {
    if (Serial1.available())
    {
      String result = Serial1.readString();
      Serial.println("Modem response after start:");
      Serial.println(result);
      moduleSleeps = false;
    }
    delay(1);
  }
  if (moduleSleeps)
  {
    // Module slept, wake it up
    pinMode(POWER_KEY, OUTPUT);
    digitalWrite(POWER_KEY, 0);
    delay(200);
    digitalWrite(POWER_KEY, 1);
    delay(2000);
    digitalWrite(POWER_KEY, 0);
    delay(1000);
  }

  Serial.println("RAK13101 Test Begin!");

  // ================
  // 自动化产测流程
  // ================
  bool lte_ok = test_lte_signal();

  if (!lte_ok)
  {
    Serial.println("LTE:FAILED");
    Serial.println("RAK13101 Test Failed!");
    return;
  }

  bool gnss_ok = test_gnss();
  if(!gnss_ok)
  {
    Serial.println("GNSS:FAILED");
    Serial.println("RAK13101 Test Failed!");
    return;
  }
  
  if(lte_ok && gnss_ok)
  {
    Serial.println("RAK13101 Test OK!");
  }

//  // 保留原透传逻辑（手动调试或命令交互）
//  String str_end = "RAK13101_End\r\n";
//  while ((millis() - time_now) < timeout)
//  {
//    int timeout = 100;
//    String resp = "";
//    String snd = "";
//    char cArr[128] = {0};
//    while (timeout--)
//    {
//      if (Serial1.available() > 0)
//      {
//        resp += char(Serial1.read());
//      }
//      if (Serial.available() > 0)
//      {
//        snd += char(Serial.read());
//      }
//      delay(1);
//    }
//    snd += "\r\n";
//    resp += "\r\n";
//    if (snd == str_end)
//    {
//      Serial.println("RAK13101 Test Over");
//      return;
//    }
//    if (resp.length() > 2)
//    {
//      Serial.print(resp);
//    }
//    if (snd.length() > 2)
//    {
//      memset(cArr, 0, 128);
//      snd.toCharArray(cArr, snd.length() + 1);
//      Serial1.write(cArr);
//      delay(10);
//    }
//    resp = "";
//    snd = "";
//  }
}

#endif
