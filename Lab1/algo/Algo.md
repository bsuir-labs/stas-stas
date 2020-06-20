Для решения задачи необходимы переменные:

* n - количество вершин
* m - количество рёбер
* graph - множество, которое содержит рёбра графа
* NotChecked - множество непроверенных вершин обрабатываемого графа
* Cycles - Множество, которое будет содержать найденные циклы заданной длины
* Way - Текущий рассматриваемый путь

### Вход

![img0]()

### Шаг 1

Создаём и заполняем множество рёбер графа

![img1]()

### Шаг 2

Создаём и заполняем множество непроверенных вершин

![img2]()

### Шаг 3

Создаём переменные Cycles и Way.

![img3]()

### Шаг 4

Из множества непроверенных вершин достаём вершину (А) и помещаем её как первую вершину в переменную Way, удаляем эту вершину из множества NotChecked.

![img4]()

### Шаг 5

Рассматриваем вершины, смежные с последней вершиной в пути. Добавляем первую непосещённую вершину в путь и продолжаем работу уже с ней. Если пути вперёд нет, возвращаемся на один шаг назад и рассматриваем следующую вершину, смежную с последней вершиной в пути. Если следующая вершина равна первой вершине в пути, значит найден цикл.

![img5]()

### Шаг 6

Так как найденный цикл имеет длину больше, чем положено, возвращаемся назад по пути и продолжаем искать циклы.

![img6]()

### Шаг 7

Находим следующий цикл.

![img7]()

### Шаг 8

Найденный цикл имеет длину 12, так что сохраняем его в ответ.

![img8]()

### Шаг 9

Так как путей, начинающихся с вершины А больше нет, выходим из пути и начинаем новый обход со следующей вершины из множества непроверенных вершин. Удаляем вершину В из множества непроверенных вершин.

![img9]()

### Шаг 10

Первый найденный цикл имеет неподходящую длину, ищем дальше.

![img10]()

### Шаг 11

Найден подходящий цикл. Сохраняем его в ответ (на иллюстрациях в целях экономии места не стал его обозначать в ответах, т.к. он такой же, как и первый найденный).

![img11]()

### Шаг 12

Hачинаем новый обход со следующей вершины из множества непроверенных вершин. Удаляем вершину C из множества непроверенных вершин.

![img12]()

### Шаг 13

Ни один найденный цикл с данной вершиной не подходит.

![img13]()

### Шаг 14

Hачинаем новый обход со следующей вершины из множества непроверенных вершин. Удаляем вершину D из множества непроверенных вершин. Ни один из найденных циклов не подходит по длине

![img14]()

### Шаг 15

Hачинаем новый обход со следующей вершины из множества непроверенных вершин. Удаляем вершину Е из множества непроверенных вершин. Первый найденный цикл не подходит по длине

![img15]()

### Шаг 16

Найденный цикл имеет длину 12, так что сохраняем его в ответ.

![img16]()

### Шаг 17

Множество непроверенных вершин пусто. Найденный цикл длины 12: *A-B-E-A*, а также *B-E-A-B* и *E-A-B-E*.