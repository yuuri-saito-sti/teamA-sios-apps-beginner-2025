#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

void pay(int money){
    while(true){
        printf("お会計金額は%d円です。\n", money);
        std::cout << "支払金額を入力してください:";
        int price;
        std::cin >> price;
        printf("お支払い金額は%d円です。\n", price);

        if(price < money){
            printf("お支払い金額が%d円不足しています。\n", money - price);
        } else if(price == money){
            printf("お支払い金額はちょうどです。\n");
            printf("おつりは0円です。\n");
        }else {
            int change = price - money;
            printf("おつりは%d円です。\n", change);

            // お札と硬貨の種類
            std::vector<int> denominations = {10000, 5000, 1000, 500, 100, 50, 10, 5, 1};
            std::vector<int> counts(denominations.size(), 0);

            // おつりを計算
            for (size_t i = 0; i < denominations.size(); ++i) {
                counts[i] = change / denominations[i];
                change %= denominations[i];
            }

            // 結果を出力
            printf("おつりの内訳:\n");
            for (size_t i = 0; i < denominations.size(); ++i) {
                if (counts[i] > 0) {
                    printf("%d円: %d枚\n", denominations[i], counts[i]);
                }
            }
            break; // 正しい金額が入力されたらループを終了
        }
    }
    
}

