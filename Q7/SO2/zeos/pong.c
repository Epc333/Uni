#include <libc.h>

#include "include/libc.h"

#define SCREEN_ROWS 23
#define SCREEN_COLS 80
#define PADDLE_HEIGHT 3
#define LEFT_PADDLE_X 1
#define RIGHT_PADDLE_X (SCREEN_COLS - 2)

#define LOGIC_TICKS 25
#define FPS 10
#define TPF (1000/FPS)

#define AI_DEADZONE 3
#define AI_REACTION_DELAY 3

int ai_tick = 0;

// Pales
struct paddle {
    int y; //punt superior de la pala
};

struct paddle *player;
struct paddle *enemy;

// Bola
struct ball {
    int x, y;
    int dx, dy;
};

struct ball *ball;

enum states {ONGOING, RESET, NEW};

struct status {
    int scoreLeft;
    int scoreRight;
    enum states state;
};

char input;
struct status *status;

void clear_screen(void) {
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
}

void keyboard(void* arg) {
    struct event_t ev;
    struct sem_t *sem_key = (struct sem_t *)arg;
    while(1) {
        int r = pollEvent(&ev);
        if (r > 0 && ev.pressed == 1) {
            char key = 0;
            if (ev.scancode == 0x11) key = 'w';
            else if (ev.scancode == 0x1F) key = 's';
            if (key) {
                semWait(sem_key);
                input = key;
                semSignal(sem_key);
            }
        }
        int delay = gettime();
        while (gettime() - delay < 50);
    }
}

void update_player(struct sem_t * sem) {

    // Llegim la tecla de forma segura (exclusió mútua)
    semWait(sem);
    char key = input;
    input = '\0';
    semSignal(sem);

    // Mou la pala cap amunt
    if (key == 'w') {
        // Evitem que entri a la paret superior (y = 0)
        if (player->y > 1) {
            player->y--;
        }
    }
    // Mou la pala cap avall
    else if (key == 's') {
        // Evitem que entri a la paret inferior (y = 22)
        if (player->y + PADDLE_HEIGHT - 1 < SCREEN_ROWS - 2) {
            player->y++;
        }
    }
}

void update_enemy(void)
{
    // Incrementem el comptador de ticks de la IA
    ai_tick++;

    // La IA només reacciona cada AI_REACTION_DELAY ticks
    if (ai_tick < AI_REACTION_DELAY) {
        return;
    }

    // Reiniciem el comptador
    ai_tick = 0;

    // Calculem el centre de la pala enemiga
    int enemy_center = enemy->y + PADDLE_HEIGHT / 2;

    // Només reaccionem si la bola ve cap a l'enemic
    if (ball->dx > 0) {

        // La bola està per sobre del centre
        if (ball->y < enemy_center - AI_DEADZONE) {

            // Movem cap amunt sense tocar la paret superior
            if (enemy->y > 1) {
                enemy->y--;
            }
        }
        // La bola està per sota del centre
        else if (ball->y > enemy_center + AI_DEADZONE) {
            // Movem cap avall sense tocar la paret inferior
            if (enemy->y + PADDLE_HEIGHT - 1 < SCREEN_ROWS - 2) {
                enemy->y++;
            }
        }
    }
    else {
        // Tornem lentament cap al centre de la zona jugable
        int center_y = (SCREEN_ROWS - 2) / 2 - PADDLE_HEIGHT / 2 + 1;

        if (enemy->y < center_y && enemy->y + PADDLE_HEIGHT - 1 < SCREEN_ROWS - 2) {
            enemy->y++;
        }
        else if (enemy->y > center_y && enemy->y > 1) {
            enemy->y--;
        }
    }
}

