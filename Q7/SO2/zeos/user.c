#include <errno.h>
#include <libc.h>

void test_pollEvent(){
    char buff[24];
    struct event_t ev;
    write(1, "Test 1 de pollEvent(), prem qualsevol tecla, q per sortir\n", 59);
    while (ev.scancode != 16) { //16 es el scancode de q
        int r = pollEvent(&ev);
        if (r > 0) {  //Nomes escrivim si hi ha tecles
            write(1, "Scancode: ", 10);
            itoa(ev.scancode, buff);
            write(1, buff, strlen(buff));
            write(1, ", Pressed: ", 11);
            itoa(ev.pressed, buff);
            write(1, buff, strlen(buff));
            write(1, "\n", 1);
        }
    }
}

void test_ansi() {
    //bucle per esborrar la pantalla
    for (int i = 0; i < 80; ++i) {
        for (int j = 0; j < 25; ++j) {
            char buffer[10];
            int len = 0;

            //\x1B[j;i;f
            buffer[len++] = '\x1B';
            buffer[len++] = '[';

            int i_temp = i;
            if (i_temp >= 10) {
                buffer[len++] = '0' + i_temp / 10;
            }
            buffer[len++] = '0' + i_temp % 10;

            buffer[len++] = ';';

            int j_temp = j;
            if (j_temp >= 10) {
                buffer[len++] = '0' + j_temp / 10;
            }
            buffer[len++] = '0' + j_temp % 10;

            buffer[len++] = 'f';

            if (write(1, buffer, len) < 0) perror();

            if (write(1, "\x1B[K", 3) < 0) perror();
        }
    }
    int delay = gettime();
    while (gettime() - delay < 500);

    // ---------------------------------------------
    // Test 1: Mou cursor
    // ---------------------------------------------
    if (write(1, "Test 1: Mou cursor a (1,3)\n", 27) < 0) perror();
    if (write(1, "\x1B[1;3H", 6) < 0) perror();

    delay = gettime();
    while (gettime() - delay < 1000);

    // ---------------------------------------------
    // Test 2: Mou cursor amb 'f'
    // ---------------------------------------------
    if (write(1, "Test 2: Mou cursor a (2,2) amb 'f'\n", 36) < 0) perror();
    if (write(1, "\x1B[2;2f", 6) < 0) perror();

    delay = gettime();
    while (gettime() - delay < 1000);

    // ---------------------------------------------
    // Test 3: Esborrar
    // ---------------------------------------------
    if (write(1, "Test 3: Esborrar caracter\n", 27) < 0) perror();
    if (write(1, "\x1B[11;11f", 8) < 0) perror();
    if (write(1, "X", 1) < 0) perror();
    delay = gettime();
    while (gettime() - delay < 1000);
    if (write(1, "\x1B[11;11f", 8) < 0) perror();
    if (write(1, "\x1B[K", 3) < 0) perror();

    delay = gettime();
    while (gettime() - delay < 1000);

    if (write(1, "\x1B[1;6f", 6) < 0) perror();

    delay = gettime();
    while (gettime() - delay < 1000);

    // ---------------------------------------------
    // Test 4: Canvi de color foreground
    // ---------------------------------------------
    if (write(1, "Test 4: Canvi foreground a 6\n", 29) < 0) perror();
    if (write(1, "\x1B[3;6m", 6) < 0) perror();
    if (write(1, "TEXT FG 6\n", 10) < 0) perror();

    delay = gettime();
    while (gettime() - delay < 1000);

    // ---------------------------------------------
    // Test 5: Canvi de color background
    // ---------------------------------------------
    if (write(1, "Test 5: Canvi background a 4\n", 29) < 0) perror();
    if (write(1, "\x1B[4;4m", 6) < 0) perror();
    if (write(1, "TEXT BG 4\n", 10) < 0) perror();

    delay = gettime();
    while (gettime() - delay < 1000);

    // ---------------------------------------------
    // Test 6: Comanda desconeguda (hauria de donar ENOSYS)
    // ---------------------------------------------
    if (write(1, "Test 6: Comanda no implementada (X)\n", 37) < 0) perror();
    if (write(1, "\x1B[10;10X", 8) < 0) perror();

    // ---------------------------------------------
    // Test 7: Paràmetres fora de rang
    // ---------------------------------------------
    if (write(1, "Test 7: Cursor fora de rang\n", 28) < 0) perror();
    if (write(1, "\x1B[999;999H", 10) < 0) perror();

    // ---------------------------------------------
    // Test 8: Color fora de rang
    // ---------------------------------------------
    if (write(1, "Test 8: Color fora rang\n", 25) < 0) perror();
    if (write(1, "\x1B[3;999m", 8) < 0) perror();


    if (write(1, "--- FI TEST ANSI ---\n", 21) < 0) perror();
}

