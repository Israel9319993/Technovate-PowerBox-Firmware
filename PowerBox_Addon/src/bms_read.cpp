#include "bms_read.h"
#include "buzzer_alert.h"

uint8_t modbusRequest[] = {0x01, 0x03, 0x00, 0x80, 0x00, 0x0B, 0x05, 0xE5};
unsigned long lastSendTime = 0;

extern Buzzer buzzerAlert;

ReadBMS::ReadBMS() {}

void ReadBMS::BMSInit(uint8_t rxPin, uint8_t txPin, uint32_t baudRate)
{

    Serial2.begin(9600, SERIAL_8N1, rxPin, txPin); // Initialize Serial2 with 9600 baud rate, 8 data bits, no parity, 1 stop bit

    // Invert TX and RX signals to match BMS logic
    uart_set_line_inverse(UART_NUM_2, UART_SIGNAL_RXD_INV | UART_SIGNAL_TXD_INV);
}

void ReadBMS::sendModbusRequest()
{
    // Send the Modbus request to the BMS
    if (millis() - lastSendTime >= 1000)
    {
        // Serial.println("Sending Modbus request...");
        Serial2.write(modbusRequest, sizeof(modbusRequest));
        lastSendTime = millis();
    }
}

void ReadBMS::readModbusResponse()
{
    sendModbusRequest(); // Send the Modbus request to the BMS

    uint8_t response[64];
    int index = 0;
    unsigned long startTime = millis();

    // Wait for response (max 200 ms)
    while (millis() - startTime < 200)
    {
        while (Serial2.available())
        {
            uint8_t b = Serial2.read();
            if (index < sizeof(response))
            {
                response[index++] = b;
            }
        }
    }

    // Parse only if valid Modbus response
    if (index >= 3 && response[0] == 0x01 && response[1] == 0x03)
    {
        uint8_t byteCount = response[2];

        if (index >= (3 + byteCount + 2))
        {
            // Extract values and round to 2 decimal places
            uint16_t value = ((response[3] << 8) | response[4]);

            sign = (value > maxPositvieValue) ? "-" : "+"; // Determine sign based on value
            if (value > maxPositvieValue)
            {
                // value = value - 65536; // Convert to negative value
                // Serial.println("greater than maxPositvieValue: " + String(value));
                bmsCurrent = round(((value - (maxPositvieValue*2)) / 100.0) * 100) / 100.0; // Round to 2 decimal places
                deviceState = "discharging";
            }
            else if (value == 0)
            {
                bmsCurrent = 0.0; // Set to 0 if value is 0
                deviceState = "idle";
            }
            
            else if (value < maxPositvieValue){
                value = value;
                Serial.println("less than maxPositvieValue: " + String(value));
                bmsCurrent = round(((value ) / 100.0) * 100) / 100.0; // Round to 2 decimal places
                deviceState = "charging";
            }
        

            // Serial.println("Original Value: " + String(value));
    
            bmsVoltage = round(((response[5] << 8) | response[6]) / 100.0 * 100) / 100.0;
            bmsSOC = round(((response[7] << 8) | response[8]) / 100.0 * 100);
            bmsSOH = round(((response[9] << 8) | response[10]) / 100.0 * 100);
            bmsRCC = round(((response[11] << 8) | response[12]) / 100.0 * 100) / 100.0;
            bmsFCC = round(((response[13] << 8) | response[14]) / 100.0 * 100) / 100.0;
            chargeCycles = (response[17] << 8) | response[18];

            // uint16_t value5  = (response[11] << 8) | response[12];
            // uint16_t value6  = (response[13] << 8) | response[14];
            // uint16_t value7  = (response[15] << 8) | response[16];
            // uint16_t value8  = (response[17] << 8) | response[18];
            // uint16_t value9  = (response[19] << 8) | response[20];
            // uint16_t value10 = (response[21] << 8) | response[22];
            // uint16_t value11 = (response[23] << 8) | response[24];

            // // Print parsed variables
            // Serial.println("\n--- Parsed BMS Variables ---");
            // Serial.println("Current: " + String(bmsCurrent) + " A");
            // Serial.print("Voltage: ");
            // Serial.println(bmsVoltage);
            // Serial.print("SOC: ");
            // Serial.println(bmsSOC);
            // Serial.print("SOH: ");
            // Serial.println(bmsSOH);
            // Serial.print("RCC: ");
            // Serial.println(bmsRCC);
            // Serial.print("FCC: ");
            // Serial.println(bmsFCC);
            // Serial.print("Charge Cycles: ");
            // Serial.println(chargeCycles);

            // // Optional: print remaining values
            // Serial.print("Value5: "); Serial.println(value5);
            // Serial.print("Value6: "); Serial.println(value6);
            // Serial.print("Value7: "); Serial.println(value7);
            // Serial.print("Value8: "); Serial.println(value8);
            // Serial.print("Value9: "); Serial.println(value9);
            // Serial.print("Value10: "); Serial.println(value10);
            // Serial.print("Value11: "); Serial.println(value11);
        }
        else
        {
            Serial.println("Incomplete response received.");
        }
    }
    else
    {
        static unsigned long lastInvalidResponseTime = 0;
        if (millis() - lastInvalidResponseTime >= 4000) {
            Serial.println("Invalid or no response.");
            buzzerAlert.PlayWarning();
            lastInvalidResponseTime = millis();
        }

    }
}
