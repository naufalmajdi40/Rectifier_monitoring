void sendModbus(){
  Serial.print("bacamodbus");
  Serial.println(flag);
  uint16_t crc = calcCRC(perintah[flag], sizeof(perintah[flag]));
  Serial2.write(perintah[flag], sizeof(perintah[flag]));
  Serial2.write(lowByte(crc));
  Serial2.write(highByte(crc));
  while (Serial2.available()>0)
  {
   byte b = Serial2.read();
    *ptr ++= b;
     dtSerial+=(String)b;
    Serial.print(b);
    delay(2);
  }
  int count = dtSerial.indexOf("444");
  dtSerial="";
    memcmp(bufferDataModbus, perintah[flag], 2);
    ptr = bufferDataModbus;

    
    if (ptr[0] ==1) {
       teg1      = ((ptr[3] << 8) + ptr[4]) * 0.01;
 }
    else if (ptr[0] == 2) {
      teg2      = ((ptr[3] << 8) + ptr[4]) * 0.01;
  }
    if (flag == 2) {
       temp1 = ((ptr[24] << 8)+ptr[25])*0.1;
       hum1 =((ptr[26] << 8)+ptr[27])*0.1;
  }

  
}
uint16_t calcCRC(byte *data, byte panjang)
{
  int i;
  uint16_t crc = 0xFFFF;
  for (byte p = 0; p < panjang; p++)
  {
    crc ^= data[p];
    for (i = 0; i < 8; ++i)
    {
      if (crc & 1)
        crc = (crc >> 1) ^ 0xA001;
      else
        crc = (crc >> 1);
    }
  }
  return crc;
}