char stacks[10][4096]; 
int sum_total=0;

void thread_test_1(void* arg){
  int time = gettime();
  while (gettime() - time < 50);
  exit();
}

void thread_test_2(void* arg){
  char buff[24];
  write(1, "Soc un thread del PID: ", strlen("Soc un thread del PID: "));
  int pid = getpid();
  itoa(pid, buff);
  write(1, buff, strlen(buff));
  write(1, " amb TID: ", strlen(" amb TID: "));
  itoa((int)(long)arg, buff);
  write(1, buff, strlen(buff));
  write(1, "\n", 1);
  exit();
}

void thread_test_3(void* arg){
  char buff[24];
  int val = (int)arg;
  sum_total += val;
  write(1, "Thread TID: ", 13);
  int tid = gettid();
  itoa(tid, buff);
  write(1, buff, strlen(buff));
  write(1, " ha sumat ", 10);
  itoa(val, buff);
  write(1, buff, strlen(buff));
  write(1, "\n", 1);
  exit();
}

void thread_test_5(void* arg){
  //Escriu alguna cosa cada cert temps
  int i = 0;
  while( i < 10){
    int time = gettime();
    while (gettime() - time < 200);
    write(1, "Fent res...\n", 12);
    i++;
  }
  exit();
}

void thread_test_6(void* arg){
  char buff[24];
  int err = write(2, "Prova error errno\n", 19); //fd 2 no valid
  int delay = gettime();
  while (gettime() - delay < 100);
  if (err < 0) {
    write (1, "PID: ", 5);
    int pid = getpid();
    itoa(pid, buff);
    write(1, buff, strlen(buff));
    write(1, ", ", 2);
    write(1, "TID: ", 5);
    int tid = gettid();
    itoa(tid, buff);
    write(1, buff, strlen(buff));
    write(1, " errno: ", 8);
    int errno = geterrno();
    itoa(errno, buff);
    write(1, buff, strlen(buff));
    write(1, "\n", 1);
    perror();
  }
  exit();
}

void thread_test6_2(void* arg){
  char buff[24];
  int err = write(1, "", -2); 
  if (err < 0) {
    write (1, "PID: ", 5);
    int pid = getpid();
    itoa(pid, buff);
    write(1, buff, strlen(buff));
    write(1, ", ", 2);
    write(1, "TID: ", 5);
    int tid = gettid();
    itoa(tid, buff);
    write(1, buff, strlen(buff));
    write(1, " errno: ", 8);
    int errno = geterrno();
    itoa(errno, buff);
    write(1, buff, strlen(buff));
    write(1, "\n", 1);
    perror();
  }
  exit();
}

