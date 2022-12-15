# Домашнее задание 4. Вариант 8
## _Нарин Алексей, БПИ217_

*Критерии выполнены на оценку 4.*

![img.png](img.png)
### Описание решения
Реализован класс Страна (State), имеющий два экземпляра, обозначающих Анчуарию и Тарантерию. </br></br>
Каждая страна имеет карту (state_map), на которой случайно расположены здания.</br></br>
Страны многократно "атакуют" друг друга, то есть выбирают случайную из неатакованных клеток на карте противника. Если там здание, оно разрушается, если нет - снаряд тратится впустую.</br></br>
Атаки прекращаются когда суммарная стоимость оставшихся зданий не превышает суммарную стоимость израсходованных боеприпасов.</br></br>

### Ввод
Позволяется вручную ввести любые неотрицательные цены на боеприпасы и здания каждой из стран, либо использовать дефолтные.</br></br>
Ввод осуществляется через консоль.

### Параллельные вычисления
Каждая страна атакует другую независимо, в отдельном потоке. </br></br>
Программа завершается после завершения обоих потоков, показав итоговые карты государств, где разрушенные здания отмечены х</br></br>
Использован итеративный параллелизм, т.к. потоки практически идентичные, содержат циклы и не пересекаются областями используемой памяти.
