# Neuronale Netze in C/C++

Dies ist das Repository für den **LinkedIn Learning** Kurs `Neuronale Netze in C/C++`. Den gesamten Kurs finden Sie auf [LinkedIn Learning][lil-course-url].

![COURSENAME][lil-thumbnail-url] 

Neuronale Netze sind ein wesentlicher Bestandteil der künstlichen Intelligenz (KI), da sie die Funktionsweise des menschlichen Gehirns nachahmen und es ermöglichen, komplexe Muster und Zusammenhänge in Daten zu erkennen und zu lernen.<br><br>

In diesem LinkedIn Learning Kurs richtet sich der erfahrene Maschinenbau-ingenieur und Entwickler Dr. Gerhard Stein an fortgeschrittene C/C++-Entwickler:innen und erläutert, wie die einzelnen Disziplinen miteinander funktionieren und wie C++ zum Beispiele auch seine Vorteile gegenüber Python optimal nutzen kann. Am Ende des Kurses werden Sie eigene Netze bauen und bei Themen des Machine Learning mitreden können.

Mit der Hilfe von praktischen Challenge/Solution-Einheiten am Ende der Kapitel können Sie ihr Wissen immer wieder überprüfen und Ihre Lösung mit der Ihres Trainers vergleichen.


## Anleitung

Dieses Repository hat Branches für jedes Video im Kurs. Verwenden Sie das Ausklappmenü "Branch: ..." in GitHub um zwischen den unterschiedlichen Branches hin und her zu wechseln bzw. um bei einem spezifischen Status einzusteigen. Oder Sie fügen `/tree/BRANCH_NAME` der URL hinzu um direkt in den gewünschten Branch zu wechseln.

## Branches

Die Git Branches sind passend zu den Videos im Kurs strukturiert. Die Namenskonvention lautet `Kapitel#_Video#`. Der Branch `02_03` beinhaltet zum Beispiel die Übungen für das dritte Video im zweiten Kapitel. 
Einige Branches haben einen Anfangsstatus (`b`) für "beginning" und einen Endstatus (`e`). Der Branch mit dem `e` am Ende beinhaltet in diesem Fall stets den Code der am Ende des Videos zu sehen ist. Der `master` Branch beinhaltet den initialen Quellcode und wird nicht für die Übungen innerhalb des Kurses genutzt.

Wenn Sie von einem Branch nach Änderungen zum nächsten Branch wechseln, erhalten Sie möglicherweise die folgende Meldung:

```
error: Your local changes to the following files would be overwritten by checkout:        [files]
Please commit your changes or stash them before you switch branches.
Aborting
```

Dieses Problem lösen Sie wie folgt:
    Add changes to git using this command: git add .
    Commit changes using this command: git commit -m "some message"

## Installation

1. Klonen Sie das Repository in Ihre lokale Maschine unter Verwendung von terminal (Mac), CMD (Windows) oder ein anderes Werkzeug mit grafischer Bedienoberfläche wie SourceTree.

### Autor

**Gerhard Stein**

_Head of Product Development_

Sehen Sie sich andere Kurse des Autors auf [LinkedIn Learning](https://www.linkedin.com/learning/instructors/dr-gerhard-stein) an.

[0]: # (Replace these placeholder URLs with actual course URLs)
[lil-course-url]: https://www.linkedin.com/learning/neuronale-netze-in-c-c-plus-plus
[lil-thumbnail-url]: https://media.licdn.com/dms/image/v2/D4E0DAQGmvP-OSH1MyA/learning-public-crop_675_1200/learning-public-crop_675_1200/0/1731415559840?e=2147483647&v=beta&t=YrFdDUCIkeAlFOGFMwFb_8EE3B47O9MbCqTEKxqsy-I
