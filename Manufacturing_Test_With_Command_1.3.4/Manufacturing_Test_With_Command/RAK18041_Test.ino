#ifdef RAK18041_MODULE

#include "Production_test_configure.h"
#include <I2S.h>          // Arduino I2S 库
#include "audio.h"        // NAU85L40B 驱动库，请确保已安装

#define I2S_DATA_BLOCK_WORDS  512

void RAK18041_test(unsigned long timeout)
{
    unsigned long start = millis();
    bool test_passed = false;

    // 给模块供电 (WB_IO2 通常用于控制外设电源)
    pinMode(WB_IO2, OUTPUT);
    digitalWrite(WB_IO2, HIGH);
    delay(500);   // 等待电源稳定

    Wire.begin();          // 初始化 I2C（用于配置 NAU85L40B）

    NAU85L40B mic(0x1D);   // 创建麦克风对象，I2C 地址 0x1D

    if (!mic.begin()) {
        Serial.printf("RAK18041: MIC begin failed\n");
        digitalWrite(WB_IO2, LOW);
        Serial.printf("RAK18041 Test Failed\n");
        return;
    }

    // 配置为 16kHz、立体声、16 位
    mic.config(16000, (MIC_CHANNEL1 | MIC_CHANNEL2), I2S_SAMPLE_16BIT);

    // 配置并启动 I2S
    I2S.begin(Stereo, 16000, 16);
    I2S.start();
    delay(100);   // 等待数据流稳定

    uint32_t readbuff[I2S_DATA_BLOCK_WORDS] = {0};

    // 在超时时间内尝试读取有效数据
    while (millis() - start < timeout) {
        size_t bytes_read = I2S.read(readbuff, sizeof(readbuff));
        if (bytes_read > 0) {
            // 简单检查是否有非零采样值
            for (int i = 0; i < I2S_DATA_BLOCK_WORDS; i++) {
                if (readbuff[i] != 0) {
                    test_passed = true;
                    break;
                }
            }
            if (test_passed) break;
        }
        delay(10);
    }

    I2S.stop();
    digitalWrite(WB_IO2, LOW);   // 关闭模块电源

    if (test_passed) {
        Serial.printf("RAK18041 Test OK\n");
    } else {
        Serial.printf("RAK18041 Test Failed\n");
    }
}

#endif