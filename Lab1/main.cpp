#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>

using namespace std;

/// \brief Graph - заведём дефайн для типа, в котором будет храниться список смежности
/// нашего графа.
typedef vector<vector<pair<int, int>>> Graph;


// Также заведём пару дефайнов для того, чтобы было понятнее, что происходит
// В списке смежности лежат пары, где первый элемент (first) - это номер смежной вершины,
// а второй (second) - вес ребра до неё.
// Т.е. если раньше к элементам пары нужно было обращаться как:
//
// pair<int, int> p;
// p.first = 1;
// p.second = 2;
//
// То теперь можно писать:
//
// p.NODE = 1;
// p.WEIGHT = 2;
#define NODE    first
#define WEIGHT  second

// Также заведём дефайн для создания пары
#define MAKE_NODE(node, weight) make_pair(node, weight)
#define LENGTH  second

// Прототипы функций

///
/// \brief readGraphFromFile - чтение графа из файла
/// \param fin - параметр, в который передаётся поток ввода, из которого следует читать
/// \return Возвращает список смежности (хоть и читает список инцидентности, сразу преобразовывает)
///
Graph readGraphFromFile(ifstream &fin);

///
/// \brief findRoutes - главная функция, которая и будет искать циклы заданного размера
/// \param graph - сюда передаётся по ссылке граф, в котором нужно искать
/// \param length - и задаётся размер цикла
/// \return Возвращает массив с циклами заданного размера, отсортированный по возрастанию
///
vector<vector<int>> findRoutes(const Graph &graph, int length);

///
/// \brief dfs - Поиск в глубину, который и ищет наши циклы
/// \param graph - сюда передаётся граф
/// \param v - текущая обрабатываемая вершина
/// \param used - ссылка на массив, где если в used[i] == true, значит, мы уже побывали в этой вершине
/// \param route - ссылка на массив (работает как стэк), в котором хранится весь текущий путь
/// \param limit - размер цикла, который ищем
/// \param output - ссылка на массив, куда нужно складывать найденные циклы
/// \param cost - текущая длина пути, который сейчас обрабатывается (изначально 0, потом увеличивается)
/// \param start - номер стартовой вершины, чтобы не забыть
///
void dfs(const Graph &graph,
         int v,
         vector<bool> &used,
         vector<pair<int, int>> &route,
         int limit,
         vector<vector<int>> &output,
         int cost = 0,
         int start = 0);

///
/// \brief addRoute - Функция, которая вызывается, если dfs наткнулся на подходящий цикл.
/// Просто добавляет текущий цикл к ответу
/// \param route - ссылка на массив с текущим путём (циклом)
/// \param output - ссылка на массив, куда следует положить ответ
///
void addRoute(const vector<pair<int, int>> &route,
              vector<vector<int>> &output);

///
/// \brief main - погнали
/// \return
///
int main()
{
    // Количество тестовых файлов
    const unsigned kTestCasesNumber = 5;

    // Начинаем обрабатывать каждый тест
    for (unsigned test = 1; test <= kTestCasesNumber; ++test)
    {

        // Сразу запомним имена файлов для текущего теста
        // Файлы именуются как input-X.txt и output-X.txt, где Х - номер теста
        // Нумеруются тесты с единицы
        string inputFileName = "input-" + to_string(test) + ".txt";
        string outputFileName = "output-" + to_string(test) + ".txt";

        // Создадим потоки ввода и вывода
        ifstream fin;
        ofstream fout;

        // И попытаемся открыть файлы
        fin.open(inputFileName);
        fout.open(outputFileName);

        // Если хотя бы один файл не открылся, то пропускаем тест
        if (!fin.is_open() || !fout.is_open())
        {
            cout << "Can't open files for test #" << test << endl;
            cout << "Skipping test." << endl;
            continue;
        }

        // Читаем из файла длину цикла, который нужно найти
        int cycleLength;
        fin >> cycleLength;
        if (fin.eof())      // Если не вышло прочитать, значит тест плохой, пропускаем его
        {
            cout << "Can't find the length limit for test #" << test << endl;
            cout << "Skipping test." << endl;
            continue;
        }

        // Читаем сам граф из файла
        Graph graph = readGraphFromFile(fin);

        // Если граф оказался пустым, то такой тест тоже как-то не очень, пропустим
        if (graph.empty())
        {
            cout << "Empty test #" << test << endl;
            cout << "Skipping." << endl;
            continue;
        }

        // Ищем циклы
        vector<vector<int>> routes = findRoutes(graph, cycleLength);

        // Выводим ответ
        for (const auto &route : routes)
            for (size_t i = 0; i < route.size(); ++i)
            {
                fout << route[i];
                if (i < route.size() - 1)
                    fout << " ";
                else
                    fout << "\n";
            }

    }

    return 0;
}

