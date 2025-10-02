5 argüman alınacak
./pipex dosya1 komut1 komut2 dosya2

\\ ~ Kontroller ~ //
Argüman sayısı doğru mu?
Verilen yollar doğru mu?
Yolları verilen dosyalar gerekli izinlere sahip mi?

\\ ~ Algoritma ~ //

dosya1 den oku, PATH içerisinde bulduğun komutu dosya1 verisi ile gerçekleştir.
Çıktı terminale hedefli olacak ama onu dup ve dup2 ile boş bir dosyaya aktar.
Geçici dosyadan oku ve geçici dosyanın verisi ile komut ikiyi çalıştır.
Çıktı terminale hedefli olacak ama onu dup2 ile dosya2 ye yaz.
sonra standart çıktı yı eskisi gibi fd = 1 e geri aktar.

\\ ~ KOMUTLAR ~//

open  		:	Hedef dosyaya bir file descriptor atar, eğer dosya yoksa seçilen izinlerle dosyayı oluşturur ve file descriptor atar.

close 		:	File descriptorı bilinen dosyaların file descriptor bağlantısını kapatır. Cihaz devamlı okuma yapmaz artık.

read  		:	Hedef dosyadan hedef buffera istenilen buffer_size kadar okur ve okuma adetini return eder.

Write 		:	Hedeflenen File descriptora istenilen byte kadar yazma yapar.

malloc		:	Heap'te istenilen kadar alan tahsis eder.

free  		:	Heap'te tahsis edilen dinamik alanın sahipliğini iptal eder.

perror		:	Yaşanan hatanın kodunu alır ve hata koduna karşılık gelen açıklamayı ve istenen stringi terminale basar.  

strerror	:	errno ile elde edilen son hatanın kodunu parametre olarak alır ve karşılık gelen hata mesajını terminale basar.

access		:	Yolu verilen dosyanın ikinci parametrede sorulan izinlerine sahip olup olmadığını kontrol eder.

dup			:	Parametre verilen file descriptorın işaret ettiği dosyayı boşta olan en küçük file descriptorın işaret etmesini sağlar.

dup2		:	Parametre olarak verilen ilk file descriptorın hedefini, parametre olarak verilen ikinci file descriptorın hedefi ile aynı olacak şekilde değiştirir.
				Değişiklik program boyunca kalıcı ancak sisteme etki etmiyor.

execve		:	Programın mevcut sürecini yolu girilen işleme dönüştürür. Ram üzerindeki veriler silinirken kerneldaki veriler korunur.
				pathname = /bin/ls gibi komut dosyasının olduğu yol, 
				argv[] = "ls -l /home(varsa yoksa .)" gibi komutları belirlediğimiz yer(cat gibi infile  alan komutlar stdin a bakarken ls gibi komutlar bakmaz.)
				envp[] = çalışma ortamı(main den miras alınacak)

pipe		:	int bir dizi alır ve bu dizi 2 elemanlı bir fd dizisindir. Girdi ve çıktı uçları bu dizinin elemanlarıdır.
				Girdi ve çıktı arasında direkt bir bağlantı kurar. Kernel bufferı kullandığı için ram üzerinde yazma olmaz.

fork		:	Bu fonksiyon kullanıldığında çağırıldığı ana kadar ki tüm datalara sahip yeni bir işlem başlatır.
				Bu işlem alt süreç(child process) olarak adlandırılır ve PID(Process ID) == 0 olur.
				Ana süreç (mother process) ise alt sürecin kimliğini saklar ve alt sürecin bitmesini bekler(waitpid() || wait()).
				Bu süreçler artık birbirinden ayrı işler ve birbirini etkilemez.
