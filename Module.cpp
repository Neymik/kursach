#include <windows.h>
#include <iostream>

using namespace std;

inline void Obrabitka(const char*);								//Выполняет основную функцию обрабоки
inline void Animate(char*, int, char, int);						//отвечает за анимацию
inline char* char_add(char*, char, int, int);					//Вставляет символ в массив
inline char* char_del(char*, int, int);							//Удаляет символ из массива
inline char* Velosiped_const_to_ne_const(const char*, int);		//Копирует строку
inline int Velosiped_char_mas_get_str_len(const char*);			//Получает размер строки в символах
inline bool is_number(char);									//Проверяет на число


//Заменить в строке все целые числа соответствующим повторением следующего за ними символа (например "abc5xacb15y" - " abcxxxxxacbyyyyyyyyyyyyyyy ").
void Obrabitka(const char* const_str) {

	char* buffer;
	char next_char;
	char term;

	int letter_number;
	int str_len;
	int i;
	int j;

	str_len = Velosiped_char_mas_get_str_len(const_str);
	term = Velosiped_const_to_ne_const("\0", 1)[0];
	buffer = Velosiped_const_to_ne_const(const_str, str_len);

	Animate(buffer, str_len, term, 0);
	Sleep(2000);

	for (i = 0; i < str_len; i++) {

		if (is_number(buffer[i])) { //Проверка на число

			letter_number = 0;

			while (is_number(buffer[i])) {

				letter_number = letter_number * 10;
				letter_number = letter_number + (int(buffer[i]) - 48);

				str_len--;
				buffer = char_del(buffer, str_len, i);
				Animate(buffer, str_len, term, letter_number);

				next_char = buffer[i];

			}

			if (letter_number == 0) {
				str_len--;
				buffer = char_del(buffer, str_len, i);
				i--;
				Animate(buffer, str_len, term, letter_number);
			}
			else {
				Animate(buffer, str_len, term, letter_number - 1);
			}
			
			

			for (j = 0; j < letter_number - 1; j++) {

				str_len++;
				buffer = char_add(buffer, next_char, str_len, i);
				Animate(buffer, str_len, term, letter_number - j - 2);

			}

			str_len++;

		}
	}
}

bool is_number(char num) {

	if (int(num) >= 48 && int(num) <= 57) {
		return true;
	}

	return false;

}

void Animate(char* buffer, int str_len, char term, int sec_data) {

	buffer[str_len-1] = term;

	system("cls");
	cout << buffer << endl << sec_data;
	Sleep(500);

}

char* char_add(char* str, char char_to_add, int str_len, int add_point) {

	char* re_str = new char[str_len];

	for (int i = 0, i2 = 0; i < str_len; i++, i2++) {

		if (i == add_point) {
			re_str[i] = char_to_add;
			i++;
		}

		re_str[i] = str[i2];

	}

	delete[] str;

	return re_str;

}

char* char_del(char* str, int str_len, int del_point) {

	char* re_str = new char[str_len];

	for (int i = 0, i2 = 0; i < str_len; i++, i2++) {

		if (i == del_point) {
			i2++;
		}

		re_str[i] = str[i2];

	}

	delete[] str;

	return re_str;

}

char* Velosiped_const_to_ne_const(const char* const_str, const int len) {

	char* ne_const_str = new char[len];

	for (int i = 0; i < len; i++) {

		ne_const_str[i] = const_str[i];

	}

	return ne_const_str;

}

int Velosiped_char_mas_get_str_len(const char* str) {

	int i = 0;

	while (str[i] != '\0') {
		i++;
	}

	return i + 1;

}