// Чтение графа
Graph readGraphFromFile(ifstream &fin)
{
    Graph res;  // Сюда будем читать граф

    unsigned from, to, weight;
    fin >> from >> to >> weight;    // Читаем ребро (откуда, куда, вес)

    while (!fin.eof())              // Если ещё не в конце файла
    {
        if (res.size() < max(from, to)) // Увеличим размер графа, если требуется (размер явно не задан, понимаем его
            res.resize(max(from, to));  // исходя из введённых рёбер. Если есть ребро 3 -> 10, то считаем, что как минимум
        --from, --to;                   // 10 вершин в графе есть.
                                        // Уменьшим номера вершин, т.к. внутри программы они нумеруются с 0

        res[from].push_back(MAKE_NODE(to, weight)); // И добавим в список смежности нужную запись

        fin >> from >> to >> weight;    // Пытаемся прочитать следующее ребро
    }

    return res;
}

// Поиск циклов
vector<vector<int>> findRoutes(const Graph &graph, int length)
{
    // Запомним количество вершин в графе
    unsigned nodes = graph.size();

    vector<vector<int>> routes;     // Тут будут все циклы, наш ответ
    vector<pair<int, int>> route;   // Это массив для "текущего" маршрута, который обрабатывается

    for (unsigned i = 0; i < nodes; ++i)    // Запустимся от каждой вершины
    {
        vector<bool> used(nodes);           // Создадим массив посещений

        // И запускаем поиск в глубину от i-той вершины
        dfs(graph, i, used, route, length, routes, 0, i);
    }

    // Когда запустились от каждой вершины, отсортируем ответ
    sort(routes.begin(), routes.end());
    // И вернём его
    return routes;
}

// Поиск в глубину
void dfs(const Graph &graph,
         int v,
         vector<bool> &used,
         vector<pair<int, int>> &route,
         int limit,
         vector<vector<int>> &output,
         int cost,
         int start)
{
    // Добавляем текущую обрабатываемую вершину в наш маршрут
    route.push_back(make_pair(v, cost));

    // Помечаем, что мы уже заходили сюда
    used[v] = true;

    // И теперь пройдёмся по смежным вершинам
    for (const auto &nxt : graph[v])
        // Если мы ещё не ходили туда и длина маршрута с новой вершиной не будет больше, чем нам надо найти
        if (!used[nxt.NODE] && cost + nxt.WEIGHT <= limit)
            // То идём глубже рекурсивно в эту вершину. Не забываем передать туда новую длину маршрута - cost + nxt.WEIGHT
            dfs(graph, nxt.NODE, used, route, limit, output, cost + nxt.WEIGHT, start);
        // Иначе, если у нас длина машрута больше, чем положено, то вообще нет смысла идти
        // А если равна, а следующая вершина, хоть и посещена, но мы с неё начинали, то мы нашли ровно нужный нам цикл
        else if (nxt.NODE == start && cost + nxt.WEIGHT == limit)
        {
            // Добавим снова первую вершину в маршрут
            route.push_back(make_pair(nxt.NODE, cost + nxt.WEIGHT));
            // Запишем цикл в ответ
            addRoute(route, output);
            // И удалим вершину из маршрута, т.к. мы туда не пойдём
            route.pop_back();
        }

    // Когда выходим из вершины, удаляем себя из маршрута
    route.pop_back();
}

// Добавление маршрута в ответ
void addRoute(const vector<pair<int, int>> & route, vector<vector<int>> &output)
{
    vector<int> path;   // Сюда перепишем маршрут
    for (const auto &node : route)
        path.push_back(node.NODE);
    output.push_back(path); // И запихнём в ответ
}