void update_ball(void) {
    // Calculem la següent posició de la bola
    int next_x = ball->x + ball->dx;
    int next_y = ball->y + ball->dy;

    // Rebot amb la paret superior (y = 0)
    if (next_y <= 0) {
        next_y = 1;          // Evitem que la bola entri a la paret
        ball->dy = -ball->dy; // Invertim la direcció vertical
    }
    // Rebot amb la paret inferior (y = 22)
    else if (next_y >= SCREEN_ROWS - 1) {
        next_y = SCREEN_ROWS - 2; // y = 21
        ball->dy = -ball->dy;       // Invertim la direcció vertical
    }

    // Col·lisió amb la pala esquerra (jugador)
    if (ball->dx < 0 && next_x == LEFT_PADDLE_X + 1) {
        if (next_y >= player->y &&
            next_y < player->y + PADDLE_HEIGHT) {

            // Invertim la direcció horitzontal
            ball->dx = -ball->dx;
            // Ajustem la direcció vertical segons el punt d'impacte
            int center = player->y + PADDLE_HEIGHT / 2;
            if (next_y < center)
                ball->dy = -1;
            else if (next_y > center)
                ball->dy = 1;
        }
    }

    // Col·lisió amb la pala dreta (enemic)
    if (ball->dx > 0 && next_x == RIGHT_PADDLE_X - 1) {
        if (next_y >= enemy->y &&
            next_y < enemy->y + PADDLE_HEIGHT) {

            // Invertim la direcció horitzontal
            ball->dx = -ball->dx;

            // Ajustem la direcció vertical segons el punt d'impacte
            int center = enemy->y + PADDLE_HEIGHT / 2;
            if (next_y < center)
                ball->dy = -1;
            else if (next_y > center)
                ball->dy = 1;
        }
    }

    // Apliquem el moviment definitiu de la bola
    ball->x += ball->dx;
    ball->y += ball->dy;

    // Gol de l'enemic (la bola surt per l'esquerra)
    if (ball->x < 0) {
        status->scoreRight++;
        status->state = RESET;
    }
    // Gol del jugador (la bola surt per la dreta)
    else if (ball->x >= SCREEN_COLS) {
        status->scoreLeft++;
        status->state = RESET;
    }
}

void logic(void* arg) {

    struct sem_t *sem_key = (struct sem_t *)arg;

    while (1) {
        if(status->state == ONGOING){
            update_player(sem_key);
            update_enemy();
            update_ball();
        }
        else if (status->state == RESET) {
            // Posició inicial de la pala del jugador
            player->y = SCREEN_ROWS / 2 - PADDLE_HEIGHT / 2;

            // Posició inicial de la pala de l'enemic
            enemy->y = SCREEN_ROWS / 2 - PADDLE_HEIGHT / 2;

            // Posició inicial de la bola (centre de la pantalla)
            ball->x = SCREEN_COLS / 2;
            ball->y = SCREEN_ROWS / 2;

            // Direcció inicial de la bola
            // dx: cap a l'esquerra o dreta aleatòriament
            // dy: 0, -1 o 1 aleatoriament
            if (gettime() % 2 == 0) ball->dx = 1;
            else ball->dx = -1;

            int tmod = gettime() % 2;
            if (tmod == 0) ball->dy = -1;
            else if (tmod == 1) ball->dy = 1;

            int delay = gettime();
            while (gettime() - delay < 2000); //2 segons delay

            // Canviem l'estat a ONGOING
            status->state = ONGOING;
        }

        int delay = gettime();
        while (gettime() - delay < LOGIC_TICKS);
    }

}

