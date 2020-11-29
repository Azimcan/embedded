#include "hal.h"

#include <stdio.h>
#include <string.h>

static void yazdir(const char *s) {
  hal_send_str(s);
}

static void intyazdir(const char *s, const int a) {
  char out[32];
  snprintf(out,32,s,a);
  hal_send_str(out);
}

char tam[32];
char virgul[2];
void op(int bolunen, int bolen){

  int bolum = 0;
  int toplam = 0;
  int kalan = -1;

  int i = 0;
  while(i < 2){
    i++;
    while (bolunen >= toplam){
      bolum++;
      toplam += bolen;
      if (bolunen >= toplam) {
        printf("%d %d %d\n", bolunen, bolum, toplam);
      }
    }

    toplam -= bolen;
    bolum -= 1;

    if (i == 1){
      sprintf(tam, "%d", bolum);
    }
    else if(i == 2){
      sprintf(virgul, "%d", bolum);
    }

    kalan = bolunen - toplam;

    printf("Bolum: %d\n", bolum);
    printf("Kalan: %d\n", kalan);

    bolunen = kalan*100;
    toplam = 0;
    bolum = 0;
  }
}


int main(void) {
  hal_setup(CLOCK_FAST);


  op(386, 89);
  char string_number[34];
  sprintf(string_number, "%s, %s", tam, virgul);
  
  yazdir(string_number);

  yazdir("#");

  while (1);

  return 0;
}
