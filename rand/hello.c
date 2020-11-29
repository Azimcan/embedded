
#include "hal.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

int sayac[4]={0,0,0,0};
int bos=0;

#define THRESHOLD 96
#define DINAMIK


int randombytes(uint8_t *x, size_t xlen);

static void ekranayazdir(const int t) {
  int8_t s[32];
  snprintf(s,32,"%d",t);
  hal_send_str(s);
}

static int tusbasildi(uint8_t tus){
  return (tus&1);
}
static int tusbirak(uint8_t tus){
  return 1^(tus&1);
}
static void kontrolet(uint8_t *a){
  randombytes(a,1);
}
static int tus(void){
  uint8_t tus;
  kontrolet(&tus);
  int flag = tusbasildi(tus);
  while(flag){
    kontrolet(&tus);
    if (tusbirak(tus))
      return 1;
  }
  return 0;
}

static int sensor(void){
  uint8_t data;
  kontrolet(&data);
  return (data>THRESHOLD);
}

static int artir0(int t){
  sayac[0]+=(t==0);
  return (t!=0);
}

static int artir1(int t){
  sayac[1]+=(t==1);
  return (t!=1);
}
static int artir2(int t){
  sayac[2]+=(t==2);
  return (t!=2);
}
static int artir3(int t){
  sayac[3]+=(t==3);
  return (t!=3);
}
static void dummy(void){
  uint8_t a;
  
  hal_send_str("\n");
  hal_send_str("$");
  randombytes(&a,1);
  hal_send_str("$");
  hal_send_str("\n");
}

static inline void Statik(int t){
    // Cyclic (Döngüsel - Statik) programlama
    bos+=artir0(t);
    bos+=artir1(t);
    bos+=artir2(t);
    bos+=artir3(t);
}  

static inline void Dinamik(int t){
  // Dinamik programlama
    switch(t){
      case 0:
        bos+=artir0(t);
        break;
      case 1:
        bos+=artir1(t);
        break;
      case 2:
        bos+=artir2(t);
        break;
      case 3:
        bos+=artir3(t);
        break;
      default:
        break;
    }
}
static void Sayacyazdir(int t){
    hal_send_str("#");
    hal_send_str("#");
    ekranayazdir(t);
    ekranayazdir(sayac[0]);
    ekranayazdir(sayac[1]);
    ekranayazdir(sayac[2]);
    ekranayazdir(sayac[3]);
    hal_send_str("#");
    ekranayazdir(bos);
    hal_send_str("#");
}

int idle(int t){
  return (t>3);
}

int main(void) {
  hal_setup(CLOCK_FAST);
  int i=100;
  int t=0;
  
baslangic:
  if(!i--)
    goto bitis;
 
  // 0 0 = 0 tus basılmadı ve sensor karanlık
  // 0 1 = 1 tus basıldı ve sensor karanlık
  // 1 0 = 2 tus basılmadı ve sensor aydınlık
  // 1 1 = 3 tus basıldı ve sensor aydınlık
  t = tus();
  t += (sensor()<<1);
  if (i%10==9)
    t=4;
  if(idle(t))
    goto baslangic;
#if defined(DINAMIK) 
    hal_send_str("Dinamik");
    Dinamik(t);   
    //
    Sayacyazdir(t);
    goto baslangic; 
#else
    hal_send_str("Statik");   
    Statik(t);
    //
    Sayacyazdir(t);
    goto baslangic;
#endif

  hal_send_str("#");
bitis:
  while (1);

  return 0;
}


