**Часть 1.**

- **Лабораторная работа №1 «Управляющие структуры и циклы» (Lab\_1-1)**

**Цель:** Познакомиться управляющими структурами, циклами и массивами. Научиться использовать управляющие структуры, для обработки различных частных условий выполнения алгоритма, циклы для выполнения обработки многократно повторяющихся действий, массивов для удобной работы с большим множеством переменных содержащих однотипные данные. Освоить метод решения задач с использованием комбинаций управляющих структур и циклов и массивов для достижения более гибких алгоритмов в программе.

**Задание:** Сформировать массив простых множителей заданного числа.

**Входные данные:** Целое положительное число A

**Результат:** Сформированный массив K, содержащий простые числа, где перемножение между собой всех значений данного массива в результате дает то же число A, указанное во входных данных

**Метод решения:** Последовательно делим число A на все простые числа (начиная с 2) проверяя при этом есть ли остаток от деления или нет. Если остаток от деления имеется (больше 0), то переходим к следующему простому числу, на которое снова делим число A. Если на каком-то шаге, остатка от деления не обнаружено (равен 0), значит текущее простое число является одним из искомых простых делителей числа A. Добавляем данное простое число в массив K, а результат деления (число A1), сохраняем и в дальнейшем производим все те же операции над числом A1 какие были сделаны для числа A (т.е. заменяем число A на A1). Выполняем до тех пор, пока число Anне станет простым числом, т.е. на последнем шаге число An также будет добавлено в массив K.

- **Лабораторная работа №2 «Итерационные процессы» (Lab\_1-2)**

**Цель:** Познакомиться итерационными процессами и циклами. Научиться использовать итерационные циклы для выполнения многократно повторяющихся действий и предусматривать соответствующий выход из данного цикла.

Освоить метод решения задач с использованием интеграционных циклов где число повторений цикла заранее не известно и зависит от вычисляемого условия в программе.

**Задание:** Рассчитатьln (x) = 2/1\*z + 2/3\*z^3 +…+2/(2n-1)\*z^(2n-1), где z=(x-1)/(x+1), n – кол-во элементов ряда.

**Входные данные:** Вещественная переменная x которая будет принимать значения от 0.1 до 1 с шагом 0.1.

**Результат:** Сформированная таблица, содержащий три столбца, 1-ый столбец, значение x указанного выше диапазона, 2-ой столбец значение функции ln (x) вычисленного способом представления через ряд с точностью до 4-го знака после запятой, 3-й столбец значение функции ln (x) вычисленное с помощью библиотечной функции.

**Метод решения:** Рассмотрим методику расчета ln(x) через ряд. Расчет будет осуществляться через накопительное суммирование всех элементов ряда до числа n. При этом сам по себе ряд является сходящимся, каждый последующий элемент меньше предыдущего, соответственно, чем больше число n, тем точнее получается итоговая величина и тем больше операций суммирования нам нужно сделать, т.к. кол-во элементов рядя у нас равно числу n. Соответственно сравнивая получившееся значение текущего элемента ряда с некой величиной определенной точности (знаков после запятой) мы можем в итоге управлять итоговой точностью получающего значения ln(x). Далее делаем перебор значений x от 0,1 до 1 с шагом 0,1 высчитываем на каждом шаге значение ln(x).

- **Лабораторная работа №3 «Строки» (Lab\_1-3)**

**Цель:** Познакомиться со строками в языке Си. Научится использовать различные комбинации управляющих структур и циклов и массивов для достижения различных манипуляций со строками. Научится решать задачи с использованием библиотечных функции языка Си для работы со строками.

**Задание:**&quot;Перевернуть&quot; в строке все слова. (Например: &quot;Жили были дед и баба&quot; - &quot;илиЖ илиб дед и абаб&quot;).

**Входные данные:** Строка содержащее предложение из нескольких строк разделенных пробелами.

**Результат:** Строка содержащее исходное предложение, но каждое слово, в котором инвертировано. Инвертированное слово – это такое слово, где все символы в слове переставлены задом наперед, т.е. 1-я буква в исходном слове становится последней в перевернутом, 2-ая буква -  предпоследней и т.д. где последняя буква в исходном слове становится 1-ой в перевернутом. Причем регистр букв перестановке сохраняется.

**Метод решения:** Исходное предложение (строку) разбиваем на массив слов (подстрок), где пробел будет определять начало или конец каждого слова (подстроки). Далее имея массив слов (подстрок) перебираем по порядку каждую слово и инвертируем его по алгоритму, описанному выше. После в конечную строку добавляем каждое инвертированное слово в том же порядке, как и в исходной строке.

- **Лабораторная работа №4 «Сортировки» (Lab\_1-4)**

**Цель:** Познакомиться со алгоритмами сортировок в языке Си. Научится использовать различные комбинации сортировок для получения различных конечных данных.

