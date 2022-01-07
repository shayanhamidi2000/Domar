#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#pragma warning(disable:4996)

//colors
#define RED 12
#define BLUE 3
#define GREEN 10
#define YELLOW 14
#define GRAY 8
#define PINK 13
#define WHITE 15
#define WAIT_TIME_MILI_SEC 100
//directions
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
// some_specifications
#define BOARD_SIZE 30
#define INITIAL_SNAKE_LENGTH 3
#define MINIMUM_SNAKE_LENGTH 2
#define MAX_LEN_SNAKES 30
#define NUMBER_OF_MOUSES 20
//board_characters
#define EMPTY '0'
#define MOUSE 'm'
#define PLAYER1_SNAKE_HEAD '1'
#define PLAYER2_SNAKE_HEAD '2'
#define PLAYER1_SNAKE_BODY 'a'
#define PLAYER2_SNAKE_BODY 'b'
//Bernard, Poison and golden star
#define BERNARD_CLOCK 'c' //on the board character
#define GOLDEN_STAR '*' //on the board character
#define POISON 'x' //on the board character
#define NUMBER_OF_POISONS 5
#define NUMBER_OF_GOLDEN_STARS 3
#define BERNARD_CLOCK_APPEARANCE_CHANCE_PERCENT 20
#define BERNARD_CLOCK_APPEARANCE_CHECK_PERIOD_MILI_SEC 2000
#define BERNARD_CLOCK_FROZEN_TIME_MILI_SEC 4000
// events
#define NO_EVENT 0
#define PLAYER1_WON 1
#define PLAYER2_WON 2
#define DRAW 3
#define PLAYER_FROZE 4
//frozen_player
#define NO_ONE 0
#define PLAYER_ONE 1
#define PLAYER_TWO 2

// prototypes
    //Given functions
    void init_screen();
    void reset_console();
    void hidecursor(HANDLE consoleHandle);
    void set_console_font_and_font_size(HANDLE consoleHandle);
    void set_full_screen_mode(HANDLE consoleHandle);
    void wait_and_get_direction(int* player1_snake_direction, int* player2_snake_direction);
    //Drawings
    void draw_horizonatal_walls();
    void draw_point(char point_content);
    void draw_board(char board_content[BOARD_SIZE][BOARD_SIZE]);
    
     //Utility functions
    void finish_game(int result);
    int go_up(int row);
    int go_down(int row);
    int go_right(int column);
    int go_left(int column);
    void clean_snake_on_the_board(char board_content[BOARD_SIZE][BOARD_SIZE], int snake_position[MAX_LEN_SNAKES][2], int snake_length);
    int generate_new_point_in_bound_of_the_board();
    int generate_random_percent();
    void generate_a_new_mouse(char board_content[BOARD_SIZE][BOARD_SIZE]);
    void generate_a_new_golden_star(char board_content[BOARD_SIZE][BOARD_SIZE]);
    void generate_a_new_poison(char board_content[BOARD_SIZE][BOARD_SIZE]);
    int try_to_generate_bernard_clock(char board_content[BOARD_SIZE][BOARD_SIZE]);
    void put_player_one_snake_at_the_position(char board_content[BOARD_SIZE][BOARD_SIZE], int player1_snake_position[MAX_LEN_SNAKES][2], int player1_snake_length);
    void put_player_two_snake_at_the_position(char board_content[BOARD_SIZE][BOARD_SIZE], int player2_snake_position[MAX_LEN_SNAKES][2], int player2_snake_length);
    void put_mouses_on_the_initial_board(char board_content[BOARD_SIZE][BOARD_SIZE]);
    void put_golden_stars_on_the_initial_board(char board_content[BOARD_SIZE][BOARD_SIZE]);
    void put_poisons_on_the_initial_board(char board_content[BOARD_SIZE][BOARD_SIZE]);
    
    //Initializations
    void initialize_board(char board_content[BOARD_SIZE][BOARD_SIZE]);
    void initialize_player1_snake_position(int player1_snake_position[MAX_LEN_SNAKES][2], char board_content[BOARD_SIZE][BOARD_SIZE]);
    void initialize_player2_snake_position(int player2_snake_position[MAX_LEN_SNAKES][2], char board_content[BOARD_SIZE][BOARD_SIZE]);
    void initialize_board_content(char board_content[BOARD_SIZE][BOARD_SIZE]);

    //Player one functions
    void move_player1_snake(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], 
        int snake_position[MAX_LEN_SNAKES][2], int snake_length);
    void move_player1_snake_after_eating_a_mouse(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], 
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length);
    void make_player1_snake_longer_one_house(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], 
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length);
    void make_player1_snake_shorter_one_house(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2],
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length);
    void make_player2_snake_shorter_one_house_by_player1(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2],
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length);
    int manage_player1_facing_new_house(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2],
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length);
    int manage_player1_snake_movement(char board_content[BOARD_SIZE][BOARD_SIZE], int snake_direction,
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length);
    
    //Player two functions
    void move_player2_snake(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], 
        int snake_position[MAX_LEN_SNAKES][2], int snake_length);
    void move_player2_snake_after_eating_a_mouse(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], 
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length);
    void make_player2_snake_longer_one_house(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], 
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length);
    void make_player2_snake_shorter_one_house(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], 
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length);
    void make_player1_snake_shorter_one_house_by_player2(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2],
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length);
    int manage_player2_facing_new_house(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2],
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length);
    int manage_player2_snake_movement(char board_content[BOARD_SIZE][BOARD_SIZE], int snake_direction,
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length);
    
    //Bernard Clock
    void check_bernard(char board_content[BOARD_SIZE][BOARD_SIZE], int* bernard_clock_exists,
        DWORD* bernard_check_end_time, int* frozen_player, DWORD* frozen_end_time);
    void freeze_player(int demanded_player_to_be_frozen, int* bernard_clock_exists, DWORD* bernard_check_end_time,
        int* frozen_player, DWORD* frozen_end_time);


