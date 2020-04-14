#include <HTTPClient.h>
#include <tinyxml2.h>
#include <math.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 115200;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
using namespace tinyxml2;
const int Joy = A0; 
int sportif= 1; //non
int handi= 1; //non
#define BTN_NONE   0
#define BTN_CLICK  1
#define BTN_UP     2
#define BTN_DOWN   3
#define BTN_LEFT   4
#define BTN_RIGHT  5

void afficheError(){

}
void afficheLoading(){

}
void afficheResult(){

}
void afficheParametre(){
}
void afficheMenu(){

}
void mypos(float *lon, float *lat){
    if (ss.available() > 0){
        gps.encode(ss.read());
    if (gps.location.isUpdated()){
      lat = gps.location.lat();
      lon = gps.location.lng();
    }


}


void dispo(int *disp, char park){
    HTTPClient http;

    http.begin("https://data.montpellier3m.fr/sites/default/files/ressources/"+park+".xml"); //Specify the URL
    int httpCode = http.GET();
    if (httpCode > 0) { //Check for the returning code
        String payload = http.getString();
        XMLDocument xmlDocument;
        if(xmlDocument.Parse(payload)!= XML_SUCCESS){
            afficheError();
            menu();
        }
        XMLNode * park = xmlDocument.FirstChild();
        XMLElement * freeP = park->FirstChildElement("Free");
        freeP->QueryIntText(disp);
    }    
}

void parkingProche( char *P1, char *P2, char *P3, float lon, float lat){
    float corum[2]= 43.6144154,3.8793361;
    float come[2]= 43.6087024,3.8781513;
    float gare[2]= 43.6027102,3.8742258;
    //SA-B = arc cos (sin latA sin latB + cos latA cos latB cos (lonA-lonb)
    float moiCorum, moiCom,moiGare;
    moiCorum= arc(cos(sin(lat)*sin(corum[0])+cos(lat)*cos(corum[0])*cos(lon-corum[1])));
    moiCom= arc(cos(sin(lat)*sin(come[0])+cos(lat)*cos(come[0])*cos(lon-come[1])));
    moigare= arc(cos(sin(lat)*sin(gare[0])+cos(lat)*cos(gare[0])*cos(lon-gare[1])));
    if (moiCorum < moiCom){ // JE TRAITRE PAS TOUS LES CAS mais c'est pour l'idee
        if (moiCorum < moigare){
            P1= moiCorum;
            if (moiCom<moigare){
                P2= moiCom;
                P3= moigare;
            }}}
    if (moicom < moigare){
        P1= moiCom;
        if(moiCorum < moigare){
            P2= moiCorum;
            P3=moigare;
            }
    }
    else{
        P1= moigare;
        P2= moiCorum;
        P3= moiCom
    }

     
    
}


void recherche(){
    afficheLoading();
    float lon, lat;
    mypos(&lon, &lat);
    char P1, P2, P3;
    parkingProche(&P1, &P2, &P3, lon, lat);
    int p1dispo, p2dispo, p3dispo;
    dispo(&p1dispo,P1);
    dispo(&p2dispo,P2);
    dispo(&p3dispo,P3);
    if(handi==0){
        if( p1dispo!= 0){
            afficheResult(P1, p1dispo);
        }
        else if( p2dispo!=0){
            afficheResult(P2, p2dispo);
        }
        else if( p3dispo!=0){
            afficheResult(P3, p3dispo);
        }
    }
    if(sportif==0){
        if(p1dispo>50){
            afficheResult(P1, p1dispo);
        }
        else{
            if( p2dispo<50){
                if(p3dispo<50){
                    if( p1dispo>p2dispo){
                        if (p1dispo>p3dispo){
                            afficheResult(P1, p1dispo);
                        }
                    }else if( p2dispo>p3dispo){
                            afficheResult(P2, p2dispo);
                    }else{
                        afficheResult(P3, p3dispo);
                    }
                }
        }

    }


}




void parametre(){
    select=0;
    afficheParametre(select);    
while(1){
    byte btn;
    btn = readJoy();
    if( btn == BTN_UP )
       select=0;
       afficheParametre(select);
    else if( btn == BTN_DOWN ){
       select=0;
       afficheParametre(select);
    }
    else if( btn == BTN_RIGHT ){
       if (select==0){
            sportif=1;
       }
       if (select==1){
            handi=1;
       }
       afficheParametre(select);
    }
    else if( btn == BTN_LEFT ){
       if (select==0){
            sportif=0;
       }
       if (select==1){
            handi=0;
       }
       afficheParametre(select);
    }

    else if( btn == BTN_CLICK )
        menu();
}


}
void menu(){
    select=0;
    afficheMenu(select);

while(1){
    byte btn;
    btn = readJoy();
    if( btn == BTN_UP ){
        select=0;
        afficheMenu( select);
    }
    else if( btn == BTN_DOWN ){
        select=1;
        afficheMenu( select);
    }
    else if( btn == BTN_CLICK ){
        if(select==0){
            recherche();
        }
        else if(select==1){
            parametre();
         }
    }

}
}

byte readJoy(){
  int buttonValue = 0; 
  buttonValue = analogRead(Joy );
  Serial.println( buttonValue );
  if( buttonValue > 760 ) {
    return BTN_CLICK; }
  else if( buttonValue > 580 ) {
    return BTN_RIGHT; }
  else if( buttonValue > 400 ) {
    return BTN_UP; }
  else if( buttonValue > 220 ) {
    return BTN_LEFT;}
  else if( buttonValue > 100 ) {
    return BTN_DOWN; }
  else {
    return BTN_NONE;
  }
}
}
void initLCD();
void initSIM(){
// On suppose que ca marche
}
void initGPS(){
    ss.begin(GPSBaud);
}
void initLCD();
void setup(){
    initGPS();
    initSIM();
    initLCD();
    menu();
}
void loop(){}
