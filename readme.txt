###################################
Universität Augsburg
Institut für Informatik
Fakultät für Angewandte Informatik
Übung zur Vorlesung Informatik 1
Semesteraufgabe WiSe 2023/2024
###################################

Systembeschreibung B: Gleitkommacodierung
Abgabe von: Philipp Köhn (2229902), Sebastian Traub (2226828)

###################################

1. Hinweise zur Funktionalität des Programms

Dieses Programm richtet sich an alle Informatik-Interessierten, die ihr Wissen bezüglich
der Gleitkommacodierung auffrischen wollen.

Es wird eine Anwendung für die Codierung und Decodierung von reellen Zahlen bzgl. der
Gleitkomma-Codierung mit und ohne Darstellung der zugehörigen Rechnung zur Verfügung 
gestellt. Dabei können folgende Codierungen verwendet werden:
        cGK,5,8, cGK,11,16, cGK,24,32
Die Anwendung kann mit der Eingabe von reellen Zahlen sowohl als Bitmuster als auch als
Dezimalzahl in Fest- und Gleitkomma-Schreibweise umgehen.
Außerdem kann die Addition und Subtraktion von zwei reellen Zahlen dargestellt werden.

Dabei kann der Benutzer zwischen einer simplen Ausgabe des Ergebnissen der gewuensch-
ten Operation oder einer interaktiven Schritt-für-Schritt-Ausführung von Rechnungen
und (De-)Codierungen wählen. 

Die besonders schoene und durchdachte textuelle Benutzerschnittstelle mit Benutzer-
fuehrung bietet Lernenden einen kompakten Einstieg in das Thema.
Um auch internationalen Interessierten einen Einblick in die Welt der Gleit-
kommacodierung zu geben, wurde das Programm in englischer Sprache geschrieben.

###################################

2. Hinweise zur Ausführung des Programms

Bei der Programmierung wurde insbesondere auf eine sinnvolle Strukturierung des
Quellcodes geachtet. Dies dient insbesondere der besseren Wartung und Erweiter-
barkeit des Programms.

Aus diesem Grund müssen mehrere .c-Dateien kompiliert werden:
Im ZIP-Archiv befinden sich das Hauptprogramm "main_testing.c", das gemeinsam
mit den zugehörigen anderen .c-Dateien kompiliert werden muss.

Wir stellen im zip-Archiv aber schon die entsprechenden Übersetzungseinheiten
zur Verfügung, die dann wie folgt kompiliert werden müssen:

        headers>gcc main_testing.c -o gleitkomma arithmetic.o bits.o decode.o 
        encode.o menu_util.o print_util.o read_util.o -Wall -Wextra -ansi -pedantic 
        -I arithmetic -I bits -I decode -I encode -I menu -I print -I read

Mit Ausführung dieses Befehls wird eine Datei "gleitkomma.exe" erstellt.
Die Ausführung ist Windows-kompatibel, daher kann es auf anderen Betriebs-
systemen zu Abweichungen kommen.

Sollte das Kompilieren der .o-Dateien nicht funktionieren, bitte die Übersetzungs-
einheiten selbst kompilieren und o.g. Schritt wiederholen:

        headers>gcc -c main_testing.c arithmetic\arithmetic.c bits\bits.c
        decode\decode.c encode\encode.c menu\menu_util.c print\print_util.c
        read\read_util.c -Wall -Wextra -ansi -pedantic
        -I arithmetic -I bits -I decode -I encode -I menu -I print -I read



