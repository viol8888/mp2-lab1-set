// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0) {
		throw "The len is too small";
	}
	else {
		BitLen = len;
		MemLen = (BitLen - 1) / (sizeof(TELEM) * 8) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >= BitLen)) {
		throw "incorrect n value";
	}
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n >= BitLen)) {
		throw "incorrect n value";
	}
	return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen)) {
		throw "incorrect n value";
	}
	pMem[GetMemIndex(n)] = (pMem[GetMemIndex(n)] | GetMemMask(n));
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen)) {
		throw "incorrect n value";
	}
	pMem[GetMemIndex(n)] = (pMem[GetMemIndex(n)] & (~(GetMemMask(n))));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen) {
		throw "incorrect n value";
	}
	return (pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.GetLength()) {
		return 0;
	}
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i]) {
			return 0;
			break;
		}
		else { return 1; }
	}
	
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.GetLength()) {
		return 1;
	}
	for (int i = 0; i < MemLen; i++)
	{
		if (pMem[i] != bf.pMem[i]) {
			return 1;
			break;
		}
		else { return 0; }
	}
	
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int maxx = max(bf.BitLen, BitLen);
	TBitField ret(maxx);
	for (int i = 0; i < MemLen; i++)
	{
		ret.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return ret;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int maxx = max(bf.BitLen, BitLen);
	TBitField ret(maxx);
	for (int i = 0; i < MemLen; i++)
	{
		ret.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return ret;
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < BitLen; ++i)
	{
		if (GetBit(i) == 0)
		{
			SetBit(i);
		}
		else
		{
			ClrBit(i);
		}
	}
	return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	for (int i = 0; i < bf.GetLength(); i++) {
		if (istr) {
			bf.SetBit(i);
		}
	}
	return  istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++) {

		ostr << bf.GetBit(i);
	}
	return ostr;
}
