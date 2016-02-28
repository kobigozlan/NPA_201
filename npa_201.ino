  #include <Wire.h>
  
  uint8_t   npadata[5];
  uint16_t  p_tmp,t_tmp;
  float     t,p,alt;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  delay(1000);
  Serial.println("start");
}

void loop() {


readNPA();
readCmd();
printdata();
delay(50);// can be 20mS
}

//for starting collecting data
void readCmd(){
  Wire.beginTransmission(0x27);
  Wire.send(0xAC);
  Wire.endTransmission();
}


// read from slave 0x27 5 byte
void readNPA(){

  Wire.requestFrom(0x27, 5);
  while (Wire.available()) 
  {
     npadata[0] = Wire.read();
     npadata[1] = Wire.read();
     npadata[2] = Wire.read();
     npadata[3] = Wire.read();
     npadata[4] = Wire.read();
   }

    p_tmp =( npadata[2]  |( npadata[1] << 8));
    t_tmp =( npadata[4]  |( npadata[3] << 8));
    
    t =((float)t_tmp/65535*(85+40)-40);
    p = ((float)p_tmp/65535*(1000)+260);
    alt= 44330*(1-pow(p/1013.25f,1/5.255f));
    
}

//print the data
void printdata(){
    
    Serial.print( npadata[0],BIN);
    Serial.print("  ,  ");
    Serial.print(t);
    Serial.print("  ,  ");
    Serial.print(p);
    Serial.print("  ,  ");
    Serial.print(alt);
    Serial.print("  ,  ");
    Serial.print(t_tmp);
    Serial.print("  ,  ");
    Serial.println(p_tmp);
}





