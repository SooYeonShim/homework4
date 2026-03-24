#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "PotionRecipe.h"
#include "RecipeManager.h"
#include "StockManager.h"

// AlchemyWorkshop 클래스
class AlchemyWorkshop {
private:
    RecipeManager recipeManager_;
    StockManager stockManager_;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void AddRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipeManager_.addRecipe(name, ingredients);
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
        stockManager_.initializeStock(name); // 기본 포션 3개 

    }

    // 모든 레시피 출력 메서드
    void DisplayAllRecipes() const {
        std::vector<PotionRecipe> recipes = recipeManager_.getAllRecipes();
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i) {
            std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
            std::cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                std::cout << recipes[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].ingredients.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }

    // 재고 조회 (이름)
    int GetStockByName(const std::string& potionName) const
    {
        int n = stockManager_.getStock(potionName);
        std::cout << potionName << " 재고: " << n << "개" << std::endl;
        return n;
    }

    // potionName으로 검색하여 재고 있으면 지급처리하고 true, 재고 없으면 false
    bool DispensePotionByName(const std::string& potionName) 
    {
        if (stockManager_.dispensePotion(potionName))
        {
            std::cout << potionName << " 1개 지급" << std::endl;
            std::cout << potionName << " 재고 : " << stockManager_.getStock(potionName) << std::endl;

            return true;
        }
        else
        {
            std::cout << potionName << " 재고가 없습니다." << std::endl;
            return false;
        }
    };

    // 해당 재료를 포함하는 레시피들 중, 재고 있는 것들을 지급처리
    // 반환: 실제로 지급된 물약 이름 목록(없으면 빈 벡터)
    std::vector<std::string> DispensePotionsByIngredient(const std::string& ingredient)
    {
        std::vector<PotionRecipe> requiredPotions = recipeManager_.findRecipeByIngredient(ingredient);
        std::vector<std::string> dispensedPotions;
        if (!requiredPotions.empty())
        {
            for (int i = 0; i < requiredPotions.size(); i++)
            {
                std::string potionName = requiredPotions[i].potionName;
                if (stockManager_.dispensePotion(potionName))
                {
                    dispensedPotions.push_back(potionName);
                }
             }
        }
        else
        {
            std::cout << "해당하는 물약이 없습니다." << std::endl; 
        }

        return dispensedPotions;
        
    };

    // potionName에 공병을 반환 처리(최대 3개 제한)
    void ReturnPotionByName(const std::string& potionName)
    {
        stockManager_.returnPotion(potionName);
    }

    void searchRecipeByName(std::string name) {
        PotionRecipe* recipe = recipeManager_.findRecipeByName(name);

        if (recipe != nullptr)
        {
            std::cout << "- 물약 이름: " << recipe->potionName << std::endl;
            std::cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipe->ingredients.size(); ++j) {
                std::cout << recipe->ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipe->ingredients.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
            

        }
        else
        {
            std::cout << "해당하는 물약이 없습니다." << std::endl;
        }
    }
    void searchRecipeByIngredient(std::string ingredient) {
        std::vector<PotionRecipe> recipes = recipeManager_.findRecipeByIngredient(ingredient);

        if (!recipes.empty())
        {
            for (int i = 0; i < recipes.size(); ++i)
            {
                std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
                std::cout << "  > 필요 재료: ";

                // 재료 목록을 순회하며 출력
                for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                    std::cout << recipes[i].ingredients[j];
                    // 마지막 재료가 아니면 쉼표로 구분
                    if (j < recipes[i].ingredients.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
            }
        }
        else
        {
            std::cout << "해당하는 물약이 없습니다." << std::endl;
        }
    }
};