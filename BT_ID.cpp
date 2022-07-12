// Скрипт для разбора BLE метки 
// Пример датчика: Vd28994 D2:89:94:79:5A:07    
//сообщение: 02 0A 00 0F  16 10 73 05  12 1E 4B 0F  A4 99 4E CE  B5 31 F4 08  09 56 64 32  38 39 39 34
// 
main()
{
    #define LEN_ID 6
    #define BLUE_TOOTH_0 0x70

    const timeout = 2000
    const LEN_MAC = 6

    new MAC{LEN_MAC} = {0xEB, 0x62, 0xC9, 0x54, 0x24, 0x89}  // MAC: EB:62:C9:54:24:89
    new message[BTMSG]  // объявление структуры сообщения BLUETOOTH
    new num = 0
    new lastID = 0
    new lastRSSI = -100
    new nearID = 0
    new id = 0
    new idx = 0
    new dec = 1
    new hex = 1
    new lastTime = 0
    new tmp[1] = 0
    // Delay(timeout)
    // DiagnosticsHex(MAC, LEN_MAC)

    BTInit()  // инициализация BLUETOOTH
    
    while(1)
    {
        if(BTReceive(message, timeout) && message.dataSize > LEN_ID && message.data{message.dataSize - LEN_ID - 1} == 0x56)
        {
            // Diagnostics("Received")
            // Diagnostics("\nMAC: %X:%X:%X:%X:%X:%X", message.mac{0}, message.mac{1}, message.mac{2}, message.mac{3}, message.mac{4}, message.mac{5})
            // Diagnostics("RSSI: %d", message.rssi | 0xFFFFFF00)
            // Diagnostics("Data: size %d", message.dataSize)
            DiagnosticsHex(message.data, message.dataSize)

            // dec = 1
            // id = 0
            // for(new i = LEN_ID - 1; i >= 0; i--)
            // {
            //     num = message.data{message.dataSize - LEN_ID + i} - 48
            //     id =id + num * dec
            //     dec = dec * 10
            // }

            // hex = 1
            // idx = 0
            // for(new i = LEN_ID - 1; i >= 0; i--)
            // {
            //     num = message.data{message.dataSize - LEN_ID + i} - 48
            //     id =id + num * hex
            //     hex = hex * 16
            // }


            for(new i = LEN_ID; i > 0; i--)
            {
                num = message.data{message.dataSize - LEN_ID + i} - 48
                if(num > 16){
                    num = num - 39
                }
                id =id + num * hex
                hex = hex * 16
                
            }

            // for(new i = 0; i < 4; i++)
            // {
            //     tmp{i} = message.data{message.dataSize - LEN_ID + 2}
            // }
            // id = tmp[0]
            // Diagnostics("%d >= %d", lastRSSI, message.rssi | 0xFFFFFF00)
            lastTime = GetVar(TIME)
            Diagnostics("time: %d ID: %d :: %x rssi: %d", lastTime, id, idx, (message.rssi | 0xFFFFFF00))
            if(lastRSSI <= message.rssi | 0xFFFFFF00)
            {
                nearID = id
                lastRSSI = message.rssi | 0xFFFFFF00
                Diagnostics("new ID: %d::%x", nearID, nearID)
                TagWriteValue(BLUE_TOOTH_0, nearID)
            }

            
        }

        if((lastTime + 60) < GetVar(TIME))
        {
            lastRSSI = -100
            // Diagnostics("%d-%d::%d --> BLUE_TOOTH_0", lastTime, GetVar(TIME), nearID)
            TagWriteValue(BLUE_TOOTH_0, -1)
        }

        Delay(100)
    }
}