void test_thread(){
  char stacks[10][4096]; 
  char buff[24];
  write(1, "Test 1, crear masses threads i que salti error\n", 48);
  int total_error=0;
  for (int i = 0; i < 10; i++) {
    int tid = clone(thread_test_1, (void*)i, stacks[i]+4096);
    if (tid < 0) total_error++;
  }
  if (total_error > 0){
    write(1, "TEST 1 PASSED\n", 14);
    write(1, "Errors al crear threads: ", 25);
    itoa(total_error, buff); write(1, buff, strlen(buff));
    write(1, "\n", 1);
  }
  int delay = gettime();
  while (gettime() - delay < 500); //Esperem que acabin els threads 
  write(1, "Test 2, crear threads i que mostrin PID i TID\n", 46);
  for (int i = 0; i < 5; i++) {
    clone(thread_test_2, (void*)i, stacks[i]+4096);
  }
  delay = gettime();
  while (gettime() - delay < 500);
  write(1, "Test 3, crear threads que facin una suma\n", 41);
  sum_total = 0;
  for (int i = 1; i <= 5; i++) {
    int tid = clone(thread_test_3, (void*)(long)i, stacks[i]+4096);
    write(1, "Created thread with TID: ", 25);
    itoa(tid, buff); write(1, buff, strlen(buff));
    write(1, "\n", 1);
  }
  delay = gettime();
  while (gettime() - delay < 500); 
  if (sum_total == 15)
    write(1, "TEST 3 PASSED\n", 14);
  else
    write(1, "TEST 3 FAILED\n", 14);

  delay = gettime();
  while (gettime() - delay < 500);
  write(1, "Test 4, test d'errors\n", 22);
  int err1 = clone(0, (void*)0, stacks[0] + 4096);
  if (err1 < 0) write(1, "Funcio NULL OK\n", 15);
  int err2 = clone(thread_test_1, (void*)0, 0);
  if (err2 < 0) write(1, "Stack NULL OK\n", 14);

  write(1, "Test 5, allocate_DIR correcte\n", 30);
  int pid = 0;
  int tid= clone(thread_test_5, (void*)0, stacks[0] + 4096);
  if (tid > 0) { //S'ha creat bé, faig un fork i moro
    pid = fork();
    if (pid == 0) {
      write(1, "Estic viu, el meu pid és: ", 26);
      itoa(getpid(), buff);
      write(1, buff, strlen(buff));
      write(1, "\n", 1);
    } else{
      exit();
    }
  }
  write(1, "Només quedo jo, amb pid ", 25);
  itoa(getpid(), buff);
  write(1, buff, strlen(buff));
  write(1, "\n", 1);
  if (pid == 0) {
    write(1, "TEST 5 PASSED\n Provarem de crear un process que ocupi l'espai del vell\n", 71);
    pid = fork();
    write(1, "Estic viu, el meu pid és: ", 26);
    itoa(getpid(), buff);
    write(1, buff, strlen(buff));
    write(1, "\n", 1);
    if (pid == 0) exit();
  }else write(1, "TEST 5 FAILED\n", 14);
  delay = gettime();
  while (gettime() - delay < 3000); //Esperem que acabi el thread que escriu Fent res
  write(1, "Test 6, test d'errno i race condition\n", 38);
  tid = clone(thread_test_6, (void*)(long)0, stacks[0]+4096);
  tid = clone(thread_test6_2, (void*)(long)0, stacks[1]+4096);
  delay = gettime();
  while (gettime() - delay < 500);
  write(1, "Hauriem de veure dos missatges d'error diferents\n", 49);

}

struct sem_t *sync_sem;

void thread_sync(void *arg) {
  int id = (int)arg;

  if (id == 1) {
    write(1, "[T1] Inici\n", 11);

    int delay = gettime();
    while (gettime() - delay < 500);

    write(1, "[T1] Senyalitzo per a que T2 continui\n", 38);
    semSignal(sync_sem);

    write(1, "[T1] Fi\n", 8);
  }

  if (id == 2) {
    write(1, "[T2] Esperant a T1...\n", 22);
    semWait(sync_sem);

    write(1, "[T2] Desbloquejat per T1\n", 25);
    write(1, "[T2] Fi\n", 8);
  }
}

struct sem_t *mutex;
int counter = 0;

void thread_mutex(void *arg) {
  int id = (int)arg;
  unsigned long delay;

  for (int i = 0; i < 5; i++) {

    semWait(mutex);   // ENTRADA SECCIÓ CRÍTICA

    if (id == 1)
      write(1, "[T1] Dins SC\n", 14);
    else
      write(1, "[T2] Dins SC\n", 14);

    // Simula treball amb delay
    delay = gettime();
    while (gettime() - delay < 500);

    counter++;   // Increment protegit pel mutex

    semSignal(mutex); // sortida secció crítica
  }
}

