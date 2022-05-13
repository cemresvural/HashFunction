#include <dirent.h>
#include <stdlib.h>
#include <conio.h>  
#include <string.h>  
#include<fstream>
#include<sstream>
using namespace std;

const char dosyaYol[ ] = "C:\\Users\\CEMRE\\Desktop\\Metinler";
int getFileCount()
  {
  int fileCount = 0;
  DIR *dir;
  struct dirent *ent;
  FILE *dd;
  if ( ( dir = opendir( dosyaYol ) ) != NULL )
    {
    int sayac = 0;
    while ( ( ent = readdir( dir ) ) != NULL )
      {
      if ( sayac > 1 )
        {
        fileCount ++;
      } sayac ++;
      }
    }
  return fileCount;
  }
int enYakinAsal( int sayi )
  {
  int j, k, l, m;
  j = sayi;
  for ( int k = 2; k < j; k ++ ) 
    {
    if ( j % k == 0 ) 
      {
      k = 2;            
      j = j - 1;
      }
    }
  l = sayi + 1;
  m = sayi + 1;
  for ( int k = 2; k < l; k ++ )
    {
    if ( l % k == 0 )
      {
      k = 2;
      l = l + 1;
      m = m + 1;
      }
    }
  if ( j == sayi )
    {
    return sayi;
    }
  else
  if ( l - sayi == sayi - j )
    {
    return j;
    }
  else
  if ( l - sayi < sayi - j )
    {
    return m;
    }
  else
  {
    return j;
  }
  }