**Задание:** Шейкер-сортировка. Процесс движения в прямом и обратном направлении реализовать в виде одного цикла, используя параметр - направление движения (+1/-1) и меняя местами нижнюю и верхнюю границы просмотра.

**Входные данные:** Шейкер-сортировка. Процесс движения в прямом и обратном направлении реализовать в виде одного цикла, используя параметр - направление движения (+1/-1) и меняя местами нижнюю и верхнюю границы просмотра.

**Результат:** Отсортированный массив элементов по возрастанию: от меньших к большим.

**Метод решения:** Сортировка методом сравнения и обмена пары соседних элементов до тех пор, пока не будут отсортированы все элементы, чередуются проходы по массиву, сначала слева на право - сдвигая каждый раз наибольший элемент вправо, потом проход справа на лево - сдвигая каждый раз наименьший элемент влево. Проходы совершаются до тех пор, пока все элементы массива не будут отсортированы.

**Часть 2.**

- **Лабораторная работа №1 «Сортировка и поиск с указателями» (Lab\_2-1)**

**Цель:** Познакомиться с работой с указателями в языке Си. Научится использовать различные приемы работы с указателями для реализации различных алгоритмов поиска и сортировки.

**Задание:** Функция производит двоичный поиск места размещения нового элемента в упорядоченном массиве и возвращает указатель на место включения нового элемента. С помощью функции реализовать сортировку вставками.

**Входные данные:** Массив символов (строка), содержащий случайный набор символов.

**Результат:** Массив символов (строка), отсортированный по коду символа – от меньшего к большему.

**Метод решения:**

_Для бинарного поиска:_ На каждом шаге алгоритма выбирается символ со средним индексом в уже отсортированной строке и сравнивается с &#39;k&#39;. Если &#39;k&#39; меньше или равен значению из середины, то такой же алгоритм осуществляется в первой половине элементов, иначе — во второй. Процесс повторяется тех пор, пока интервал для поиска не сузится до одного символа, и правая граница которого и будет искомым местом для вставки символа &#39;k&#39;.

_Для сортировки вставками:_ На каждом шаге алгоритма выбирается по порядку один из символов сортируемой строки и помещается на нужную позицию в уже отсортированной строке (такая строка начинается с одного символа) до тех пор, пока набор входных данных не будет исчерпан.

- **Лабораторная работа №2 «БД на структурах» (Lab\_2-2)**

**Цель:** Познакомиться с работой со структурами в языке Си. Научится использовать различные приемы работы со структурами и массивом структур и реализовать алгоритмов поиска и сортировки данных массивов структур.

**Задание:**

Определить структурированный тип «Авиабилет»:

- номер рейса
- пункт назначения
- время вылета
- дата вылета
- стоимость билета

Определить набор функций для работы с массивом структур. В структурированной переменной предусмотреть способ отметки ее как не содержащей данных (т.е. &quot;пустой&quot;). Функции должны работать с массивом структур или с отдельной структурой через указатели, а также при необходимости возвращать указатель на структуру. В перечень функций входят:

- ввод элементов (полей) структуры с клавиатуры;
- вывод элементов (полей) структуры на экран;
- «очистка» структурированных переменных;
- удаление заданного элемента;
- изменение (редактирование) заданного элемента.
- сортировка массива структур в порядке возрастания заданного поля (при сортировке можно использовать тот факт, что в Си++ разрешается присваивание структурированных переменных);
- поиск свободной структурированной переменной;
- поиск в массиве структур минимального значения заданного поля;
- поиск в массиве структур элемента с заданным значением поля или с наиболее близким к нему по значению.

**Входные данные:** Массив структур, содержащий случайный набор данных полей структуры.

**Результат:** Массив структур, отсортированный по заданному полю структуры – от меньшего к большему.

**Метод решения:** _Сортировка вставками:_ На каждом шаге алгоритма выбирается по порядку один из символов сортируемой строки и помещается на нужную позицию в уже отсортированной строке (такая строка начинается с одного символа) до тех пор, пока набор входных данных не будет исчерпан.

- **Лабораторная работа №3 «Работа с памятью через указатели» (Lab\_2-3)**

**Цель:** Научится работать с памятью на низком уровне. Научится упаковывать и распаковывать данные в памяти с использованием различных алгоритмов с применением указателей.

**Задание:** Разработать две функции, одна из которых вводит с клавиатуры набор данных в произвольной последовательности и размещает в памяти в заданном формате. Другая функция читает эти данные и выводит на экран. Программа запрашивает и размещает в памяти несколько наборов данных при помощи первой функции, а затем читает их и выводит на экран при помощи второй. Размещение данных производить в выделенном массиве байтов с контролем его переполнения.

