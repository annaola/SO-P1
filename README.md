# SO-P1
Pracownia z systemów operacyjnych

Zespół: Anna Biadasiewicz, Michał Martusewicz


## Problem ucztujących filozofów

### Podstawowy problem
Pięciu filozofów siedzi przy stole i wykonuje jedną z dwóch czynności - je albo rozmyśla. Stół jest okrągły, przed każdym z filozofów postawiono miseczkę z ryżem. Między każdą parą filozofów leży pałeczka do ryżu. Do jedzenia każdy filozof potrzebuje dwóch pałeczek. Oczywiście, może korzystać tylko z pałeczek znajdujących się tuż obok niego. Gdy filozof przestaje rozmyślać, sięga kolejno po jedną i drugą pałeczkę, pod warunkiem, że jest to możliwe.
Brak pałeczek jest analogią do braku dostępu do plików.

#### Potencjalne problemy
Filozofowie nie rozmawiają ze sobą, co stwarza zagrożenie impasu (gdy każdy z filozofów trzyma jeden widelec) lub zagłodzenia (gdy jeden z filozofów w ogóle nie otrzymuje dostępu do pałeczek).

#### Rozszerzenie problemu
Rozważamy problem dla dowolnej ustalonej liczby filozofów i dowolnej ustalonej liczby pałeczek.

### Możliwe rozwiązanie (wg Chandy/Misra)
Filozofowie są ponumerowani od 1 do ustalonego n. Pałeczki mogą być *czyste* lub *brudne*.
  1. Dla każdej pary ubiegającej się o dostęp do zasobów, tworzymy brudną pałeczkę i przekazujemy ją filozofowi o niższym numerze.
  2. Kiedy filozof chce zjeść, próbuje uzyskać pałeczki od sąsiadów. Jeśli jest to niemożliwe, wysyła żądanie, aby je otrzymać.
  3. Jeśli filozof otzymuje żądnie o pałeczkę, ma dwie możliwości:
    * zatrzymać ją, jeśli jest czysta
    * przekazać sąsiadowi, jeśli jest brudna.
  Przed przekazaniem pałeczki, filozof musi ją wyczyścić.
  4. Gdy filozof kończy jeść, pałeczki stają się brudne.

### Praktyczne uzasadnienie realizowanego problemu
???

*Na podstawie: https://en.wikipedia.org/wiki/Dining_philosophers_problem*
