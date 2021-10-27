<div align="center">
Министерство науки и высшего образования Российской Федерации <br />
Федеральное государственное бюджетное образовательное учреждение <br />
высшего образования <br />
«Московский государственный технический университет <br />
имени Н.Э. Баумана <br />
(национальный исследовательский университет)» <br />
(МГТУ им. Н.Э. Баумана)
</div>
<hr />
<div align="center">
ФАКУЛЬТЕТ ИНФОРМАТИКА И СИСТЕМЫ УПРАВЛЕНИЯ <br />
КАФЕДРА КОМПЬЮТЕРНЫЕ СИСТЕМЫ И СЕТИ (ИУ6)
</div>
<br />
<div align="center">
ОТЧЕТ <br />
к лабораторной работе №2 <br />
по дисциплине "Современные средства разработки <br />
программного обеспечения" <br />
Реализация типовых решений с применением шаблонов проектирования.
</div>

<br />

Преподаватель: Фетисов М.В.

Студенты группы ИУ6-52Б Астахов Сергей Викторович, Лапшин Никита Валерьевич

## Описание задания

Задание: ШП Factory method (фабричный метод)

С использованием шаблона проектирования Factory method (фабричный метод)
выполните создание карточки из вашего домашнего задания и поместите ее в контейнер.
Выполните вывод содержимого контейнера в стандартный поток.

## Адрес проекта

Проект хранится в репозитории по адресу: [u6-52b-svastakhov-nvlapshin-l2](https://bmstu.codes/lsx/mstd/iu6-5-2021/iu6-52b-svastakhov-nvlapshin/l2).

## Диаграмма классов

![lab2](lab2.png)

## Функция main

```c++
int main(){
    vector<ICandidate*> candidates;
    CandidateFM candidateCreator;
    candidates.push_back(candidateCreator.create("Zhirinovsky V.V.", 75, 
        20000156, FRACTION_LDPR, 42345));
    candidates.push_back(candidateCreator.create("Kaz M.E", 36, 
        10000003, FRACTION_YABLOKO, 12043));
    candidates.push_back(candidateCreator.create("Zyganov G.A", 77, 
        15000002,FRACTION_KPRF, 24021));

    for(const auto cand: candidates){
        cout << cand->getFio() << endl
        << "Age: " << cand->getAge() << endl
        << "Income: " << cand->getIncome() << endl
        << "Fraction: " << cand->getFraction() << endl
        << "Voices: " << cand->getVoices() << endl
        << endl << endl;
    }

    return 0;
}
```

## Выводы

В данной лабораторной работе мы познакомились с основными ШП, а также реализовали на практике ШП Factory method (фабричный метод), позволяющий создавать объекты с заданным интерфейсом, абстрагируясь от их реализации.