CONSOLE_FONT_INFOEX former_cfi;
CONSOLE_CURSOR_INFO former_info;
COORD former_screen_size;

void reset_console() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleDisplayMode(consoleHandle, CONSOLE_WINDOWED_MODE, &former_screen_size);
    SetCurrentConsoleFontEx(consoleHandle, FALSE, &former_cfi);
    SetConsoleCursorInfo(consoleHandle, &former_info);
}

void hidecursor(HANDLE consoleHandle)
{
    GetConsoleCursorInfo(consoleHandle, &former_info);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void set_console_font_and_font_size(HANDLE consoleHandle) {
    former_cfi.cbSize = sizeof(former_cfi);
    GetCurrentConsoleFontEx(consoleHandle, FALSE, &former_cfi);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 24;
    cfi.dwFontSize.Y = 24;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Courier");
    SetCurrentConsoleFontEx(consoleHandle, FALSE, &cfi);
}

void set_full_screen_mode(HANDLE consoleHandle) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    former_screen_size.X = csbi.dwSize.X; former_screen_size.Y = csbi.dwSize.Y;
    COORD coord;
    SetConsoleDisplayMode(consoleHandle, CONSOLE_FULLSCREEN_MODE, &coord);
}

void init_screen()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    set_full_screen_mode(consoleHandle);
    hidecursor(consoleHandle);
    set_console_font_and_font_size(consoleHandle);
    
}

void wait_and_get_direction(int* player1_snake_direction, int* player2_snake_direction) {
    DWORD64 start_time, check_time;
    start_time = GetTickCount64();
    check_time = start_time + WAIT_TIME_MILI_SEC; //GetTickCount returns time in miliseconds
    char key = 0;
    char player1_key_hit = 0; 
    char player2_key_hit = 0;

    while (check_time > GetTickCount64()) {
        if (_kbhit()) {
            key = _getch();
            if (key == 0)
                key = _getch();
            if (key == 'w' || key == 'a' || key == 's' || key == 'd')
                player1_key_hit = key;
            if (key == 'i' || key == 'j' || key == 'k' || key == 'l')
                player2_key_hit = key;
        }
    }

    switch (player1_key_hit) {
        case 'w': if(*player1_snake_direction != DOWN) *player1_snake_direction = UP; break;
        case 'a': if (*player1_snake_direction != RIGHT) *player1_snake_direction = LEFT; break;
        case 's': if (*player1_snake_direction != UP) *player1_snake_direction = DOWN; break;
        case 'd': if (*player1_snake_direction != LEFT) *player1_snake_direction = RIGHT; break;
        default: break;
    }
    
    switch (player2_key_hit) {
        case 'i': if (*player2_snake_direction != DOWN) *player2_snake_direction = UP; break;
        case 'j': if (*player2_snake_direction != RIGHT) *player2_snake_direction = LEFT; break;
        case 'k': if (*player2_snake_direction != UP) *player2_snake_direction = DOWN; break;
        case 'l': if (*player2_snake_direction != LEFT) *player2_snake_direction = RIGHT; break;
        default: break;
    }
}

