
int pin=3;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
}
class Notes{
  private:
  int p_note;
  public:
  Notes(int note):p_note(note){}
  float get_pnote(){
    return p_note;
  }
  float oct1(){
    return (1/get_pnote()*1000000)/2;// 1/hz = sec *1000 
  }
  float oct2(){
    return (1/get_pnote()*1000000)/4;
  }
  float oct3(){
    return (1/get_pnote()*1000000)/8;
  }
  float oct4(){
    return (1/get_pnote()*1000000)/16;
  }
  float oct5(){
    return (1/get_pnote()*1000000)/36;
  }
  float oct6(){
    return (1/get_pnote()*1000000)/64;
  }
  float oct7(){
    return (1/get_pnote()*1000000)/128;
  }
  float oct8(){
    return (1/get_pnote()*1000000)/256;
  }
};

//   public:
void forloop(int time, float note){
  for( int i=0; i<time; i++){
    digitalWrite(pin,1);
    delayMicroseconds(note);
    digitalWrite(pin,0);
    delayMicroseconds(note);
    //Serial.println(i); 
  }
}

Notes C(65.41);
Notes D(73.42);
Notes E(82.41);
Notes F2(87.31);
Notes G(98);
Notes A(55);
Notes B(61.74);


//musics
void jinglebells();
void soltanGhalbha();
void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(A.oct4(),6);
  jinglebells();
  //soltanGhalbha();
}
//music functions
void jinglebells(){
  forloop(500,E.oct3());
  forloop(500,E.oct3());
  forloop(1000,E.oct3());
  forloop(500,E.oct3());
  forloop(500,E.oct3());
  forloop(1000,E.oct3());
  forloop(500,E.oct3());
  forloop(500,G.oct3());
  forloop(500,C.oct3());
  forloop(500,D.oct3());
  forloop(2000,E.oct3());
  //
  forloop(500,F2.oct3());
  forloop(500,F2.oct3());
  forloop(500,F2.oct3());
  forloop(500,F2.oct3());
  //
  forloop(500,F2.oct3());
  forloop(500,E.oct3());
  forloop(500,E.oct3());
  forloop(500,E.oct3());
  //
  forloop(500,E.oct3());
  forloop(500,D.oct3());
  forloop(500,D.oct3());
  forloop(500,E.oct3());
  //
  forloop(1000,D.oct3());
  forloop(1000,G.oct3());
  //
  forloop(500,E.oct3());
  forloop(500,E.oct3());
  forloop(1000,E.oct3());
  forloop(500,E.oct3());
  forloop(500,E.oct3());
  forloop(1000,E.oct3());
  forloop(500,E.oct3());
  forloop(500,G.oct3());
  forloop(500,C.oct3());
  forloop(500,D.oct3());
  forloop(2000,E.oct3());
  //
  forloop(500,F2.oct3());
  forloop(500,F2.oct3());
  forloop(500,F2.oct3());
  forloop(500,F2.oct3());
  //
  forloop(500,F2.oct3());
  forloop(500,E.oct3());
  forloop(500,E.oct3());
  forloop(500,E.oct3());
  //
  forloop(500,G.oct3());
  forloop(500,G.oct3());
  forloop(500,F2.oct3());
  forloop(500,D.oct3());
  //
  forloop(2000,C.oct3());
  exit(0);
};
void soltanGhalbha(){
  forloop(600,A.oct4());
  forloop(600,B.oct4());
  forloop(600,C.oct4());
  //
  forloop(600,E.oct4());
  forloop(300,F2.oct4());
  forloop(600,E.oct4());
  forloop(300,F2.oct4());
  //
  forloop(600,E.oct4());
  forloop(300,F2.oct4());
  forloop(300,E.oct4());
  forloop(300,F2.oct4());
  forloop(300,D.oct4());
  //
  forloop(600,C.oct4());
  forloop(300,D.oct4());
  forloop(600,C.oct4());
  forloop(300,D.oct4());
  exit(0);
};
