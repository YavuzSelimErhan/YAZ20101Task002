#include <stdio.h>
#include <stdlib.h>

//structlarımızı tanımlıyoruz.
typedef struct {
    int teklifveren_no;
    double teklif;
} Teklif;

typedef struct {
    Teklif teklif;
} Bid;

typedef struct {
    int teklifveren_sayisi;
    Teklif* teklifler;
} Yapi;

typedef struct {
    Yapi yapi;
} Artirma;

//odemeyi_hesapla fonksiyonunu tanımlıyoruz.
double odemeyi_hesapla(Artirma a, int kazanan_no) {
    double odeme = 0.0;
    int i;

    for (i = 0; i < a.yapi.teklifveren_sayisi; i++) {
        if (i != kazanan_no) {
            odeme += a.yapi.teklifler[i].teklif;
        }
    }

    return odeme;
}

//acikarttirma fonksiyonunu tanımlıyoruz.
void acikarttirma(Artirma a) {
    double enyuksek_teklif = -1.0;
    int kazanan_no = -1;
    int i;

    for (i = 0; i < a.yapi.teklifveren_sayisi; i++) {
        if (a.yapi.teklifler[i].teklif > enyuksek_teklif) {
            enyuksek_teklif = a.yapi.teklifler[i].teklif;
            kazanan_no = i;
        }
    }

    // kazanan teklif sahibini gösteriyoruz.
    printf("Kazanan Teklif Sahibi: Teklifveren No %d, Teklif %lf\n", a.yapi.teklifler[kazanan_no].teklifveren_no, a.yapi.teklifler[kazanan_no].teklif);

    // odemeyi hesaplayıp gösteriyoruz.
    double odeme = odemeyi_hesapla(a, kazanan_no);
    printf("Odeme: %lf\n", odeme);
}

int main() {
    // Artirma yapısını tanımlıyoruz.
    Artirma a;

    // Kullanıcıdan teklifveren sayısını alıyoruz.
    printf("Teklifveren Sayisini Girin: ");
    scanf("%d", &a.yapi.teklifveren_sayisi);

    // Belleği dinamik olarak tahsis ediyoruz.
    a.yapi.teklifler = (Teklif*)malloc(sizeof(Teklif) * a.yapi.teklifveren_sayisi);

    // Kullanıcıdan teklifleri alıyoruz.
    int i;
    for (i = 0; i < a.yapi.teklifveren_sayisi; i++) {
        printf("Teklifveren %d Teklifini Girin: ", i + 1);
        scanf("%lf", &a.yapi.teklifler[i].teklif);
        a.yapi.teklifler[i].teklifveren_no = i + 1;
    }

    // Açık artırmayı gerçekleştirip sonucu ekrana yazdırıyoruz.
    acikarttirma(a);

    // Belleği serbest bırakıyoruz.
    free(a.yapi.teklifler);

    return 0;
}
