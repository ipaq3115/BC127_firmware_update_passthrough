
#define SERIAL_A Serial
#define SERIAL_B Serial2

void setup() {
  // Serial.begin(0);
  // SERIAL_A.begin(38400);
  // SERIAL_B.begin(38400);
  SERIAL_A.begin(9600);
  SERIAL_B.begin(9600);
  // SERIAL_B.begin(115200);
  // SERIAL_A.begin(115200,SERIAL_8E1);
  // SERIAL_A.begin(115200,SERIAL_9N1);
  // SERIAL_B.begin(230400);
  // SERIAL_B.begin(38400);
}

int inChar = -1;

char DFUstr[] = "DFU\r";
int dfuCount = 0;

void loop() {

    inChar = SERIAL_A.read(); 
    if(inChar != -1) {
        
        SERIAL_B.write(inChar);
        
        if(dfuCount != -1) {
        
            if(DFUstr[dfuCount] == inChar) {
            
                dfuCount++;
                if(dfuCount == 4) {
                
                    dfuCount = -1;
        
                    SERIAL_B.end(); 
                    SERIAL_B.begin(115200,SERIAL_8E1);
                    
                }
            
            } else {
            
                dfuCount = 0;
            
            }
        
        }
    
    }

    inChar = SERIAL_B.read(); 
    if(inChar != -1) {
        SERIAL_A.write(inChar);
    }

}