int main()
  {
  	//Klas�r�n i�indeki dosya say�s� bulunuyor
  int fileCount = getFileCount();
  // en yak�n asal say� bulunuyor
  int m = enYakinAsal( fileCount *3 );
  printf("Dosya sayisi:%d, asal sayi:%d\n",fileCount,m); //de�erler ekrana yazd�r�l�yor
  char hashTablo[ m ][200]; //m boyutunda hast tablosu olu�turuluyor. [200] de�eri ise dosya isimleri i�in ayarland�
  //hash tablosundaki her bir de�eri '-' de�eri atan�oyor. �lerde bo� mu kontrol i�in kullan�lacak
  for ( int i = 0; i < m; i ++ )
    {
    hashTablo[ i ][0] = '-';
    }
  DIR *dir;
  struct dirent *ent;
  FILE *dd;
  if ( ( dir = opendir( dosyaYol ) ) != NULL ) //metinler klas�r� a��l�yor
    {
    int sayac = 0;
    while ( ( ent = readdir( dir ) ) != NULL )// her bir klas�r�n i�indeki dosyalar al�n�yor
      {
      if ( sayac > 1 )//. ve .. �eklinde iki dosya ismi g�r�nd��� i�in onlar� sayac ile atlay�p bizim esas dosyalara ge�iyoruz
        {
        char txtYol[ 100 ];
        strcpy( txtYol, dosyaYol );
        strcat( txtYol, "\\" );
        strcat( txtYol, ent -> d_name ); // ilgili dosyan�n tam konumu al�n�yor
       FILE *dosya; 
        dd = fopen( txtYol, "r" );//dosya okunuyor
        if ( dd != NULL )
          {
          char metin[ 200 ];
          int addr = 0;
          // dosyan�n i�indeki her bir sat�r tek tek dolan�p addr hesab� yap�l�yor
          while ( !feof( dd ) )
            {
            fgets( metin, 200, dd );
            for ( int i = 0; metin[ i ] != '\0'; i ++ )//hello merhaba
              {
              int metinAsci = metin[ i ];
              int a = 'a';
              addr += ( metinAsci - a ) *26;// addr hesab� burada ger�ekle�iyor
              } 
            }
          int addr1 = addr % m; // hash tablosunda ilk bak�lacak indis
          int addr2 = 1+( addr % ( m - 1 ) ); // ilk indis doluysa ikinci bak�lacak indis
          if ( hashTablo[ addr1 ][0] == '-' )// ilk indisin bo� olup olmad��� kontrol yap�l�yor
            {
            	//e�er ilk indis bo�sa
            	strcpy( hashTablo[ addr1 ],ent -> d_name);// addr1 indisine dosyan�n ismi ekleniyor 
				// yukar�ya da yazabilirdik ama kod karma��kl��� olmamas� i�in buraya yazd�k d_name i
            	
                printf( "dosya adi: %s , addr1 indis: %d\n ", hashTablo[ addr1 ],addr1 ); //hangi dosya tablonun hangi indisine yerle�ti�i bilgisi yaz�l�yor
            }
          else if ( hashTablo[ addr2 ][0] == '-' )// ikinci indisin bo� olup olmad��� kontrol yap�l�yor
            { 
                //e�er ikinci indis bo�sa
            	strcpy( hashTablo[ addr2 ],ent -> d_name);// addr2 indisine dosyan�n ismi ekleniyor
                printf( "dosya adi: %s , addr2 indis: %d\n ", hashTablo[ addr2 ], addr2 );//hangi dosya tablonun hangi indisine yerle�ti�i bilgisi yaz�l�yor
            }
          else // e�er her iki adresde doluysa indisler dolu �eklinde ekrana bilgi veriliyor
          {
                printf("YER BULUNAMADI: dosya adi: %s , addr1 indis: %d ,addr2 indis: %d\n ",
               ent -> d_name, addr1, addr2 );
          }
          }
        else
          {
          // Dosya a��l�rken bir hata olu�ursa.
          printf("Dosya acilma hatasi!!\n");
          }
        }
      sayac ++;
      }
    closedir( dir );
    }
  // klas�rdeki t�m dosyalar hashtablosuna eklendi�i zaman kullan�cya bilgi veriliyor
    printf( "Metinler klasorundeki %d tane dosya hash tablosuna eklendi",fileCount );
 
  while ( 1 == 1 )  //kullan�c� ��k�� yapmak isteyene kadar d�ng� devam edecek
    {
    int deger;
    // kullan�c� yapmak istedi�i i�lemi a�a��daki gibi girecek
    printf("\n         #################\n         Yeni dosya ekle:1 \n         Hash tablosunu listele:2 \n         Cikis: 0 \n" );
    scanf( "%d", &deger );
    // ge�ersiz bir de�er girip girmedi�i kontrol� yap�l�yor
    if ( deger != 0 && deger != 1 && deger != 2 )
    {
      printf( "lutfen gecerli bir deger giriniz....\n" );
    }
    // ��k�� i�lemini se�erse d�ng�den ��kacak
    if ( deger == 0 )
    {
      break;
    }
    // yeni metin girilmek istenirse
    if ( deger == 1 )
      {
      char yenimetin[ 200 ];
      // kullan�c�dan girileek metin isteniyor
      printf( "Metni giriniz... " );
      scanf( "%s", &yenimetin );
      int addr = 0;
      // girilen metnin hangi adresde olunaca�� hesaplan�yor
      for ( int i = 0; yenimetin[ i ] != '\0'; i ++ )
        {
        int metinAsci = yenimetin[ i ];
        int a = 'a';
        addr += ( metinAsci - a ) *26;
        }
      int addr1 = addr % m;
      int addr2 = 1+( addr % ( m - 1 ) );
      if ( hashTablo[ addr1 ][0] != '-' ) // ilk adres doluysa dosya var deniyor
        {
        printf( "dosya var : dosya adi: %s , addr1 indis: %d\n ", hashTablo[addr1 ], addr1 );
        }
      else if ( hashTablo[ addr2 ][0] != '-' ) // ikinci adres doluysa dosya var deniyor
        {
        printf( "dosya var : dosya adi: %s , addr2 indis: %d\n ", hashTablo[addr2 ], addr2 );
        }
      else
        {// addr1 ve addr2 her ikiside bo� ise dosyay� klas�re ekleme ve hash tablosuna ekleme i�lemi ger�ekle�tiriliyor
        char txtYol[ 100 ];
        strcpy( txtYol, dosyaYol );
        strcat( txtYol, "\\" );
        fileCount = fileCount + 1;
        std :: stringstream gstream;
        gstream << fileCount;
        std :: string g = gstream.str();
        string dosyaisim=g + ".txt";
        string uzanti = txtYol + g + ".txt";
        printf( "%s", uzanti.c_str() );
        FILE *dosya = fopen( uzanti.c_str(), "w" );
        fprintf( dosya, yenimetin );
        strcpy( hashTablo[ addr1 ],dosyaisim.c_str());
        fclose( dosya );
        }
      }
      // hash tablosunu listeleyip hangi dosya tabloda nereye yerle�mi� g�rmek i�in lsiteme i�lemi yap�l�yor
      if(deger==2)
      {
      	for(int i=0;i<m;i++)
      	{
      		if ( hashTablo[ i ][0] != '-' )
			  {
			  	 printf( " dosya adi: %s ,  indis: %d\n ", hashTablo[i], i );
			  }	
		}
	  }
    }
 
    
	
	
	return 0;
}

