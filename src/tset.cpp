// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
    MaxPower = s.GetMaxPower();
    BitField = TBitField(s.BitField);
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(-1)
{
    MaxPower = bf.GetLength();
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
    if (Elem < 0 || Elem >= MaxPower) {
        throw "element error";
    }
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw "element error";
    }
    return BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower) {
        throw "element error";
    }
    return BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if ((MaxPower == s.MaxPower) & (BitField == s.BitField)) {
        return 1;
    }
    else { return 0; }
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    if ((MaxPower == s.MaxPower) & (BitField == s.BitField)) {
        return 0;
    }
    else {
        return 1;
    }
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet ret = max(MaxPower, s.GetMaxPower());
    ret.BitField = BitField | s.BitField;
    return ret;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if ((Elem < 0) || (Elem > MaxPower))
    {
        throw "non-correct value of Elem";
    }
    TSet ret(*this);
    ret.BitField.SetBit(Elem);
    return ret;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
    {
        throw "non-correct value of Elem";
    }
    TSet ret(*this);
    ret.BitField.ClrBit(Elem);
    return ret;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet ret = max(MaxPower, s.GetMaxPower());
    ret.BitField = BitField & s.BitField;
    return ret;
}

TSet TSet::operator~(void) // дополнение
{
    TSet ret(*this);
    ret.BitField = ~ret.BitField;
    return ret;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    for (int i = 0; i < s.GetMaxPower(); i++) {
        if (istr) {
            s.InsElem(i);
        }
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.GetMaxPower(); i++) {

        ostr << s.IsMember(i);

    }
    return ostr;
}