#include <iostream>
#include <vector>
#include <string>

struct Item {
    std::string name;
    int price;
    int stock;

    Item(std::string name, int price, int stock) {
        this->name = name;
        this->price = price;
        this->stock = stock;
    }
};

int main() {
    std::vector<Item> items = {
        {"りんご", 100, 10},
        {"バナナ", 80, 20},
        {"みかん", 50, 15},
        {"お肉", 500, 5},
        {"牛乳", 300, 25},
        {"魚", 400, 30}
    };
    std::cout << "お会計システム作成" << std::endl;

    return 0;
}
