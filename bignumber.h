#pragma once

#include <vector>
#include <string>

using namespace std;

class BigNumber{
	public:
		BigNumber();
		BigNumber(string);
		string ToStr();
		BigNumber operator + (BigNumber&);
		BigNumber operator - (BigNumber&);
		BigNumber operator * (BigNumber&);

	private:
		/*Type of data*/
		vector <int> number;
		int sign;
		bool min_sign;

		/*functions*/
		BigNumber _Plus(BigNumber);
		BigNumber _Minus(BigNumber);
		BigNumber _Multi(BigNumber);
		BigNumber _Offset(int);
		void _Reverse();
		void _ReverseUp();

};

BigNumber::BigNumber(){
	sign = 1;
	number.resize(1);
	number[0] = 0;
	min_sign = false;
}

BigNumber::BigNumber(string temp){
	int index = 0;
	sign = 1;
	min_sign = false;
	if(temp[0] == '-'){
		sign = -1;
		index = 1;
	}
	else if(temp[0] == '+'){
		index = 1;
	}
	number.resize(temp.length() - index);
	for (int i(0); i < number.size(); i++){
		number[i] = temp[number.size() - i + index - 1] -'0';
	}
}

BigNumber BigNumber::_Plus(BigNumber temp){
	BigNumber res;
	/*if first number != second number*/
	if (number.size() != temp.number.size()){ 
		/*case 1 : if first number > second number*/
		if (number.size() > temp.number.size()){ 
			res.number.resize(number.size());
			for (int i(0); i < res.number.size(); i++){
				if (temp.number.size() - 1 < i){
					res.number[i] = sign * number[i];
					continue;
				}
				res.number[i] = sign * number[i] + temp.number[i] * temp.sign;
			}
		}
		/*case 2 : if first number < second number*/
		else {
			res.number.resize(temp.number.size());
			for (int i(0); i < res.number.size(); i++){
				if (number.size() - 1 < i){
					res.number[i] = sign * temp.number[i];
					continue;
				}
				res.number[i] = sign * number[i] + temp.number[i] * temp.sign;
			}
		}
		min_sign = 1;
	}
	/*if first number == second number*/
	else {
		res.number.resize(number.size());
		for (int i(0); i < res.number.size(); i++){
			res.number[i] = sign * number[i] + temp.number[i] * temp.sign;
		}
	}
	return res;
}

BigNumber BigNumber::_Minus(BigNumber temp){
	BigNumber res;
	/*if first number != second number*/
	if (number.size() != temp.number.size()){
		/*case 1 : if first number > second number*/
		if (number.size() > temp.number.size()){
			res.number.resize(number.size());
			for (int i(0); i < res.number.size(); i++){
				if (temp.number.size() - 1 < i){
					res.number[i] = sign * number[i];
					continue;
				}
				res.number[i] = sign * number[i] - temp.number[i] * temp.sign;
			}
		}
		/*case 2 : if first number < second number*/
		else {
			res.number.resize(temp.number.size());
			for (int i(0); i < res.number.size(); i++){
				if (number.size() - 1 < i){
					res.number[i] = sign * temp.number[i];
					continue;
				}
				res.number[i] = temp.number[i] * temp.sign - sign * number[i];
			}
			res.min_sign = true;
		}
	}
	/*if first number == second number*/
	else {
		res.number.resize(number.size());
		for (int i(0); i < res.number.size(); i++){
			res.number[i] = sign * number[i] - temp.number[i] * temp.sign;
		}
	}
	return res;
}

BigNumber BigNumber::_Multi(BigNumber temp){
	BigNumber res;
	if (number.size() != temp.number.size())
		return res;
	else
		res.number.resize(2 * number.size());
	for (int i(0); i < number.size(); i++){
		for (int j(0); j < temp.number.size(); j++)
			res.number[i+j] += number[i] * temp.number[i];
	}
	res.sign = sign * temp.sign;
	return res;
}

BigNumber BigNumber::_Offset(int offset){
	BigNumber res;
	res.number.resize(number.size() + offset);
	for (int i(0); i < number.size(); i++)
		res.number[i + offset] = number[i];
	res.sign = sign;
	return res;
}

int div10(int num){
	if(num >= 0)
		return num / 10;
	if(num % 10)
		return -(-num) / 10 - 1;
	return num / 10;
}

int mod10(int num){
	return num - 10 * div10(num);
}



void BigNumber::_Reverse(){
	for(int i = 0; i < number.size() - 1; i++){
		number[i + 1] += div10(number[i]);
		number[i] = mod10(number[i]);
	}
}

void BigNumber::_ReverseUp(){
	_Reverse();

	int high = number.size() - 1;
	if(number[high] < 0){
		sign = -sign;
		for(int i = 0; i < number.size(); i++){
			number[i] = -number[i];
		}
		_Reverse();
	}

	while(number.size() > 1 && number[number.size() - 1] == 0)
		number.pop_back();
	while(number[number.size() - 1] > 9){
		high = number.size() - 1;
		number.push_back(number[high] / 10);
		number[high] %= 10;
	}
}

string BigNumber::ToStr(){
	string str = "";
	if(sign == -1)
		str = '-';
	if (min_sign)
		str += '-';
	for(int i = 0; i < number.size(); i++){
		str += number[number.size() - i - 1] + '0';
	}
	return str;
}

BigNumber BigNumber::operator + (BigNumber &numb){
	BigNumber temp = _Plus(numb);
	temp._ReverseUp();
	return temp;
}

BigNumber BigNumber::operator - (BigNumber &numb){
	BigNumber temp = _Minus(numb);
	temp._ReverseUp();
	return temp;
}

BigNumber BigNumber::operator * (BigNumber &numb){
	BigNumber temp = _Multi(numb);
	temp._ReverseUp();
	return temp;
}
