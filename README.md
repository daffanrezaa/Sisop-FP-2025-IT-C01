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
├── fork_simulation.c   # File Utama
├── README.md           # Dokumentasi 

```

## Pengerjaan

**Teori**

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
    `gcc fork_simulation.cpp -o fork_simulation.exe`

  - Run :
    `./fork_simulation`



  

**Video Menjalankan Program**

[Klik di sini untuk melihat video menjalankan program](assets/DEMO_PROGRAM_SIMULASI_FORK.mp4)


**Gambar Output Program**

![output](assets/Output_Fork_Simulation.png)


## Daftar Pustaka

Sitasi 1
Sitasi 2
Sitasi 3
