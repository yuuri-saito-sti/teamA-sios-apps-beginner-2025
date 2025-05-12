#include <iostream>
#include <vector>
#include <string>      
#include <algorithm>   
#include <stdexcept>   
#include <iomanip>     
#include <cctype>      
#include <cwctype>     
#include <locale>      
#include <sstream>     


struct Item {
    std::wstring name; 
    int price;
    int stock;

    Item(const std::wstring& name_val, int price_val, int stock_val)
        : name(name_val), price(price_val), stock(stock_val) {}
};


std::wstring ConvertToHalfWidth(const std::wstring& input) {
    std::wstring result = input;
    for (wchar_t& wc : result) {
        if (wc >= L'０' && wc <= L'９') { 
            wc = wc - (L'０' - L'0');    
        }
    }
    return result;
}


std::wstring Trim(const std::wstring& str) {
    const std::wstring WHITESPACE = L" \t"; 
    size_t first = str.find_first_not_of(WHITESPACE);
    if (std::wstring::npos == first) {
        return L"";
    }
    size_t last = str.find_last_not_of(WHITESPACE);
    return str.substr(first, last - first + 1);
}


int CalculateTotalAmount(std::vector<Item>& items) {
    int totalAmount = 0;

    while (true) {
        std::wcout << L"\n注文可能な商品一覧:" << std::endl;
        std::wcout << std::left << std::setw(14) << L"商品名"
                   << std::right << std::setw(8) << L"金額"
                   << std::setw(8) << L"在庫" << std::endl;
        std::wcout << L"----------------------------------" << std::endl;
        for (const auto& item : items) {
            if (item.stock > 0) {
                std::wcout << std::left << std::setw(14) << item.name
                           << std::right << std::setw(8) << item.price
                           << std::setw(8) << item.stock << std::endl;
            }
        }
        std::wcout << L"----------------------------------" << std::endl;

        std::wcout << L"\n注文する商品名を入力してください: ";
        std::wstring inputName;
        std::getline(std::wcin, inputName); 
        inputName = Trim(inputName);

        if (inputName.empty()) {
            std::wcout << L"商品名が入力されていません。" << std::endl;
            continue;
        }

        auto it = std::find_if(items.begin(), items.end(), [&](const Item& item) {
            return item.name == inputName;
        });

        if (it == items.end()) {
            std::wcout << L"指定された「" << inputName << L"」は存在しません。" << std::endl;
            continue;
        }
        if (it->stock <= 0) {
            std::wcout << L"「" << it->name << L"」は在庫切れです。" << std::endl;
            continue;
        }

        std::wcout << L"注文数を入力してください（全角数字も可）: ";
        std::wstring inputQuantityStr;
        std::getline(std::wcin, inputQuantityStr); // ワイド入力
        inputQuantityStr = Trim(inputQuantityStr);

        if (inputQuantityStr.empty()) {
            std::wcout << L"注文数が入力されていません。" << std::endl;
            continue;
        }

        std::wstring normalizedQuantityStr = ConvertToHalfWidth(inputQuantityStr);
        int quantity;
        std::wstringstream wss;
        wss << normalizedQuantityStr; 
        if (!(wss >> quantity) || !wss.eof()) { 
        
            std::wstring temp_check_remaining;
            wss.clear(); 
            wss.seekg(0); 
            wss >> quantity; 
            if (wss >> temp_check_remaining && !temp_check_remaining.empty()){ 
                 std::wcout << L"無効な注文数です。数字以外が含まれているか、形式が正しくありません。" << std::endl;
                 continue;
            }
            if (wss.fail() && !wss.eof()){ 
                std::wcout << L"無効な注文数です。数字として解釈できませんでした。" << std::endl;
                continue;
            }

        }
         
        if (quantity <= 0) {
            std::wcout << L"無効な注文数です。1以上の整数を入力してください。" << std::endl;
            continue;
        }

        if (quantity > it->stock) {
            std::wcout << L"在庫が不足しています。「" << it->name << L"」の在庫は残り" << it->stock << L"個です。" << std::endl;
            continue;
        }

        it->stock -= quantity;
        int amount = it->price * quantity;
        totalAmount += amount;

        std::wcout << L"\n注文内容: " << it->name << L" x " << quantity << std::endl;
        std::wcout << L"小計: " << amount << L"円" << std::endl;
        std::wcout << L"現在の合計金額: " << totalAmount << L"円" << std::endl;

        std::wcout << L"\n他に注文はありますか？（はい/いいえ または y/n）: ";
        std::wstring response;
        std::getline(std::wcin, response); 
        response = Trim(response);

        std::wstring lower_response = response;
        std::transform(lower_response.begin(), lower_response.end(), lower_response.begin(),
                       std::towlower); 

        if (response != L"はい" && response != L"いいえ" &&
            lower_response != L"yes" && lower_response != L"no" &&
            lower_response != L"y" && lower_response != L"n") {
            std::wcout << L"無効な入力です。「はい」または「いいえ」（または y/n, yes/no）を入力してください。" << std::endl;
            continue;
        }

        if (response == L"いいえ" || lower_response == L"no" || lower_response == L"n") {
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
    std::wcout << L"最終合計金額は " << totalAmount << L" 円です" << std::endl;

    return 0;
}