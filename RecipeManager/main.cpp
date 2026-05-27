#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Recipe {
public:
    string name;
    double calories;
    Recipe(string n, double c) : name(n), calories(c) {}
};

// простое меню
void printMenu() {
    cout << "\n===============================" << endl;
    cout << "Доступные команды:" << endl;
    cout << "add    - добавить новый рецепт" << endl;
    cout << "del    - удалить рецепт" << endl;
    cout << "show   - показать все рецепты" << endl;
    cout << "bb     - сохранить и выйти" << endl;
    cout << "===============================" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Recipe> myRecipes;

    // достаем информацию  из файлов
    ifstream inFile("recipes.txt");
    string n;
    double c;
    while (inFile >> n >> c) {
        myRecipes.push_back(Recipe(n, c));
    }
    inFile.close();
    cout << "Загружено " << myRecipes.size() << " рецептов." << endl;

    printMenu(); // Показываем подсказку

    while (true) {
        string command;
        cout << "\nВведите команду: ";
        cin >> command;

        if (command == "bb") break;

        if (command == "add") {
            string name;
            double cal;
            cout << "Введите название блюда: "; cin >> name;
            cout << "Введите калорийность: "; cin >> cal;
            myRecipes.push_back(Recipe(name, cal));
            cout << "Успешно добавлено!" << endl;
        }
        else if (command == "show") {
            cout << "\nВаши рецепты:" << endl;
            double totalCalories = 0; // ---счетчик

            for (size_t i = 0; i < myRecipes.size(); ++i) {
                cout << i + 1 << ". " << myRecipes[i].name << " — " << myRecipes[i].calories << " ккал" << endl;
                totalCalories += myRecipes[i].calories; // калькулируем калории
            }

            cout << "-------------------------------" << endl;
            cout << "Итого калорий: " << totalCalories << " ккал" << endl;
        }
        else if (command == "del") {
            cout << "Введите номер рецепта для удаления: ";
            int index;
            cin >> index;
            if (index > 0 && index <= (int)myRecipes.size()) {
                myRecipes.erase(myRecipes.begin() + index - 1);
                cout << "Рецепт удален." << endl;
            }
            else {
                cout << "Ошибка: такого номера нет в списке." << endl;
            }
        }
        else {
            cout << "Неизвестная команда. Попробуйте еще раз." << endl;
            printMenu(); 
        }
    }

    // сохпранение рецептоав перед выходом
    ofstream outFile("recipes.txt");
    for (const auto& r : myRecipes) {
        outFile << r.name << " " << r.calories << endl;
    }
    outFile.close();
    cout << "Данные сохранены. До свидания!" << endl;

    return 0;
}