void test_sems() {

  int pid = fork();
  char buff[24];

  if (pid == 0) {

    write(1, "Test 1, crear masses sems i que salti error\n", 45);
    int total_error=0;
    for (int i = 0; i < 18; i++) {
      struct sem_t* sem = semCreate(1);
      if (!sem) total_error++;
    }
    if (total_error > 0){
      write(1, "TEST 1 PASSED\n", 14);
      write(1, "Errors al crear sems: ", 22);
      itoa(total_error, buff); write(1, buff, strlen(buff));
      write(1, "\n", 1);
    }

    //Veure si funciona la lliberació de recursos (semàfors) a l'exit
    //Aquí es proba sys_semDestroy, ja que l'exit el fa servir
    write(1, "Test 2, lliberar semafors a exit\n", 36);
    exit();
  }

  //Espera al test 1
  int delay = gettime();
  while (gettime() - delay < 2000);


  sync_sem = semCreate(0);
  if (!sync_sem) {
    write(1, "TEST 2 FAILED\n", 13);
    exit();
  }
  write(1, "TEST 2 PASSED\n", 14);


  write(1, "Test 3, sincronitzacio\n", 23);

  char stacks[10][4096];

  clone(thread_sync, (void*)1, stacks[0]+4096);
  clone(thread_sync, (void*)2, stacks[1]+4096);

  delay = gettime();
  while (gettime() - delay < 2000);


  //Hauríem de veure com surten els missatges d'entrada a SC cada 0.5sec
  //(ajustable amb delay), i mai surten dos seguits en menys que aquest temps
  write(1, "==== TEST EXCLUSIO MUTUA ====\n", 32);

  counter = 0;
  mutex = semCreate(1);

  clone(thread_mutex, (void*)1, stacks[2]+4096);
  clone(thread_mutex, (void*)2, stacks[3]+4096);

}

// Funció auxiliar per escriure un missatge literal
void print_msg(const char *msg) {
    int len = 0;
    while (msg[len]) len++;
    write(1, msg, len);
}

// Funció auxiliar per imprimir un valor hexadecimal (32 bits)
void print_hex(unsigned int val) {
    char buf[9];
    for (int i = 0; i < 8; i++) {
        int nibble = (val >> (28 - i*4)) & 0xF;
        if (nibble < 10) buf[i] = '0' + nibble;
        else buf[i] = 'A' + nibble - 10;
    }
    buf[8] = '\0';
    write(1, buf, 8);
}

void print_hex_char(unsigned char val) {
    char buf[2];
    char hex_digits[] = "0123456789ABCDEF";

    buf[0] = hex_digits[(val >> 4) & 0xF];
    buf[1] = hex_digits[val & 0xF];

    write(1, buf, 2);
}

// Test bàsic de creació i eliminació de slots al heap
void test_heap_slot() {
    print_msg("=== TEST: Creacio i eliminacio de slots ===\n");

    //Reservar 2 pàgines per un slot
    char *slot1 = getSlot(8192); // 2 pàgines
    if (!slot1) {
        print_msg("ERROR: sys_getSlot(8192) fallida\n");
        return;
    }
    print_msg("sys_getSlot OK, addr=");
    print_hex((unsigned int)slot1);
    print_msg("\n");

    // reservar 1 pàgina més
    char *slot2 = getSlot(4096); // 1 pàgina
    if (!slot2) {
        print_msg("ERROR: sys_getSlot(4096) fallida\n");
        return;
    }
    print_msg("sys_getSlot OK, addr=");
    print_hex((unsigned int)slot2);
    print_msg("\n");

    //Alliberar el primer slot
    if (delSlot(slot1) != 0) {
        print_msg("ERROR: sys_delSlot(slot1) fallida\n");
        return;
    }
    print_msg("sys_delSlot(slot1) OK\n");

    //Intentar alliberar de nou el mateix slot (hauria de fallar)
    if (delSlot(slot1) == 0) {
        print_msg("ERROR: sys_delSlot(slot1) hauria de fallar, però no\n");
        return;
    }
    print_msg("sys_delSlot(slot1) falla correctament al duplicat\n");
}

// Test de fork i còpia del heap
void test_fork_heap() {
    print_msg("\n=== TEST: Fork i copia del heap ===\n");

    //Reservar un slot abans del fork
    char *slot = getSlot(8192); // 2 pàgines
    if (!slot) {
        print_msg("ERROR: sys_getSlot(8192) fallida abans del fork\n");
        return;
    }
    print_msg("Slot reservat abans del fork, addr=");
    print_hex((unsigned int)slot);
    print_msg("\n");

    //Executar fork
    int pid = fork();
    if (pid < 0) {
        print_msg("ERROR: sys_fork() fallida\n");
        return;
    }

    if (pid == 0) {
        print_msg("Fill: Verificant slot copiat...\n");
        // intentar alliberar el slot copiat
        if (delSlot(slot) != 0) {
            print_msg("ERROR: Fill no pot alliberar slot copiat\n");
        } else {
            print_msg("Fill: Slot copiat alliberat OK\n");
        }
        return;
    } else {
        print_msg("Pare: fork OK, pid=");
        print_hex((unsigned int)pid);
        print_msg("\n");

        //   Alliberar el slot original del pare
        if (delSlot(slot) != 0) {
            print_msg("ERROR: Pare no pot alliberar slot original\n");
        } else {
            print_msg("Pare: Slot original alliberat OK\n");
        }
    }
}

