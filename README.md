# fifoserver-and-fifoclient
Wywołanie programu:

    program katalog

Każdy z programów przegląda zawartość katalogu, podanego jako argument wywołania, w poszukiwaniu plików typu FIFO (łącze nazwane). Po znalezieniu takiego pliku, pierwszy proces otwiera go do pisania, a drugi do czytania. Jeśli proces nie znajdzie żadnego pliku FIFO w podanym katalogu, to tworzy nowe łącze o nazwie odczytanej z terminala (prosi o podanie nazwy łącza).
Następnie, pierwszy proces odczytuje wiadomości z terminala (standardowe wejście stdin) i przesyła je przez łącze do drugiego procesu. Drugi proces odczytuje wiadomości z łącza i wyświetla je na terminalu (standardowe wyjście stdout). Procesy kończą działanie po odczytaniu z stdin i przesłaniu przez łącze ustalonego komunikatu (np. END).
