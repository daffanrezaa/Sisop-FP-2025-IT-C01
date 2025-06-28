# Final Project Sistem Operasi IT

## Peraturan
1. Waktu pengerjaan dimulai hari Kamis (19 Juni 2025) setelah soal dibagikan hingga hari Rabu (25 Juni 2025) pukul 23.59 WIB.
2. Praktikan diharapkan membuat laporan penjelasan dan penyelesaian soal dalam bentuk Readme(github).
3. Format nama repository github “Sisop-FP-2025-IT-[Kelas][Kelompok]” (contoh:Sisop-FP-2025-IT-A01).
4. Setelah pengerjaan selesai, seluruh source code dan semua script bash, awk, dan file yang berisi cron job ditaruh di github masing - masing kelompok, dan link github dikumpulkan pada form yang disediakan. Pastikan github di setting ke publik.
5. Commit terakhir maksimal 10 menit setelah waktu pengerjaan berakhir. Jika melewati maka akan dinilai berdasarkan commit terakhir.
6. Jika tidak ada pengumuman perubahan soal oleh asisten, maka soal dianggap dapat diselesaikan.
7. Jika ditemukan soal yang tidak dapat diselesaikan, harap menuliskannya pada Readme beserta permasalahan yang ditemukan.
8. Praktikan tidak diperbolehkan menanyakan jawaban dari soal yang diberikan kepada asisten maupun praktikan dari kelompok lainnya.
9. Jika ditemukan indikasi kecurangan dalam bentuk apapun di pengerjaan soal final project, maka nilai dianggap 0.
10. Pengerjaan soal final project sesuai dengan modul yang telah diajarkan.

## Kelompok C01

Nama | NRP
--- | ---
Diva Aulia Rosa | 5027241003
Aditya Reza Daffansyah | 5027241034
Hanif Mawla Faizi | 5027241064
Nafis Faqih Allmuzaky Maolidi | 5027241095

## Deskripsi Soal
### Fork Wait Race
Buat program untuk simulasi fork dalam jumlah banyak dengan delay yang berbeda-beda untuk mengeluarkan sebuah print statement, sehingga muncul sebuah urutan berdasarkan delay masing-masing fork.

### Catatan

Struktur repository:
```
.
├── fork_sim.c   # File Utama
├── README.md           # Dokumentasi 

```

## Pengerjaan

**Teori**
### Simulasi Fork dan Sinkronisasi Proses
# 1. Pendahuluan
Dalam dunia sistem operasi modern, kemampuan untuk menjalankan berbagai program secara bersamaan merupakan inti dari fungsionalitas dan efisiensi. Kemampuan ini terwujud melalui konsep "proses", sebuah unit eksekusi mandiri yang memiliki sumber dayanya sendiri. Namun, bagaimana sebuah sistem operasi dapat menciptakan proses-proses baru ini? Jawabannya terletak pada "system call", antarmuka yang memungkinkan program berinteraksi langsung dengan kernel sistem operasi. Di antara berbagai system call yang vital, fork() menonjol sebagai salah satu yang paling fundamental dan transformatif, khususnya dalam arsitektur sistem operasi berbasis Unix.

Untuk gambaran mudahnya kita bisa mengumpamakan laptop kita yang sedang menjalankan banyak aplikasi sekaligus: browser web, pemutar musik, dan yang lainnya. Setiap aplikasi ini sebenarnya adalah sebuah proses. Gampangnya, proses itu seperti sebuah "pekerja" independen di dalam laptop kita. Setiap pekerja punya tugasnya sendiri, punya area kerjanya sendiri (memori), dan punya alat-alatnya sendiri (register CPU).
Nah, bagaimana sebuah komputer bisa menciptakan pekerja-pekerja baru ini? Di sinilah peran panggilan sistem (system call) masuk. Panggilan sistem itu seperti "perintah khusus" yang bisa diberikan program kepada otak utama komputer (disebut kernel sistem operasi) untuk melakukan sesuatu yang penting. Salah satu perintah khusus yang sangat penting adalah fork().

