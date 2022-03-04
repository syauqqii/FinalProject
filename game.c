/*
	FINAL PROJECT - BINUS UNIVERSITY
	
	NAME : Dimas Syauqi Syafa
	NIM  : 2502004405
*/

/*============================
	Area Import Library
============================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

/*============================
	Area Import Bersyarat
============================*/
#ifdef _WIN32
#include <windows.h>
#define OS_Windows
#else
#include <unistd.h>
#endif

// =========================================================================================================================================

/*============================
Area Deklarasi Variable Global
============================*/
char huruf[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};
char os[32];
char hasil[16][4];
char nama_pemain[100];
int skor_pemain = 0;
int skor_komputer = 0;
int acak_angka[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
};
int size_acak_angka = sizeof(acak_angka) / sizeof(acak_angka[0]);
int line_data_skor;
char cheat[32];

/*============================
	Area Deklarasi Struct
============================*/
struct data_kata{
	char kata_acak[5];
} kata[16];

struct data_score{
	int skor;
	char nm_pemain[100];
} skor[500];

/*============================
	Area Deklarasi Function
============================*/
void clear_screen(); // Untuk membersihkan layat
void deteksi_os();
void password();
void menu(int parameter); // Menampilkan menu, parameter : -1 handle error / 0 menu utama
void generator(int parameter, int acak);
// Untuk generate kata acak, parameter : 0 list / 1 kotak
// acak : 0 false / 1 true
void simpan_hasil(int set);
void sort();
void start_game();
void score();
void bermain(char cheat[]);
void tampilkan_pemenang();
void tampilkan_score(int set);
void baca_score();

// =========================================================================================================================================

/*============================
	Area Function Main()
============================*/
int main(){
	srand(time(NULL));
	
	deteksi_os();
	
	strcpy(cheat, "tidak_aktif_OFF_0_fals3");
	
	menu(0);
	
	return 0;
}

// =========================================================================================================================================

/*============================
	Area clear_screen()
============================*/
void clear_screen(){
	system("@cls||clear");
}

/*============================
	  Area deteksi_os()
============================*/
void deteksi_os(){
	#ifdef OS_Windows
	strcpy(os, "Windows");
	system("title Permainan Yang Sangat Menyenangkan");
	#else
	strcpy(os, "Linux");
	#endif
}

/*============================
	  Area password()
============================*/
void password(){
	int temp = 0, inc;
	char code[32];
	char pil;
	
	if(strcmp(cheat, "aktif_ON_1_tru3") == 0){
		clear_screen();
		printf("\n [#] Cheat Game\n");
		printf("  |\n");
		printf("  | [>] Cheat : ON\n");
		printf("  |\n");
		printf(" [>] OFF cheat [Y/T] ? ");
		scanf(" %c", &pil);
		pil = toupper(pil);
		if(pil == 'Y'){
			strcpy(cheat, "tidak_aktif_OFF_0_fals3");
			menu(0);
		} else if(pil == 'T'){
			menu(0);
		} else {
			menu(-1);
		}
	} else if(strcmp(cheat, "tidak_aktif_OFF_0_fals3") == 0){
		for(inc = 0; inc < 3; inc++){
			clear_screen();
			printf("\n [#] Input Cheat Code : ");
			scanf(" %s", code);
			if(strcmp(code, "aktif_ON_1_tru3") == 0){
				strcpy(cheat, "aktif_ON_1_tru3");
				break;
			}
		}
		menu(0);
	}
}

