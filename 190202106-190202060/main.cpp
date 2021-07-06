#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include <string.h>

typedef struct nokta
{
    double x;
    double y;

} nokta;



double mesafe(nokta a, nokta b)
{

    return sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2));

}


int faktoriyel(int n)
{
    if(n==0)
        return 1;
    else
        return n*faktoriyel(n-1);

}


int kombinasyon(int n,int r)
{
    return (faktoriyel(n)/(faktoriyel(n-r)*faktoriyel(r)));
}


//Kaç nokta olduðunu okutuyor
int satirOku()
{

    FILE *dosya;
    dosya=fopen("noktalar.txt","r");

    int i = 0;
    char ch;

    while(!feof(dosya))
    {
        ch=fgetc(dosya);
        if(ch=='\n')
            i++;

    }
    return i+1;
}


//En uç noktalardan birini buluyor
int enBuyukNokta(nokta noktalar[], int n)
{
    int i,j;
    int indeks = 0;
    double maks = 0;

    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(maks < mesafe(noktalar[i],noktalar[j]))
            {
                maks = mesafe(noktalar[i],noktalar[j]);
                indeks = i;
            }
        }
    }
    return indeks;
}


//En uç noktalardan diðerini buluyor
int enKucukNokta(nokta noktalar[], int n)
{
    int i,j;
    int indeks = 0;
    double maks = 0;
    int enBuyuk = enBuyukNokta(noktalar,n);

    for(i=0; i<n; i++)
    {
        if(maks < mesafe(noktalar[i],noktalar[enBuyuk]))
        {
            maks = mesafe(noktalar[i],noktalar[enBuyuk]);
            indeks = i;
        }

    }
    return indeks;
}




int main()
{
    int satirSayisi = satirOku();

    FILE *fp = fopen("noktalar.txt","r");

    if(fp == NULL)
    {
        printf("Dosya bulunmamaktadir.");
    }

    else
    {
        printf("Dosya olusturuldu\n");
    }

    nokta p[satirSayisi];
    int i,j;

    //Dosyadan okuma
    for(i=0; i<satirSayisi; i+2)
    {
        fscanf(fp,"%lf%lf",&p[i].x,&p[i].y);
        i++;
    }

    printf("Noktalar: ");

    //Koordinatlarý yazdýr
    for(i=0; i<satirSayisi; i++)
    {
        printf("{%1.lf,%1.lf},",p[i].x,p[i].y);
    }

    printf("\n");

    nokta merkez;


    //En uç noktalarýn indeksleri
    int n2 = enBuyukNokta(p,satirSayisi);
    int n1 = enKucukNokta(p,satirSayisi);
    double yariCap = mesafe(p[n2],p[n1])/2;


    //Merkezin koordinatlarý
    merkez.x = (p[n1].x + p[n2].x)/2;
    merkez.y = (p[n1].y + p[n2].y)/2;

    double yariCapKontrol = yariCap;

    nokta nokta3;

    int bayrak = 0;

    //2 noktaya daha uzak bir nokta daha varsa onu bulur
    //ona göre yarýçapý ve merkezi tekrar düzenler



    for(i=0; i<satirSayisi; i++)
    {
        if(mesafe(p[i],merkez) > yariCapKontrol)
        {
            //p[yN] = 1
            //p[xN] = 2;
            //p[i] = 3;
            //x² + y² + 2ax + 2by + c = 0


            bayrak = 1;
            nokta3 = p[i];
            double x12 = p[n1].x - p[n2].x;//x1-x2
            double x13 = p[n1].x - p[i].x;//x1-x3

            double y12 = p[n1].y - p[n2].y;//y1-y2
            double y13 = p[n1].y - p[i].y;//y1-y3

            double y31 = p[i].y - p[n1].y;//y3-y1
            double y21 = p[n2].y - p[n1].y;//y2-y1

            double x31 = p[i].x - p[n1].x;//x3-x1
            double x21 = p[n2].x - p[n1].x;//x2-x1


            double x13kareFarki = pow(p[n1].x, 2) - pow(p[i].x, 2);//x1^2-x3^2
            double y13kareFarki = pow(p[n1].y, 2) - pow(p[i].y, 2);//y1^2-y3^2

            double x21kareFarki = pow(p[n2].x, 2) - pow(p[n1].x, 2);//x2^2-x1^2
            double y21kareFarki = pow(p[n2].y, 2) - pow(p[n1].y, 2);//y2^2-y1^2


            double a = ((x13kareFarki) * (y12) + (y13kareFarki) * (y12) + (x21kareFarki) * (y13) + (y21kareFarki) * (y13))
            / (2 * ((x31) * (y12) - (x21) * (y13)));


            double b = ((x13kareFarki) * (x12) + (y13kareFarki) * (x12) + (x21kareFarki) * (x13) + (y21kareFarki) * (x13))
            / (2 * ((y31) * (x12) - (y21) * (x13)));


            double c = -pow(p[n1].x, 2) - pow(p[n1].y, 2) - 2 * a * p[n1].x - 2 * b * p[n1].y;


            double x = -a;
            double y = -b;
            double r = sqrt(x*x + y*y - c);


            printf("-Merkez: {%.1f,%.1f}\n",x,y);
            printf("-Yaricap: %.1f",r);

            merkez.x = x;
            merkez.y = y;
            yariCap = r;

            break;
        }

    }

    if(bayrak!=1){
        printf("\nYaricap: %f\n\n",yariCap);
        printf("Merkez: {%.1f,%.1f}\n\n",merkez.x,merkez.y);
    }



    int gd = DETECT,gm;
    initgraph(&gd,&gm,"");

    //Koordinat sistemini çizer
    line(0,240,640,240);
    line(320,0,320,640);

    //x koordinatýný ölçeklendirir
    for(i = 0; i<480; i=i+8)
    {
        line(317,i,323,i);
        setcolor(YELLOW);
    }


    //y koordinatýný ölçeklendirir
    for(i = 0; i<640; i=i+8)
    {
        line(i,237,i,243);
        setcolor(YELLOW);
    }


    setcolor(WHITE);

    //Daireyi çizdirir
    circle(320+(merkez.x)*8,240-(merkez.y)*8,yariCap*8);
    circle(320+(merkez.x)*8,240-(merkez.y)*8,5);

    //Noktalarý koordinat sisteminde gösterir
    for(i=0; i<satirSayisi; i++)
    {
        setcolor(LIGHTGREEN);
        circle(320+(p[i].x)*8,240-(p[i].y)*8,4);

    }

    double t,xt = 0,yt = 0;

    //Egriyi cizdirir
    for(t=0.0; t<=1.0; t=t+0.0005)
    {
        xt = 0;
        yt = 0;
        for(i=0; i<satirSayisi; i++)
        {
            xt=xt+(kombinasyon(satirSayisi-1,i)*pow(1-t,satirSayisi-1-i)*pow(t,i)*p[i].x);
            yt=yt+(kombinasyon(satirSayisi-1,i)*pow(1-t,satirSayisi-1-i)*pow(t,i)*p[i].y);
        }
        putpixel(320+xt*8,240-yt*8,YELLOW);
    }


    getch();
    closegraph();


    return 0;
}