# 2. Konsep Dasar
## 2.1 Proses dan Sistem Call fork()
Menurut "Operating System Concepts" oleh Silberschatz, Galvin, dan Gagne
- Proses fork adalah system call yang digunakan untuk membuat proses baru, yang disebut proses anak (child process). Proses anak ini merupakan duplikat dari proses induk (parent process) yang memanggil fork(). Duplikasi ini mencakup salinan memori, register, dan status lainnya.
- Sistem adalah kejadian setelah fork() berhasil, sistem operasi akan memiliki dua proses yang hampir identik: proses induk dan proses anak. Kedua proses ini kemudian akan melanjutkan eksekusi dari titik setelah panggilan fork(). Perbedaan utama adalah nilai kembalian dari fork(): proses anak menerima 0, sedangkan proses induk menerima Process ID (PID) dari proses anak.

!! (( proses ada di halaman 61-62, gambaran proses ada di halaman 106, dan sistem fork ada di halaman 110 ))

Menurut "Modern Operating Systems" oleh Andrew S. Tanenbaum dan Herbert Bos 
- Proses fork adalah penciptaan proses baru dengan menyalin ruang alamat proses pemanggil. Ini berarti semua segmen teks, data, dan stack dari proses induk disalin ke proses anak. Kedua proses kemudian berjalan secara independen, meskipun awalnya mereka berbagi banyak kode dan data.
- Sistem fork adalah inti dari cara sistem operasi Unix-like membuat proses baru. Setelah fork(), seringkali diikuti oleh panggilan execve() (atau varian exec lainnya) oleh proses anak untuk mengganti program yang sedang dieksekusi dengan program baru. Ini adalah pola umum untuk menjalankan program baru dengan parameter.

!! (( proses di halaman 53-55, sistem di halaman 61 ))

Menurut "The Linux Programming Interface" oleh Michael Kerrisk
- Proses fork adalah pembuatan proses anak baru yang merupakan duplikat dari proses pemanggil. Pada Linux, implementasi fork() menggunakan teknik copy-on-write (COW) untuk efisiensi. Ini berarti halaman memori hanya akan disalin ke proses anak jika salah satu proses (induk atau anak) mencoba memodifikasinya. Sebelum modifikasi, mereka berbagi halaman memori yang sama.
- Sistem fork adalah dasar dari konkurensi dan eksekusi program di lingkungan Unix/Linux. Ini memungkinkan satu proses untuk melahirkan proses lain yang dapat melakukan tugas yang berbeda secara bersamaan. Nilai kembalian yang berbeda (0 untuk anak, PID anak untuk induk) adalah kunci untuk membedakan perilaku kedua proses.

!! (( di halaman 583-586 ))

Dari tiga sumber di atas dapat disimpulkan secara umum bahwa fork() adalah system call fundamental dalam sistem operasi mirip Unix (termasuk Linux) yang berfungsi untuk membuat proses baru (proses anak) sebagai duplikat dari proses yang memanggilnya (proses induk).

## 2.2 Konsep Delay dan Sleep
Setiap proses anak disimulasikan memiliki waktu eksekusi yang berbeda menggunakan fungsi sleep(). Fungsi ini menunda eksekusi proses selama sejumlah detik, yang dalam konteks ini disetel secara acak (rand() % 5 + 1), mencerminkan variasi beban kerja atau waktu tanggap proses dalam sistem nyata.

- Menurut "Operating System Concepts" oleh Silberschatz, Galvin, dan Gagne
  Pengaruh sleep() pada Urutan Eksekusi, bahwa setelah fork(), kedua proses (induk
  dan anak) berjalan secara bersamaan (konkuren). Tidak ada jaminan pasti mengenai
  urutan eksekusi relatif antara proses induk dan anak, kecuali jika ada mekanisme
  sinkronisasi yang eksplisit. Jika salah satu proses memanggil sleep(), proses
  tersebut akan menghentikan eksekusinya untuk jangka waktu yang ditentukan,
  memungkinkan proses lain (induk atau anak) untuk dieksekusi lebih dulu oleh
  penjadwal sistem operasi.

- Menurut  "Advanced Programming in the UNIX Environment" oleh W. Richard Stevens dan Stephen A. Rago
  sleep() sebagai Fungsi Penundaan Waktu: Stevens dan Rago merinci sleep() sebagai
  fungsi standar POSIX yang menunda eksekusi proses pemanggil untuk sejumlah detik
  yang ditentukan. Fungsi ini adalah salah satu cara paling sederhana untuk
  memperkenalkan jeda. Dalam konteks fork(), baik proses induk maupun proses anak
  dapat memanggil sleep().

