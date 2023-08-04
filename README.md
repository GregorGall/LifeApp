# LifeApp

![Logo](/doc/Logo.png)

## Описание

Cимулятор "жизни". Представляет собой графическое приложение написанное с использованием Qt
на основе соответствующей библиотеки LifeLib.

## Содержание

* [Обзор](#обзор)
* [Управление](#управление)
* [Сборка](#сборка)
* [Документация](#документация)

## Обзор

Поле клеток


<img src="CellField.png" width="600">

Окно настроек и справки

<img src="Help.png" height="250">
<img src="Settings.png" height="260">

В окне настроек доступно изменение размеров поля, выбор расчетного ядра и задержки между кадрами.
Настройки могут изменяться "на лету" без закрытия соответствующего окна, для этого требуется нажать кнопку Apply.
Кнопка Ok применяет изменения и закрывает окно настроек.

О программе

<img src="About.png" height="260">

## Управление

Основное:

ЛКМ - переключает состояние клетки  
ПКМ - фокус на определенной клетке  
Двойной ПКМ - снятие фокуса  

Горячие клавиши:

Сtrl+Q - Выход  
Сtrl+E - Настройки  
Ctrl+H - Помощь  
Ctrl+A - О программе  

## Сборка

Для сборки требуется компилятор с поддержкой стандарта не ниже C++17. Сборка с поддержкой OpenMp требует наличия соответствующей
библиотеки. Проект поддерживает условную компиляцию. При отсутствии нужных компонентов сборка будет продолжена с отключением
соответствующих движков. Версия Qt используемая для отрисовки интерфейса 6.3.1

Можно также использовать docker. Файл для контейнера с настроенным окружением /docker/Dockerfile.

## Документация

Обзор библиотеки c тестами, benchmark и doxygen документацией,реализующей расчетную
модель приведен тут: ![LifeLib](../lib/LifeLib/README.md)

Диграмма классов отражающая архитектуру приложения:

<img src="ClassDiagram.png" height="450">
