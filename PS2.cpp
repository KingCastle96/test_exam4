#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients;

    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients) : potionName(name), ingredients(ingredients) {}

    void display() const {
        std::cout << "- 물약 이름: " << potionName << std::endl;
        std::cout << "  > 필요 재료: ";
        for (size_t i = 0; i < ingredients.size(); ++i) {
            std::cout << ingredients[i];
            if (i < ingredients.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
};

class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }
        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (const auto& recipe : recipes) {
            recipe.display();
        }
        std::cout << "---------------------------\n";
    }

    const PotionRecipe* searchRecipeByName(const std::string& name) const {
        for (const auto& recipe : recipes) {
            if (recipe.potionName == name) {
                return &recipe;
            }
        }
        return nullptr;
    }

    std::vector<PotionRecipe> searchRecipesByIngredient(const std::string& ingredient) const {
        std::vector<PotionRecipe> foundRecipes;
        for (const auto& recipe : recipes) {
            if (std::find(recipe.ingredients.begin(), recipe.ingredients.end(), ingredient) != recipe.ingredients.end()) {
                foundRecipes.push_back(recipe);
            }
        }
        return foundRecipes;
    }
};

int main() {
    AlchemyWorkshop myWorkshop;
    while (true) {
                
        std::cout << " 연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 물약 이름으로 검색" << std::endl;
        std::cout << "4. 재료로 레시피 검색" << std::endl;
        std::cout << "5. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;
        system("cls");
        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);
                if (ingredient == "끝") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3) {
            std::string searchName;
            std::cout << "검색할 물약의 이름을 입력하세요: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, searchName);

            const PotionRecipe* foundRecipePtr = myWorkshop.searchRecipeByName(searchName);

            if (foundRecipePtr != nullptr) {
                std::cout << "\n--- [ 검색된 물약 ] ---" << std::endl;
                foundRecipePtr->display();
                std::cout << "---------------------\n";
            }
            else {
                std::cout << ">> '" << searchName << "' 이름의 물약 레시피를 찾을 수 없습니다." << std::endl;
            }

        }
        else if (choice == 4) {
            std::string searchIngredient;
            std::cout << "검색할 재료 이름을 입력하세요: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, searchIngredient);

            std::vector<PotionRecipe> foundRecipes = myWorkshop.searchRecipesByIngredient(searchIngredient);

            if (!foundRecipes.empty()) {
                std::cout << "\n--- [ '" << searchIngredient << "' 재료가 포함된 물약 목록 ] ---" << std::endl;
                for (const auto& recipe : foundRecipes) {
                    recipe.display();
                }
                std::cout << "-----------------------------------------------------\n";
            }
            else {
                std::cout << ">> '" << searchIngredient << "' 재료가 포함된 물약 레시피를 찾을 수 없습니다." << std::endl;
            }

        }
        else if (choice == 5) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "잘못된 선택입니다. 1부터 5 사이의 숫자를 입력하세요." << std::endl;
        }
        
    }
    
    return 0;
}