Dari kedua suber di atas dapat disimpulkan secara umum, sleep() adalah system call yang digunakan untuk menunda eksekusi proses untuk durasi waktu tertentu. Ketika digunakan bersamaan dengan fork(), sleep() dapat ditempatkan di proses induk atau anak untuk mengendalikan (secara non-deterministik) urutan eksekusi relatif antara kedua proses tersebut. Ini berguna untuk simulasi, observasi perilaku penjadwal, atau memberikan jeda sederhana.

## 2.3 Sinkronisasi Proses dengan wait()
Proses induk harus memanggil wait() untuk: mengetahui kapan proses anak selesai dan menghindari zombie process (proses yang sudah selesai tapi belum diambil statusnya). Fungsi wait() akan memblokir proses induk hingga satu proses anak menyelesaikan eksekusinya, lalu mengembalikan PID-nya dan status keluarannya.

- Menurut "Operating System Concepts" oleh Silberschatz, Galvin, dan Gagne
  wait() adalah system call yang digunakan oleh proses induk untuk menunda
  eksekusinya sampai salah satu proses anaknya berakhir. Ketika sebuah proses anak
  berakhir, ia menjadi "zombie process" sampai proses induk memanggil wait() atau
  waitpid(). wait() akan mengumpulkan status terminasi dari proses anak dan kemudian
  menghapus entri proses anak tersebut dari tabel proses sistem.

- Menurut  "Advanced Programming in the UNIX Environment" oleh W. Richard Stevens dan Stephen A. Rago
  wait(): Fungsi ini akan menunda proses pemanggil hingga proses anaknya berakhir.
  Jika ada beberapa proses anak, wait() akan menunggu anak manapun yang selesai.
  Fungsi ini mengembalikan Process ID (PID) dari anak yang selesai, atau -1 jika
  terjadi kesalahan.
  waitpid(): Fungsi ini lebih fleksibel. Ia memungkinkan proses induk untuk menunggu
  anak tertentu (dengan menentukan PID anak tersebut), atau menunggu anak manapun.
  Selain itu, waitpid() memiliki opsi (options) yang memungkinkan proses induk untuk
  tidak memblokir, artinya jika tidak ada anak yang sudah selesai, waitpid() akan
  segera kembali daripada menunggu.

Dapat disimpulkan secara singkatnya, wait() dan waitpid() adalah system call esensial yang memungkinkan proses induk untuk:
  - Menunggu hingga proses anaknya selesai.
  - Mengumpulkan status terminasi dari proses anak tersebut.
  - Membersihkan sumber daya yang terkait dengan proses anak yang telah berakhir,
    mencegahnya menjadi "proses zombie" yang tidak perlu.
    
Ini adalah bentuk sinkronisasi yang berfokus pada manajemen siklus hidup proses, memastikan bahwa proses induk memiliki kontrol atas dan dapat bereaksi terhadap akhir dari proses yang telah dilahirkannya.

## 2.4 Penggunaan Warna Output (ANSI Escape Codes)
Untuk meningkatkan keterbacaan, pewarnaan digunakan melalui kode ANSI. Contoh warna: Biru (proses induk), Kuning (status delay anak), Cyan (anak selesai), Hijau (sukses), Merah (error). Ini membantu debugging visual dan pelacakan log pada sistem real-time.

# 3. Implementasi Simulasi
## 3.1 Struktur Program
Program utama menciptakan NUM_FORKS proses anak. Proses anak memiliki delay acak dan akan keluar setelah delay.

## 3.2 Alur Eksekusi
1. Proses induk memulai simulasi dan menyiapkan seed acak.
2. Proses induk membuat 5 anak menggunakan fork().
3. Setiap anak tidur dengan delay acak dan keluar dengan exit().
4. Proses induk menunggu semua anak selesai menggunakan wait().
4. Analisis dan Relevansi
Simulasi ini menggambarkan prinsip dasar multiprogramming, asynchronous execution, dan proses sinkronisasi dalam OS. Penggunaan delay dan wait() memungkinkan kita melihat perbedaan urutan selesai antar proses. Hal ini berkaitan erat dengan scheduling, CPU resource sharing, dan proses lifecycle.
5. Kesimpulan
Melalui simulasi ini, kita memahami secara praktis cara kerja fork() dalam menciptakan proses anak, bagaimana delay mempengaruhi urutan eksekusi, serta bagaimana wait() menjaga keteraturan dan mencegah zombie process. Simulasi ini penting sebagai dasar untuk memahami konsep lanjutan seperti exec(), signal handling, dan inter-process communication (IPC).

