#include <iostream>
#include"AddPointsToCard.h"

bool addPointToCard(int totalAmount)
{
    std::cout << "ポイントカードはお持ちですか？(y/n)" << std::endl;
    char hasCard;
    std::cin >> hasCard;
    if (hasCard == 'y')
    {
    }
    else if (hasCard == 'n')
    {
        std::cout << "ポイントカードはお持ちでないようですね。" << std::endl;
        std::cout << "ポイントカードを作成しますか？(y/n)" << std::endl;
        char willCreateCard;
        std::cin >> willCreateCard;

        if (willCreateCard == 'y')
        {
            std::cout << "ポイントカードを作成します" << std::endl;
            std::cout << "名前を入力してください" << std::endl;
            std::string name;
            std::cin >> name;
            std::cout << "電話番号を入力してください" << std::endl;
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

int main()
{
    addPointToCard(1000);
}   