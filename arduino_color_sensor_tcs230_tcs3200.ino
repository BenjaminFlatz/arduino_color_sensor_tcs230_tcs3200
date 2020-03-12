/*********
  Benjamin Flatz
*********/

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 3
#define S1 4
#define S2 5
#define S3 6
#define sensorOut 7

#define btnAdd 12
// Stores Freq read by the photodiodes
int redFreq = 0;
int greenFreq = 0;
int blueFreq = 0;

int sw[] = {8, 9, 10, 11};
//memset(color,0,sizeof(color));

struct NRGB{
  int pos[50] = {0,1,2,3,4,5,6,7};
  String name[50] = {"red","orange","yellow","green","blue","purple","pink","brown"};
  int r[50] = {180,142,130,165,164,198,165,190};
  int g[50] = {287,224,162,177,171,224,238,247};
  int b[50] = {202,183,171,171,117,144,151,201};  
};

NRGB color;



/*
typedef struct IRGB{
  int id;
  int r;
  int g;
  int b;  
};*/

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
//RGB color[50];

/*
RGB color[] = {
  {"red", 172, 280, 198}, 
  {"orange", 142, 224, 183},
  {"yellow", 130, 162, 171},
  {"green", 165, 177, 171},
  {"blue", 164, 171, 117},
  {"purple", 198, 224, 144},
  {"pink", 165, 238, 151},
  {"brown", 190, 247, 201},

};*/
/*
IRGB color[10] = {
  {0, 172, 280, 198}, 
  {1, 142, 224, 183},
  {2, 130, 162, 171},
  {3, 165, 177, 171},
  {4, 164, 171, 117},
  {5, 198, 224, 144},
  {6, 165, 238, 151},
  {7, 190, 247, 201},

};*/



int tolerance = 7;

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  pinMode(sw[0], INPUT_PULLUP);
  pinMode(sw[1], INPUT_PULLUP);
  pinMode(sw[2], INPUT_PULLUP);
  pinMode(sw[3], INPUT_PULLUP);

  pinMode(btnAdd, INPUT_PULLUP);
  
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

int get_pos(){
  int j = 0;
  int pos = 0;
  int mlt = 1;
  
  for(j=0; j<sizeof(sw)/sizeof(int); j++){
    
    if(digitalRead(sw[j]) == 0){
      pos = pos+mlt;
      //Serial.println(pos);
    }
    mlt = mlt*2;
  }
  return pos;
}

void add_color(String readStr, int red, int green, int blue, int pos){
  int i = 0;
  int index;
  for(i=0; i<sizeof(color.name)/sizeof(String); i++){
    if(color.name[i] != ""){
      index = i+1;
    }
  }
  
  //index = sizeof(color.name)/sizeof(NRGB);
  //RGB(color[index], {readStr, red, green, blue});
  //Serial.println("Added: " + readStr + "\nTo: " + String(color.r[index]) + " " + String(color.g[index]) + " " + String(color.b[index]));

  color.pos[index] = pos;
  color.name[index] = readStr;
  color.r[index] = red;
  color.g[index] = green;
  color.b[index] = blue;
  //color[index] = {readStr, red, green, blue};
  //RGB* color = new RGB[index];
  //color[index+1] = {readStr, red, green, blue};
  //color[8] = {readStr, red, green, blue};
  
  Serial.println("");
  Serial.println(color.pos[index]);
  Serial.println("Added: " + readStr + "\nTo: " + String(color.r[index]) + " " + String(color.g[index]) + " " + String(color.b[index]));
  Serial.println("");

  return;
}

void set_color(String readStr, int red, int green, int blue, int index, int pos){
  
  int j = 0;
  
  color.pos[index] = pos;
  color.name[index] = readStr;
  color.r[index] = red;
  color.g[index] = green;
  color.b[index] = blue;

  Serial.println("");
  Serial.println(color.pos[index]);
  Serial.println("Set: " + String(color.name[index]) + "\nTo: " + String(red) + " " + String(green) + " " + String(blue));
  Serial.println("");

  return;
  
}
String get_color(){
  int i = 0;
  for(i=0; i<sizeof(color.name)/sizeof(String); i++){
    if((color.r[i]<(tolerance+redFreq) && color.r[i]>(redFreq-tolerance)) &&
    (color.g[i]<(tolerance+greenFreq) && color.g[i]>(greenFreq-tolerance)) &&
    (color.b[i]<(tolerance+blueFreq) && color.b[i]>(blueFreq-tolerance))){
      //Serial.println(color[i].name);
      return "Name=" + color.name[i] + " Pos=" + String(color.pos[i]);     
    }
  }
  return "not found";
}


void loop() {

  
  redFreq = get_freq("R");
  greenFreq = get_freq("G");
  blueFreq = get_freq("B");
  int pos = get_pos();

  
  Serial.println(get_color());
  Serial.println("R="+String(redFreq)+" G="+String(greenFreq)+" B="+String(blueFreq));
  
  
  if(digitalRead(btnAdd) == 0){
    int i = 0;
    bool found = false;
    for(i=0; i<sizeof(color.pos)/sizeof(int); i++){
      //Serial.println(color.name[i]);
      delay(1);
      
      if(color.pos[i] == pos){
        //Serial.println(str);
        //Serial.println("identified");
        set_color("", redFreq, greenFreq, blueFreq, i, pos);
        found = true;
        break;
      }
      else{
        //set_color(str, redFreq, greenFreq, blueFreq);
        //Serial.println("unknown");
      }
    }
    if(found == false){
      add_color("", redFreq, greenFreq, blueFreq, pos);
    }
  }
  
  
  if (Serial.available() > 0 ){
    String str = Serial.readString();
    int i = 0;
    bool found = false;
  
    for(i=0; i<sizeof(color.name)/sizeof(String); i++){
      //Serial.println(color.name[i]);
      delay(1);
      
      if(str == color.name[i]){
        //Serial.println(str);
        //Serial.println("identified");
        set_color(str, redFreq, greenFreq, blueFreq, i, pos);
        found = true;
        break;
      }
      else{
        //set_color(str, redFreq, greenFreq, blueFreq);
        //Serial.println("unknown");
      }
    }
    if(found == false){
      add_color(str, redFreq, greenFreq, blueFreq, pos);
    }
    str = "";
  }
  
  //Serial.println(String(sizeof(color.name)/sizeof(NRGB)));

  delay(1000);
  

}