...

**Solusi**

- Inisialisasi dan Setup
  Mendefinisikan jumlah fork dan warna untuk output terminal. Seed random akan diinisialisasi di proses induk.
  ```
  #define NUM_FORKS 5
  #define COLOR_RESET   "\x1b[0m"
  #define COLOR_RED     "\x1b[31m"
  #define COLOR_GREEN   "\x1b[32m"
  #define COLOR_YELLOW  "\x1b[33m"
  #define COLOR_BLUE    "\x1b[34m"
  #define COLOR_MAGENTA "\x1b[35m"
  #define COLOR_CYAN    "\x1b[36m"

  srand(time(NULL)); 
  printf(COLOR_BLUE "Proses Induk (PID: %d) memulai simulasi...\n" COLOR_RESET, getpid());
  ```
  
- Membuat Child Process
  Parent process akan menjalankan loop untuk membuat proses anak sebanyak `NUM_FORKS`. Setiap fork menghasilkan proses anak baru. Jika eror maka akan ada error mesagge.
  ```
  for (int i = 0; i < NUM_FORKS; i++) {
        pid = fork();
        if (pid == -1) {
            perror(COLOR_RED "Fork failed" COLOR_RESET);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            ...
        }
    }
  ```

- Random Sleep dan Keluar pada Child Process
  Setiap child process akan mengatur seed random dengan `getpid()`, menentukan delay acak 1 - 5 detik, sleep selama delay tersebut, dan mengeluarkan status sukses.
  ```
  srand(getpid());
            int delay_time = rand() % 5 + 1; 

            printf(COLOR_YELLOW "[Child PID: %d] (Parent PID: %d) akan tidur selama %d detik...\n" COLOR_RESET, getpid(), getppid(), delay_time);
            sleep(delay_time);
            printf(COLOR_CYAN "[Child PID: %d] Selesai dengan delay %d detik\n" COLOR_RESET, getpid(), delay_time);
            exit(EXIT_SUCCESS); 
  ```

- Parent Process Akan Menunggu Setiap Child Process
  Parent Process akan menunggu setiap anak selesai, satu per satu, dan mencetak status keluar masing-masing.
  ```
  for (int i = 0; i < NUM_FORKS; i++) {
        pid_t child_pid = wait(&status); 
        if (child_pid == -1) {
            perror(COLOR_RED "wait failed" COLOR_RESET); 
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
            printf(COLOR_GREEN "Proses Induk: Anak dengan PID %d telah selesai dengan status %d (SUKSES).\n" COLOR_RESET, child_pid, WEXITSTATUS(status));
        } else {
            printf(COLOR_RED "Proses Induk: Anak dengan PID %d selesai dengan status %d (GAGAL).\n" COLOR_RESET, child_pid, WEXITSTATUS(status));
        }
    }
  ```

- Cara Compile dan Run Program
  - Compile :
    `gcc fork_sim.cpp -o fork_simu.exe`

  - Run :
    `./fork_sim`



  

**Video Menjalankan Program**

[Klik di sini untuk melihat video menjalankan program](assets/DEMO_PROGRAM_FORK_SIMULATION.mp4)


**Gambar Output Program**

![output](assets/Output_Fork_Simulation.png)


## Daftar Pustaka
Silberschatz, A., Galvin, P. B., & Gagne, G. (2020). 

Operating System Concepts (10th ed.). Wiley.

Tanenbaum, A. S., & Bos, H. (2015). 

Modern Operating Systems (4th ed.). Pearson. Kerrisk, M. (2010). 

The Linux Programming Interface: A Linux and UNIX System Programming Handbook.

Robbins, K. A., & Robbins, S. (2003). 

Unix Systems Programming: Communication, Concurrency and Threads. Prentice Hall. Bach, M. J. (1986). 

The Design of the UNIX Operating System. Prentice-Hall. Stallings, W. (2018). 

Operating Systems: Internals and Design Principles (9th ed.). Pearson. Love, R. (2010). 

Linux System Programming (2nd ed.). O’Reilly Media. ANSI. (1986). 

American National Standard for Information Systems — Programming Language C (ANSI X3.159-1989).
