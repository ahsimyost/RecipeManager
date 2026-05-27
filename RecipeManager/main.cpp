#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
// Класс для хранения данных о блюде 

class Recipe {
public:
    string name;
    double calories;
    Recipe(string n, double c) : name(n), calories(c) {}
};

//конец


int main() {
    setlocale(LC_ALL, "Russian");

    vector<Recipe> myRecipes;
    string name;
    double cal;

    cout << "--- Калькулятор Калорий ---" << endl;
    cout << "\nВведите название блюда (или напишите 'bb' для завершения): ";
    while (true) {
        cin >> name;
        if (name == "bb") break; // bb из цикла

        cout << "Введите калорийность: ";
        cin >> cal;
        myRecipes.push_back(Recipe(name, cal));
        cout << "\nДобавлено! Введите следующее блюдо или 'bbb': ";
    }


    //конец цикла 


    ofstream outFile("recipes.txt");
    for (const auto& r : myRecipes) {
        outFile << r.name << " " << r.calories << endl;
    }
    outFile.close();
    cout << "\nРецепты сохранены в файл recipes.txt!" << endl;

    cout << "\n--- Итоговый список ---" << endl;
    for (const auto& r : myRecipes) {
        cout << r.name << " : " << r.calories << " ккал" << endl;
    }

    return 0;
}
// ПРОВЕРКА ГИТХАБА АЛЛО АЛЛО АЛЛО