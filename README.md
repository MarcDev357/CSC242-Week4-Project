# Assignment 5 — Comprehensive Program Challenge (Signature Assignment)

C++ Streams projects for CSC242. Two programs from *Big C++: Late Objects, Enhanced*, Chapter 8: a spell checker (P8.2) and a random monoalphabet cipher (P8.7).

## Team

| Member | Owns |
|--------|------|
| Marcus Wiggs (lead/integrator) | Spell Checker (P8.2), entire project — `normalize`, `loadDictionary`, `checkFile`, `main` |
| David Cruz | Cipher (P8.7) — `buildCipherAlphabet`, `transformChar` |
| Cassius Miller | Cipher (P8.7) — `parseArguments`, `processFile`, `main` |

The lead owns `main`, performs final merges, builds the submission zip, and confirms both projects compile clean before everyone submits.

## Repository structure

```
/SpellChecker/      Visual Studio project for P8.2
/Cipher/            Visual Studio project for P8.7
/docs/              Pseudocode Word document
.gitignore          Visual Studio template (ignores bin/, obj/, .vs/, *.user)
README.md
TEAM_WORKFLOW.md    How we use Git on this project — read it first
```

## P8.2 — Spell Checker

Reads every word of a target file and prints any word not found in the system dictionary (`/usr/share/dict/words`).

**Functions:** `normalize`, `loadDictionary`, `checkFile`, `main`

**Run:** launch the program, then enter the name of the file to check when prompted.

## P8.7 — Monoalphabet Cipher

Encrypts or decrypts a file using a keyword-derived substitution alphabet (keyword letters first with duplicates removed, then the rest of the alphabet in reverse order).

**Functions:** `buildCipherAlphabet`, `transformChar`, `parseArguments`, `processFile`, `main`

**Run (command line):**
```
crypt -kFEATHER input.txt output.txt        encrypt with keyword FEATHER
crypt -d -kFEATHER output.txt restored.txt  decrypt
```
A keyword is required (`-k`). Default mode is encrypt; `-d` switches to decrypt.

**Sanity test:** encrypting a file then decrypting the result with the same keyword should return the original text exactly.

## Author attribution

Every function carries an inline author comment, e.g.:

```cpp
// ----- Author: David Cruz -----
string buildCipherAlphabet(const string& keyword) {
```

The commit history is the backup record of who wrote what — keep commits honest (each person pushes their own work).

