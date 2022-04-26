//Задача 1. Хеш - таблица(6 баллов)
//Обязательная задача
//Реализуйте структуру данных типа “множество строк” на основе динамической хеш - таблицы с открытой адресацией.
//Хранимые строки непустые и состоят из строчных латинских букв.
//Хеш - функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
//Начальный размер таблицы должен быть равным 8 - ми.Перехеширование выполняйте при добавлении элементов в случае, 
//когда коэффициент заполнения таблицы достигает 3 / 4.
//Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и 
//проверки принадлежности данной строки множеству.
//1_1.Для разрешения коллизий используйте квадратичное пробирование.i - ая проба
//g(k, i) = g(k, i - 1) + i(mod m).m - степень двойки.
//
//Требования: В таблице запрещено хранение указателей на описатель элемента.
//Формат входных данных
//Каждая строка входных данных задает одну операцию над множеством.Запись операции состоит из типа операции и 
//следующей за ним через пробел строки, над которой проводится операция.
//Тип операции  – один из трех символов :
//+означает добавление данной строки в множество;
//-означает удаление  строки из множества;
//? означает проверку принадлежности данной строки множеству.
//При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.При удалении элемента из 
//множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
//Формат выходных данных
//Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того, встречается ли 
//данное слово в нашем множестве;

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

struct StringHasher {
	StringHasher(const unsigned int param = 137) : param(param) {}

	unsigned int operator() (const string& key) const
	{
		unsigned int hash = 0;
		for (size_t i = 0; i < key.length(); ++i)
		{
			hash = hash * param + key[i];
		}
		return hash;
	}

private:
	unsigned int param;
};

template<class Type, class Hasher>
class HashTable
{
public:
	HashTable(const Hasher& hasher, const size_t initialSize = 8);
	~HashTable();

	HashTable() = delete;
	HashTable(const HashTable& srcHashTable) = delete;
	HashTable& operator = (const HashTable& srcHashTable) = delete;
	HashTable(HashTable&& srcHashTable) = delete;
	HashTable& operator = (HashTable&& srcHashTable) = delete;

	bool add(const Type& key);
	bool del(const Type& key);
	bool has(const Type& key) const;

private:
	void rehashTable(const size_t newSize);

private:
	typedef int TCellState;

	enum TCellStateEnum
	{
		EMPTY,
		DELETED,
		KEY
	};

	struct _HashTableCell
	{
		_HashTableCell() : state(TCellStateEnum::EMPTY), absHash(0) {}
		_HashTableCell(const Type& data, TCellState state, const unsigned long absHash) : data(data), state(state), absHash(absHash) {}

		Type data;
		TCellState state;
		unsigned long absHash;
	};

	Hasher _hasher;
	vector<_HashTableCell> _table;
	size_t keysCount;
	size_t deletedCellsCount;
};

template<class Type, class Hasher>
HashTable<Type, Hasher>::HashTable(const Hasher& hasher, const size_t initialSize) :
	_hasher(hasher),
	_table(initialSize % 2 ? initialSize + 1 : initialSize, _HashTableCell()),
	keysCount(0),
	deletedCellsCount(0)
{
}

template<class Type, class Hasher>
HashTable<Type, Hasher>::~HashTable()
{
}

template<class Type, class Hasher>
bool HashTable<Type, Hasher>::add(const Type& key)
{
	unsigned long absHash = _hasher(key);
	unsigned long hash = absHash % _table.size();
	unsigned long firstDeletedCellHash = 0;
	bool foundDeleted = false;

	for (unsigned long i = 0; true; hash = (hash + ++i) % _table.size())
	{
		if (_table[hash].state == TCellStateEnum::EMPTY)
		{
			_table[foundDeleted ? firstDeletedCellHash : hash] = _HashTableCell(key, TCellStateEnum::KEY, absHash);
			++keysCount;

			if (foundDeleted)
				--deletedCellsCount;

			if (keysCount >= 3 * _table.size() / 4)
			{
				rehashTable(_table.size() * 2);
			}

			return true;
		}

		if (_table[hash].state == TCellStateEnum::DELETED && !foundDeleted)
		{
			foundDeleted = true;
			firstDeletedCellHash = hash;
		}

		if (_table[hash].state == TCellStateEnum::KEY && _table[hash].data == key)
		{
			return false;
		}
	}
}

template<class Type, class Hasher>
bool HashTable<Type, Hasher>::del(const Type& key)
{
	unsigned long hash = _hasher(key) % _table.size();
	for (unsigned long i = 0; true; hash = (hash + ++i) % _table.size())
	{
		if (_table[hash].state == TCellStateEnum::EMPTY)
		{
			return false;
		}

		if (_table[hash].state == TCellStateEnum::KEY && _table[hash].data == key)
		{
			_table[hash].state = TCellStateEnum::DELETED;
			--keysCount;
			++deletedCellsCount;

			if (deletedCellsCount >= _table.size() / 2)
			{
				rehashTable(_table.size());
			}

			return true;
		}
	}
}

template<class Type, class Hasher>
bool HashTable<Type, Hasher>::has(const Type& key) const
{
	unsigned long hash = _hasher(key) % _table.size();

	for (unsigned long i = 0; true; hash = (hash + ++i) % _table.size())
	{
		if (_table[hash].state == TCellStateEnum::EMPTY)
		{
			return false;
		}

		if (_table[hash].state == TCellStateEnum::KEY && _table[hash].data == key)
		{
			return true;
		}
	}
}

template<class Type, class Hasher>
void HashTable<Type, Hasher>::rehashTable(const size_t newSize)
{
	assert(newSize >= _table.size());

	vector<_HashTableCell> newTable(newSize % 2 ? newSize + 1 : newSize);
	deletedCellsCount = 0;

	for (size_t i = 0; i < _table.size(); ++i)
	{
		if (_table[i].state == TCellStateEnum::KEY)
		{
			unsigned long newHash = _table[i].absHash % newTable.size();

			for (unsigned long j = 0; newTable[newHash].state != TCellStateEnum::EMPTY; newHash = (newHash + ++j) % newTable.size());

			newTable[newHash] = _table[i];
		}
	}
	_table = std::move(newTable);
}

int main()
{
	StringHasher h;
	HashTable<string, StringHasher> t(h);
	char command;
	string str;

	while (cin >> command >> str)
	{
		switch (command)
		{
		default:
		{
			assert(false);
		}
		case '+':
		{
			cout << (t.add(str) ? "OK" : "FAIL") << endl;
			break;
		}
		case '-':
		{
			cout << (t.del(str) ? "OK" : "FAIL") << endl;
			break;
		}
		case '?':
		{
			cout << (t.has(str) ? "OK" : "FAIL") << endl;
			break;
		}
		}

	}

	return EXIT_SUCCESS;
}