/*============================
		Area menu()
============================*/
void menu(int parameter){
	clear_screen();
	int pilihan = '\0';
	char pertanyaan;
	
	if(parameter == -1){
		printf("\n [#] Error: Menu / Pilihan Tidak Tersedia!\n");
		printf("  |\n");
		printf("  |  [>] OS terdeteksi : %s\n  |  [>] Restart Untuk Bermain Kembali\n", os);
		printf("  |\n");
		printf(" [!] Terima Kasih!\n");
		
		sleep(5);
		
		exit(1);
	}
	
	if(parameter == 0){
		if(strcmp(cheat, "aktif_ON_1_tru3") == 0){
			printf("\n [#] Permainan Yang Sangat Menyenangkan | Cheat : ON\n");
		} else if(strcmp(cheat, "tidak_aktif_OFF_0_fals3") == 0){
			printf("\n [#] Permainan Yang Sangat Menyenangkan | Cheat : OFF\n");
		}
		printf("  |\n");
		printf("  |  [1] Generate Kata\n");
		printf("  |  [2] Mulai Bermain\n");
		printf("  |  [3] Lihat Skor\n");
		printf("  |  [4] Cheat\n");
		printf("  |  [0] Keluar\n");
		printf("  |\n");
		
		printf(" [>] Masukkan pilihan anda : [0-4] ");
		scanf("%d", &pilihan);
		
		if(pilihan == 1){
			generator(0, 1);
		} else if(pilihan == 2){
			start_game();
		} else if(pilihan == 3){
			score();
		} else if(pilihan == 4){
			password();	
		} else if(pilihan == 0){
			printf(" [>] Yakinkah ingin keluar ? [Y/T] ");
			scanf(" %c", &pertanyaan);
			
			pertanyaan = toupper(pertanyaan);
			
			if(pertanyaan == 'Y'){
				exit(0);
			} else if(pertanyaan == 'T'){
				menu(0);
			} else {
				menu(-1);
			}
		} else {
			menu(-1);
		}
	}
}

