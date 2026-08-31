# foxAndDot SDK V2.0.0

Встречайте новую и улучшенную версию SDK для разработки 2D игр на базе **SFML 3.1.0**
[foxAndDot-SDK-v2.0.0-windows-x64.zip](https://github.com/user-attachments/files/31662788/foxAndDot-SDK-v2.0.0-windows-x64.zip)

## Список изменений

- Новая сигнально-слотовая система (`Signal<args>` & `Slot<args, owner>`). Сигналы и слоты превратились в отдельные объекты. Слоты существуют в рамках своих владельцев, а не глобально.
- Появление игровой сцены (`Scene`). Теперь игровая сцена является отдельным от ядра (`Core`) объектом и предоставляет широкий интерфейс для манипулирования компонентами на ней.
- Переработана система коллизий. Добавление класса `Collider` позволяет вам писать собственные компоненты, обрабатывающие столкновения.
- Появление новых компонентов `Advanced_Entity`, `Advanced_Animated_Entity` и `Visualized_Collider`.
- Новая система скриптов для `Entity`.
- Несколько минорных нововведений в `Media_Manager`.

## Перед началом работы

Перед началом работы с библиотекой AndDot SDK вам также необходимо выполнить следующие действия:

- Подключить **SFML 3.1.0** (статически или динамически)
- Убедиться в том, что в конфигурации проекта выбран стандарт **ISO C++17** (`/std:c++17`)
- Убедиться в том, что в конфигурации проекта выбрана многопоточная отладочная библиотека времени выполнения (`/MDd`)

Описание интерфейсов классов находится в файлах заголовков.

## Вопросы

Остались вопросы? — [a3shirnin@gmail.com](mailto:a3shirnin@gmail.com)

=======================================================================================

Meet the new and improved version of the SDK for developing 2D games based on **SFML 3.1.0**
[foxAndDot-SDK-v2.0.0-windows-x64.zip](https://github.com/user-attachments/files/31662788/foxAndDot-SDK-v2.0.0-windows-x64.zip)

## List of changes

- A new signal-slot system (`Signal<args>` & `Slot<args, owner>`). Signals and slots have become separate objects. Slots exist within their owners, not globally.
- The introduction of the game scene (`Scene`). Now, the game scene is a separate object from the core (`Core`) and provides a broad interface for manipulating components on it.
- The collision system has been reworked. Adding the `Collider` class allows you to write custom components that handle collisions.
- The appearance of new components: `Advanced_Entity`, `Advanced_Animated_Entity`, and `Visualized_Collider`.
- A new scripting system for `Entity`.
- Several minor innovations in `Media_Manager`.

## Before you begin

Before you start working with the AndDot SDK library, you also need to perform the following actions:

- Include **SFML 3.1.0** (statically or dynamically)
- Make sure that the **ISO C++17** standard (`/std:c++17`) is selected in the project configuration
- Make sure that the multithreaded debug runtime library (`/MDd`) is selected in the project configuration

The description of the class interfaces is located in the header files.

## Questions

Any other questions? — [a3shirnin@gmail.com](mailto:a3shirnin@gmail.com)