int generate_new_point_in_bound_of_the_board() {
    return rand() % BOARD_SIZE;
}

int generate_random_percent() {
    return rand() % 100;
}

int try_to_generate_bernard_clock(char board_content[BOARD_SIZE][BOARD_SIZE]) {
    int row, column;
    if (generate_random_percent() < BERNARD_CLOCK_APPEARANCE_CHANCE_PERCENT) {
        do {
            row = generate_new_point_in_bound_of_the_board();
            column = generate_new_point_in_bound_of_the_board();
        } while (board_content[row][column] != EMPTY);
        board_content[row][column] = BERNARD_CLOCK;
        return 1;
    }
    return 0;
}

void generate_a_new_mouse(char board_content[BOARD_SIZE][BOARD_SIZE]) {
    int row, column;
    do {
        row = generate_new_point_in_bound_of_the_board();
        column = generate_new_point_in_bound_of_the_board();
    } while (board_content[row][column] != EMPTY);
    board_content[row][column] = MOUSE;
}

void generate_a_new_golden_star(char board_content[BOARD_SIZE][BOARD_SIZE]) {
    int row, column;
    do {
        row = generate_new_point_in_bound_of_the_board();
        column = generate_new_point_in_bound_of_the_board();
    } while (board_content[row][column] != EMPTY);
    board_content[row][column] = GOLDEN_STAR;
}

void generate_a_new_poison(char board_content[BOARD_SIZE][BOARD_SIZE]) {
    int row, column;
    do {
        row = generate_new_point_in_bound_of_the_board();
        column = generate_new_point_in_bound_of_the_board();
    } while (board_content[row][column] != EMPTY);
    board_content[row][column] = POISON;
}

void put_player_one_snake_at_the_position(char board_content[BOARD_SIZE][BOARD_SIZE], int player1_snake_position[MAX_LEN_SNAKES][2], int player1_snake_length) {
    board_content[player1_snake_position[0][0]][player1_snake_position[0][1]] = PLAYER1_SNAKE_HEAD;
    for (int i = 1; i < player1_snake_length; ++i)
        board_content[player1_snake_position[i][0]][player1_snake_position[i][1]] = PLAYER1_SNAKE_BODY;
}

void put_player_two_snake_at_the_position(char board_content[BOARD_SIZE][BOARD_SIZE], int player2_snake_position[MAX_LEN_SNAKES][2], int player2_snake_length) {
    board_content[player2_snake_position[0][0]][player2_snake_position[0][1]] = PLAYER2_SNAKE_HEAD;
    for (int i = 1; i < player2_snake_length; ++i)
        board_content[player2_snake_position[i][0]][player2_snake_position[i][1]] = PLAYER2_SNAKE_BODY;
}

void put_mouses_on_the_initial_board(char board_content[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < NUMBER_OF_MOUSES; ++i)
        generate_a_new_mouse(board_content);
}

void put_golden_stars_on_the_initial_board(char board_content[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < NUMBER_OF_GOLDEN_STARS; ++i)
        generate_a_new_golden_star(board_content);
}

void put_poisons_on_the_initial_board(char board_content[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < NUMBER_OF_POISONS; ++i)
        generate_a_new_poison(board_content);
}

void initialize_board(char board_content[BOARD_SIZE][BOARD_SIZE]) {
    put_mouses_on_the_initial_board(board_content);
    put_golden_stars_on_the_initial_board(board_content);
    put_poisons_on_the_initial_board(board_content);
}

int go_up(int row) {
    if (row <= 0)
        return BOARD_SIZE - 1;
    return row - 1;
}

int go_down(int row) {
    if (row >= BOARD_SIZE - 1)
        return 0;
    return row + 1;
}

