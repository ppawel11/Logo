Budowa i kompilacja programu:
>cd build/
>cmake ..
>make

Uruchomienie testów:
>./TKOM_testing

Uruchomienie głównego programu:
>./TKOM  

W pliku qt_requirements.txt znajdują się nazwy modułów, które należy zainstalować w celu poprawnego działania wersji okienkowej programu. Na Ubuntu wszystkie z nich można zainstalować za pomocą apt (sudo apt install <nazwa modułu>). Po zainstalowaniu, należy zmienić opcję set(GUI 0) na set(GUI 1) wewnątrz pliku CMakeList.txt w celu zbudowania części graficznej. W tym momencie nie jest to potrzebne, bo powstał dopiero skromny zalążek tej części, stąd też pozwoliłem sobie na toporne zmienianie flagi w CMakeList.txt. W końcowej wersji programu coś takiego oczywiście nie będzie miało miejsca.
