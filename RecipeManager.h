#pragma once
class RecipeManager {

private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    PotionRecipe* addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        return &recipes.back();
    }

    // 모든 레시피 출력 메서드
    const std::vector<PotionRecipe>& getAllRecipes() const {
        return recipes;
    }

    PotionRecipe* findRecipeByName(std::string name) {
        auto it = find_if(recipes.begin(), recipes.end(), [&name](const PotionRecipe& recipe) {
            return recipe.potionName.find(name) != std::string::npos;
            });

        if (it != recipes.end()) {
            return &(*it); // 이터레이터 → 포인터 변환
            // *it  = PotionRecipe 객체
            // &*it = 그 객체의 주소 = 포인터
        }
        return nullptr; // 못 찾으면 nullptr
    }
    std::vector<PotionRecipe> findRecipeByIngredient(std::string ingredient) {
        std::vector<PotionRecipe> result; // 결과 담을 벡터

        for (auto& recipe : recipes) {
            // ingredients 목록에서 ingredient 찾기
            auto it = std::find_if(recipe.ingredients.begin(), recipe.ingredients.end(),
                [&ingredient](const std::string& ing) {
                    return ing.find(ingredient) != std::string::npos;
                }
            );

            if (it != recipe.ingredients.end()) {
                result.push_back(recipe); // 있으면 결과에 추가
            }
        }
        return result;
    }
};