/*============================
      Area generator()
============================*/
void generator(int parameter, int acak){
	clear_screen();
	int inc, proc, random, pilihan;
	
	if(acak == 1){
		for(inc = 0; inc < 16; inc++){
			for(proc = 0; proc < 5; proc++){
				random = rand() % sizeof(huruf);
				hasil[inc][proc] = huruf[random];
			}
		}
		if(parameter == 0){
			printf("\n [#] Hasil Generate Kata Acak :\n");
			printf("  |\n");
			
			for(inc = 0; inc < 16; inc++){
				printf("  |  [>] %.5s\n", hasil[inc]);
			}
			
			printf("  |\n");
			printf("  |  [1] Simpan\n");
			printf("  |  [2] Acak Kembali\n");
			printf("  |  [3] Tampilkan Dengan Kotak\n");
			printf("  |\n");
			
			printf(" [?] Masukkan pilihan anda : [1-3] ");
			scanf(" %d", &pilihan);
			
			if(pilihan == 1){
				simpan_hasil(1);
				menu(0);
			} else if(pilihan == 2){
				generator(0, 1);
			} else if(pilihan == 3){
				generator(1, 0);
			} else {
				menu(-1);
			}
		} else if(parameter == 1){
			printf("\n [#] Hasil Generate Kata Acak :\n");
			printf("  |\n");
			
			for(inc = 1; inc <= 21; inc++){
				if(inc == 1){
					printf("  |   _______________________________________________\n");
				} else if(inc == 6 || inc == 11 || inc == 16 || inc == 21){
					printf("  |  |___________|___________|___________|___________|\n");
				}else if(inc == 2 || inc == 3 || inc == 5 || inc == 7 || inc == 8 || inc == 10 || inc == 12 || inc == 13 || inc == 15 || inc == 17 || inc == 18 || inc == 20){
					printf("  |  |           |           |           |           |\n");
				} else if(inc == 4 || inc == 9 || inc == 14 || inc == 19){
					if(inc == 4){
						printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", hasil[inc-4], hasil[inc-3], hasil[inc-2], hasil[inc-1]);
					} else if(inc == 9){
						printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", hasil[inc-5], hasil[inc-4], hasil[inc-3], hasil[inc-2]);
					} else if(inc == 14){
						printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", hasil[inc-6], hasil[inc-5], hasil[inc-4], hasil[inc-3]);
					} else if(inc == 19){
						printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", hasil[inc-7], hasil[inc-6], hasil[inc-5], hasil[inc-4]);
					}
				}
			}
			
			printf("  |\n");
			printf("  |  [1] Simpan\n");
			printf("  |  [2] Acak Kembali\n");
			printf("  |  [3] Tampilkan Dengan List\n");
			printf("  |\n");
			
			printf(" [?] Masukkan pilihan anda : [1-3] ");
			scanf(" %d", &pilihan);
			
			if(pilihan == 1){
				simpan_hasil(1);
				menu(0);
			} else if(pilihan == 2){
				generator(1, 1);
			} else if(pilihan == 3){
				generator(0, 0);
			} else {
				menu(-1);
			}
		}
	} else if(acak == 0){
		if(parameter == 0){
		printf("\n [#] Hasil Generate Kata Acak :\n");
		printf("  |\n");
		
		for(inc = 0; inc < 16; inc++){
			printf("  |  [>] %.5s\n", hasil[inc]);
		}
		
		printf("  |\n");
		printf("  |  [1] Simpan\n");
		printf("  |  [2] Acak Kembali\n");
		printf("  |  [3] Tampilkan Dengan Kotak\n");
		printf("  |\n");
		
		printf(" [?] Masukkan pilihan anda : [1-3] ");
		scanf(" %d", &pilihan);
		
		if(pilihan == 1){
			simpan_hasil(1);
			menu(0);
		} else if(pilihan == 2){
			generator(0, 1);
		} else if(pilihan == 3){
			generator(1, 0);
		} else {
			menu(-1);
		}
	} else if(parameter == 1){
		printf("\n [#] Hasil Generate Kata Acak :\n");
			printf("  |\n");
			
			for(inc = 1; inc <= 21; inc++){
				if(inc == 1){
					printf("  |   _______________________________________________\n");
				} else if(inc == 6 || inc == 11 || inc == 16 || inc == 21){
					printf("  |  |___________|___________|___________|___________|\n");
				}else if(inc == 2 || inc == 3 || inc == 5 || inc == 7 || inc == 8 || inc == 10 || inc == 12 || inc == 13 || inc == 15 || inc == 17 || inc == 18 || inc == 20){
					printf("  |  |           |           |           |           |\n");
				} else if(inc == 4 || inc == 9 || inc == 14 || inc == 19){
					if(inc == 4){
						printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", hasil[inc-4], hasil[inc-3], hasil[inc-2], hasil[inc-1]);
					} else if(inc == 9){
						printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", hasil[inc-5], hasil[inc-4], hasil[inc-3], hasil[inc-2]);
					} else if(inc == 14){
						printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", hasil[inc-6], hasil[inc-5], hasil[inc-4], hasil[inc-3]);
					} else if(inc == 19){
						printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", hasil[inc-7], hasil[inc-6], hasil[inc-5], hasil[inc-4]);
					}
				}
			}
			
			printf("  |\n");
			printf("  |  [1] Simpan\n");
			printf("  |  [2] Acak Kembali\n");
			printf("  |  [3] Tampilkan Dengan List\n");
			printf("  |\n");
			
			printf(" [?] Masukkan pilihan anda : [1-3] ");
			scanf(" %d", &pilihan);
			
			if(pilihan == 1){
				simpan_hasil(1);
				menu(0);
			} else if(pilihan == 2){
				generator(1, 1);
			} else if(pilihan == 3){
				generator(0, 0);
			} else {
				menu(-1);
			}
		}
	}
}