void test_fork_heap2() {
    print_msg("\n=== TEST: Fork i copia del heap ===\n");

    //Reservar un slot abans del fork
    char *slot = getSlot(8192); // 2 pàgines
    if (!slot) {
        print_msg("ERROR: sys_getSlot(8192) fallida abans del fork\n");
        return;
    }
    print_msg("Slot reservat abans del fork, addr=");
    print_hex((unsigned int)slot);
    print_msg("\n");

    int pid = fork();
    if (pid < 0) {
        print_msg("ERROR: sys_fork() fallida\n");
        perror();
        return;
    }

    if (pid == 0) {
        print_msg("Fill: escric al heap...\n");

        slot[0] = 0x22;
        slot[100] = 0x33;

        print_msg("Fill: valors escrits, ara allibero...\n");

        if (delSlot(slot) != 0) {
            print_msg("ERROR: fill no pot alliberar slot!\n");
            perror();
        } else {
            print_msg("Fill: slot alliberat OK\n");
        }

        return;
    } else {
        print_msg("Pare: fork OK, pid=");
        print_hex((unsigned int)pid);
        print_msg("\n");

        int delay = gettime();
        while (gettime() - delay < 2000);

        //Ara el pare escriu als mateixos offsets
        print_msg("Pare: escric al heap (despres del fill)...\n");

        slot[0] = 0xAA;
        slot[100] = 0xBB;

        //Si el fill hagués escrit en el mateix frame,
        //aquests valors estarien corromputs (no són independents)

        if (delSlot(slot) != 0) {
            print_msg("ERROR: pare no pot alliberar el seu slot!\n");
        } else {
            print_msg("Pare: slot alliberat OK\n");
        }
    }
}
void test_fork_heap3() {
    print_msg("\n=== TEST: Fork i copia del heap ===\n");

    //Reservar un slot abans del fork
    char *slot = getSlot(8192); // 2 pàgines
    if (!slot) {
        print_msg("ERROR: sys_getSlot(8192) fallida abans del fork\n");
        return;
    }
    print_msg("Slot reservat abans del fork, addr=");
    print_hex((unsigned int)slot);
    print_msg("\n");

    //Escriure dades al heap del pare
    slot[0] = 'a';
    slot[4095] = 'b'; // al final de la 1a pàgina
    slot[4096] = 'c'; // a la 2a pàgina

    print_msg("Pare: Dades escrites al heap abans del fork\n");
    print_msg("slot[0] = "); print_hex_char(slot[0]); write(1, "\n", 1);
    print_msg("slot[4095] = "); print_hex_char(slot[4095]); write(1, "\n", 1);
    print_msg("slot[4096] = "); print_hex_char(slot[4096]); write(1, "\n", 1);

    // executar fork
    int pid = fork();
    if (pid < 0) {
        print_msg("ERROR: sys_fork() fallida\n");
        perror();
        return;
    }

    if (pid == 0) {
        print_msg("Fill: Verificant heap copiat...\n");

        print_msg("slot[0] = "); print_hex_char(slot[0]); write(1, "\n", 1);
        print_msg("slot[4095] = "); print_hex_char(slot[4095]); write(1, "\n", 1);
        print_msg("slot[4096] = "); print_hex_char(slot[4096]); write(1, "\n", 1);

        if (slot[0] == 'a' && slot[4095] == 'b' && slot[4096] == 'c') {
            print_msg("Fill: OK — El heap ha estat copiat correctament\n");
        } else {
            print_msg("ERROR: Fill veu dades incorrectes al heap (la còpia ha fallat)\n");
        }

        //escriure una dada per verificar que el pare no la rep
        slot[0] = 'h';
        print_msg("Fill: Escric 'h' al slot[0]\n");
        print_msg("slot[0] = "); print_hex_char(slot[0]); write(1, "\n", 1);

        // Intentar alliberar el slot
        if (delSlot(slot) != 0) {
            perror();
            print_msg("ERROR: Fill no pot alliberar slot copiat\n");
        } else {
            print_msg("Fill: Slot copiat alliberat OK\n");
        }
        return;

    } else {
        print_msg("Pare: fork OK, pid=");
        print_hex((unsigned int)pid);
        print_msg("\n");

        print_msg("slot[0] = "); print_hex_char(slot[0]); write(1, "\n", 1);
        print_msg("slot[4095] = "); print_hex_char(slot[4095]); write(1, "\n", 1);
        print_msg("slot[4096] = "); print_hex_char(slot[4096]); write(1, "\n", 1);

        if (slot[0] == 'a' && slot[4095] == 'b' && slot[4096] == 'c') {
            print_msg("Pare: OK — El heap s'ha conservat\n");
        } else {
            print_msg("ERROR: Pare veu dades incorrectes al heap\n");
        }

        // esperar una mica perquè el fill escrigui
        int delay = gettime();
        while (gettime() - delay < 2000);

        print_msg("Pare despres que el fill escrigui:\n");
        print_msg("slot[0] = "); print_hex_char(slot[0]); write(1, "\n", 1);
        print_msg("slot[4095] = "); print_hex_char(slot[4095]); write(1, "\n", 1);
        print_msg("slot[4096] = "); print_hex_char(slot[4096]); write(1, "\n", 1);

        if (slot[0] == 'h') {
            print_msg("ERROR: El pare ha rebut el valor escrit pel fill -> comparteixen pàgina física!!\n");
        } else {
            print_msg("Pare: OK — El pare NO veu l’escriptura del fill (heap independent)\n");
        }
        print_msg("slot[0] = "); print_hex_char(slot[0]); write(1, "\n", 1);

        //Alliberar slot del pare
        if (delSlot(slot) != 0) {
            print_msg("ERROR: Pare no pot alliberar slot original\n");
        } else {
            print_msg("Pare: Slot original alliberat OK\n");
        }
    }
}

