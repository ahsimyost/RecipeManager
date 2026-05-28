#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <locale.h> 
#include <algorithm> 

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
    cout << "sort   - отсортировать по калорийности" << endl;
    cout << "bb     - сохранить и выйти" << endl;
    cout << "===============================" << endl;
}

int main() {

    setlocale(LC_ALL, "Russian");
    vector<Recipe> myRecipes;

    // достаем информацию из файлов
    ifstream inFile("recipes.txt");
    string n;
    double c;
    while (inFile >> n >> c) {
        myRecipes.push_back(Recipe(n, c));
    }
    inFile.close();
    cout << "Загружено " << myRecipes.size() << " рецептов." << endl;

    // Вод дневного лимита калл
    double limit = 0;
    cout << "Введите дневной лимит калорий: ";
    cin >> limit;
    if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); limit = 0; }

    while (true) {
        system("cls"); // Очищаем экранчик 
        printMenu();

        string command;
        cout << "\nВведите команду: ";
        cin >> command;

        if (command == "bb") break;

        if (command == "add") {
            string name;
            double cal;
            cout << "Введите название блюда на англ: "; cin >> name;
            cout << "Введите калорийность(цифры!): ";
            if (!(cin >> cal)) {
                cout << "Ошибка: нужно ввести число!" << endl;
                cin.clear(); cin.ignore(10000, '\n');
            }
            else {
                myRecipes.push_back(Recipe(name, cal));
                cout << "Успешно добавлено!" << endl;
            }
            cout << "\nНажмите Enter..."; cin.ignore(); cin.get();
        }
        else if (command == "show") {
            cout << "\nВаши рецепты:" << endl;
            double totalCalories = 0; // Переменная-счетчик

            for (size_t i = 0; i < myRecipes.size(); ++i) {
                cout << i + 1 << ". " << myRecipes[i].name << " — " << myRecipes[i].calories << " ккал" << endl;
                totalCalories += myRecipes[i].calories; // Складываем калории
            }

            cout << "-------------------------------" << endl;
            cout << "Итого калорий: " << totalCalories << "/" << limit << " ккал" << endl;

            if (totalCalories > limit) {
                cout << "Внимание: вы превысили лимит!" << endl;
            }
            else {
                cout << "Осталось до лимита: " << limit - totalCalories << " ккал" << endl;
            }
            cout << "\nНажмите Enter..."; cin.ignore(); cin.get();
        }
        else if (command == "sort") {
            sort(myRecipes.begin(), myRecipes.end(), [](const Recipe& a, const Recipe& b) {
                return a.calories < b.calories;
                });
            cout << "Список отсортирован по возрастанию калорий!" << endl;
            cout << "\nНажмите Enter..."; cin.ignore(); cin.get();
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
            cout << "\nНажмите Enter..."; cin.ignore(); cin.get();
        }
        else {
            cout << "Неизвестная команда. Попробуйте еще раз." << endl;
            cout << "\nНажмите Enter..."; cin.ignore(); cin.get();
        }
    }

    // сохранение рецептов перед выходом
    ofstream outFile("recipes.txt");
    for (const auto& r : myRecipes) {
        outFile << r.name << " " << r.calories << endl;
    }
    outFile.close();
    cout << "Данные сохранены. До свидания!" << endl;

    return 0;
}