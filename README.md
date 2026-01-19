# IZP – Projekt 1: Práce s textem

Riešenie 1. projektu z predmetu IZP (Základy programování) na FIT VUT.

## Obsah úlohy
- **T9 Vyhledávání** – emulace hledání kontaktů v telefonním seznamu pomocí číselné sekvence.
- **Filtrace dat** – vyhledávání v jménech i číslech (case insensitive).
- **Práce se vstupy** – načítání neuspořádaných ASCII dat ze standardního vstupu.
- **Statická alokace** – implementace bez použití dynamické paměti (`malloc`).

Projekt bol vytvorený výlučne na vzdelávacie účely.

## Hodnotenie
- Získané body: **7.28 / 10**

---

<details>
<summary><b>Zobrazit kompletní zadání</b></summary>

### Motivační příklad
Cílem projektu je vytvořit program, který by emuloval zjednodušený algoritmus hledání kontaktů zadaných pomocí posloupnosti číslic (jako na starých tlačítkových telefonech).

### Popis projektu
Vstupem programu je posloupnost číslic. Výstup programu bude obsahovat seznam kontaktů, které odpovídají zadanému číselnému filtru.

### Specifikace
- **Soubor:** `tnine.c`
- **Překlad:** `gcc -std=c11 -Wall -Wextra -Werror tnine.c -o tnine`
- **Spuštění:** `./tnine CISLO`

### Kritérium nalezení kontaktu
Hledání **nepřerušené posloupnosti** znaků. Číslice mapují znaky následovně:
- 2 (abc), 3 (def), 4 (ghi), 5 (jkl)
- 6 (mno), 7 (pqrs), 8 (tuv), 9 (wxyz), 0 (+)

### Formát výstupu
1. **Kontakt nenalezen:** Vypíše `Not found`.
2. **Kontakt nalezen:** Vypíše řádek ve formátu `JMENO, TELCISLO`.

### Omezení
- **Zakázané funkce:** `malloc`, `free`, `fopen`, `fscanf` (práce s dynamickou pamětí a externími soubory).
- **Vstup:** Data čtena ze `stdin`.
- **Délka řádku:** Program musí podporovat alespoň 100 znaků.

### Příklad použití
```bash
$ ./tnine 12 < seznam.txt
petr dvorak, 603123456
bedrich smetana ml., 541141120