/*============================
	Area simpan_hasil()
============================*/
void simpan_hasil(int set){
	int inc;
	
	if(set == 1){
		FILE *data_file = fopen("data.txt", "w");
		
		for(inc = 0; inc < 16; inc++){
			fprintf(data_file, "%.5s\n", hasil[inc]);
		}
		
		fclose(data_file);
	} else if(set == 2){
		FILE *score_file = fopen("score.txt", "a");
		
	
		if(skor_pemain > skor_komputer){
			fprintf(score_file, "%d,%s\n", skor_pemain, nama_pemain);
		} else if(skor_pemain < skor_komputer){
			fprintf(score_file, "%d,[KOMPUTER]\n", skor_komputer);
		} else if(skor_pemain == skor_komputer){
			fprintf(score_file, "%d,[DRAW] %s + [KOMPUTER]\n", skor_pemain, nama_pemain);
		}
	
		fclose(score_file);
	}
}

/*============================
		Area sort()
============================*/
void sort(int angka[], int jumlah_index){
	int step, swapped, i, temp;
	
	for(step = 0; step < jumlah_index - 1; ++step){
		swapped = 0;
		for(i = 0; i < jumlah_index - step - 1; ++i){
			if(angka[i] > angka[i+1]){
				temp = angka[i];
				angka[i] = angka[i + 1];
				angka[i + 1] = temp;
				swapped = 1;
			}
		}
		if(swapped == 0){
			break;
		}
	}
}

/*============================
	Area start_game()
============================*/
void start_game(){
	clear_screen();
	
	int inc = 0;
	char siap;
	
	FILE *fname = fopen("data.txt", "r");
	
	if(fname == NULL){
		printf("\n [#] Error!!");
		printf("\n  |\n  | [>] OS terdeteksi : %s\n  | [>] Masuk ke menu generate dahulu sebelum bermain.\n  |\n", os);
		printf(" [!] Terima Kasih!\n");
		sleep(5);
		exit(1);
	}
	
	while(!feof(fname)){
		fscanf(fname, " %s", kata[inc].kata_acak);
		inc++;
	}
	
	if(inc < 2){
		printf("\n [#] Error!!");
		printf("\n  |\n  | [>] OS terdeteksi : %s\n  | [>] Masuk ke menu generate dahulu kemudian pilih [1] Simpan\n  |\n",os);
		printf(" [!] Terima Kasih!\n");
		sleep(5);
		exit(1);
	}
	
	fclose(fname);
	
	printf("\n [#] Mulai Permainan\n");
	for(inc = 1; inc <= 21; inc++){
		if(inc == 1){
			printf("  |   _______________________________________________\n");
		} else if(inc == 6 || inc == 11 || inc == 16 || inc == 21){
			printf("  |  |___________|___________|___________|___________|\n");
		}else if(inc == 2 || inc == 3 || inc == 5 || inc == 7 || inc == 8 || inc == 10 || inc == 12 || inc == 13 || inc == 15 || inc == 17 || inc == 18 || inc == 20){
			printf("  |  |           |           |           |           |\n");
		} else if(inc == 4 || inc == 9 || inc == 14 || inc == 19){
			if(inc == 4){
				printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", kata[inc-4].kata_acak, kata[inc-3].kata_acak, kata[inc-2].kata_acak, kata[inc-1].kata_acak);
			} else if(inc == 9){
				printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", kata[inc-5].kata_acak, kata[inc-4].kata_acak, kata[inc-3].kata_acak, kata[inc-2].kata_acak);
			} else if(inc == 14){
				printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", kata[inc-6].kata_acak, kata[inc-5].kata_acak, kata[inc-4].kata_acak, kata[inc-3].kata_acak);
			} else if(inc == 19){
				printf("  |  |   %.5s   |   %.5s   |   %.5s   |   %.5s   |\n", kata[inc-7].kata_acak, kata[inc-6].kata_acak, kata[inc-5].kata_acak, kata[inc-4].kata_acak);
			}
		}
	}
	printf("  |\n [?] Apakah anda sudah siap bermain [Y/T] ? ");
	scanf(" %c", &siap);
	
	siap = toupper(siap);
	
	if(siap == 'Y'){
		clear_screen();
	
		printf(" [#] Masukkan Nama Anda : ");
		scanf(" %[^\n]s ", nama_pemain);
		
		bermain(cheat);
	} else if(siap == 'T'){
		menu(0);
	} else{
		menu(-1);
	}
}

