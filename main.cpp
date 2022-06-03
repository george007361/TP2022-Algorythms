/*
Требуется отыскать самый выгодный маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.

Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.

Формат ввода
Первая строка содержит число N – количество городов.

Вторая строка содержит число M - количество дорог.

Каждая следующая строка содержит описание дороги (откуда, куда, время в пути). Все указанные дороги двусторонние. Между любыми двумя городами может быть больше одной дороги.

Последняя строка содержит маршрут (откуда и куда нужно доехать).

Формат вывода
Вывести длину самого выгодного маршрута.


Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.
*/

#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

class CityGraph
{
public:
	typedef int CityName;
	typedef size_t Time;
	typedef pair<CityName, Time> City;

public:
	CityGraph(const size_t countOfCities);

	CityGraph(const CityGraph&) = default;
	CityGraph(CityGraph&&) = default;

	CityGraph& operator=(const CityGraph&) = default;
	CityGraph& operator=(CityGraph&&) = default;

	~CityGraph() = default;

	void addWay(const CityName from, const CityName to, const Time time);
	CityGraph::Time getTime(const CityName from, const CityName to) const;
	vector<CityGraph::CityName> getNeibours(const CityName from) const;
	int getCountOfWays(const CityName from) const;
	int getCityName(const CityName from, const CityName to) const; //~
	CityGraph::Time getFastestWay(const CityName from, const CityName to) const;

private:
	struct WayTimeComparator
	{
		bool operator()(City city_1, City city_2)
		{
			return city_1.second > city_2.second;
		}
	};

private:
	vector<vector<City>> graph;
};

CityGraph::CityGraph(const size_t countOfCities)
{
	graph.resize(countOfCities);
}

void CityGraph::addWay(const CityName from, const CityName to, const Time time)
{
	graph[from].emplace_back(City(to, time));
}

CityGraph::Time CityGraph::getTime(const CityName from, const CityName to) const
{
	return graph[from][to].second;
}

vector<CityGraph::CityName> CityGraph::getNeibours(const CityName from) const
{
	vector<int> result;

	for (const auto& city : graph[from])
	{
		result.push_back(city.first);
	}

	return result;
}

int CityGraph::getCityName(const CityName from, const CityName to) const //!
{
	return graph[from][to].first;
}

int CityGraph::getCountOfWays(const CityName from) const
{
	return (int)graph[from].size();
}

CityGraph::Time CityGraph::getFastestWay(const CityName from, const CityName to) const
{
	vector<Time> minTimes(graph.size(), INT_MAX);
	priority_queue<City, vector<City>, WayTimeComparator> prQue;

	minTimes[from] = 0;
	prQue.push(City(from, 0));

	while (!prQue.empty())
	{
		auto city = prQue.top();
		prQue.pop();

		vector<CityName> nextCities = getNeibours(city.first);
		int countOfWays = getCountOfWays(city.first);

		for (int i = 0; i < countOfWays; ++i)
		{
			Time newTime = minTimes[city.first] + getTime(city.first, i);
			if (newTime < minTimes[getCityName(city.first, i)])
			{
				minTimes[getCityName(city.first, i)] = newTime;
				prQue.push(City(getCityName(city.first, i), minTimes[getCityName(city.first, i)]));
			}
		}
	}

	return minTimes[to];
}

int main()
{
	size_t  N, M;

	CityGraph::CityName from, to;
	CityGraph::Time time;

	cin >> N >> M;

	CityGraph cities(N);

	for (size_t i = 0; i < M; i++)
	{
		cin >> from >> to >> time;
		cities.addWay(from, to, time);
		cities.addWay(to, from, time);
	}

	cin >> from >> to;
	cout << cities.getFastestWay(from, to);

	return EXIT_SUCCESS;
}