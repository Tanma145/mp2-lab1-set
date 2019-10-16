// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (len / 32) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return pMem[n / 32];
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int a = n % 32;
	return 1 << a;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return MemLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int pos;
	pos = GetMemIndex(n);
	TELEM mask;
	mask = GetMemMask(n);
	pMem[pos] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;
	for (int i = 0; i < MemLen - 1; i++)
		if (pMem[i] != bf.pMem[i]) return 0;
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
		if (GetBit(i) != bf.GetBit(i)) return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 1;
	for (int i = 0; i < MemLen - 1; i++)
		if (pMem[i] != bf.pMem[i]) return 1;
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
		if (GetBit(i) != bf.GetBit(i)) return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = pMem[i] | bf.pMem[i];
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++)
		res.pMem[i] = pMem[i] & bf.pMem[i];
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField bf(BitLen);
	for (int i = 0; i < MemLen; i++)
		bf.pMem[i] = ~pMem[i];
	return bf;
}

// ввод/вывод

istream &operator>>(istream &is, TBitField &bf) // ввод
{
	int i = 0;
	char c;
	do {
		is >> c;
		if (c == '0') bf.ClrBit(i);
		if (c == '1') bf.SetBit(i);
		i++;
	} while (c == '0' || c == '1');
	return is;
}

ostream &operator<<(ostream &os, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		if (bf.GetBit(i)) os << 1;
		else os << 0;
	return os;
}