void test_forats() {
    print_msg("\n=== TEST: Reutilització parcial de forats a l'espai d'adreces ===\n");

    // 1. Reservar una pàgina
    char *slot1 = getSlot(4096);
    // 2. Reservar dues pàgines
    char *slot2 = getSlot(8192);
    // 3. Reservar una pàgina
    char *slot3 = getSlot(4096);

    if (!slot1 || !slot2 || !slot3) {
        print_msg("ERROR: No s'han pogut reservar els slots inicials\n");
        return;
    }

    print_msg("slot1 (1 pàgina) = "); print_hex((unsigned int)slot1); print_msg("\n");
    print_msg("slot2 (2 pàgines) = "); print_hex((unsigned int)slot2); print_msg("\n");
    print_msg("slot3 (1 pàgina) = "); print_hex((unsigned int)slot3); print_msg("\n");

    // Verificar que estan mapejats
    slot1[0] = 'A';
    slot2[0] = 'B';
    slot3[0] = 'C';

    // 4. Alliberar el slot de dues pàgines → forat de 2 pàgines
    if (delSlot(slot2) != 0) {
        print_msg("ERROR: No s'ha pogut alliberar slot2\n");
        return;
    }
    print_msg("slot2 alliberat: queda un forat de 2 pàgines\n");

    // 5. Reservar una pàgina (ha d'anar dins del forat)
    char *slot4 = getSlot(4096);
    if (!slot4) {
        print_msg("ERROR: No s'ha pogut reservar slot4\n");
        return;
    }

    print_msg("slot4 (1 pàgina) = "); print_hex((unsigned int)slot4); print_msg("\n");

    // Comprovar que slot4 està entre slot1 i slot3
    if (slot4 > slot1 && slot4 < slot3) {
        print_msg("OK: slot4 reutilitza parcialment el forat\n");
    } else {
        print_msg("ERROR: slot4 NO reutilitza el forat esperat\n");
    }

    /*
     * Ara queda un forat d'1 pàgina entre slot4 i slot3
     */
    char *forat = slot4 + 4096;

    // 6. Reservar dues pàgines més
    char *slot5 = getSlot(8192);
    if (!slot5) {
        print_msg("ERROR: No s'ha pogut reservar slot5\n");
        return;
    }

    print_msg("slot5 (2 pàgines) = "); print_hex((unsigned int)slot5); print_msg("\n");

    // Comprovar que slot5 NO ha estat col·locat al forat d'1 pàgina
    if (slot5 >= forat && slot5 < slot3) {
        print_msg("ERROR: slot5 s'ha reservat dins d'un forat massa petit\n");
    } else {
        print_msg("OK: slot5 NO reutilitza el forat d'una sola pàgina\n");
    }

    print_msg("Intentant escriure desde un buffer al heap a slot5:\n");

    slot5="OK\n";
    write(1, slot5, 3);

    print_msg("Intentant accedir al forat restant (1 pàgina) en l'adreça=");
    print_hex((unsigned int)forat);
    print_msg("\n");

    print_msg("L'accés següent HAURIA de provocar un error a write\n");

    int error = write(1, forat, 1);
    if (error < 0) print_msg("S'ha produït correctament error al write, accés denegat");
    else print_msg("ERROR: No s'ha produït error al write\n");
}

