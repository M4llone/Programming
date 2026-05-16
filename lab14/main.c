#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Game
{
    char name[128];
    char genre[128];
    int release;
    float rating;
} Game;

typedef struct Node {
    Game *game;
    struct Node *next;  
    struct Node *prev;  
    struct Node *down;  
} Node;


Game *CreateGame(char *name, char *genre, int release, float rating) {
    Game *game = (Game *)malloc(sizeof(Game));
    strcpy(game->name, name);
    strcpy(game->genre, genre);
    game->release = release;
    game->rating = rating;
    return game;
}


Node *createNode(Game *game) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->game = game;  
    node->next = NULL;
    node->prev = NULL; 
    node->down = NULL;
    return node;
}


Node* appendBack(Node* head, Game *game)
{
    Node* new_node = createNode(game);

    if (head == NULL) {
        return new_node;
    }

    new_node->next = head;
    head->prev = new_node; 

    return new_node;
}

Node* generateGameList(int n) {
    Game games[] = {{"DOTA2", "MOBA", 2014, 8.9},
                    {"CS GO", "SHOOTER", 2000, 7.8},
                    {"MINECRAFT", "SANDBOX", 2011, 10},
                    {"ROBLOX", "PLATFORM", 2006, 6.7},
                    {"VALORANT", "SHOOTER", 2020, 9.1},
                    {"GENSHIN", "RPG", 2021, 9.9},
                    {"TERRARIA", "SANDBOX", 2001, 5.2}};
    
    Node *head = NULL;
    Node *bottomList = NULL;
    

    for (int i = 0; i < n; i++) {
        int random = rand() % 7;
        Game *game_copy = CreateGame(games[random].name, games[random].genre, 
                                    games[random].release, games[random].rating);
        head = appendBack(head, game_copy);
    }
    

    int random = rand() % 7;
    Game *game_copy = CreateGame(games[random].name, games[random].genre, 
                                games[random].release, games[random].rating);
    bottomList = appendBack(bottomList, game_copy);


    Node* cur = head;
    while (cur != NULL) {
        cur->down = bottomList;
        cur = cur->next;
    }
    
    return head;
}


void printGameList(Node *head, Node* current, int n) {
    Node *cur = head;
    

    while(cur) {
        if (cur == current) {
            printf("[*%s*] -> ", cur->game->name);
        } else {
            printf("%s -> ", cur->game->name);
        }
        cur = cur->next;
    }
    printf("NULL\n");


    printf("\n");


    if (head && head->down) {
        Node* bottom = head->down;
        int k = n;
        while(bottom) {
            if (bottom == current) {
                printf("[*%s*] -> ", bottom->game->name);
            } else {
                printf("%s -> ", bottom->game->name);
            }
            bottom = bottom->next;
        }
        printf("NULL\n");
    }
}


Node* moveRight(Node* current, Node* head) {
    if (current->next) {
        return current->next;
    }
    printf("Достигли конца списка\n");
    return current;
}


Node* moveLeft(Node* head, Node* current) {
    if (current->prev) {
        return current->prev;
    }
    printf("Начало списка\n");
    return current;
}


Node* moveDown(Node* current, Node* head) {
    if (current->down) {
        return current->down;
    }
    printf("Нет нижнего списка\n");
    return current;
}


Node* moveUp(Node* head, Node* current) {
    if (head == current) {
        printf("Верхний список\n");
        return current;
    }
    return head;
}


void printCurrentNode(Node* current) {
    printf("\nТекущий элемент: %s (%s, %d, %.1f)\n", 
           current->game->name, 
           current->game->genre, 
           current->game->release, 
           current->game->rating);
}


void freeGameList(Node* head) {
    if (head == NULL){
        return;
    }
    
    if (head->down != NULL) {
        Node *current = head->down;
        Node *next;
        
        while (current != NULL) {
            next = current->next;
            free(current->game);
            free(current);
            current = next;
        }
    }
    
    
    Node *current = head;
    Node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current->game);
        free(current);
        current = next;
    }
}


int main() {
    srand(time(NULL));

    int n;
    printf("Введите длину верхнего списка (N): ");
    scanf("%d", &n);

    Node *head = generateGameList(n);
    Node *current = head;

    char input;
    do {
        printf("\n=== ТЕКУЩИЙ СПИСОК ===\n");
        printGameList(head, current, n);
        printCurrentNode(current);
        
        scanf(" %c", &input);
        
        switch(input) {
            case 'd':
                current = moveRight(current, head);
                break;
            case 'a':
                current = moveLeft(head, current);  
                break;
            case 'w':
                current = moveUp(head, current);
                break;
            case 's':
                current = moveDown(current, head);
                break;
            default:
                printf("Нет такой команды\n");
        }
    } while (input != 'q');

    freeGameList(head);
    return 0;
}