/*============================
		Area bermain()
============================*/
void bermain(char cheat[]){
	int inc, proc, jawab, random, temp, pilihan, i;
	
	skor_pemain = 0;
	skor_komputer = 0;
	
	srand(time(NULL));
	
	for(inc = 0; inc < size_acak_angka; inc++){
		proc = (rand() % 14) + 1;
		random 			 = acak_angka[inc];
		acak_angka[inc]	 = acak_angka[proc];
		acak_angka[proc] = random;
	}
	
	if(strcmp(cheat,"aktif_ON_1_tru3") == 0){
		for(proc = 0; proc < 16; proc++){
			clear_screen();
			random = acak_angka[proc];
			if(proc == 0){
				printf("\n [#] Game di mulai | Ronde : %d | komputer : %d | Anda : %d | Index : %d |", proc+1, skor_komputer, skor_pemain, random+1);
			} else if(proc > 0){
				printf("\n [#] Ronde : %d | komputer : %d | Anda : %d | Index : %d |", proc+1, skor_komputer, skor_pemain, random+1);
			}
			for(inc = 1; inc <= 21; inc++){
				if(inc == 1){
					printf("\n  |  _______________________________________________\n");
				} else if(inc == 6 || inc == 11 || inc == 16 || inc == 21){
					printf("  | |___________|___________|___________|___________|\n");
				}else if(inc == 2 || inc == 3 || inc == 5 || inc == 7 || inc == 8 || inc == 10 || inc == 12 || inc == 13 || inc == 15 || inc == 17 || inc == 18 || inc == 20){
					printf("  | |           |           |           |           |\n");
				} else if(inc == 4 || inc == 9 || inc == 14 || inc == 19){
					if(inc == 4){
						printf("  | |   %3d     |   %3d     |   %3d     |   %3d     |\n", inc-3, inc-2, inc-1, inc);
					} else if(inc == 9){
						printf("  | |   %3d     |   %3d     |   %3d     |   %3d     |\n", inc-4, inc-3, inc-2, inc-1);
					} else if(inc == 14){
						printf("  | |   %3d     |   %3d     |   %3d     |   %3d     |\n", inc-5, inc-4, inc-3, inc-2);
					} else if(inc == 19){
						printf("  | |   %3d     |   %3d     |   %3d     |   %3d     |\n", inc-6, inc-5, inc-4, inc-3);
					}
				}
			}
			printf("  |\n [?] Dikotak manakah tulisan \"%.5s\" berada ?", kata[random].kata_acak);
			
			printf("\n [>] %s [1-16] : ", nama_pemain);
			scanf(" %d", &jawab);
			
			if(jawab < 1 || jawab > 16){
				menu(-1);
			}
			
			if(jawab - 1 == random){
				skor_pemain = skor_pemain + 10;
			} else {
				for(i = 0; i < 16; i++){
					temp = rand() % 16;
					if(temp != jawab && temp-1 != jawab-1 && temp > 0 && temp <= 16){
						temp = temp;
						break;
					}
				}
				printf(" [>] Komputer [1-16] : ");
				sleep(1);
				printf("%d", temp);
				sleep(1);
				if(temp-1 == random){
					skor_komputer = skor_komputer + 10;
				}
			}
		}
	} else if(strcmp(cheat, "tidak_aktif_OFF_0_fals3") == 0){
		for(proc = 0; proc < 16; proc++){
			clear_screen();
			random = acak_angka[proc];
			if(proc == 0){
				printf("\n [#] Game di mulai | Ronde : %d | komputer : %d | Anda : %d |", proc+1, skor_komputer, skor_pemain);
			} else if(proc > 0){
				printf("\n [#] Ronde : %d | komputer : %d | Anda : %d |", proc+1, skor_komputer, skor_pemain);
			}
			for(inc = 1; inc <= 21; inc++){
				if(inc == 1){
					printf("\n  |  _______________________________________________\n");
				} else if(inc == 6 || inc == 11 || inc == 16 || inc == 21){
					printf("  | |___________|___________|___________|___________|\n");
				}else if(inc == 2 || inc == 3 || inc == 5 || inc == 7 || inc == 8 || inc == 10 || inc == 12 || inc == 13 || inc == 15 || inc == 17 || inc == 18 || inc == 20){
					printf("  | |           |           |           |           |\n");
				} else if(inc == 4 || inc == 9 || inc == 14 || inc == 19){
					if(inc == 4){
						printf("  | |   %3d     |   %3d     |   %3d     |   %3d     |\n", inc-3, inc-2, inc-1, inc);
					} else if(inc == 9){
						printf("  | |   %3d     |   %3d     |   %3d     |   %3d     |\n", inc-4, inc-3, inc-2, inc-1);
					} else if(inc == 14){
						printf("  | |   %3d     |   %3d     |   %3d     |   %3d     |\n", inc-5, inc-4, inc-3, inc-2);
					} else if(inc == 19){
						printf("  | |   %3d     |   %3d     |   %3d     |   %3d     |\n", inc-6, inc-5, inc-4, inc-3);
					}
				}
			}
			printf("  |\n [?] Dikotak manakah tulisan \"%.5s\" berada ?", kata[random].kata_acak);
			
			printf("\n [>] %s [1-16] : ", nama_pemain);
			scanf(" %d", &jawab);
			
			if(jawab < 1 || jawab > 16){
				menu(-1);
			}
			
			if(jawab - 1 == random){
				skor_pemain = skor_pemain + 10;
			} else {
				for(i = 0; i < 16; i++){
					temp = rand() % 16;
					if(temp != jawab && temp-1 != jawab-1 && temp > 0 && temp <= 16){
						temp = temp;
						break;
					}
				}
				printf(" [>] Komputer [1-16] : ");
				sleep(1);
				printf("%d", temp);
				sleep(1);
				if(temp-1 == random){
					skor_komputer = skor_komputer + 10;
				}
			}
		}
	}
	
	clear_screen();
	
	pilihan = '\0';
	
	printf("\n [#] Game telah selsai..\n");
	printf("  |\n");
	tampilkan_pemenang();
	printf("  |\n");
	printf("  | [1] Kembali Ke Menu Utama\n");
	printf("  | [2] Lihat Skor\n");
	printf("  |\n [>] Masukkan Pilihan Anda : [1-2] ");
	scanf(" %d", &pilihan);
	
	simpan_hasil(2);
	
	if(pilihan == 1){
		menu(0);
	} else if(pilihan == 2){
		score();
	} else {
		menu(-1);
	}
}

