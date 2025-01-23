# code-examples

Репозиторий содержит примеры для MIPS-процессоров компании АО НПЦ "ЭЛВИС" в среде разработки MCStudio:

* [1892ВМ206](./mcstudio/1892vm206/README.md)

Сборка выполняется в [MCStudio](https://support.elvees.com/docs/Soft/mcstudio). Для отладки можно использовать [утилиту mdb](https://support.elvees.com/docs/Soft/#mdb).

## Подготовка среды

1. Скачать [MCStudio](https://support.elvees.com/docs/Soft/mcstudio).
2. Установить на Linux CentOS 8 или Windows 10/11.
3. Выгрузить данный репозиторий (git clone, либо zip архив).
4. Для запуска примеров на отладочной плате требуется установка драйверов mjtag (в составе mdb) и [утилита mdb](https://support.elvees.com/docs/Soft/#mdb).

## Сборка примеров

Сборка примеров может производиться как из графической оболочки MCStudio, так и командой из терминала.

### Примеры из этого репозитория

#### GUI

1. File &rarr; Open Projects from File System...
2. Выбрать пример в файловой системе.
3. Project &rarr; Build Project.

#### Terminal

1. Перейти в папку с распакованной MCStudio.
2. Сборка производится командой (на примере [MCStudio DEMO](https://nc2.elvees.com/index.php/s/6zjeDTjNr5x5Np4)):

```bash
LD_LIBRARY_PATH=`pwd`/MCStudio_DEMO_2024.09_70/ToolsMGCC/local/lib \
MCS4_HOME=`pwd`/MCStudio_DEMO_2024.09_70 \
./MCStudio_DEMO_2024.09_70/eclipse/eclipse -nosplash \
    -application org.eclipse.cdt.managedbuilder.core.headlessbuild \
    -importAll <projects_path> -build <project_name>
```

* `projects_path` - путь до папки с примерами
* `project_name` - имя (регулярное выражение) названия проекта, либо `all` - собрать все примеры в папке projects_path

### Примеры, встроенные в MCStudio

#### GUI

1. Help &rarr; Multicore Studio &rarr; Примеры проектов &rarr; (Выбор процессора) &rarr; (Выбор примера)

2. Project &rarr; Build Project.

#### Terminal

1. Сборка производится командой (на примере MCStudio DEMO):

```bash
LD_LIBRARY_PATH=`pwd`/MCStudio_DEMO_2024.09_70/ToolsMGCC/local/lib \
MCS4_HOME=`pwd`/MCStudio_DEMO_2024.09_70 \
./MCStudio_DEMO_2024.09_70/eclipse/eclipse -nosplash \
    -application org.eclipse.cdt.managedbuilder.core.headlessbuild \
    -importAll ./MCStudio_DEMO_2024.09_70/SAMPLES/<chip> -build <project_name>
```

* `chip` - путь до папки с примерами для конкретного процессора
* `project_name` - имя (регулярное выражение) названия проекта, либо `all` - собрать все примеры в папке chip.

## Запуск на плате

Запуск примеров может производиться как из графической оболочки, так и с использованием [утилиты mdb](https://support.elvees.com/docs/Soft/#mdb) (порядок запуска - в [руководстве пользователя mdb](https://nc2.elvees.com/index.php/s/bkLjKqpra5rPaXJ)).

> [!WARNING]
> Запуск отладки с использованием эмулятора невозможен в MCStudio DEMO.

Запуск из GUI:

1. Собрать проект (Project &rarr; Build Project).
2. Подключить отладчик [MC-USB-JTAG](https://support.elvees.com/docs/Solutions/MC-USB-JTAG) к ПК и отладочному модулю, подать питание питание на модуль.
3. Run &rarr; Debug Configurations...
4. В всплывающем окне добавить новую конфигурацию (New launch configuration). В поле Project выбрать проект, в поле Executable file выбрать исполняемый файл (по умолчанию файл вида <project_name>.elf в директории MultiCore_Configuration_Debug). Выбрать Emulator, Target (внутреннее название процессора), проверить наличие отладчика в Connected targets.
5. При необходимости (см. README в папке с примером) внести изменения в файл GDB Init.
6. Нажать Apply для применения изменений, Debug для запуска отладки.
