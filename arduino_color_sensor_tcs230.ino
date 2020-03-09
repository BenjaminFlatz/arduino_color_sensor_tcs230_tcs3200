/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define sensorOut 7

// Stores Freq read by the photodiodes
int redFreq = 0;
int greenFreq = 0;
int blueFreq = 0;

int red[] = {172, 280, 198};
int orange[] = {142, 224, 183};
int yellow[] = {130, 162, 171};
int green[] = {165, 177, 171};
int blue[] = {164, 171, 117};
int purple[] = {198, 224, 144};
int pink[] = {165, 238, 151};
int brown[] = {190, 247, 201};

int tolerance = 15;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting Freq scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(9600);
}
int get_freq(String color){

  if(color == "R"){
    // Setting RED (R) filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);

    int redReading[10];
    int i = 0;
    // Reading the output Freq
    for(i=0; i<10; i++){
      redReading[i] = pulseIn(sensorOut, LOW);
      redFreq += redReading[i];
    }
    redFreq = (redFreq/10);
    return redFreq;
    
  }
  else if(color == "G"){
    // Setting GREEN (G) filtered photodiodes to be read
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    
    int greenReading[10];
    int i = 0;
    // Reading the output Freq
    for(i=0; i<10; i++){
      greenReading[i] = pulseIn(sensorOut, LOW);
      greenFreq += greenReading[i];
    }
    greenFreq = (greenFreq/10);
    return greenFreq;
    //delay(100);
  }
  else if(color == "B"){
    // Setting BLUE (B) filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    
    int blueReading[10];
    int i = 0;
    // Reading the output Freq
    for(i=0; i<10; i++){
      blueReading[i] = pulseIn(sensorOut, LOW);
      blueFreq += blueReading[i];
    }
    blueFreq = (blueFreq/10);
    return blueFreq;
    //delay(100);
  }
 
}

String get_color(){
  if((red[0]<(tolerance+redFreq) && red[0]>(redFreq-tolerance)) &&
  (red[1]<(tolerance+greenFreq) && red[1]>(greenFreq-tolerance)) &&
  (red[2]<(tolerance+blueFreq) && red[2]>(blueFreq-tolerance))){
    Serial.println("red");
    return "red";
    
      
  }
  else if((orange[0]<(tolerance+redFreq) && orange[0]>(redFreq-tolerance)) &&
  (orange[1]<(tolerance+greenFreq) && orange[1]>(greenFreq-tolerance)) &&
  (orange[2]<(tolerance+blueFreq) && orange[2]>(blueFreq-tolerance))){
    Serial.println("orange");
    return "orange";
  }
  
  else if((yellow[0]<(tolerance+redFreq) && yellow[0]>(redFreq-tolerance)) &&
  (yellow[1]<(tolerance+greenFreq) && yellow[1]>(greenFreq-tolerance)) &&
  (yellow[2]<(tolerance+blueFreq) && yellow[2]>(blueFreq-tolerance))){
    Serial.println("yellow");
    return "yellow";
  
  }
  else if((green[0]<(tolerance+redFreq) && green[0]>(redFreq-tolerance)) &&
  (green[1]<(tolerance+greenFreq) && green[1]>(greenFreq-tolerance)) &&
  (green[2]<(tolerance+blueFreq) && green[2]>(blueFreq-tolerance))){
    Serial.println("green");
    return "green";
  }
  else if((blue[0]<(tolerance+redFreq) && blue[0]>(redFreq-tolerance)) &&
  (blue[1]<(tolerance+greenFreq) && blue[1]>(greenFreq-tolerance)) &&
  (blue[2]<(tolerance+blueFreq) && blue[2]>(blueFreq-tolerance))){
    Serial.println("blue");
    return "blue";
  }
  else if((purple[0]<(tolerance+redFreq) && purple[0]>(redFreq-tolerance)) &&
  (purple[1]<(tolerance+greenFreq) && purple[1]>(greenFreq-tolerance)) &&
  (purple[2]<(tolerance+blueFreq) && purple[2]>(blueFreq-tolerance))){
    Serial.println("purple");
    return "purple";
  }
  else if((pink[0]<(tolerance+redFreq) && pink[0]>(redFreq-tolerance)) &&
  (pink[1]<(tolerance+greenFreq) && pink[1]>(greenFreq-tolerance)) &&
  (pink[2]<(tolerance+blueFreq) && pink[2]>(blueFreq-tolerance))){
    Serial.println("pink");
    return "pink";
  
  }
  else if((brown[0]<(tolerance+redFreq) && brown[0]>(redFreq-tolerance)) &&
  (brown[1]<(tolerance+greenFreq) && brown[1]>(greenFreq-tolerance)) &&
  (brown[2]<(tolerance+blueFreq) && brown[2]>(blueFreq-tolerance))){
    Serial.println("brown");
    return "brown";
  }
  else{
    Serial.println("not recognized");
    return "not recognized";
  }
}


void loop() {
  get_freq("R");
  get_freq("G");
  get_freq("B");
  get_color();
  Serial.println("R="+String(redFreq)+" G="+String(greenFreq)+" B="+String(blueFreq));
  delay(100);
}