int go_right(int column) {
    if (column >= BOARD_SIZE - 1)
        return 0;
    return column + 1;
}

int go_left(int column) {
    if (column <= 0)
        return BOARD_SIZE - 1;
    return column - 1;
}

void clean_snake_on_the_board(char board_content[BOARD_SIZE][BOARD_SIZE], int snake_position[MAX_LEN_SNAKES][2], int snake_length) {
    for (int i = 0; i < snake_length; ++i)
        board_content[snake_position[i][0]][snake_position[i][1]] = EMPTY;
}

void move_player1_snake(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], int snake_position[MAX_LEN_SNAKES][2], int snake_length) {
    clean_snake_on_the_board(board_content, snake_position, snake_length);
    for (int i = snake_length - 1; i >= 0; i--) {
        if (i == 0) {
            snake_position[0][0] = new_house_position[0];
            snake_position[0][1] = new_house_position[1];
            break;
        }
        snake_position[i][0] = snake_position[i - 1][0];
        snake_position[i][1] = snake_position[i - 1][1];
    }
    put_player_one_snake_at_the_position(board_content, snake_position, snake_length);
}

void move_player1_snake_after_eating_a_mouse(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], int snake_position[MAX_LEN_SNAKES][2], int* snake_length) {
    clean_snake_on_the_board(board_content, snake_position, *snake_length);
    snake_position[*snake_length][0] = snake_position[*snake_length - 1][0];
    snake_position[*snake_length][1] = snake_position[*snake_length - 1][1];
    for (int i = *snake_length - 1; i >= 0; i--) {
        if (i == 0) {
            snake_position[0][0] = new_house_position[0];
            snake_position[0][1] = new_house_position[1];
            break;
        }
        snake_position[i][0] = snake_position[i - 1][0];
        snake_position[i][1] = snake_position[i - 1][1];
    }
    *snake_length = *snake_length + 1;
    put_player_one_snake_at_the_position(board_content, snake_position, *snake_length);
}

void make_player1_snake_longer_one_house(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], int snake_position[MAX_LEN_SNAKES][2], int* snake_length) {
    if (*snake_length < MAX_LEN_SNAKES)
        move_player1_snake_after_eating_a_mouse(board_content, new_house_position, snake_position, snake_length);
    else
        move_player1_snake(board_content, new_house_position, snake_position, *snake_length);
    generate_a_new_mouse(board_content);
}

void make_player1_snake_shorter_one_house(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], int snake_position[MAX_LEN_SNAKES][2], int* snake_length) {
    board_content[snake_position[*snake_length - 1][0]][snake_position[*snake_length - 1][1]] = EMPTY;
    *snake_length = *snake_length - 1;
    move_player1_snake(board_content, new_house_position, snake_position, *snake_length);
    generate_a_new_poison(board_content);
}

void make_player2_snake_shorter_one_house_by_player1(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2],
    int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length) {

    board_content[other_snake_position[*other_snake_length - 1][0]][other_snake_position[*other_snake_length - 1][1]] = EMPTY;
    *other_snake_length = *other_snake_length - 1;
    move_player1_snake(board_content, new_house_position, snake_position, *snake_length);
    generate_a_new_golden_star(board_content);
}

int manage_player1_facing_new_house(char board_content[BOARD_SIZE][BOARD_SIZE] ,int new_house_position[2], 
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length) {
    
    switch (board_content[new_house_position[0]][new_house_position[1]])
    {
    case GOLDEN_STAR:
        if (*other_snake_length == MINIMUM_SNAKE_LENGTH) return PLAYER1_WON;
        make_player2_snake_shorter_one_house_by_player1(board_content, new_house_position, snake_position, snake_length, other_snake_position, other_snake_length);
        break;
    case PLAYER1_SNAKE_BODY:
        return PLAYER2_WON;
    case PLAYER2_SNAKE_BODY:
        return PLAYER2_WON;
    case PLAYER2_SNAKE_HEAD:
        if (*snake_length > *other_snake_length)
            return PLAYER1_WON;
        else if (*snake_length == *other_snake_length)
            return DRAW;
        else
            return PLAYER2_WON;
    case MOUSE:
        make_player1_snake_longer_one_house(board_content, new_house_position, snake_position, snake_length); 
        break;
    case BERNARD_CLOCK:
        move_player1_snake(board_content, new_house_position, snake_position, *snake_length);
        return PLAYER_FROZE;
    case POISON: 
        if (*snake_length == MINIMUM_SNAKE_LENGTH) return PLAYER2_WON; 
        make_player1_snake_shorter_one_house(board_content, new_house_position, snake_position, snake_length); 
        break;
    case EMPTY:
        move_player1_snake(board_content, new_house_position, snake_position, *snake_length); 
        break;
    default: break;
    }
    return NO_EVENT;
}

