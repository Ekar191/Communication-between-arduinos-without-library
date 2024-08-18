  #define Yollama_Hizi 5
  #define Yollama_pini 13
  #define Senkron 2

  const char *message = "Hello";

  void setup(){
    pinMode(Yollama_pini, OUTPUT);
    pinMode(Senkron, OUTPUT);


    Serial.begin(9600); 
    Serial.print(message);
    Serial.print("\n");

    for (int Cumle = 0; Cumle < strlen(message); Cumle++) {
    
      char yollanan_cumle = message[Cumle];
    
      for (int karakter = 0; karakter < 8; karakter++) {
        bool yollanan_karakter = yollanan_cumle & (0x80 >> karakter);
    
        digitalWrite(Yollama_pini, yollanan_karakter);
        delay(Yollama_Hizi);
        
        //Serial.print(yollanan_karakter ? "1" : "0");
        
        digitalWrite(Senkron, HIGH);
        delay(Yollama_Hizi);
        digitalWrite(Senkron, LOW);
      
      }
    }
    digitalWrite(Yollama_pini, LOW);   
  }

  void loop(){
  }