void draw_match(void) {
    char buffer[16];
    int len;

    write(1, "\x1B[4;7m", 6);

    // ---------------- PARET SUPERIOR (y = 0) ----------------
    // Espai en blanc amb colors per defecte

    write(1, "\x1B[0;0f", 6);
    for (int i = 0; i < SCREEN_COLS; ++i) write(1, " ", 1);

    // ---------------- PARET INFERIOR (y = 22) ----------------

    write(1, "\x1B[0;22f", 7);
    for (int i = 0; i < SCREEN_COLS; ++i) write(1, " ", 1);


    // ---------------- PALA JUGADOR (vermella) ----------------

    write(1, "\x1B[4;1m", 6);
    for (int i = 0; i < PADDLE_HEIGHT; i++) {
        int y = player->y + i;

        len = 0;
        buffer[len++] = '\x1B';
        buffer[len++] = '[';
        buffer[len++] = '0' + LEFT_PADDLE_X;
        buffer[len++] = ';';
        if (y >= 10) buffer[len++] = '0' + y / 10;
        buffer[len++] = '0' + y % 10;
        buffer[len++] = 'f';

        write(1, buffer, len);
        write(1, " ", 1);
    }


    // ---------------- PALA ENEMIC (blava) ----------------
    write(1, "\x1B[4;4m", 6);

    for (int i = 0; i < PADDLE_HEIGHT; i++) {
        int y = enemy->y + i;

        len = 0;
        buffer[len++] = '\x1B';
        buffer[len++] = '[';
        if (RIGHT_PADDLE_X >= 10) buffer[len++] = '0' + RIGHT_PADDLE_X / 10;
        buffer[len++] = '0' + RIGHT_PADDLE_X % 10;
        buffer[len++] = ';';
        if (y >= 10) buffer[len++] = '0' + y / 10;
        buffer[len++] = '0' + y % 10;
        buffer[len++] = 'f';

        write(1, buffer, len);
        write(1, " ", 1);
    }


    // ---------------- BOLA (verd, fons negre) ----------------
    write(1, "\x1B[3;2m", 6); // foreground verd
    write(1, "\x1B[4;0m", 6); // background negre


    len = 0;
    buffer[len++] = '\x1B';
    buffer[len++] = '[';
    if (ball->x >= 10) buffer[len++] = '0' + ball->x / 10;
    buffer[len++] = '0' + ball->x % 10;
    buffer[len++] = ';';
    if (ball->y >= 10) buffer[len++] = '0' + ball->y / 10;
    buffer[len++] = '0' + ball->y % 10;
    buffer[len++] = 'f';

    write(1, buffer, len);
    write(1, "O", 1);



    // ---------------- RESTAUREM COLORS PER DEFECTE ----------------
    // Foreground verd, background negre
    //write(1, "\x1B[3;2m", 6);
    //write(1, "\x1B[4;0m", 6);
}

void draw_score(void) {
    char buff[5];

    // Construïm el text del marcador: "L - R"
    buff[0] = '0' + status->scoreLeft;
    buff[1] = ' ';
    buff[2] = '-';
    buff[3] = ' ';
    buff[4] = '0' + status->scoreRight;

    // Calculem la posició centrada
    // Amplada 80, centre aproximat a la columna 40
    write(1, "\x1B[37;24f", 8);

    // Escrivim el marcador
    write(1, buff, 5);

}

void graphic(void* arg) {
    while (1)  {
        int start = gettime();

        if(status->state == ONGOING || status->state == RESET)
        {
            clear_screen();
            draw_match();
            draw_score();
        }

        while (gettime() - start < TPF); //esperar per assegurar refresc constant
    }
}


void init_status(void) {
    status->state = RESET;
    status->scoreLeft = 0;
    status->scoreRight = 0;
}

void joc()
{
    char* mem = getSlot(4096); 
    if ((int)mem == -1) -1; 

    player = (struct paddle*) mem;
    enemy = (struct paddle*) (mem + sizeof(struct paddle));
    ball = (struct ball*) (mem + 2*sizeof(struct paddle));
    status = (struct status*) (mem + 2*sizeof(struct paddle) + sizeof(struct ball));

    init_status();


    struct sem_t *sem_key = semCreate(1);

    char stacks[3][4096];

    clone(keyboard, (void*)sem_key, stacks[0] + 4096);
    clone(logic, (void*)sem_key, stacks[1] + 4096);
    clone(graphic, (void*)0, stacks[2] + 4096);

    while (1);
}
