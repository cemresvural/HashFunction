Metinler klasöründeki her bir txt dosyasını açarak içeriğini okudum
getFileCount fonksiyonu oluşturdum
Aşağıdaki 1. hash fonksiyonundan geçirerek hash değerini elde ettim 
1. Hash fonksiyonu: 
		for(i=addr=0;i < length(word); i++) 
addr+=  (word[i] –‘a’ )*26;
addr = addr % m;

Hash tablosunda, hash değerine karşılık gelen adres boş ise ilgili dokümanın adını buraya yazar. Alan dolu ise 2. Hash fonksiyonundan 2. Hash değerini eder ve hash tablosunda bu değere karşılık gelen adresi kontrol eder. Boşsa dosyanın adını yazar, doluysa ‘yer bulunamadı’ şeklinde uyarı verir. 

         2. Hash fonksiyonu:
addr  =  1+ (addr % (m-1))

Yeni bir metin eklenmek istendiğinde;
Metnin içeriği 1. Hash fonksiyonundan geçirerek hash değerini ürettim ve hash tablosunda, hash değerine karşılık gelen adrese baktım. Adres doluysa metin daha önce klasöre eklenmiş demektir.Ve ekrana yazdırdım.
Eğer 1. Hashing işlemi sonrasında baktığımız alan boşsa, 2. Hash fonksiyonundan geçirerek tekrar hash tablosunu kontrol ettim. İlgili adres doluysa metin daha önce eklenmiş demektir. Boşsa, metni txt formatında, metinler klasörüne kaydeder.
Hash tablosunun boyutunu hesaplamak için ;
          (Klasördeki dosya sayısı*3) değerine en yakın asal sayı.
formülü kullandım. 
