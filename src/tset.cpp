// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem < 0 || Elem >= MaxPower) throw Elem;
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 || Elem >= MaxPower) throw Elem;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0 || Elem >= MaxPower) throw Elem;
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this != &s) {
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int n = MaxPower;
	if (s.MaxPower > MaxPower) n = s.MaxPower;
	TSet t(n);
	t.BitField = BitField | s.BitField;
	return t;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if ((Elem < 0) || (Elem >= MaxPower)) throw Elem;
	BitField.SetBit(Elem);
	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if ((Elem < 0) || (Elem >= MaxPower)) throw Elem;
	BitField.ClrBit(Elem);
	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int n = MaxPower;
	if (s.MaxPower > MaxPower)
		n = s.MaxPower;
	TSet t(n);
	t = BitField & s.BitField;
	return t;
}

TSet TSet::operator~(void) // дополнение
{
	return ~BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &is, TSet &s) // ввод
{
	int a;
	is >> a;
	while (a >= 0) is >> a;
	return is;
}

ostream& operator<<(ostream &os, const TSet &s) // вывод
{
	os << "{";
	for (int i = 0; i < s.MaxPower; i++)
		if (s.IsMember(i)) {
			os << i;
			if (i != s.MaxPower - 1) os << ", ";
		}
	os << "}" << endl;
	return os;
}
