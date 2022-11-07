/*
 * A simple watchdog test for pi pico.
 * The loop delay gradually increases until it is longer than the watchdog timeout
 * Tested on a standard pi pico
 * Set board using Earle F. Philhower, III's excellent board library:
 *  https://github.com/earlephilhower/arduino-pico
 * 
 */




uint32_t watchdog_timeout = 1000;               // time to wait before the watchdog reboots pi (ms)
unsigned long timer = 0;                        // saves the millis to count the loop_delay
unsigned long timerfast = 0;                    //
unsigned long loop_delay = 990;                 // how long we delay before resetting the watchdog timer
unsigned long loop_delayfast = 500;             //
char watchdog_rebooted_me[2] = "n";
unsigned int loop_count = 0;                    // how many times have we looped since (re)booting

void setup() {
  Serial.begin(9600); // start USB serial
  /*while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }*/
  delay(2000);    // using delay instead of wait for serial > if the pico is not plugged into a serial port it seems to halt at while
  Serial.print("\n******** BOOTING ********\n\n");
  watchdog_enable(watchdog_timeout,1);
  //rp2040.wdt_begin(watchdog_timeout);
  if (watchdog_caused_reboot()) {         // this will persist over watchdog reboots, but reset if you power off the pico
    strcpy(watchdog_rebooted_me,"y");
  }
}

void loop() {
  if (millis()-timerfast >= loop_delayfast) {
    timerfast = millis();
    //Serial.print("countdown: ");
    //Serial.print(watchdog_get_count()/1000);  // this function appears to not work
    //Serial.print("\n");
  }
  if (millis()-timer >= loop_delay) {
    timer = millis();
    loop_count++;
    watchdog_update();
    //rp2040.wdt_reset();
    if (loop_delay >= watchdog_timeout-1) {                      
      Serial.print("\ngonna crash...\n\n");
    }
    Serial.print("loops done ");
    Serial.print(loop_count);
    Serial.print("\n");
    Serial.print("timeout vs delay: ");
    Serial.print(watchdog_timeout);
    Serial.print(" - ");
    Serial.print(loop_delay);
    Serial.print("\n");
    Serial.print("rebooted by watchdog? ");
    Serial.print(watchdog_rebooted_me);
    Serial.print("\n");
    loop_delay++;                                 // cause timeout eventually by increasing the time before watchdog update/reset 
  }
}
