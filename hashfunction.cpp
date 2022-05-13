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
  	//Klasörün içindeki dosya sayýsý bulunuyor
  int fileCount = getFileCount();
  // en yakýn asal sayý bulunuyor
  int m = enYakinAsal( fileCount *3 );
  printf("Dosya sayisi:%d, asal sayi:%d\n",fileCount,m); //deðerler ekrana yazdýrýlýyor
  char hashTablo[ m ][200]; //m boyutunda hast tablosu oluþturuluyor. [200] deðeri ise dosya isimleri için ayarlandý
  //hash tablosundaki her bir deðeri '-' deðeri atanýoyor. Ýlerde boþ mu kontrol için kullanýlacak
  for ( int i = 0; i < m; i ++ )
    {
    hashTablo[ i ][0] = '-';
    }
  DIR *dir;
  struct dirent *ent;
  FILE *dd;
  if ( ( dir = opendir( dosyaYol ) ) != NULL ) //metinler klasörü açýlýyor
    {
    int sayac = 0;
    while ( ( ent = readdir( dir ) ) != NULL )// her bir klasörün içindeki dosyalar alýnýyor
      {
      if ( sayac > 1 )//. ve .. þeklinde iki dosya ismi göründüðü için onlarý sayac ile atlayýp bizim esas dosyalara geçiyoruz
        {
        char txtYol[ 100 ];
        strcpy( txtYol, dosyaYol );
        strcat( txtYol, "\\" );
        strcat( txtYol, ent -> d_name ); // ilgili dosyanýn tam konumu alýnýyor
       FILE *dosya; 
        dd = fopen( txtYol, "r" );//dosya okunuyor
        if ( dd != NULL )
          {
          char metin[ 200 ];
          int addr = 0;
          // dosyanýn içindeki her bir satýr tek tek dolanýp addr hesabý yapýlýyor
          while ( !feof( dd ) )
            {
            fgets( metin, 200, dd );
            for ( int i = 0; metin[ i ] != '\0'; i ++ )//hello merhaba
              {
              int metinAsci = metin[ i ];
              int a = 'a';
              addr += ( metinAsci - a ) *26;// addr hesabý burada gerçekleþiyor
              } 
            }
          int addr1 = addr % m; // hash tablosunda ilk bakýlacak indis
          int addr2 = 1+( addr % ( m - 1 ) ); // ilk indis doluysa ikinci bakýlacak indis
          if ( hashTablo[ addr1 ][0] == '-' )// ilk indisin boþ olup olmadýðý kontrol yapýlýyor
            {
            	//eðer ilk indis boþsa
            	strcpy( hashTablo[ addr1 ],ent -> d_name);// addr1 indisine dosyanýn ismi ekleniyor 
				// yukarýya da yazabilirdik ama kod karmaþýklýðý olmamasý için buraya yazdýk d_name i
            	
                printf( "dosya adi: %s , addr1 indis: %d\n ", hashTablo[ addr1 ],addr1 ); //hangi dosya tablonun hangi indisine yerleþtiði bilgisi yazýlýyor
            }
          else if ( hashTablo[ addr2 ][0] == '-' )// ikinci indisin boþ olup olmadýðý kontrol yapýlýyor
            { 
                //eðer ikinci indis boþsa
            	strcpy( hashTablo[ addr2 ],ent -> d_name);// addr2 indisine dosyanýn ismi ekleniyor
                printf( "dosya adi: %s , addr2 indis: %d\n ", hashTablo[ addr2 ], addr2 );//hangi dosya tablonun hangi indisine yerleþtiði bilgisi yazýlýyor
            }
          else // eðer her iki adresde doluysa indisler dolu þeklinde ekrana bilgi veriliyor
          {
                printf("YER BULUNAMADI: dosya adi: %s , addr1 indis: %d ,addr2 indis: %d\n ",
               ent -> d_name, addr1, addr2 );
          }
          }
        else
          {
          // Dosya açýlýrken bir hata oluþursa.
          printf("Dosya acilma hatasi!!\n");
          }
        }
      sayac ++;
      }
    closedir( dir );
    }
  // klasördeki tüm dosyalar hashtablosuna eklendiði zaman kullanýcya bilgi veriliyor
    printf( "Metinler klasorundeki %d tane dosya hash tablosuna eklendi",fileCount );
 
  while ( 1 == 1 )  //kullanýcý çýkýþ yapmak isteyene kadar döngü devam edecek
    {
    int deger;
    // kullanýcý yapmak istediði iþlemi aþaðýdaki gibi girecek
    printf("\n         #################\n         Yeni dosya ekle:1 \n         Hash tablosunu listele:2 \n         Cikis: 0 \n" );
    scanf( "%d", &deger );
    // geçersiz bir deðer girip girmediði kontrolü yapýlýyor
    if ( deger != 0 && deger != 1 && deger != 2 )
    {
      printf( "lutfen gecerli bir deger giriniz....\n" );
    }
    // çýkýþ iþlemini seçerse döngüden çýkacak
    if ( deger == 0 )
    {
      break;
    }
    // yeni metin girilmek istenirse
    if ( deger == 1 )
      {
      char yenimetin[ 200 ];
      // kullanýcýdan girileek metin isteniyor
      printf( "Metni giriniz... " );
      scanf( "%s", &yenimetin );
      int addr = 0;
      // girilen metnin hangi adresde olunacaðý hesaplanýyor
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
        {// addr1 ve addr2 her ikiside boþ ise dosyayý klasöre ekleme ve hash tablosuna ekleme iþlemi gerçekleþtiriliyor
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
      // hash tablosunu listeleyip hangi dosya tabloda nereye yerleþmiþ görmek için lsiteme iþlemi yapýlýyor
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

