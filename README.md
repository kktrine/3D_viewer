
Qt/C++. \
Программа для визуализации каркасной модели в трехмерном пространстве. MVC паттерн. Программа реализует следующий функционал:

- Сборка программы  настроена с помощью Makefile со стандартным набором целей для GNU-программ: all, install, uninstall, clean, dvi, dist, tests. Установка должна вестись в любой другой произвольный каталог
- Загрузка каркасной модели из файла формата obj (поддержка только списка вершин и поверхностей).
- Перемещение модели на заданное расстояние относительно осей X, Y, Z.
- Поворот модели на заданный угол относительно своих осей X, Y, Z.
- Масштабирование модель на заданное значение.


Графический пользовательский интерфейс содержит:

- Кнопку для выбора файла с моделью и поле для вывода его названия.
- Зону визуализации каркасной модели.
- Кнопку/кнопки и поля ввода для перемещения модели.
- Кнопку/кнопки и поля ввода для поворота модели.
- Кнопку/кнопки и поля ввода для масштабирования модели.
- Информацию о загруженной модели - название файла, кол-во вершин и ребер.

 Программа  корректно обрабатывает модели до 1 000 000 вершин без зависания.