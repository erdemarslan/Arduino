void engelden_kacan() {
  int on_mesafe = uzaklik_olc(onAci);
  //delay(250);

  if(on_mesafe > 30) {
    yon_belirle(1);
    araba_ileri(250);
  } else {
    
    yon_belirle(0);
    araba_dur(10);
    
    int sol_mesafe = uzaklik_olc(solAci);
    int sag_mesafe = uzaklik_olc(sagAci);

    if(sol_mesafe > sag_mesafe) {
      
      yon_belirle(2);
      araba_geri(250);
      yon_belirle(3);
      araba_sola(250);
      yon_belirle(0);
      araba_dur(10);
      
    } else {
      
      yon_belirle(2);
      araba_geri(250);
      yon_belirle(4);
      araba_saga(250);
      yon_belirle(0);
      araba_dur(10);
      
    }
  }
}


void bluetooth() {

  char veri;

  if(BT.available()) {
    veri = BT.read();
  }

  if(veri == 'w') {
    arabaYon = 1;
  }

  else if(veri == 's') {
    arabaYon = 2;
  }

  else if(veri == 'a') {
    arabaYon = 3;
  }

  else if(veri == 'd') {
    arabaYon = 4;
  }

  else if(veri == 'b') {
    arabaYon = 0;
  }



  if(arabaYon == 1) {
    araba_ileri(100);
  }

  if(arabaYon == 2) {
    araba_geri(100);
  }

  if(arabaYon == 3) {
    araba_sola(100);
  }

  if(arabaYon == 4) {
    araba_saga(100);
  }

  if(arabaYon == 0) {
    araba_dur(100);
  }

  
  

  
}

void cizgi_izleyen() {
  
}

