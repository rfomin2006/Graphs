<h1>Графы</h1>
<br>
<h2>Задача: реализовать граф на C++</h2>
<br>
<p>Необходимо реализовать функции добавления города (вершина графа), добавления дороги (ребро графа) и вывода всех путей из одного города в другой с указанием общей протяженности. Представим абстракцию графа, 
  как структуру данных:</p>

| Абстракция | Детали абстракции |
| ------------- | ------------- |
| ![Graph](https://github.com/rfomin2006/Graphs/assets/146825482/9d6899a8-96eb-4bf0-ada6-1f09c124ab7b) | Вершина - точка в графе, отдельный объект, для топологической модели графа (в задаче каждая вершина является городом). <br> Ребро - неупорядоченная пара двух вершин, которые связаны друг с другом (в задаче каждое ребро является путем из одного города в другой).|

<br>
<h2>Контрольный пример</h2>
<br>

| Изображение графа | Результаты поиска путей |
| ------------- | ------------- |
| ![PrintGraph 1](https://github.com/rfomin2006/Graphs/assets/146825482/e70ccc8f-2fe6-400d-b67a-8f7c733ffc67) | ![FindPaths 1](https://github.com/rfomin2006/Graphs/assets/146825482/cb77aaec-1d28-463c-83f2-9608e8e835f9) |

| Циклы | 
| ------------- |
| ![1 1](https://github.com/rfomin2006/Graphs/assets/146825482/c4f49266-cb23-4034-a049-f7bef2480f5e) |
