#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//Скобочная запись
//Выражение вида (a)O(b) наз элементарной формулой, где a,b из X; O из R;
//Выражение вида (A)O(B) наз формулой, если A,B - формулы или A,B из X; O из R;

//Бесскобочная запись
//Выражение вида Oab наз элементарной формулой, где a,b из X; O из R;
//Выражение вида OAB наз формулой, если A,B - формулы или A,B из X; O из R;

char R[] = {'+', '-', '*', '/'};
char X[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

bool in_R(char c)
{
	bool res = false;
	for (int i = 0; i < 4 && !res; i++)
	{
		if (R[i] == c) res = true;
	}
	return res;
}

bool in_X(char c)
{
	bool res = false;
	for (int i = 0; i < 10 && !res; i++)
	{
		if (X[i] == c) res = true;
	}
	return res;
}

bool is_substring(string word1, string word2) //Проверяет является ли word2 подстрокой word1, если они начинаются с одного символа
{
	if (word2.length() > word1.length()) return false;

	bool res = true;
	int i = 0;
	while (i < word1.length() && i < word2.length() && res)
	{
		if (word1[i] != word2[i]) res = false;
		i++;
	}
	return res;
}

int has_right_combination(string formula, string substr) //Возвращает индекс вхождения подстроки в строку, -1 если не входит
{
	string temp;
	if (substr.length() > formula.length()) return -1;

	for (int i = 0; i < formula.length(); i++)
	{
		if (formula[i] == substr[0])
		{
			temp = "";
			for (int j = i; j < formula.length(); j++)
			{
				temp += formula[j];
			}
			if (is_substring(temp, substr))
			{
				return i;
			}
		}
	}
	return -1;
}

string replace(string word1, string word2, string word3) //Заменяет вхождение word2 в word1 на word3
{
	int ind = has_right_combination(word1, word2);
	if (ind == -1) return word1;
	string new_word = "";
	for (int i = 0; i < ind; i++)
	{
		new_word += word1[i];
	}
	new_word += word3;
	for (int i = ind + word2.length(); i < word1.length(); i++)
	{
		new_word += word1[i];
	}
	return new_word;
}

bool correct_formula_a()
{
	bool is_correct = true;
	/*
	0 - "(", 
	1 - ")", 
	2 - O, in_R()
	3 - a, b, in_X()
	*/
	string formula;
	string new_formula = "";
	cout << "Enter formula: " << endl;
	cin >> formula;
	
	//Строит новую строку на основе старой
	for (int i = 0; i < formula.length() && is_correct; i++) 
	{
		if (formula[i] == '(')
		{
			new_formula += '0';
		}
		else if (formula[i] == ')')
		{
			new_formula += '1';
		}
		else if (in_R(formula[i]))
		{
			new_formula += '2';
		}
		else if (in_X(formula[i]))
		{
			new_formula += '3';
		}
		else
		{
			cout << "Wrong symbol: " << formula[i] << endl;
			is_correct = false;
		}
	}
	
	while (has_right_combination(new_formula, "0312031") != -1)
	{
		new_formula = replace(new_formula, "0312031", "3");
	}
	if (new_formula != "3") is_correct = false;
	return is_correct;
}

bool correct_formula_b()
{
	bool is_correct = true;
	/*
	0 - O, in_R
	1 - a, b, in_X
	*/
	string formula;
	string new_formula = "";
	cout << "Enter formula: " << endl;
	cin >> formula;

	//Строит новую строку на основе старой
	for (int i = 0; i < formula.length() && is_correct; i++)
	{
		if (in_R(formula[i]))
		{
			new_formula += '0';
		}
		else if (in_X(formula[i]))
		{
			new_formula += '1';
		}
		else
		{
			cout << "Wrong symbol: " << formula[i] << endl;
			is_correct = false;
		}
	}

	while (has_right_combination(new_formula, "011") != -1)
	{
		new_formula = replace(new_formula, "011", "1");
	}
	if (new_formula != "1") is_correct = false;
	return is_correct;

}

//string convert_a_to_b(string formula)
//{
//	string elementary_formula;
//	string temp;
//	int ind = has_right_combination(formula, ")");
//	while (ind != -1) //Пока есть скобка
//	{
//		elementary_formula = "";
//		temp = "";
//		if (formula[ind - 2] == '(') //Если в скобках слева от операции элементарная формула в скобочной записи
//		{
//			for (int i = -2; i <= 4; i++) elementary_formula += formula[ind + i];
//			temp += elementary_formula[3];
//			temp += elementary_formula[1];
//			temp += elementary_formula[5];
//		}
//		else //если слева от операции выражение в бесскобочной записи
//		{
//			for (int i = -4; i <= 10; i++) elementary_formula += formula[ind + i];
//			temp += elementary_formula[5];
//			for (int i = 1; i <= 3; i++) temp += elementary_formula[i];
//			for (int i = 7; i <= 13; i++) temp += elementary_formula[i];
//		}
//		formula = replace(formula, elementary_formula, temp);
//		cout << formula << endl;
//		ind = has_right_combination(formula, ")");
//	}
//	return formula;
//}

string convert_a_to_b(string formula)
{
	int is_bracket;
	int open_brackets = 0;
	int close_brackets = 0;
	int first_open_bracket = -1;
	int last_close_bracket = -1;
	int ind = -1;
	string part_with_brackets = "";
	string part_without_brackets = "";
	is_bracket = has_right_combination(formula, "(");
	while (is_bracket != -1)
	{
		open_brackets = 0;
		close_brackets = 0;
		first_open_bracket = -1;
		last_close_bracket = -1;
		ind = -1;

		for (int i = 0; i < formula.length() && first_open_bracket == -1; i++) //Поиск первой открывающей скобки
		{
			if (formula[i] == '(') first_open_bracket = i;
		}

		for (int i = first_open_bracket; i < formula.length() && ind == -1; i++) //Поиск тета
		{
			if (formula[i] == '(') open_brackets++;
			if (formula[i] == ')') close_brackets++;
			if (in_R(formula[i]) && open_brackets == close_brackets) ind = i;
		}

		for (int i = ind; i < formula.length() && last_close_bracket == -1; i++) //Поиск последней закрывающей скобки
		{
			if (formula[i] == '(') open_brackets++;
			if (formula[i] == ')') close_brackets++;
			if (formula[i] == ')' && open_brackets == close_brackets) last_close_bracket = i;
		}

		part_with_brackets = "";
		part_without_brackets = "";

		for (int i = first_open_bracket; i <= last_close_bracket; i++) //Запись части, которую нужно заменить
		{
			part_with_brackets += formula[i];
		}

		ind -= first_open_bracket;
		part_without_brackets += part_with_brackets[ind];
		for (int i = 1; i < part_with_brackets.length() - 1; i++) //Бесскобочная запись
		{
			if (i != ind-1 && i != ind && i != ind+1)
			{
				part_without_brackets += part_with_brackets[i];
			}
		}
		cout << part_with_brackets << endl;
		cout << part_without_brackets << endl;
		formula = replace(formula, part_with_brackets, part_without_brackets);

		is_bracket = has_right_combination(formula, "(");
	}

	return formula;
}

int main()
{
	//cout << correct_formula();
	//cout << correct_formula_b();
	cout << convert_a_to_b("((1)+(2))-((3)+(4))");

}