/*============================
  Area tampilkan_pemenang()
============================*/
void tampilkan_pemenang(){
	if(skor_pemain > skor_komputer){
		printf("  | [>] Hasil : %s Menang!\n", nama_pemain);
	} else if(skor_pemain < skor_komputer){
		printf("  | [>] Hasil : Komputer Menang!\n");
	} else if(skor_pemain == skor_komputer){
		printf("  | [>] Hasil : Seri! Tidak ada Pemenang!\n");
	}
}

/*============================
		Area score()
============================*/
void score(){
	clear_screen();
	
	int inc, proc;
	
	baca_score();
	tampilkan_score(2);
}

/*============================
	  Area baca_score()
============================*/
void baca_score(){
	FILE *fname = fopen("score.txt", "r");
	int i;
	
	if(fname == NULL){
		printf("\n [#] Error!!");
		printf("\n  |\n  | [>] OS terdeteksi : %s\n  | [>] Bermainlah dahulu!\n  |\n", os);
		printf(" [!] Terima Kasih!\n");
		sleep(5);
		exit(1);
	}
	
	for(i = 0; i < line_data_skor-1; i++){
		skor[i].skor = '\0';
		skor[i].nm_pemain == NULL;
	}
	
	line_data_skor = 0;
	
	while(!feof(fname)){
		fscanf(fname, " %d,%[^\n]", &skor[line_data_skor].skor, skor[line_data_skor].nm_pemain);
		line_data_skor++;
	}
	
	if(line_data_skor-1 < 1){
		printf("\n [#] Error!!");
		printf("\n  |\n  | [>] OS terdeteksi : %s\n  | [>] Belum ada pemenang / Scoreboard masih kosong!\n", os);
		printf("  | [>] Berimainlah Terlebih Dahulu!\n  |\n");
		printf(" [!] Terima Kasih!\n");
		sleep(5);
		exit(1);
	}
	
	fclose(fname);
}

