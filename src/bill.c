#include <stdio.h>

struct Item {
    char name[10];
    int price;
    int stock;
};

int main() {
    struct Item items[] = {
        {"りんご", 100, 10},
        {"バナナ", 80, 20},
        {"みかん", 50, 15},
        {"お肉", 500, 5},
        {"牛乳", 300, 25},
        {"魚", 400, 30},
    };

    printf("お会計システム作成\n");
    return 0;
}