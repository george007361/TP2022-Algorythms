//Задача № 1 (3 балла)
//Во всех задачах необходимо использование битовых операций.
//Использование арифметических операций запрещено.
//Входное число лежит в диапазоне 0..232 - 1 и вводится в десятичном виде.

//1.3 Если в числе содержится только один бит со значением 1, записать в выходной поток OK.Иначе записать FAIL
//in //out

//32 //OK
//34 //FAIL



#include <iostream>

using namespace std;

string checkNumber(int data);

int main()
{
    int data;
    cin >> data;
    cout << checkNumber(data);
}

string checkNumber(int data)
{
    int countOnes = 0;
    for (int i = 0; i < sizeof(data) * 8 && countOnes < 2; ++i)
    {
        if (bool((1 << i) & data))
            ++countOnes;
    }
    
    return countOnes == 1 ? "OK" : "FAIL";
}