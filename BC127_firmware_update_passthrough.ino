
/**
 * \brief BC127 firware update serial passthrough program
 * This sketch allows the Pi Watch to pass data back and forth
 * between the BC127 and the firmware update program provided
 * by BlueCreation. This allows easy updates to the Melody 
 * software of the BC127 integrated into the Pi Watch.
 */

#define SERIAL_A Serial
#define SERIAL_B Serial2

void setup() {
  
  SERIAL_A.begin(9600);
  
  // This should be set to whatever the current baud of the BC127 is
  // if it has been changed. 9600 is the default baud rate.
  SERIAL_B.begin(9600);
  
}

int inChar = -1;

// The message string that puts the BC127 into firmware update mode
char DFUstr[] = "DFU\r";
int dfuCount = 0;

void loop() {

    inChar = SERIAL_A.read(); 
    if(inChar != -1) {
        
        // Echo data from the firware updater to the BC127
        SERIAL_B.write(inChar);
        
        // Search for the DFU string to trigger the baud rate change
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

    // Echo the data from the BC127 back up to the firmware updater
    inChar = SERIAL_B.read(); 
    if(inChar != -1) SERIAL_A.write(inChar);
    
}