int manage_player1_snake_movement(char board_content[BOARD_SIZE][BOARD_SIZE], int snake_direction, 
        int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length) {
    
    int new_house_position[2] = {snake_position[0][0], snake_position[0][1]};
    if (snake_direction == UP)
        new_house_position[0] = go_up(new_house_position[0]);
    if (snake_direction == DOWN)
        new_house_position[0] = go_down(new_house_position[0]);
    if (snake_direction == RIGHT)
        new_house_position[1] = go_right(new_house_position[1]);
    if (snake_direction == LEFT)
        new_house_position[1] = go_left(new_house_position[1]);
    
    return manage_player1_facing_new_house(board_content, new_house_position, snake_position, snake_length, other_snake_position, other_snake_length);
}

void move_player2_snake(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], int snake_position[MAX_LEN_SNAKES][2], int snake_length) {
    clean_snake_on_the_board(board_content, snake_position, snake_length);
    for (int i = snake_length - 1; i >= 0; i--) {
        if (i == 0) {
            snake_position[0][0] = new_house_position[0];
            snake_position[0][1] = new_house_position[1];
            break;
        }
        snake_position[i][0] = snake_position[i - 1][0];
        snake_position[i][1] = snake_position[i - 1][1];
    }
    put_player_two_snake_at_the_position(board_content, snake_position, snake_length);
}

void move_player2_snake_after_eating_a_mouse(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], int snake_position[MAX_LEN_SNAKES][2], int* snake_length) {
    clean_snake_on_the_board(board_content, snake_position, *snake_length);
    snake_position[*snake_length][0] = snake_position[*snake_length - 1][0];
    snake_position[*snake_length][1] = snake_position[*snake_length - 1][1];
    for (int i = *snake_length - 1; i >= 0; i--) {
        if (i == 0) {
            snake_position[0][0] = new_house_position[0];
            snake_position[0][1] = new_house_position[1];
            break;
        }
        snake_position[i][0] = snake_position[i - 1][0];
        snake_position[i][1] = snake_position[i - 1][1];
    }
    *snake_length = *snake_length + 1;
    put_player_two_snake_at_the_position(board_content, snake_position, *snake_length);
}

void make_player2_snake_longer_one_house(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], int snake_position[MAX_LEN_SNAKES][2], int* snake_length) {
    if (*snake_length < MAX_LEN_SNAKES)
        move_player2_snake_after_eating_a_mouse(board_content, new_house_position, snake_position, snake_length);
    else
        move_player2_snake(board_content, new_house_position, snake_position, *snake_length);
    generate_a_new_mouse(board_content);
}

void make_player2_snake_shorter_one_house(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2], int snake_position[MAX_LEN_SNAKES][2], int* snake_length) {
    board_content[snake_position[*snake_length - 1][0]][snake_position[*snake_length - 1][1]] = EMPTY;
    *snake_length = *snake_length - 1;
    move_player2_snake(board_content, new_house_position, snake_position, *snake_length);
    generate_a_new_poison(board_content);
}

void make_player1_snake_shorter_one_house_by_player2(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2],
    int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length) {

    board_content[other_snake_position[*other_snake_length - 1][0]][other_snake_position[*other_snake_length - 1][1]] = EMPTY;
    *other_snake_length = *other_snake_length - 1;
    move_player2_snake(board_content, new_house_position, snake_position, *snake_length);
    generate_a_new_golden_star(board_content);
}