void test_slab(){
  write(1, "Test 1, crear slabs de diferent mida i que salti error\n", 55);
  int total_error=0;
  char* slab[20];
  for (int i = 10; i < 30; i++) {
    slab[i - 10] = slab_alloc(i);
    if (!slab[i - 10]) total_error++;
  }
  if (total_error == 4) {
    write(1, "Test 1 PASSED\n", 15);
  }

  //Netejem els slabs creats
  for (int i = 0; i < 20; i++) {
    if (slab[i]) slab_free(slab[i]);
  }

  write(1, "Test 2, omplir una pàgina\n", 28);
  char* slab2 = slab_alloc(256);
  if (!slab2) {
    write(1, "Error Test 2\n", 48);
  }
  char* pointers[18];
  int i = 0;
  while (i < 18) {
    char* p = slab_alloc(256);
    if (!p) {
      write(1, "No es pot assignar més memòria slab\n", 37);
      break;
    }
    pointers[i] = p;
    i++;
  }
  write(1, "Hem colocat tots els blocs slab de 256 bytes\n", 39);
  //Netejem els slabs creats
  for (int j = 0; j < i; j++)
    slab_free(pointers[j]);

  write (1, "Test 2 PASSED\n", 15);
  write(1, "Test 3, crida amb parametres invàlids\n", 39);
  char* err1 = slab_alloc(0);
  if (!err1) write(1, "Parametre 0 OK\n", 16);
  char* err2 = slab_alloc(5000);
  if (!err2) write(1, "Parametre 5000 OK\n", 19);
  write(1, "Si hi ha 2 errors, Test 3 PASSED\n", 36);  

  write(1, "Test 4, Reutilització de slots de cache\n", 41);
  char* s4 = slab_alloc(123);
  if (s4) {
    write(1, "Test 4 PASSED: Cache reutilitzada correctament\n", 47);
    slab_free(s4);
  } else {
    write(1, "Test 4 FAILED: No s'ha pogut reutilitzar la cache\n", 50);
  }

   write(1, "Test 5, Reutilització de slots\n", 34);
  char* a = slab_alloc(128);
  char* b = slab_alloc(128);
  char* c = slab_alloc(128);
  
  // Guardem l'adreça de 'b'
  unsigned int addr_b = (unsigned int)b;
  slab_free(b);
  char* d = slab_alloc(128);
  if ((unsigned int)d == addr_b) write(1, "Test 5 PASSED\n", 14);
  slab_free(a);
  slab_free(c);
  slab_free(d);

  write(1, "Test 6, Mides molt petites\n",27);
  char* s5_1 = slab_alloc(1);
  write(1, "Test 6 PASSED\n", 14);

}

int __attribute__ ((__section__(".text.main")))
  main(void)
  {
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

    //test_pollEvent();
    //test_ansi();
    //test_thread();
    //test_sems();
    //test_heap_slot();
    //test_fork_heap1();
    //test_fork_heap2();
    //test_fork_heap3();
    //test_forats();
    test_slab();

    //joc();

    while(1) { }
}