/*============================
	Area tampilkan_score()
============================*/
void tampilkan_score(int set){
	int sorting[line_data_skor-1];
	int reverse[line_data_skor-1];
	int inc = '\0', i, proc = '\0', pilihan;
	
	
	int display[500];
	int displat[500];
	
	clear_screen();
	
	for(inc = 0; inc < line_data_skor-1; inc++){
		sorting[inc] = skor[inc].skor;
	}
	
	sort(sorting, line_data_skor-1);
	
	i = 0;
	
	for(inc = line_data_skor-2; inc > -1; inc--){
		reverse[i] = sorting[inc];
		i++;
	}
	
	if(set == 1){	
		printf("\n [#] Scoreboard\n  |");
		
		printf("\n  |  SKOR  |  NAMA\n");
		printf("  | ===========================\n");
		for(proc = 0; proc < line_data_skor-1; proc++){
			for(inc = 0; inc < line_data_skor-1; inc++){
				if(reverse[proc] == skor[inc].skor && display[inc] != 1){
					if(skor[inc].skor < 10){
						printf("  |     %d  |  %s\n", skor[inc].skor, skor[inc].nm_pemain);
					} else if (skor[inc].skor < 100){
						printf("  |    %d  |  %s\n", skor[inc].skor, skor[inc].nm_pemain);
					} else if(skor[inc].skor > 100){
						printf("  |   %d  |  %s\n", skor[inc].skor, skor[inc].nm_pemain);
					}
					display[inc] = 1;
				}
			}
		}
		
		printf("  |\n [1] Sorting Berdasarkan Skor Terendah\n");
		printf(" [2] Kembali Ke Menu Utama\n  |\n");
		
		printf(" [>] Masukkan Pilihan Anda : ");
		scanf(" %d", &pilihan);
		
		if(pilihan == 1){
			tampilkan_score(2);
		} else if(pilihan == 2){
			menu(0);
		} else {
			menu(-1);
		}
	} else if(set == 2){
		printf("\n [#] Scoreboard\n  |");
		
		printf("\n  |  SKOR  |  NAMA\n");
		printf("  | ===========================\n");
		for(proc = 0; proc < line_data_skor-1; proc++){
			for(inc = 0; inc < line_data_skor-1; inc++){
				if(sorting[proc] == skor[inc].skor && displat[inc] != 1){
					if(skor[inc].skor < 10){
						printf("  |     %d  |  %s\n", skor[inc].skor, skor[inc].nm_pemain);
					} else if (skor[inc].skor < 100){
						printf("  |    %d  |  %s\n", skor[inc].skor, skor[inc].nm_pemain);
					} else if(skor[inc].skor > 100){
						printf("  |   %d  |  %s\n", skor[inc].skor, skor[inc].nm_pemain);
					}
					displat[inc] = 1;
				}
			}
		}
		
		printf("  |\n [1] Sorting Berdasarkan Skor Tertinggi\n");
		printf(" [2] Kembali Ke Menu Utama\n  |\n");
		
		printf(" [>] Masukkan Pilihan Anda : ");
		scanf(" %d", &pilihan);
		
		if(pilihan == 1){
			tampilkan_score(1);
		} else if(pilihan == 2){
			menu(0);
		} else {
			menu(-1);
		}
	}
}