int manage_player2_facing_new_house(char board_content[BOARD_SIZE][BOARD_SIZE], int new_house_position[2],
    int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length) {

    switch (board_content[new_house_position[0]][new_house_position[1]])
    {
    case GOLDEN_STAR:
        if (*other_snake_length == MINIMUM_SNAKE_LENGTH) return PLAYER2_WON;
        make_player1_snake_shorter_one_house_by_player2(board_content, new_house_position, snake_position, snake_length, other_snake_position, other_snake_length);
        break;
    case PLAYER2_SNAKE_BODY:
        return PLAYER1_WON;
    case PLAYER1_SNAKE_BODY:
        return PLAYER1_WON;
    case PLAYER1_SNAKE_HEAD:
        if (*snake_length > *other_snake_length)
            return PLAYER2_WON;
        else if (*snake_length == *other_snake_length)
            return DRAW;
        else
            return PLAYER1_WON;
    case MOUSE:
        make_player2_snake_longer_one_house(board_content, new_house_position, snake_position, snake_length);
        break;
    case BERNARD_CLOCK:
        move_player2_snake(board_content, new_house_position, snake_position, *snake_length);
        return PLAYER_FROZE;
    case POISON:
        if (*snake_length == MINIMUM_SNAKE_LENGTH) return PLAYER1_WON;
        make_player2_snake_shorter_one_house(board_content, new_house_position, snake_position, snake_length);
        break;
    case EMPTY:
        move_player2_snake(board_content, new_house_position, snake_position, *snake_length);
        break;
    default: break;
    }
    return NO_EVENT;
}

int manage_player2_snake_movement(char board_content[BOARD_SIZE][BOARD_SIZE], int snake_direction,
    int snake_position[MAX_LEN_SNAKES][2], int* snake_length, int other_snake_position[MAX_LEN_SNAKES][2], int* other_snake_length) {
    int new_house_position[2] = { snake_position[0][0], snake_position[0][1] };
    if (snake_direction == UP)
        new_house_position[0] = go_up(new_house_position[0]);
    if (snake_direction == DOWN)
        new_house_position[0] = go_down(new_house_position[0]);
    if (snake_direction == RIGHT)
        new_house_position[1] = go_right(new_house_position[1]);
    if (snake_direction == LEFT)
        new_house_position[1] = go_left(new_house_position[1]);

    return manage_player2_facing_new_house(board_content, new_house_position, snake_position, snake_length, other_snake_position, other_snake_length);
}

void draw_point(char point_content) {
    switch (point_content) {
    case PLAYER1_SNAKE_HEAD: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED); printf("@"); break;
    case PLAYER2_SNAKE_HEAD: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);  printf("@"); break;
    case PLAYER1_SNAKE_BODY: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);  printf("o"); break;
    case PLAYER2_SNAKE_BODY: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);  printf("o"); break;
    case MOUSE: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GRAY); printf("m"); break;
    case GOLDEN_STAR: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW); printf("*"); break;
    case POISON: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN); printf("x"); break;
    case BERNARD_CLOCK: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PINK); printf("c"); break;
    default: printf(" ");
    }
}

void draw_horizonatal_walls() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
    for (int i = 0; i < BOARD_SIZE + 2; ++i)
        printf("-");
    printf("\n");
}

void draw_board(char board_content[BOARD_SIZE][BOARD_SIZE]) {
    system("cls");
    draw_horizonatal_walls();
    for (int i = 0; i < BOARD_SIZE; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
        printf("|"); // vertical wall 
        for (int j = 0; j < BOARD_SIZE; j++)
            draw_point(board_content[i][j]);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
        printf("|\n"); // vertical wall
    }
    draw_horizonatal_walls();
}

