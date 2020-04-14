













const int Joy = A0; 
int sportif= 1; //non
int handi= 1; //non
#define BTN_NONE   0
#define BTN_CLICK  1
#define BTN_UP     2
#define BTN_DOWN   3
#define BTN_LEFT   4
#define BTN_RIGHT  5

void recherche(){
    afficheLoading();
    float lon, lat;
    mypos(&lon, &lat);
    char P1, P2, P3;
    parkingProche(&P1, &P2, &P3);
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
        affiche( select);
    }
    else if( btn == BTN_DOWN ){
        select=1;
        affiche( select);
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
void initSIM(){
// On suppose que ca marche
}
void initGPS(){
}
void setup(){
    initGPS();
    initSIM();
    initLCD();
    menu();
}
void loop(){}
