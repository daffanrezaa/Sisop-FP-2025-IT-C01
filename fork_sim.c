#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>  

#define NUM_FORKS 5

// Definisi warna untuk output terminal
#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"

int main() {
    pid_t pid;
    srand(time(NULL));  // setting seed random di proses induk

    printf(COLOR_BLUE "Proses Induk (PID: %d) memulai simulasi...\n" COLOR_RESET, getpid());
    printf(COLOR_BLUE "----------------------------------------\n" COLOR_RESET);

    for (int i = 0; i < NUM_FORKS; i++) {
        pid = fork();
        if (pid == -1) {
            // pesan log kalau fork gagal
            perror(COLOR_RED "Fork failed" COLOR_RESET);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // proses anak
            srand(getpid());
            int delay_time = rand() % 5 + 1; // delay random 1-5 detik

            // child akan tidur dengan delay yang telah ditentukan sebelumnya
            printf(COLOR_YELLOW "[Child PID: %d] (Parent PID: %d) akan tidur selama %d detik...\n" COLOR_RESET, getpid(), getppid(), delay_time);
            sleep(delay_time);
            // child setelah selesai tidur
            printf(COLOR_CYAN "[Child PID: %d] Selesai dengan delay %d detik\n" COLOR_RESET, getpid(), delay_time);
            exit(EXIT_SUCCESS); // keluar setelah selesai dengan status sukses
        }
    }

    // proses parent, tunggu semua proses anak selesai
    int status;
    for (int i = 0; i < NUM_FORKS; i++) {
        pid_t child_pid = wait(&status); // menunggu proses anak selesai dan mendapatkan PID serta statusnya
        if (child_pid == -1) {
            perror(COLOR_RED "wait failed" COLOR_RESET); // pesan jika error
            exit(EXIT_FAILURE);
        }
        // mencetak PID anak dan status keluar
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
            printf(COLOR_GREEN "Proses Induk: Anak dengan PID %d telah selesai dengan status %d (SUKSES).\n" COLOR_RESET, child_pid, WEXITSTATUS(status));
        } else {
            printf(COLOR_RED "Proses Induk: Anak dengan PID %d selesai dengan status %d (GAGAL).\n" COLOR_RESET, child_pid, WEXITSTATUS(status));
        }
    }

    printf(COLOR_BLUE "----------------------------------------\n" COLOR_RESET);
    // pesan setelah semua proses selesai
    printf(COLOR_MAGENTA "Semua proses anak telah selesai. Proses Induk (PID: %d) selesai.\n" COLOR_RESET, getpid());
    return EXIT_SUCCESS; // program selesai
}