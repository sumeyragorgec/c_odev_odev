#include <stdio.h>
#include <string.h>
#include <stdbool.h> //bu olmadan bool değişkenler kullanılamıyor.
#include <stdlib.h>

//fopen: dosyayı istenilen modda açar.
//fgets: dosya okuma eylemi
//fprintf: dosyaya bir seyler yazar.
//fclose: dosyayı kapatır.
//atoi: string ifadeyi integer'a �evirir.
//strtok: satırdaki ifadeleri string olarak okur.
//strtok(null): satır içindeki diğer kelimeye geçer.
//strcmp: string1 == string2 işlemini yapar.
//strcpy: string1 = string2 işlemini yapar.

struct oyuncu
{
  char isim[25];
  char soyIsim[25];
  int oynananMacSayisi;
  int hataliPas;
  int isabetliPas;
};

//oyuncunun kayd� varsa true, yoksa false de�er.
bool oyuncununKaydiVarMi(struct oyuncu oyuncular[20], char gelenOyuncuAdi[20]) {
  int i = 0;
  for(i = 0; i < 20; i++) {
    if (strcmp(oyuncular[i].isim, gelenOyuncuAdi) == 0){//esitlik //okunandegerden veri yolladim
      return true;
    }
  }
  return false;
}

//kaydi olan oyuncunun kacinci indekste yer ald�g�n� dondurur
int oyuncununIndeksiniBul(struct oyuncu oyuncular[20], char gelenOyuncuAdi[20]) {
  int i = 0;
  for(i = 0; i < 20; i++) {
    if (strcmp(oyuncular[i].isim, gelenOyuncuAdi) == 0) {
      return i;
    }
  }
  return -1;
}

//satir satir okuyacak, toplam.txt'in icerigini uretecek.
void ekle(struct oyuncu oyuncular[20], char *karakter, char satir[100], FILE *paslar, char *okunanDeger, char neyeGore[], bool kaydiVarMi, int kacinciOyuncu, int oyuncununIndeksi, int ozellikSayaci) {
    do {
    karakter = fgets(satir, 100, paslar); // satirdeki tam veriler *where the string read is stored.=>satir// *100=>maximum number of characters to be read// *paslar =>the stream where characters are read from.
    okunanDeger = strtok(satir, neyeGore); // isim //satir icini kelime kelime okur

    if (strcmp(okunanDeger, "--\n") == 0) {//paslar icindeki 11lik kumenin sonuna geldiyse => continue diger donguye devam eder 
      continue;
    }

    kaydiVarMi = oyuncununKaydiVarMi(oyuncular, okunanDeger);//oyuncunun kaydi var mi fonksiyonuna 2 parametreyle calistirip kaydivarmi'ye esitledim

    if (kaydiVarMi) {//true ise calisir
      oyuncununIndeksi = oyuncununIndeksiniBul(oyuncular, okunanDeger);//kaydi var ise index bulunur
    }
   
    if (!kaydiVarMi) {//false ise 
      oyuncular[kacinciOyuncu].oynananMacSayisi = 1;
      while(okunanDeger != NULL) {
        if (ozellikSayaci == 0) {
          strcpy(oyuncular[kacinciOyuncu].isim, okunanDeger);//okunan degeri oyuncular[kacinciOyuncu].isim'e atadim
        }else if (ozellikSayaci == 1) {
          strcpy(oyuncular[kacinciOyuncu].soyIsim, okunanDeger);//okunan degeri oyuncular[kacinciOyuncu].soyIsim'e atadim
        }else if (ozellikSayaci == 2) {
          oyuncular[kacinciOyuncu].hataliPas = atoi(okunanDeger);//okunandeger icindeki ifadeyi int'e donusturup oyuncular[kacinciOyuncu].hataliPas'e atadim
        }else if (ozellikSayaci == 3) {
          oyuncular[kacinciOyuncu].isabetliPas = atoi(okunanDeger);//okunandeger icindeki ifadeyi  oyuncular[kacinciOyuncu].isabetliPas'a atadim
        }
        okunanDeger = strtok(NULL, neyeGore); // bir sonraki kelimeye gelir
        ozellikSayaci++;//her defasinda sayac++ sonraki ozellige gecer
      }
	  } else if (kaydiVarMi) { //kaydi onceden varsa
      kacinciOyuncu--;
      oyuncular[oyuncununIndeksi].oynananMacSayisi++;//onceden kayitli oyuncuysa oynadigi mac sayisi arttti
      while(okunanDeger != NULL) {
        if (ozellikSayaci == 2) {//ad soyad zaten ekli oldugundan hatalipas sayisini yazdirdik
          int eklenecekDeger = atoi(okunanDeger);//okunan degeri int'e cevirip eklenecekDeger'e ekledim
          oyuncular[oyuncununIndeksi].hataliPas += eklenecekDeger;// onceden kayitli olan hatali pasa sonraki mactaki hatali pasi ekledim
        }else if (ozellikSayaci == 3) {// hatali pastan sonra isabetlipas'i saydirdim
          int eklenecekDeger = atoi(okunanDeger);//isabetlipas'i okuyup eklenecekdeger'e atadim
          oyuncular[oyuncununIndeksi].isabetliPas += eklenecekDeger;//onceki isabetliPas'a bu mactakini de ekledim
        }
        okunanDeger = strtok(NULL, neyeGore); // bir sonraki kelimeye gecti ve donguye yeni okunan degerle devam etti
        ozellikSayaci++;// her eklenen ozellikte ozellikSayaci artt� ve bir sonraki degeri karsilastirdi
      }
    }
    kacinciOyuncu++;// kaydivarmi - yokmu'dan sonra sonraki oyuncuya gecti
    ozellikSayaci = 0;
  } while (karakter != NULL);//do-while ile en az bir kere dondurdum
}

void yazdir(struct oyuncu oyuncular[20]) {
  FILE *toplam;
  toplam = fopen("toplam.txt","w");//toplam.txt dosyasini acip okuma islemi yaptirdim
  int i = 0;
  for (i = 0; i < 20; i++) {
    fprintf(toplam,"%s ",oyuncular[i].isim);
    fprintf(toplam,"%s ",oyuncular[i].soyIsim);
    fprintf(toplam,"%d ",oyuncular[i].oynananMacSayisi);
    fprintf(toplam,"%d ",oyuncular[i].hataliPas);
    fprintf(toplam,"%d\n",oyuncular[i].isabetliPas);
  }
  fclose(toplam);
}

int main(){
  struct oyuncu oyuncular[20];

  char satir[100], *karakter;
  char neyeGore[] = " ", *okunanDeger;
  FILE *paslar = fopen("paslar.txt", "r");

  bool kaydiVarMi = false;
  int kacinciOyuncu = 0, oyuncununIndeksi = 0;
  int ozellikSayaci = 0;

  ekle(oyuncular, karakter, satir, paslar, okunanDeger, neyeGore, kaydiVarMi, kacinciOyuncu, oyuncununIndeksi, ozellikSayaci);

  fclose(paslar);

  yazdir(oyuncular);

	return 0;
}
