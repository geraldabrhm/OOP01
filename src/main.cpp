#include "./MainKrap.hpp"

MainKrap* MainKrap::instance = nullptr;

int main(){
    MainKrap* Game = MainKrap::getInstance();
    string configPath = "..\\config";
    string itemFile = "\\item.txt";
    string recipeFolder = "\\recipe";

    cout << "Selamat datang di dunia MainKrap!!" << endl;
    cout << "MainKrap adalah permainan sederhana berbasis CLI" << endl;
    cout << "Dibuat untuk memenuhi Tugas Besar IF2210 (Pemrograman Berorientasi Objek)" << endl;
    cout << "Credits to : " << endl;
    cout << "13520051 Flavia Beatrix Leoni A. S." << endl;
    cout << "13520099 Vincent Prasetiya Atmadja" << endl; 
    cout << "13520108 Muhammad Rakha Athaya" << endl;
    cout << "13520138 Gerald Abraham Sianturi" << endl;
    cout << "13520159 Atabik Muhammad Azfa Shofi" << endl;
    cout << endl;

    Game->initialize(configPath, itemFile, recipeFolder);
    Game->PLAY();

    return 0;
}