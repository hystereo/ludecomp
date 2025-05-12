# Zrównoleglenie rozkładu LU za pomocą OpenACC
<h2>Opis</h2> Projekt polega na równoległej implementacji rozkładu LU, algorytmu powszechnie stosowanego w analizie numerycznej do rozwiązywania układów równań liniowych. Rozkład LU dzieli macierz na dwie macierze trójkątne: dolną (L) i górną (U), co umożliwia rozwiązywanie układów równań, obliczanie odwrotności macierzy oraz wyznaczanie wyznacznika.
W projekcie wykorzystano OpenACC do równoległego przetwarzania, co pozwala na znaczne przyspieszenie obliczeń na procesorach graficznych (GPU). Program dzieli macierz na bloki, które są przetwarzane równolegle, co znacząco poprawia wydajność przy dużych macierzach. Implementacja może działać na różnych zestawach sprzętowych, w tym na systemach lokalnych z akceleracją GPU.

<h2>Języki i narzędzia użyte w projekcie</h2>

<b>C++</b> (do implementacji)

<b>OpenACC</b> (do równoległości)


<h2>Środowiska użyte w projekcie</h2>

<b>Linux</b>

<b>GPU kompatybilne z OpenACC</b> (GPU obsługujące CUDA)

<b>g++/nvcc</b>
