#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <iomanip>
#include <locale>
#include <sstream>

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



bool addPointToCard(int totalAmount)
{
    std::cout << "ポイントカードはお持ちですか？(y/n)" << std::endl;
    char hasCard;
    std::cin >> hasCard;
    if (hasCard == 'y')
    {
        std::cout << "ポイントカードを確認しました。" << std::endl;
    }
    else if (hasCard == 'n')
    {
        std::cout << "ポイントカードを作成しますか？(y/n)" << std::endl;
        char willCreateCard;
        std::cin >> willCreateCard;

        if (willCreateCard == 'y')
        {
            std::cout << "ポイントカードを作成します" << std::endl;
            std::cout << "名前を入力してください" << std::endl;
            std::string name;
            std::cin >> name;
            std::cout << "電話番号を入力してください（半角のみ・ハイフンを除く）" << std::endl;
            // TODO:ハイフンあってもなくても読めるようにしたい
            std::string phoneNumber;
            std::cin >> phoneNumber;
            std::cout << "ポイントカードを作成しました。" << std::endl;
        }
        else if (willCreateCard == 'n')
        {
            std::cout << "ポイントカードは作成しませんでした。" << std::endl;
            return true;
        }
        else
        {
            std::cout << "不正な入力です。" << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "不正な入力です。" << std::endl;
        return false;
    }
    std::cout << "ポイントを"<<totalAmount * 0.01 <<"ポイント付与しました。" << std::endl;
    return true;
}

// 商品構造体
struct Item {
    std::wstring name;
    int price;
    int stock;

    Item(const std::wstring& name_val, int price_val, int stock_val)
        : name(name_val), price(price_val), stock(stock_val) {}
};

// 全角数字を半角数字に変換する関数
std::wstring ConvertToHalfWidth(const std::wstring& input) {
    std::wstring result = input;
    for (wchar_t& wc : result) {
        if (wc >= L'０' && wc <= L'９') {
            wc = wc - (L'０' - L'0');
        }
    }
    return result;
}

// 入力をトリムする関数
std::wstring Trim(const std::wstring& str) {
    const std::wstring WHITESPACE = L" \t";
    size_t first = str.find_first_not_of(WHITESPACE);
    if (std::wstring::npos == first) {
        return L"";
    }
    size_t last = str.find_last_not_of(WHITESPACE);
    return str.substr(first, last - first + 1);
}

// 合計金額を計算する関数
int CalculateTotalAmount(std::vector<Item>& items) {
    int totalAmount = 0;

    while (true) {
        // 商品一覧の表示
        std::wcout << L"\n注文可能な商品一覧:" << std::endl;
        std::wcout << std::left << std::setw(6) << L"番号"
                   << std::setw(14) << L"商品名"
                   << std::right << std::setw(8) << L"金額"
                   << std::setw(8) << L"在庫" << std::endl;
        std::wcout << L"-------------------------------------------------------" << std::endl;
        for (size_t i = 0; i < items.size(); ++i) {
            if (items[i].stock > 0) {
                std::wcout << std::left << std::setw(6) << (i + 1)
                           << std::setw(14) << items[i].name
                           << std::right << std::setw(8) << items[i].price
                           << std::setw(8) << items[i].stock << std::endl;
            }
        }
        std::wcout << L"-------------------------------------------------------" << std::endl;

        // 商品番号の入力
        std::wcout << L"\n注文する商品の番号を入力してください: ";
        std::wstring inputNumberStr;
        std::getline(std::wcin, inputNumberStr);
        inputNumberStr = Trim(inputNumberStr);

        if (inputNumberStr.empty()) {
            std::wcout << L"商品番号が入力されていません。" << std::endl;
            continue;
        }

        std::wstring normalizedNumberStr = ConvertToHalfWidth(inputNumberStr);
        int itemIndex;
        try {
            itemIndex = std::stoi(normalizedNumberStr) - 1; // 商品番号をインデックスに変換
        } catch (...) {
            std::wcout << L"無効な商品番号です。数字を入力してください。" << std::endl;
            continue;
        }

        if (itemIndex < 0 || itemIndex >= static_cast<int>(items.size())) {
            std::wcout << L"無効な商品番号です。範囲内の番号を入力してください。" << std::endl;
            continue;
        }

        if (items[itemIndex].stock <= 0) {
            std::wcout << L"「" << items[itemIndex].name << L"」は在庫切れです。" << std::endl;
            continue;
        }

        // 注文数の入力
        std::wcout << L"注文数を入力してください（全角数字も可）: ";
        std::wstring inputQuantityStr;
        std::getline(std::wcin, inputQuantityStr);
        inputQuantityStr = Trim(inputQuantityStr);

        if (inputQuantityStr.empty()) {
            std::wcout << L"注文数が入力されていません。" << std::endl;
            continue;
        }

        std::wstring normalizedQuantityStr = ConvertToHalfWidth(inputQuantityStr);
        int quantity;
        try {
            quantity = std::stoi(normalizedQuantityStr);
        } catch (...) {
            std::wcout << L"無効な注文数です。数字を入力してください。" << std::endl;
            continue;
        }

        if (quantity <= 0) {
            std::wcout << L"無効な注文数です。1以上の整数を入力してください。" << std::endl;
            continue;
        }

        if (quantity > items[itemIndex].stock) {
            std::wcout << L"在庫が不足しています。「" << items[itemIndex].name
                       << L"」の在庫は残り" << items[itemIndex].stock << L"個です。" << std::endl;
            continue;
        }

        // 在庫を更新
        items[itemIndex].stock -= quantity;

        // 合計金額の計算
        int amount = items[itemIndex].price * quantity;
        totalAmount += amount;

        std::wcout << L"\n注文内容: " << items[itemIndex].name << L" x " << quantity << std::endl;
        std::wcout << L"小計: " << amount << L"円" << std::endl;
        std::wcout << L"現在の合計金額: " << totalAmount << L"円" << std::endl;

        // 他に注文があるか確認
        std::wcout << L"\n他に注文はありますか？（y/n）: ";
        std::wstring response;
        std::getline(std::wcin, response);
        response = Trim(response);

        std::wstring lower_response = response;
        std::transform(lower_response.begin(), lower_response.end(), lower_response.begin(),
                       std::towlower);

        if (response != L"yes" && response != L"no" &&
            lower_response != L"ｙｅｓ" && lower_response != L"ｎｏ" &&
            lower_response != L"y" && lower_response != L"n" &&
            lower_response != L"ｙ" && lower_response != L"ｎ") {
            std::wcout << L"無効な入力です。「ｙ」または「ｎ」を入力してください。" << std::endl;
            continue;
        }

        if (response == L"no" || lower_response == L"ｎｏ" || lower_response == L"n" || lower_response == L"ｎ") {
            break;
        }
    }
    return totalAmount;
}

int main() {
    try {
        std::locale::global(std::locale(""));
        std::wcin.imbue(std::locale());
        std::wcout.imbue(std::locale());
    } catch (const std::runtime_error& e) {
        std::cerr << "Locale setting failed: " << e.what() << std::endl;
    }

    std::vector<Item> items = {
        {L"りんご", 100, 10},
        {L"バナナ", 80, 20},
        {L"みかん", 50, 15},
        {L"お肉", 500, 5},
        {L"牛乳", 300, 25},
        {L"魚", 400, 30},
    };

    std::wcout << L"ようこそ！お買い物システムへ。" << std::endl;

    int totalAmount = CalculateTotalAmount(items);

    std::wcout << L"\nご注文ありがとうございました！" << std::endl;
    std::wcout << L"最終合計金額は " << totalAmount << L" 円です。" << std::endl;

    return 0;
}
