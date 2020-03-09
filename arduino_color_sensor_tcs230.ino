/*********
  Benjamin Flatz
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


//memset(color,0,sizeof(color));


typedef struct RGB{
  String name;
  int r;
  int g;
  int b;  
};

/*
struct Smarties {
  RGB red = {172, 280, 198};
  RGB orange = {142, 224, 183};
  RGB yellow = {130, 162, 171};
  RGB green = {165, 177, 171};
  RGB blue = {164, 171, 117};
  RGB purple = {198, 224, 144};
  RGB pink = {165, 238, 151};
  RGB brown = {190, 247, 201};
};*/
//RGB* color = new RGB[50];

RGB color[] = {
  {"red", 172, 280, 198}, 
  {"orange", 142, 224, 183},
  {"yellow", 130, 162, 171},
  {"green", 165, 177, 171},
  {"blue", 164, 171, 117},
  {"purple", 198, 224, 144},
  {"pink", 165, 238, 151},
  {"brown", 190, 247, 201},
  {"", 0, 0, 0},
  {"", 0, 0, 0},
  {"", 0, 0, 0},
  {"", 0, 0, 0},
  {"", 0, 0, 0},
  {"", 0, 0, 0},
};



int tolerance = 10;

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



  /*
  color['red'] = {172, 280, 198};
  color["orange"] = {142, 224, 183};
  color["yellow"] = {130, 162, 171};
  color["green"] = {165, 177, 171};
  color["blue"] = {164, 171, 117};
  color["purple"] = {198, 224, 144};
  color['pink'] = {165, 238, 151};
  color['brown'] = {190, 247, 201};
  */
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
    //redFreq = map(redFreq, 178,270,255,0);
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
    //greenFreq = map(greenFreq, 183,310,255,0);

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
    //blueFreq = map(blueFreq, 120,241,255,0);
    return blueFreq;
    //delay(100);
  }
 
}
void add_color(String readStr, int red, int green, int blue){
  int index = sizeof(color)/sizeof(RGB);
  //RGB(color[index], {readStr, red, green, blue});

  //RGB* color = new RGB[index];
  //color[index] = {readStr, red, green, blue};
  color[index] = {readStr, red, green, blue};
  Serial.println("Added: " + color[index].name + "\nTo: " + String(red) + " " + String(green) + " " + String(blue));
  return;
}

void set_color(String readStr, int red, int green, int blue, int index){
  color[index] = {readStr, red, green, blue};
  Serial.println("Set: " + color[index].name + "\nTo: " + String(red) + " " + String(green) + " " + String(blue));
  return;
  
}
String get_color(){
  int i = 0;
  for(i=0; i<sizeof(color)/sizeof(RGB); i++){
    if((color[i].r<(tolerance+redFreq) && color[i].r>(redFreq-tolerance)) &&
    (color[i].g<(tolerance+greenFreq) && color[i].g>(greenFreq-tolerance)) &&
    (color[i].b<(tolerance+blueFreq) && color[i].b>(blueFreq-tolerance))){
      //Serial.println(color[i].name);
      return color[i].name;     
    }
  }
  return "not found";
}


void loop() {

  redFreq = get_freq("R");
  greenFreq = get_freq("G");
  blueFreq = get_freq("B");
  Serial.println(get_color());
  Serial.println("R="+String(redFreq)+" G="+String(greenFreq)+" B="+String(blueFreq));
  while(Serial.available() > 0 ){
    String str = Serial.readString();
    int i = 0;
    bool found = false;
    //add_color(str, redFreq, greenFreq, blueFreq);

    for(i=0; i<sizeof(color)/sizeof(RGB); i++){
      if(str.substring(0) == (color[i].name + "")){
        //Serial.println(str);
        //Serial.println("identified");
        set_color(str, redFreq, greenFreq, blueFreq, i);
        found = true;
        break;
      }
      else{
        //set_color(str, redFreq, greenFreq, blueFreq);
        //Serial.println("unknown");
      }
    }
    if(found = false){
      add_color(str, redFreq, greenFreq, blueFreq);
    }
    



  }
  
  delay(1000);
  

}