Область памяти представляет собой строку. Если в ней встречается выражение &quot;%nnnd&quot;, где nnn – целое, то сразу же за ним следует массив из nnn целых чисел (во внутреннем представлении, то есть типа int). За выражением &quot;%d&quot; - одно целое число, за &quot;%nnnf&quot; - массив из nnn вещественных чисел, за &quot;%f&quot; - одно вещественное число.

**Входные данные:** Область памяти, представленная в виде строки, в которой записаны массивы целых и дробных чисел с их размерностью. Т.е. в памяти располагается строка %\&lt;n\&gt;\&lt;c\&gt;&quot;, где \&lt;n\&gt; – целое число в виде байта, которое характеризует количество введённых цифр одного типа. Далее идет символ \&lt;c\&gt; – который может быть либо &#39;d&#39; либо &#39;f&#39;. Символ &#39;d&#39; означает целое число типа int, &#39;f&#39; – вещественное число типа float. После символа \&lt;c\&gt; идет во внутреннем представлении подряд числа с типом (указанным в \&lt;c\&gt;) и в заданном количестве (кол-во указано в \&lt;n\&gt;).

**Результат:** Выводит на консоль последовательно массив целых либо дробных чисел. Массивы наполняются из области памяти в которой в определенном формате представлены данные массивы.

**Метод решения:**

Функция последовательно выводит на консоль массивы чисел, целых либо дробных. Массив чисел наполняется посредством раскодирования данных из области памяти. В начале из области памяти считываем 1 символ, если он равен %, далее проверяем идет ли после него символы &#39;d&#39; (целое) или &#39;f&#39; (дробное), если да, то считаем, что массив состоит из 1 элемента. Если таких символов не обнаружено, то считываем байт со значением – кол-вом чисел, сохраненных в памяти (размерность массива). После него считываем символ типа данных массива – &#39;d&#39; (целое) или &#39;f&#39; (дробное).

для целого:

p\_d = (int\*)p;

d = \*p\_d++;

p = (char\*)p\_d;

для вещественного:

p\_f = (float\*)p;

f = \*p\_f++;

p = (char\*)p\_f;

где

p – исходное представление памяти в виде строки;

p\_d – временный указатель на область памяти p представленной в типе int;

p\_f – временный указатель на область памяти p представленной в типе float;

d – переменная с целым числом (текущим элементом массива) которое будет записываться в память;

f – переменная с целым числом (текущим элементом массива) которое будет записываться в память;

После него с помощью операций последовательно считываем из памяти каждое число.

- **Лабораторная работа №4 «Функции с переменным числом параметров» (Lab\_2-4)**

**Цель:** Научится работать с функциями с переменным числом параметров. Научится извлекать параметры из списка с применением преобразования типа указателя.

**Задание:** Разработать функцию с переменным числом параметров. Для извлечения параметров из списка использовать операцию преобразования типа указателя. Последовательность указателей на вещественные переменные, ограниченная NULL. Функция возвращает динамический  массив указателей на эти переменные.

**Входные данные:** Список параметров, передающих содержащий указатели на значения типа double в функцию.

**Результат:** Функция возвращает динамический массив указателей на значения типа double, где последний элемент массива ссылается на нулевой указатель.

**Метод решения:** Сначала функция подсчитывает количество переданных элементов до последнего нулевого. После, зная кол-во переменных создаем динамический массив указателей типа double и после того перебирая каждый элемент динамического массива присеваем ему текущий указатель. Последний указатель в массиве будет нулевым – NULL.

- **Лабораторная работа №5 «Собственная реализация функций malloc и free» (Lab\_2-5)**

**Цель:** Научится работать с памятью на низком уровне. Научится выделять место в памяти заданного размера под переменные и осуществлять освобождение памяти.

**Задание:** Разработать две функции, одна из которых осуществляет выделение блока памяти заданного размера из кучи (аналог malloc) и возвращает указатель на начало данного блока, другая функция осуществляет возврат блока выделенного ранее блока памяти в кучу (аналог free) на основании полученного указателя на начало такого блока.

**Входные данные:** Целое значение sz, характеризующее размер в байтах области памяти, для которой осуществляется выделение.

**Результат:** Адрес на первый байт области памяти размером sz байт, которая была выделена из кучи. Если памяти недостаточно, чтобы удовлетворить запрос, возвращается нулевой указатель.

**Метод решения:** Осуществляется поиск, в таблице свободных адресов, записи у которой размер блока памяти равен или больше sz байт. Изначально в таблице свободных адресов присутствует только одна запись – весь объем непрерывной области памяти. Далее при нахождении такого блока, его начальный адрес и размер величиной sz добавляются таблицу занятых областей. Если в данной таблице уже есть записи (ранее уже были выделены области для др. задач) новая запись добавляется с учетом сортировки по адресам, т.к. все записи в таблице занятых блоков упорядочены в порядке возрастания адресов. После добавления блока в таблицу занятых блоков, размер блока в свободной области уменьшается на величину sz а адрес блока смещается вперед на ту же величину sz.
