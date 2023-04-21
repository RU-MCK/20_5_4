#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

void fillAtm(int (&atm)[7]) {
  std::srand(std::time(nullptr));
  int banknotes = 0;
  while (banknotes != 1000) {
    int rand1 = ((std::rand() % 5001 + 1000) / 1000) * 1000;
    if (rand1 == 5000) {
      ++atm[1];
      ++banknotes;
    } else if (rand1 == 2000) {
      ++atm[2];
      ++banknotes;
    } else if (rand1 == 1000) {
      ++atm[3];
      ++banknotes;
    }
    int rand2 = ((std::rand() % 501 + 100) / 100) * 100;
    if (rand2 == 500) {
      ++atm[4];
      ++banknotes;
    } else if (rand2 == 200) {
      ++atm[5];
      ++banknotes;
    } else if (rand2 == 100) {
      ++atm[6];
      ++banknotes;
    }
  }
  atm[0] = atm[1] * 5000 + atm[2] * 2000 + atm[3] * 1000
      + atm[4] * 500 + atm[5] * 200 + atm[6] * 100;
  for (int i = 0; (i < 7); ++i) {
    std::cout << atm[i] << " ";
  }
}

void writeFile(std::string &path, int (&arr)[7]) {
  std::ofstream bank(path, std::ios::binary);
  if (!bank.is_open()) {
    std::cout << "Error opening file!";
    return;
  }
  for (int i = 0; (i < 7); ++i) {
    int temp;
    temp = arr[i];
    bank.write((char *) &temp, sizeof(temp));
  }
  bank.close();
}
void readFile(std::string &path, int (&arr)[7]) {
  std::ifstream bank(path, std::ios::binary);
  if (!bank.is_open()) {
    std::cout << "Error opening file!";
    return;
  }
  for (int i = 0; (i < 7); ++i) {
    int number;
    bank.read((char *) &number, sizeof(int));
    arr[i] = number;
  }
  bank.close();
}
int main() {
  int atm[7]{};
  std::string path = "bankomat.bin";
  std::cout << "Enter < + > or < - > " << std::endl;
  char ch;
  std::cin >> ch;
  if (ch != '+' && ch != '-') {
    std::cout << "Enter Error!";
    return 1;
  }
  if (ch == '+') {
    fillAtm(atm);
    writeFile(path, atm);
  }
  if (ch == '-') {
    std::cout << "Enter the required amount: " << std::endl;
    int cash;
    std::cin >> cash;
    if (cash <= 0) {
      std::cout << "Enter Error!";
      return 1;
    }
    readFile(path, atm);
    if (cash > atm[0]) {
      std::cout << "Don`t have money" << std::endl
                << "Try a smaller amount" << std::endl;
      return 1;
    } else {
      int banknote_5000 = 0;
      int banknote_2000 = 0;
      int banknote_1000 = 0;
      int banknote_500 = 0;
      int banknote_200 = 0;
      int banknote_100 = 0;
      if (atm[1] > 0 && cash >= 5000) {
        banknote_5000 = cash / 5000;
        if (banknote_5000 > atm[1]) {
          banknote_5000 = (atm[1] * 5000) / 5000;
          cash -= banknote_5000 * 5000;
          atm[1] = 0;
        } else {
          cash -= banknote_5000 * 5000;
          atm[1] -= banknote_5000;
        }
      }
      if (atm[2] > 0 && cash >= 2000) {
        banknote_2000 = cash / 2000;
        if (banknote_2000 > atm[2]) {
          banknote_2000 = (atm[2] * 2000) / 2000;
          cash -= banknote_2000 * 2000;
          atm[2] = 0;
        } else {
          cash -= banknote_2000 * 2000;
          atm[2] -= banknote_2000;
        }
      }
      if (atm[3] > 0 && cash >= 1000) {
        banknote_1000 = cash / 1000;
        if (banknote_1000 > atm[3]) {
          banknote_1000 = (atm[3] * 1000) / 1000;
          cash -= banknote_1000 * 1000;
          atm[3] = 0;
        } else {
          cash -= banknote_1000 * 1000;
          atm[3] -= banknote_1000;
        }
      }
      if (atm[4] > 0 && cash >= 500) {
        banknote_500 = cash / 500;
        if (banknote_500 > atm[4]) {
          banknote_500 = (atm[4] * 500) / 500;
          cash -= banknote_500 * 500;
          atm[4] = 0;
        } else {
          cash -= banknote_500 * 500;
          atm[4] -= banknote_500;
        }
      }
      if (atm[5] > 0 && cash >= 200) {
        banknote_200 = cash / 200;
        if (banknote_200 > atm[5]) {
          banknote_200 = (atm[5] * 200) / 200;
          cash -= banknote_200 * 200;
          atm[5] = 0;
        } else {
          cash -= banknote_200 * 200;
          atm[5] -= banknote_200;
        }
      }
      if (atm[6] > 0 && cash >= 100) {
        banknote_100 = cash / 100;
        if (banknote_100 > atm[6]) {
          banknote_100 = (atm[6] * 100) / 100;
          cash -= banknote_100 * 100;
          atm[6] = 0;
        } else {
          cash -= banknote_100 * 100;
          atm[6] -= banknote_100;
        }
      }
      atm[0] = atm[1] * 5000 + atm[2] * 2000 + atm[3] * 1000
          + atm[4] * 500 + atm[5] * 200 + atm[6] * 100;
      writeFile(path, atm);
      std::cout << "5 000 - " << banknote_5000 << std::endl
                << "2 000 - " << banknote_2000 << std::endl
                << "1 000 - " << banknote_1000 << std::endl
                << "  500 - " << banknote_500 << std::endl
                << "  200 - " << banknote_200 << std::endl
                << "  100 - " << banknote_100 << std::endl;
    }
  }
  return 0;
}
