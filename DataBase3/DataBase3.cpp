#include "pch.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
static int ID = 1;


class Data_
{
	int year;
	int month;
	int day;
public:
	Data_()
	{}
	Data_(int y, int m, int d) :year(y), month(m), day(d)
	{}
	void getdata() {
		cout << "Введите год рождения: "; cin >> year;
		cout << "Введите месяц рождения: "; cin >> month;
		cout << "Введите день рождения: "; cin >> day;
	}
	void showdata() {
		cout << setw(2) << setiosflags(ios::left) << day
			<< "." << setw(2) << setiosflags(ios::left) << month
			<< "." << setw(4) << setiosflags(ios::left) << year;
	}
	void adddata(int y, int m, int d) {
		year = y; month = m; day = d;
	}
};
class man
{
public:
	int id;
	char* password;
	man* next;
	char* name;
	char* surname;
	Data_ data_of_birthday;
	long double money;

	man()
	{}
	~man()
	{
		delete[] password;
		delete next;
		delete[] name;
		delete[] surname;
	}
	void init_name(const char* name_) {
		int l = strlen(name_);
		name = new char[l + 1];
		strcpy_s(name, l + 1, name_);
	}
	void init_surname(const char* surname_) {
		int l = strlen(surname_);
		surname = new char[l + 1];
		strcpy_s(surname, l + 1, surname_);
	}
	void init_password(const char* pass) {
		int l = strlen(pass);
		password = new char[l + 1];
		strcpy_s(password, l + 1, pass);
	}
	void init_data(int y, int m, int d) {
		data_of_birthday.adddata(y, m, d);
	}
	char *return_pass() {
		return password;
	}
};
class manlist
{
	man* first;
public:
	manlist()
	{
		first = NULL;
	}
	~manlist() {
		man* current = first;
		man* temp;
		while (current) {
			temp = current;
			current = current->next;
			delete[] temp->name;
			delete[] temp->surname;
			delete[] temp->password;
		}
	}
	void addman(const char* name_, const char* surname_, int year, int month, int day, const char* pass , long double money_) {
		man* newman = new man;                    //создаем указатель на man
		newman->id = ID; ID++;
		newman->init_name(name_);
		newman->init_surname(surname_);
		newman->init_password(pass);
		newman->init_data(year, month, day);
		newman->money = money_;

		newman->next = first;
		first = newman;
	}
	void getman() {
		man* newman = new man;
		newman->id = ID; ID++;
		char name[20], surname[20], pass[20];
		cout << "Введите имя: "; cin >> name;
		newman->init_name(name);
		cout << "Введите фамилию: "; cin >> surname;
		newman->init_surname(surname);
		newman->data_of_birthday.getdata();
		cout << "Введите новый пароль: "; cin >> pass;
		newman->init_password(pass);
		cout << "Регистрация прошла успешно.\nВаш ID - " << newman->id << endl;
		newman->money = 10;
		cout << "Ваш баланс - " << newman->money << " BTC\n\n";
		newman->next = first;
		first = newman;
	}
	void delete_man(int my_id) {
		char ch; bool end = true;
		man* current = first, *current_ = first;
		cout << "Подтвердить? (д или н): "; cin >> ch;
		if (ch == 'д') {
			do {
				if (my_id == current->id) { //сначала находим объект который хотим удалить
					end = false;
					break;
				}
				else {
					current = current->next;
				}

			} while (end != false);

			while (current_->next != current){
				current_ = current_->next;
			}
			current_->next = current->next;
			current->next = NULL;
		}
		else {
			exit(1);
		}
	}  
	void display_all() {
		for (int i = 0; i < 45; i++) { //верхний ряд
			cout << "-";
		}
		cout << "\n " << "Имя            " << " " << "Фамилия            " << " "
			<< "ID   \n";
		for (int i = 0; i < 45; i++) { //нижний ряд
			cout << "-";
		}

		man* current = first;
		while (current) {
			cout << "\n " << setw(15) << setiosflags(ios::left) << current->name
				<< " " << setw(20) << setiosflags(ios::left) << current->surname;
			cout <<setw(5) << setiosflags(ios::left) << current->id;
			current = current->next;
		}
		cout << endl << endl;
	}
	void display_my_balance(int my_id) {
		man* current = first;
		bool end = true;

		while (end) {
			if (current == NULL) {
				cout << "Ошибка ID!\n";
				_exit(1);
			}
			if (my_id == current->id)
				end = false;
			else {
				current = current->next;
			}
		}
		cout << "Мой баланс: " << current->money <<" BTC"<< endl << endl;
	}
	void display_one(int id_) {
		man* current = first;
		bool end = true;

		while (end) {
			if (current == NULL) {
				cout << "Ошибка ID!\n";
				_exit(1);
			}
			if (id_ == current->id)
				end = false;
			else {
				current = current->next;
				
			}
		}

		cout << endl << endl;
		for (int i = 0; i < 68; i++) { //верхний ряд
			cout << "-";
		}
		cout << "\n " << "Имя            " << " " << "Фамилия            " << " " << "Дата рождения  "
			<< "ID   " << "Баланс      \n";
		for (int i = 0; i < 68; i++) { //нижний ряд
			cout << "-";
		}
		cout << "\n " << setw(15) << setiosflags(ios::left) << current->name
			<< " " << setw(20) << setiosflags(ios::left) << current->surname;
		current->data_of_birthday.showdata();
		cout << "     " << setw(5) << setiosflags(ios::left) << current->id;
		cout << setw(10) << setiosflags(ios::left) << current->money;
		cout << endl << endl;
	}
	void transaction(int my_id_ , int your_id_) {
		long double sum;
		
		bool end = true;
		man *current = first, *current2 = first;
		while (end) {
			if (current == NULL) {
				cout << "Ошибка Вашего ID!\n";
				_exit(1);
			}
			if (my_id_ == current->id)
				end = false;
			else {
				current = current->next;

			}
		}
		end = true;
		while (end) {
			if (current2 == NULL) {
				cout << "Ошибка чужого ID!\n";
				_exit(1);
			}
			if (your_id_ == current2->id)
				end = false;
			else {
				current2 = current2->next;
			}
		}
		bool end_do;
		do {
			cout << "Ваш баланс: " << current->money;
			cout << "\nВведите сумму которую хотите отправить: "; cin >> sum;
			if (sum <= 0) {
				cout << "Некоректная сумма!\n";
				end_do = true;
			}
			else if (sum > current->money) {
				cout << "Введенная сумма превышает ваш баланс!";
				end_do = true;
			}
			else if (sum <= current->money) {
				current2->money += sum;
				current->money -= sum;
				cout << "На счет пользователя " << current2->name << " " << current2->surname << "\nПереведено "
					<< sum << " BTC\n";
				cout << "Ваш баланс: " << current->money << endl;
				end_do = false;
			}
			else if (sum == 0) {
				cout << "Ваш баланс: " << current->money << endl;
				end_do = false;

			}
		} while (end_do != false);
		cout << endl;
	}
	void login() {
		int my_id; char pass[21]; char ch;
		bool end = true, END = true;
		man *current = first;
		do {
			cout << "Введите свой ID: "; cin >> my_id;
			if (my_id > ID) {
				cout << "Ошибка! Несуществующий ID!\n";
				end = true;
			}
			else
				end = false;
		} while (end != false);

		do {
			if (my_id == current->id) {
					cout << "Введите пароль: "; cin >> pass;
					if (*pass == *(current->return_pass())) {
						cout << "Вход прошел успешно!\n\n";
						end = false;
					}
					else {
						cout << "Неверный пароль!\n";
						end = true;
					}
			} 
			else {
				end = true;
				current = current->next;
				if (current == NULL) {
					cout << "Несуществующий ID!\n\n";
					end = false;
					END = false;
				}
			}
		}while (end != false);
		if (END == false) {

		}
		else {
			do {
				cout << "Личная информация(1)\nИзменить данные(2)\nПеревести деньги(3)\nМой баланс(4)\n"
					<< "Показать список всех пользователей(5)\nУдалить учетную запись(6)\nВыход(7): "; cin >> ch;
				if (ch == '7') {
					end = false;
				}
				if (ch == '6') {
					end = true;
					delete_man(my_id);
					end = false;
				}
				else if (ch == '5') {
					display_all();
					end = true;
				}
				else if (ch == '4') {
					display_my_balance(my_id);
					end = true;
				}
				else if (ch == '3') {
					int your_id;
					display_all();
					cout << "\nВведите ID получателя: "; cin >> your_id;
					transaction(my_id, your_id);
					end = true;
				}
				else if (ch == '2') {
					cout << "Изменить дату рождения(1)\nИзменить пароль(2):"; cin >> ch;
					if (ch == '1') {
						end = true;
						change_data_of_birthday(my_id);
					}
					else if (ch == '2') {
						end = true;
						change_password(my_id);
					}
				}
				else if (ch == '1') {
					display_one(my_id);
					end = true;
				}
			} while (end != false);
			cout << endl;
		}
	}
	void object_search(int my_id, man* &current_) {
		man* current = first; bool end = true;
		
		do {
			if (my_id == current->id) {
				current_ = current;
			}
			else {
				current = current->next;
			}
		} while (end != false);
	}
	void change_data_of_birthday(int my_id) {
		man* current = first; bool end = true;
		
		do {
			if (my_id == current->id) { //сначала находим объект который хотим удалить
				end = false;
				break;
			}
			else {
				current = current->next;
			}

		} while (end != false);
		current->data_of_birthday.getdata();
		cout << endl;
	}
	void change_password(int my_id) {
		man* current = first; bool end = true;
		char pass[21];
		do {
			if (my_id == current->id) { //сначала находим объект который хотим удалить
				end = false;
				break;
			}
			else {
				current = current->next;
			}

		} while (end != false);
		cout << "Введите новый пароль: "; cin >> pass;
		current->init_password(pass);
		cout << endl;
	}
};



int main() {
	setlocale(LC_ALL, "Russian");
	system("chcp 1251 >> null");
	manlist m1;
	m1.addman("Иван" , "Бакаев" , 2003 , 07 , 07 , "07072003" , 10000);
	m1.addman("Лука", "Бакаев", 2006, 6, 8, "68", 0);
	m1.addman("Наталия", "Бакаева", 2005, 4, 9, "49" , 0);
	m1.addman("Николай", "Бакаев", 2009, 8, 18, "818", 0);
	m1.addman("Vasiliy", "Bakaev", 2015, 4, 25, "425", 0);
	m1.addman("Ivan", "Bakaev", 2000, 13, 9, "0707" , 1000);

	int id_;
	char ch;
	bool end_do = true, a;
	do {
		cout << "Войти в систеу(1)\nСоздать учетную запись(2)\nПоказать список Зарегестрированых(3)\nВыход(4): "; cin >> ch;
		if (ch == '4')
			end_do = false;
		else if (ch == '2')
			m1.getman();
		else if (ch == '3')
			m1.display_all();
		else if (ch == '1')
			m1.login();
	} while (end_do != false);
	
	cout << "\n\n\n\n\n\n";
	return 0;
}
