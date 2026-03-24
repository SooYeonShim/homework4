#pragma once

class StockManager {
public:
    void initializeStock(std::string potionName) {
        potionStock.emplace(potionName, 3);
    }

    bool dispensePotion(std::string potionName) {
        if (potionStock[potionName] > 0)
        {
            --potionStock[potionName];
            return true;
        }
        else {
            return false;
        }
    }


    // 공병 반환
    void returnPotion(std::string potionName) {
        if (potionStock[potionName] < MAX_STOCK)
        {
            std::cout << potionName << " 1병을 돌려받았습니다." << std::endl;
            ++potionStock[potionName];
        }
        else
        {
            std::cout << "재고가 꽉 차서 받을 수 없습니다." << std::endl;
        }
    }

   int getStock(std::string potionName) const {
       auto it = potionStock.find(potionName);
       if (it != potionStock.end()) {
           return it->second;
       }
       else {
           return 0;
       }
    }
private:
    std::map<std::string, int> potionStock;

    // 창고 최대치 제한
    const int MAX_STOCK = 3;

};