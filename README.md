<p align="center">
  <img width="656" height="293" alt="fAD_logo" src="https://github.com/user-attachments/assets/65b504c6-c4b9-4264-ad90-d587012b1fae" />
</p>

# foxAndDot SDK V2.0.0

![version](https://img.shields.io/badge/version-2.0.0-blue)
![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![platform](https://img.shields.io/badge/platform-Windows%20x64-lightgrey)
![SFML](https://img.shields.io/badge/SFML-3.1.0-green)
![license](https://img.shields.io/badge/license-MPL%202.0-orange)

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
7. **Компоновщик → Общие → Дополнительные каталоги библиотек**: добавьте путь к папке `lib/$(Configuration)` из распакованного foxAndDot SDK (то есть `lib/Debug` для конфигурации Debug и `lib/Release` для конфигурации Release). Макрос `$(Configuration)` автоматически подставит имя текущей конфигурации.
8. **Компоновщик → Ввод → Дополнительные зависимости**: добавьте имя библиотечного файла `foxAndDot-SDK.lib`. Так как файлы в папках `Debug` и `Release` называются одинаково, конкретная версия выбирается автоматически благодаря пути из пункта 7 — отдельно прописывать отладочную версию не нужно.
9. Нажмите **Применить** и **ОК**, затем выполните сборку проекта, чтобы завершить подключение.

### Лицензия

foxAndDot SDK распространяется под лицензией [Mozilla Public License 2.0](LICENSE).

**Коротко:**

- Библиотеку можно использовать бесплатно в любых проектах, в том числе в закрытых коммерческих играх.
- Если вы **изменяете файлы SDK** и распространяете результат, изменённые файлы нужно опубликовать под MPL 2.0.
- Свой код (игру, расширения, новые файлы) можно держать закрытым.
- Сохраняйте уведомление об авторских правах в файлах и сообщайте, где взять исходный код SDK.

**Просьба об упоминании.** Это не обязательно, но будет очень приятно: добавьте в титры или описание игры строку

> Made with foxAndDot SDK by waterofox — https://github.com/waterofox/foxAndDot-SDK

SDK построен на SFML (лицензия zlib/libpng, см. [`SFML-3.1.0/license.md`](<foxAndDot SDK/SFML-3.1.0/license.md>)). Подробности о сторонних компонентах: [THIRD_PARTY.md](THIRD_PARTY.md).

*Это краткое описание, а не юридический текст. Действует полный текст лицензии в файле [LICENSE](LICENSE).*

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
7. **Linker → General → Additional Library Directories**: add the path to the `lib/$(Configuration)` folder from the unpacked foxAndDot SDK (i.e. `lib/Debug` for the Debug configuration and `lib/Release` for the Release configuration). The `$(Configuration)` macro automatically substitutes the name of the current configuration.
8. **Linker → Input → Additional Dependencies**: add the library file name `foxAndDot-SDK.lib`. Since the files in the `Debug` and `Release` folders have the same name, the correct version is selected automatically via the path from step 7 — there is no need to specify a separate debug version.
9. Click **Apply** and **OK**, then build the project to complete the connection.

### License

foxAndDot SDK is distributed under the [Mozilla Public License 2.0](LICENSE).

**In short:**

- You may use the SDK for free in any project, including closed-source commercial games.
- If you **modify the SDK's files** and distribute the result, the modified files must be published under MPL 2.0.
- Your own code (your game, extensions, new files) can stay closed.
- Keep the copyright notices in the files and tell recipients where to get the SDK's source code.

**A request for credit.** Not required, but much appreciated: please add a line like this to your game's credits or description:

> Made with foxAndDot SDK by waterofox — https://github.com/waterofox/foxAndDot-SDK

The SDK is built on SFML (zlib/libpng license, see [`SFML-3.1.0/license.md`](<foxAndDot SDK/SFML-3.1.0/license.md>)). More about third-party components: [THIRD_PARTY.md](THIRD_PARTY.md).

*This is a summary, not legal text. The full license in [LICENSE](LICENSE) applies.*

### Questions

Any other questions? — [a3shirnin@gmail.com](mailto:a3shirnin@gmail.com)