void initialize_board_content(char board_content[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board_content[i][j] = EMPTY;
}

void initialize_player1_snake_position(int player1_snake_position[MAX_LEN_SNAKES][2], char board_content[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < INITIAL_SNAKE_LENGTH; ++i) {
        player1_snake_position[i][0] = BOARD_SIZE - INITIAL_SNAKE_LENGTH + i;
        player1_snake_position[i][1] = 0;
    }
    put_player_one_snake_at_the_position(board_content, player1_snake_position, INITIAL_SNAKE_LENGTH);
}

void initialize_player2_snake_position(int player2_snake_position[MAX_LEN_SNAKES][2], char board_content[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < INITIAL_SNAKE_LENGTH; ++i) {
        player2_snake_position[i][0] = INITIAL_SNAKE_LENGTH - i - 1;
        player2_snake_position[i][1] = BOARD_SIZE - 1;
    }
    put_player_two_snake_at_the_position(board_content, player2_snake_position, INITIAL_SNAKE_LENGTH);
}

void check_bernard(char board_content[BOARD_SIZE][BOARD_SIZE], int* bernard_clock_exists, 
        DWORD* bernard_check_end_time, int* frozen_player, DWORD* frozen_end_time) {
    if (!*bernard_clock_exists) {
        if (GetTickCount64() > *bernard_check_end_time) {
            if (try_to_generate_bernard_clock(board_content))
                *bernard_clock_exists = 1;
            else
                *bernard_check_end_time = GetTickCount64() + BERNARD_CLOCK_APPEARANCE_CHECK_PERIOD_MILI_SEC;
        }
    }
    if (frozen_player != NO_ONE) {
        if (GetTickCount64() > *frozen_end_time)
            *frozen_player = NO_ONE;
    }
}

void freeze_player(int demanded_player_to_be_frozen, int* bernard_clock_exists, DWORD* bernard_check_end_time,
    int* frozen_player, DWORD* frozen_end_time) {

    *frozen_player = demanded_player_to_be_frozen;
    *bernard_clock_exists = 0;
    *bernard_check_end_time = GetTickCount64() + BERNARD_CLOCK_APPEARANCE_CHECK_PERIOD_MILI_SEC;
    *frozen_end_time = GetTickCount64() + BERNARD_CLOCK_FROZEN_TIME_MILI_SEC;
}

void finish_game(int result) {
    reset_console();
    system("cls");
    if (result == PLAYER1_WON)
        printf("Player 1 has won!\n");
    if (result == PLAYER2_WON)
        printf("Player 2 has won!\n");
    if (result == DRAW)
        printf("The game ended in draw!\n");
}

void main() {
    int result = NO_EVENT;
    int frozen_player = NO_ONE;
    int bernard_clock_exists = 0;
    DWORD bernard_check_end_time, frozen_end_time;
    char board_content[BOARD_SIZE][BOARD_SIZE];
    int player1_snake_position[MAX_LEN_SNAKES][2];
    int player2_snake_position[MAX_LEN_SNAKES][2];
    int player1_snake_length = INITIAL_SNAKE_LENGTH; int player2_snake_length = INITIAL_SNAKE_LENGTH;
    int player1_snake_direction = UP; int player2_snake_direction = DOWN;
    printf("Welcome to the Domar game.\nPlayer One is red and its' control keys are w,s,a,d.\nPlayer Two is blue and its' control keys are i,j,k,l.\nPress Enter to continue...\n");
    char some_key = _getch();
    init_screen();
    initialize_board_content(board_content);
    initialize_player1_snake_position(player1_snake_position, board_content);
    initialize_player2_snake_position(player2_snake_position, board_content);
    initialize_board(board_content);
    bernard_check_end_time = GetTickCount64() + BERNARD_CLOCK_APPEARANCE_CHECK_PERIOD_MILI_SEC;
    while (TRUE) {
        check_bernard(board_content, &bernard_clock_exists, &bernard_check_end_time, &frozen_player, &frozen_end_time);
        draw_board(board_content);
        wait_and_get_direction(&player1_snake_direction, &player2_snake_direction);
        if (frozen_player != PLAYER_ONE &&
            (result = manage_player1_snake_movement(board_content, player1_snake_direction,
                player1_snake_position, &player1_snake_length, player2_snake_position, &player2_snake_length)) != NO_EVENT) {
            if (result == PLAYER_FROZE)
                freeze_player(PLAYER_TWO, &bernard_clock_exists, &bernard_check_end_time, &frozen_player, &frozen_end_time);
            else
                break;
        }
        if (frozen_player != PLAYER_TWO &&
            (result = manage_player2_snake_movement(board_content, player2_snake_direction,
                player2_snake_position, &player2_snake_length, player1_snake_position, &player1_snake_length)) != NO_EVENT) {
            if (result == PLAYER_FROZE)
                freeze_player(PLAYER_ONE, &bernard_clock_exists, &bernard_check_end_time, &frozen_player, &frozen_end_time);
            else
                break;
        }
    }
    finish_game(result);
}