<p align="center">
  <img width="656" height="293" alt="fAD_logo" src="https://github.com/user-attachments/assets/65b504c6-c4b9-4264-ad90-d587012b1fae" />
</p>

# foxAndDot SDK V2.0.0

[Русский](#русский) | [English](#english)

---

## Русский

Встречайте новую и улучшенную версию SDK для разработки 2D игр на базе **SFML 3.1.0**

### Список изменений

- Новая сигнально-слотовая система (`Signal<args>` & `Slot<args, owner>`). Сигналы и слоты превратились в отдельные объекты. Слоты существуют в рамках своих владельцев, а не глобально.
- Появление игровой сцены (`Scene`). Теперь игровая сцена является отдельным от ядра (`Core`) объектом и предоставляет широкий интерфейс для манипулирования компонентами на ней.
- Переработана система коллизий. Добавление класса `Collider` позволяет вам писать собственные компоненты, обрабатывающие столкновения.
- Появление новых компонентов `Advanced_Entity`, `Advanced_Animated_Entity` и `Visualized_Collider`.
- Новая система скриптов для `Entity`.
- Несколько минорных нововведений в `Media_Manager`.

### Требования

- **SFML 3.1.0** (статически или динамически)
- Стандарт **ISO C++17** (`/std:c++17`)
- Многопоточная библиотека времени выполнения: `/MDd` для Debug, `/MD` для Release
- **Visual Studio 2022**, платформа **x64**

Описание интерфейсов классов находится в файлах заголовков.

### Инструкция по установке (Visual C++ 17 (2022))

1. Создайте пустой проект / консольное приложение.
2. Скачайте и подключите в проект **SFML версии 3.1.0 Visual C++ 17 (2022) 64-bit**, следуя инструкции с официального сайта.
3. Скачайте и распакуйте **foxAndDot SDK** последней версии.
4. Подключите foxAndDot SDK в ваш проект.
5. В Visual Studio щёлкните правой кнопкой мыши по проекту → **Свойства**, в верхней части установите для **Конфигурация** значение `Debug` или `Release`, для **Платформы** — `x64`.
6. **C/C++ → Общие → Дополнительные каталоги включаемых файлов**: добавьте путь к папке `include` из распакованного foxAndDot SDK.
7. **Компоновщик → Общие → Дополнительные каталоги библиотек**: добавьте путь к папке `lib` из распакованного foxAndDot SDK.
8. **Компоновщик → Ввод → Дополнительные зависимости**: вручную добавьте имя библиотечного файла `foxAndDot-SDK.lib`. Если в папке `lib` присутствуют файлы с суффиксом отладки (например, `-d`), в конфигурации Debug следует указать соответствующую отладочную версию.
9. Нажмите **Применить** и **ОК**, затем выполните сборку проекта, чтобы завершить подключение.

### Вопросы

Остались вопросы? — [a3shirnin@gmail.com](mailto:a3shirnin@gmail.com)

---

## English

Meet the new and improved version of the SDK for developing 2D games based on **SFML 3.1.0**

### List of changes

- A new signal-slot system (`Signal<args>` & `Slot<args, owner>`). Signals and slots have become separate objects. Slots exist within their owners, not globally.
- The introduction of the game scene (`Scene`). Now, the game scene is a separate object from the core (`Core`) and provides a broad interface for manipulating components on it.
- The collision system has been reworked. Adding the `Collider` class allows you to write custom components that handle collisions.
- The appearance of new components: `Advanced_Entity`, `Advanced_Animated_Entity`, and `Visualized_Collider`.
- A new scripting system for `Entity`.
- Several minor innovations in `Media_Manager`.

### Requirements

- **SFML 3.1.0** (statically or dynamically)
- **ISO C++17** standard (`/std:c++17`)
- Multithreaded runtime library: `/MDd` for Debug, `/MD` for Release
- **Visual Studio 2022**, **x64** platform

The description of the class interfaces is located in the header files.

### Installation Guide (Visual C++ 17 (2022))

1. Create an empty project / console application.
2. Download and connect **SFML version 3.1.0 Visual C++ 17 (2022) 64-bit** to the project, following the instructions on the official website.
3. Download and unpack the latest version of **foxAndDot SDK**.
4. Connect foxAndDot SDK to your project.
5. In Visual Studio, right-click on the project → **Properties**, at the top set **Configuration** to `Debug` or `Release`, and **Platform** to `x64`.
6. **C/C++ → General → Additional Include Directories**: add the path to the `include` folder from the unpacked foxAndDot SDK.
7. **Linker → General → Additional Library Directories**: add the path to the `lib` folder from the unpacked foxAndDot SDK.
8. **Linker → Input → Additional Dependencies**: manually add the library file name `foxAndDot-SDK.lib`. If the `lib` folder contains files with a debug suffix (e.g., `-d`), the corresponding debug version should be specified in the Debug configuration.
9. Click **Apply** and **OK**, then build the project to complete the connection.

### Questions

Any other questions? — [a3shirnin@gmail.com](mailto:a3shirnin@gmail.com)
