/**
    Frățeanu Iustin-Alexandru
**/
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <windows.h>
#include <conio.h>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ull = unsigned ll;
using i128 = __int128;
using sint = short int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;
template<typename T>
using vvector = vector<vector<T>>;
template<typename K, typename V>
using umap = unordered_map<K, V>;
template<typename T>
using uset = unordered_set<T>;
template<typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename A, typename B>
using vp = vector<pair<A, B>>;
#define FAST ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define pb push_back
#define pf push_front
#define eb emplace_back
#define ef emplace_front
#define pob pop_back
#define pof pop_front
#define fs first
#define sd second
#define inf 0x3f3f3f3f
#define infll 0xfffffffffffffff
#define sz(v) (int)v.size()

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void clearScreen() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD written;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD cells = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, ' ', cells, {0,0}, &written);
    SetConsoleCursorPosition(hConsole, {0,0});
}

void setColor(WORD attributes) {
    SetConsoleTextAttribute(hConsole, attributes);
}

void setCursorPos(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(hConsole, coord);
}

int getKey() {
    int c = _getch();

    if (c == 0 || c == 224) {
        int arrow = _getch();

        switch (arrow) {
            case 72:
                return -1; ///sus
            case 80:
                return 1; ///jos
            case 75:
                return -2; ///stanga
            case 77:
                return 2; ///dreapta
        }
    }

    return c;
}

struct Nota {
    int val;
    string idd; ///ID_Disciplina
};

struct Student {
    string n, p, id, cls; ///nume, prenume, ID, clasa
    vector<Nota> note;
    map<string, pair<int, double>> medii;
    double mg = 0.0; ///medie_generala
};

ostream& operator<<(ostream& out, Nota& x) {
    return out << x.val << ", " << x.idd << "\n";
}

ostream& operator<<(ostream& out, Student& x) {
    return out << x.n << ", " << x.p << ", " << x.id << ", " << x.cls << "\n";
}

struct Disciplina {
    string id, nd; ///ID, nume_disciplina
    int cr; ///credite
};

ostream& operator<<(ostream& out, Disciplina& x) {
    return out << x.id << ", " << x.nd << ", " << x.cr << "\n";
}

vector<Student> s;
vector<Disciplina> d;

void add() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==== ADAUGARE STUDENT ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Introduceti pe cate o linie numele, prenumele, ID-ul si clasa(anul de studiu si litera clasei, de exemplu " << '"' << "11D" << '"' << ") studentului:\n";
    Student curr;
    getline(cin, curr.n);
    getline(cin, curr.p);
    getline(cin, curr.id);
    getline(cin, curr.cls);
    s.pb(curr);
    cout << "Student adaugat! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void del() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==== STERGERE STUDENT ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if (s.empty()) {
        cout << "Lista studentilor este goala. Operatiune imposibila. Apasati orice tasta ca sa va inotarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    cout << "Introduceti ID-ul studentului pe care doriti sa-l scoateti din sistem:\n";
    string str;
    getline(cin, str);

    int cnt = 0, poz = -1;
    for (int i = 0; i < sz(s); ++i) {
        if (s[i].id == str) {
            cnt++;

            if (cnt == 1) {
                poz = i;
            }
        }
    }

    if (cnt == 1) {
        s.erase(begin(s) + poz);
        cout << "Student scos din sistem! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    } else if (cnt == 0) {
        cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    } else {
    /// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            /** Atentie speciala necesara pt zona asta **/

    /// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        cout << "Mai multi studenti cu acelasi ID identificati. Va rugam sa introduceti numele studentului.\n";
        string str1;
        getline(cin, str1);
        cnt = 0;
        poz = -1;

        for (int i = 0; i < sz(s); ++i) {
            if (s[i].n == str1 && s[i].id == str) {
                cnt++;

                if (cnt == 1) {
                    poz = i;
                }
            }
        }

        if (cnt == 1) {
            s.erase(begin(s) + poz);
            cout << "Student scos din sistem! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
            int key = getKey();
            return;
        } else if (cnt == 0) {
            cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
            int key = getKey();
            return;
        } else {
            cout << "Mai multi studenti cu acelasi nume si ID identificati. Va rugam sa introduceti prenumele studentului.\n";
            string str2;
            getline(cin, str2);
            cnt = 0;
            poz = -1;

            for (int i = 0; i < sz(s); ++i) {
                if (s[i].p == str2 && s[i].n == str1 && s[i].id == str) {
                    cnt++;

                    if (cnt == 1) {
                        poz = i;
                    }
                }
            }

            if (cnt == 1) {
                s.erase(begin(s) + poz);
                cout << "Student scos din sistem! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                int key = getKey();
                return;
            } else if (cnt == 0) {
                cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                int key = getKey();
                return;
            } else {
                cout << "Mai multi studenti cu acelasi prenume, nume si ID. Va rugam sa introduceti clasa studentului.\n";
                string str3;
                getline(cin, str3);
                cnt = 0;
                poz = -1;

                for (int i = 0; i < sz(s); ++i) {
                    if (s[i].cls == str3 && s[i].p == str2 && s[i].n == str1 && s[i].id == str) {
                        cnt++;

                        if (cnt == 1) {
                            poz = i;
                        } else {
                            if (cnt == 2) {
                                cout << "Mai multi studenti identificati cu toate criteriile. Doriti sa stergeti toate aparitiile acestuia?\n(Y/N) ";
                                string rasp;
                                getline(cin, rasp);

                                if (!(rasp == "Y" || rasp =="y")) {
                                    cout << "Operatiune finalizata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                                    int key = getKey();
                                    return;
                                }
                            }

                            s.erase(begin(s) + poz);
                            poz = i;
                        }
                    }
                }

                if (cnt) {
                    s.erase(begin(s) + poz);

                    if (cnt == 1) {
                        cout << "Student scos din sistem! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                        int key = getKey();
                        return;
                    } else {
                        cout << "Toate aparitiile studentului au fost scoase din sistem! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                        int key = getKey();
                        return;
                    }
                } else {
                    cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                    int key = getKey();
                    return;
                }
            }
        }
    }
}

void modif() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==== MODIFICARE STUDENT ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if (s.empty()) {
        cout << "Lista studentilor este goala. Operatiune imposibila. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    cout << "Introduceti ID-ul studentului pe care doriti sa-l modificati:\n";
    string str;
    getline(cin, str);
    int cnt = 0, poz = -1;

    for (int i = 0; i < sz(s); ++i) {
        if (s[i].id == str) {
            cnt++;
            poz = i;
        }
    }

    if (cnt == 0) {
        cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    if (cnt > 1) {
        cout << "Mai multi studenti cu acelasi ID. Introduceti si numele:\n";
        string str1;
        getline(cin, str1);
        cnt = 0;
        poz = -1;

        for (int i = 0; i < sz(s); ++i) {
            if (s[i].id == str && s[i].n == str1) {
                cnt++;
                poz = i;
            }
        }

        if (cnt == 0) {
            cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
            int key = getKey();
            return;
        }

        if (cnt > 1) {
            cout << "Mai multi studenti identificati. Introduceti si prenumele:\n";
            string str2;
            getline(cin, str2);
            cnt = 0;
            poz = -1;

            for (int i = 0; i < sz(s); ++i) {
                if (s[i].id == str && s[i].n == str1 && s[i].p == str2) {
                    cnt++;
                    poz = i;
                }
            }

            if (cnt == 0 || cnt > 1) {
                cout << "Operatiune imposibila (identificare nereusita). Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                int key = getKey();
                return;
            }
        }
    }

    cout << "Student gasit: " << s[poz];
    cout << "Introduceti noile date pe cate o linie (nume, prenume, ID, clasa):\n";
    getline(cin, s[poz].n);
    getline(cin, s[poz].p);
    getline(cin, s[poz].id);
    getline(cin, s[poz].cls);
    cout << "Student modificat! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void af() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==== LISTARE STUDENTi ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if (s.empty()) {
        cout << "Niciun student nu a fost inca adaugat in sistem.\n\n";
    } else {
        cout << "Lista studentilor adaugati:\n";
        int cnt = 1;

        for (Student& stdnt : s) {
            cout << cnt << ". " << stdnt;
            cnt++;
        }
    }

    cout << "\nOperatiune finalizata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void src() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==== CAUTARE STUDENT ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Introduceti pe cate o linie numele, prenumele, ID-ul si clasa(anul de studiu si litera clasei, de exemplu " << '"' << "11D" << '"' << ") studentului:\n";
    Student curr;
    getline(cin, curr.n);
    getline(cin, curr.p);
    getline(cin, curr.id);
    getline(cin, curr.cls);
    vector<int> idx;

    for (int i = 0; i < sz(s); ++i) {
        if (s[i].n == curr.n && s[i].p == curr.p && s[i].id == curr.id && s[i].cls == curr.cls) {
            idx.pb(i + 1);
        }
    }

    if (idx.empty()) {
        cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    } else if (sz(idx) == 1) {
        cout << "Student unic in sistem aflat la pozitia " << idx[0] << ". Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    } else {
        cout << "Student gasit de mai multe ori pe pozitiile ";
        for (int i = 0; i < sz(idx); ++i) {
            cout << idx[i] << " ."[i == sz(idx) - 1];
        }

        cout << "Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    }

    int key = getKey();
    return;
}

void add1() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==== ADAUGARE NOTA ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Introduceti ID-ul studentului pentru care adaugati nota:\n";
    string id;
    getline(cin, id);
    bool ok = false;

    for (Student& x : s) {
        if (x.id == id) {
            ok = true;
            continue;
        }
    }

    if (!ok) {
        cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    cout << "Introduceti pe cate o linie nota si ID-ul disciplinei:\n";
    Nota curr;
    cin >> curr.val;
    cin.ignore();
    getline(cin, curr.idd);
    ok = false;

    for (Disciplina& x : d) {
        if (x.id == curr.idd) {
            ok = true;
            break;
        }
    }

    if (!ok) {
        cout << "Disciplina inexistenta. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    for (Student& x : s) {
        if (x.id == id) {
            x.note.pb(curr);
        }
    }

    cout << "Nota adaugata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void del1() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==== STERGERE NOTA ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Introduceti ID-ul studentului pentru care stergeti nota:\n";
    string id;
    getline(cin, id);
    bool ok = false;

    for (Student& x : s) {
        if (x.id == id) {
            ok = true;
            continue;
        }
    }

    if (!ok) {
        cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    for (Student& x : s) {
        if (x.id == id) {
            if (x.note.empty()) {
                cout << "Studentul nu are note. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                int key = getKey();
                return;
            }
        }
    }

    cout << "Introduceti pe cate o linie nota si ID-ul disciplinei:\n";
    Nota curr;
    cin >> curr.val;
    cin.ignore();
    getline(cin, curr.idd);
    ok = false;

    for (Disciplina& x : d) {
        if (x.id == curr.idd) {
            ok = true;
            break;
        }
    }

    if (!ok) {
        cout << "Disciplina inexistenta. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    ok = false;
    for (Student& x : s) {
        if (x.id == id) {
            for (int i = 0; i < sz(x.note); ++i) {
                Nota nt = x.note[i];

                if (nt.idd == curr.idd && nt.val == curr.val) {
                    x.note.erase(begin(x.note) + i);
                    ok = true;
                    break;
                }
            }
        }
    }

    if (!ok) {
        cout << "Nota inexistenta. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    cout << "Nota stearsa! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void modif1() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==== MODIFICARE NOTA ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Introduceti ID-ul studentului pentru care modificati nota:\n";
    string id;
    getline(cin, id);
    bool ok = false;

    for (Student& x : s) {
        if (x.id == id) {
            ok = true;
            break;
        }
    }

    if (!ok) {
        cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    for (Student& x : s) {
        if (x.id == id) {
            if (x.note.empty()) {
                cout << "Studentul nu are note. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                int key = getKey();
                return;
            }
        }
    }

    cout << "Introduceti pe cate o linie nota veche si ID-ul disciplinei:\n";
    Nota veche;
    cin >> veche.val;
    cin.ignore();
    getline(cin, veche.idd);
    ok = false;

    for (Disciplina& x : d) {
        if (x.id == veche.idd) {
            ok = true;
            break;
        }
    }

    if (!ok) {
        cout << "Disciplina inexistenta. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    ok = false;
    for (Student& x : s) {
        if (x.id == id) {
            for (int i = 0; i < sz(x.note); ++i) {
                if (x.note[i].idd == veche.idd && x.note[i].val == veche.val) {
                    cout << "Introduceti noua valoare a notei:\n";
                    int val_nou;
                    cin >> val_nou;
                    cin.ignore();
                    x.note[i].val = val_nou;
                    ok = true;
                    break;
                }
            }
        }
    }

    if (!ok) {
        cout << "Nota inexistenta. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    cout << "Nota modificata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void af1() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "==== LISTARE NOTE ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Introduceti ID-ul studentului pentru care listati notele:\n";
    string id;
    getline(cin, id);
    bool ok = false;

    for (Student& x : s) {
        if (x.id == id) {
            ok = true;
            continue;
        }
    }

    if (!ok) {
        cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    for (Student& x : s) {
        if (x.id == id) {
            if (x.note.empty()) {
                cout << "Studentul nu are note. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                int key = getKey();
                return;
            }
        }
    }

    cout << "Introduceti ID-ul disciplinei:\n";
    string idd, nume;
    getline(cin, idd);
    ok = false;

    for (Disciplina& x : d) {
        if (x.id == idd) {
            ok = true;
            nume = x.nd;
            break;
        }
    }

    if (!ok) {
        cout << "Disciplina inexistenta. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    vector<int> v;
    for (Student& x : s) {
        if (x.id == id) {
            for (int i = 0; i < sz(x.note); ++i) {
                Nota nt = x.note[i];

                if (nt.idd == idd) {
                    v.pb(nt.val);
                }
            }
        }
    }

    if (v.empty()) {
        cout << "Note inexistente. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    cout << "Lista notelor pe disciplina " << nume << ": ";
    for (int i = 0; i < sz(v); ++i) {
        cout << v[i] << " \n"[i == sz(v) - 1];
    }

    cout << "Operatiune finalizata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void Meniu1() {
    int selectat = 0;
    vector<string> opts = {"1. Adauga student", "2. Sterge student", "3. Modifica student", "4. Listare studenti", "5. Cauta student", "6. Adauga nota", "7. Stergere nota", "8. Modificare nota", "9. Lista notelor", "10. Inapoi la meniul principal"};

    while (true) {
        clearScreen();
        setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        setCursorPos(1, 1);
        cout << "==== MENIU STUDENTI ====";

        for (int i = 0; i < sz(opts); ++i) {
            if (i == selectat) {
                setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                setCursorPos(1, 3 + i);
                cout << ">";
            } else {
                setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }

            setCursorPos(4, 3 + i);
            cout << opts[i] << "\n";
        }

        int key = getKey();

        if (key == -1 && selectat) {
            selectat--;
        } else if (key == 1 && selectat + 1 < sz(opts)) {
            selectat++;
        } else if (key == 13) {
            switch (selectat) {
                case 0:
                    add();
                    break;
                case 1:
                    del();
                    break;
                case 2:
                    modif();
                    break;
                case 3:
                    af();
                    break;
                case 4:
                    src();
                    break;
                case 5:
                    add1();
                    break;
                case 6:
                    del1();
                    break;
                case 7:
                    modif1();
                    break;
                case 8:
                    af1();
                    break;
                case 9:
                    return;
            }
        }
    }
}

void add2() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "==== ADAUGARE DISCIPLINA ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Introduceti pe cate o linie ID-ul, numele si numarul de credite ale disciplinei:\n";
    Disciplina curr;
    getline(cin, curr.id);
    getline(cin, curr.nd);
    cin >> curr.cr;
    cin.ignore();
    d.pb(curr);
    cout << "Disciplina adaugata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void del2() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "==== STERGERE DISCIPLINA ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if (d.empty()) {
        cout << "Lista disciplinelor este goala. Operatiune imposibila. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    cout << "Introduceti ID-ul disciplinei pe care doriti sa o scoateti din sistem:\n";
    string str;
    getline(cin, str);
    int poz = -1;

    for (int i = 0; i < sz(d); ++i) {
        if (d[i].id == str) {
            poz = i;
            break;
        }
    }

    if (poz == -1) {
        cout << "Disciplina inexistenta. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    d.erase(begin(d) + poz);
    cout << "Disciplina scoasa din sistem! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void modif2() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "==== MODIFICARE DISCIPLINA ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if (d.empty()) {
        cout << "Lista disciplinelor este goala. Operatiune imposibila. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    cout << "Introduceti ID-ul disciplinei pe care doriti sa o modificati:\n";
    string str;
    getline(cin, str);
    int poz = -1;

    for (int i = 0; i < sz(d); ++i) {
        if (d[i].id == str) {
            poz = i;
            break;
        }
    }

    if (poz == -1) {
        cout << "Disciplina inexistenta. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    cout << "Disciplina gasita: " << d[poz];
    cout << "Introduceti noile date pe cate o linie (ID, nume, numar credite):\n";
    getline(cin, d[poz].id);
    getline(cin, d[poz].nd);
    cin >> d[poz].cr;
    cin.ignore();
    cout << "Disciplina modificata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void af2() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "==== LISTARE DISCIPLINE ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if (d.empty()) {
        cout << "Nicio disciplina nu a fost inca adaugata in sistem.\n\n";
    } else {
        cout << "Lista disciplinelor adaugate:\n";
        for (int i = 0; i < sz(d); ++i) {
            cout << i + 1 << ". " << d[i];
        }
    }

    cout << "\nOperatiune finalizata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void src2() {
    clearScreen();
    setCursorPos(1, 1);
    setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "==== CAUTARE DISCIPLINA ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Introduceti pe cate o linie ID-ul, numele si numarul de credite ale disciplinei:\n";
    Disciplina curr;
    getline(cin, curr.id);
    getline(cin, curr.nd);
    cin >> curr.cr;
    cin.ignore();
    vector<int> idx;

    for (int i = 0; i < sz(d); ++i) {
        if (d[i].id == curr.id && d[i].nd == curr.nd && d[i].cr == curr.cr) {
            idx.pb(i + 1);
        }
    }

    if (idx.empty()) {
        cout << "Disciplina inexistenta. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    } else if (sz(idx) == 1) {
        cout << "Disciplina unica in sistem aflata la pozitia " << idx[0] << ". Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    } else {
        cout << "Disciplina gasita de mai multe ori pe pozitiile ";
        for (int i = 0; i < sz(idx); ++i) {
            cout << idx[i] << " ."[i == sz(idx) - 1];
        }

        cout << "Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    }

    int key = getKey();
    return;
}

void Meniu2() {
    int selectat = 0;
    vector<string> opts = {"1. Adauga disciplina", "2. Sterge disciplina", "3. Modifica disciplina", "4. Listare discipline", "5. Cauta disciplina", "6. Inapoi la meniul principal"};

    while (true) {
        clearScreen();
        setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        setCursorPos(1, 1);
        cout << "==== MENIU DISCIPLINE ====";

        for (int i = 0; i < sz(opts); ++i) {
            if (i == selectat) {
                setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                setCursorPos(1, 3 + i);
                cout << ">";
            } else {
                setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }

            setCursorPos(4, 3 + i);
            cout << opts[i] << "\n";
        }

        int key = getKey();

        if (key == -1 && selectat) {
            selectat--;
        } else if (key == 1 && selectat + 1 < sz(opts)) {
            selectat++;
        } else if (key == 13) {
            switch (selectat) {
                case 0:
                    add2();
                    break;
                case 1:
                    del2();
                    break;
                case 2:
                    modif2();
                    break;
                case 3:
                    af2();
                    break;
                case 4:
                    src2();
                    break;
                case 5:
                    return;
            }
        }
    }
}

void med() {
    clearScreen();
    setColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    setCursorPos(1, 1);
    cout << "==== CALCULARE MEDIE PE STUDENT ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Introduceti pe cate o linie numele, prenumele, ID-ul si clasa(anul de studiu si litera clasei, de exemplu " << '"' << "11D" << '"' << ") studentului:\n";
    Student curr;
    getline(cin, curr.n);
    getline(cin, curr.p);
    getline(cin, curr.id);
    getline(cin, curr.cls);

    for (Student& x : s) {
        if (x.n == curr.n && x.p == curr.p && x.id == curr.id && x.cls == curr.cls) {
            if (x.note.empty()) {
                cout << "Imposibil de calculat media, studentul nu are note. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                int key = getKey();
                return;
            } else {
                x.mg = 0;
                for (Disciplina& ds : d) {
                    x.medii[ds.id] = make_pair(0, 0.0);
                }

                for (Nota& nt : x.note) {
                    x.medii[nt.idd].fs++;
                    x.medii[nt.idd].sd += (double)nt.val;
                }

                int cnt = 0;
                for (auto& it : x.medii) {
                    it.sd.sd /= it.sd.fs;
                    x.mg += it.sd.sd;
                    cnt++;
                }

                x.mg /= cnt;
                cout << "Media generala a studentului: " << fixed << setprecision(3) << x.mg << "\n";
                cout << "Media pe disciplina:\n";

                for (int i = 0; i < sz(d); ++i) {
                    cout << i + 1 << ". " << d[i].nd << ": " << x.medii[d[i].id].sd << "\n";
                }

                cout << "\nOperatiune finalizata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
                int key = getKey();
                return;
            }
        }
    }

    cout << "Student inexistent. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void med1() {
    clearScreen();
    setColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    setCursorPos(1, 1);
    cout << "==== CALCULARE MEDIE PE DISCIPLINA ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Introduceti ID-ul disciplinei:\n";
    string id, nume;
    getline(cin, id);
    bool ok = false;

    for (Disciplina& x : d) {
        if (x.id == id) {
            ok = true;
            nume = x.nd;
            break;
        }
    }

    if (!ok) {
        cout << "Disciplina inexistenta. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    int total_note = 0, suma = 0;
    for (Student& x : s) {
        for (Nota& nt : x.note) {
            if (nt.idd == id) {
                suma += nt.val;
                total_note++;
            }
        }
    }

    if (total_note == 0) {
        cout << "Nu exista note pentru aceasta disciplina. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    double medie = (double)suma / total_note;
    cout << "Media pe disciplina " << nume << ": " << fixed << setprecision(3) << medie << " (" << total_note << " note).\n";
    cout << "\nOperatiune finalizata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void top() {
    clearScreen();
    setColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    setCursorPos(1, 1);
    cout << "==== LISTAREA PRIMILOR STUDENTI ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    if (s.empty()) {
        cout << "Niciun student nu a fost inca adaugat in sistem. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
        int key = getKey();
        return;
    }

    cout << "Introduceti numarul de studenti pe care doriti sa-i vedeti:\n";
    int n;
    cin >> n;
    cin.ignore();
    vector<Student> v = s;
    sort(all(v), [](const Student& a, const Student& b) {
        return a.mg > b.mg;
    });
    int afis = min(n, sz(v));
    cout << "Primii " << afis << " studenti dupa media generala:\n";

    for (int i = 0; i < afis; ++i) {
        cout << i + 1 << ". " << v[i];
        cout << "   Media generala: ";
        if (v[i].mg == 0.0) {
            cout << "N/A\n";
        } else {
            cout << fixed << setprecision(3) << v[i].mg << "\n";
        }
    }

    cout << "\nOperatiune finalizata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void rep() {
    clearScreen();
    setColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    setCursorPos(1, 1);
    cout << "==== LISTAREA STUDENTILOR REPETENTI ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Introduceti tipul de afisare pe care il doriti (scrieti 1 sau 2):\n1. Pe media generala\n2. Pe disciplina\n";
    string rasp;
    getline(cin, rasp);

    if (rasp == "1") {
        vector<Student> v;
        for (Student& x : s) {
            if (x.mg > 0.0 && x.mg < 4.5) {
                v.pb(x);
            }
        }

        cout << "Sunt " << sz(v) << " studenti ce sunt repetenti pe criteriul de medie generala.";

        if (sz(v)) {
            cout << " Acestia sunt:\n";
            for (int i = 0; i < sz(v); ++i) {
                cout << i + 1 << ". " << v[i];
            }
        } else {
            cout << "\n";
        }
    } else {
        cout << "Introduceti ID-ul disciplinei: ";
        string id, nume;
        getline(cin, id);
        bool ok = false;

        for (Disciplina& x : d) {
            if (x.id == id) {
                nume = x.nd;
                ok = true;
                break;
            }
        }

        if (!ok) {
            cout << "Disciplina inexistenta. Apasati orice tasta ca sa va intoarceti la meniul anterior.";
            int key = getKey();
            return;
        }

        vector<Student> v;
        for (Student& x : s) {
            if (x.medii[id].fs && x.medii[id].sd < 4.5) {
                v.pb(x);
            }
        }

        cout << "Sunt " << sz(v) << " studenti ce sunt repetenti pe disciplina " << nume << ".";

        if (sz(v)) {
            cout << " Acestia sunt:\n";
            for (int i = 0; i < sz(v); ++i) {
                cout << i + 1 << ". " << v[i];
            }
        } else {
            cout << "\n";
        }
    }

    cout << "\nOperatiune finalizata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

static string now_str() {
    time_t t = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d/%m/%Y, %H:%M:%S", localtime(&t));
    return string(buf);
}

void exprt() {
    clearScreen();
    setColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    setCursorPos(1, 1);
    cout << "==== EXPORTARE DATE ====";
    setCursorPos(3, 3);
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    string data = now_str();
    ofstream fout("export.txt");
    fout << "Data exportarii: " << data << "\nNumar studenti: " << sz(s) << "\n\n";

    for (int i = 0; i < sz(s); ++i) {
        string t = "   ";
        fout << i + 1 << ". " << s[i] << t << "Media generala: ";

        if (s[i].mg == 0.0) {
            fout << "N/A\n";
        } else {
            fout << fixed << setprecision(3) << s[i].mg << "\n";
        }

        fout << t << "Medii pe disciplina: ";

        if (d.empty()) {
            fout << "N/A";

            if (!(i == sz(s) - 1)) {
                fout << "\n\n";
            }
        } else {
            fout << "\n";
            for (int j = 0; j < sz(d); ++j) {
                fout << t << t << j + 1 << ") " << d[j].nd << ": ";

                if (s[i].medii[d[j].id].fs) {
                    fout << s[i].medii[d[j].id].fs << "note, media = " << fixed << setprecision(3) << s[i].medii[d[j].id].sd;
                } else {
                    fout << "N/A";
                }

                if (!(i == sz(s) - 1 && j == sz(d) - 1)) {
                    fout << "\n";
                }
            }

            if (!(i == sz(s) - 1)) {
                fout << "\n";
            }
        }
    }

    cout << "\nOperatiune finalizata! Apasati orice tasta ca sa va intoarceti la meniul anterior.";
    int key = getKey();
    return;
}

void Meniu3() {
    int selectat = 0;
    vector<string> opts = {"1. Calculare medie pe student", "2. Calculare medie pe disciplina", "3. Listarea primilor studenti", "4. Listarea studentilor repetenti", "5. Exportare date", "6. Inapoi la meniul principal"};

    while (true) {
        clearScreen();
        setColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        setCursorPos(1, 1);
        cout << "==== MENIU RAPOARTE ====";

        for (int i = 0; i < sz(opts); ++i) {
            if (i == selectat) {
                setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                setCursorPos(1, 3 + i);
                cout << ">";
            } else {
                setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }

            setCursorPos(4, 3 + i);
            cout << opts[i] << "\n";
        }

        int key = getKey();

        if (key == -1 && selectat) {
            selectat--;
        } else if (key == 1 && selectat + 1 < sz(opts)) {
            selectat++;
        } else if (key == 13) {
            switch (selectat) {
                case 0:
                    med();
                    break;
                case 1:
                    med1();
                    break;
                case 2:
                    top();
                    break;
                case 3:
                    rep();
                    break;
                case 4:
                    exprt();
                    break;
                case 5:
                    return;
            }
        }
    }
}

void save() {
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    clearScreen();

    FILE* fout = freopen("student.txt", "w", stdout);
    for (int i = 0; i < sz(s); ++i) {
        cout << s[i];

        if (!s[i].note.empty()) {
            cout << sz(s[i].note) << "\n";
            for (auto& x : s[i].note) {
                cout << x;
            }

            cout << fixed << setprecision(3) << s[i].mg << "\n";
        }

        cout << "\n";
    }

    fclose(fout);
    fout = freopen("discipline.txt", "w", stdout);

    for (int i = 0; i < sz(d); ++i) {
        cout << d[i];
    }

    fclose(fout);
    exit(0);
}

void extract_saved_data() {
    {
        ifstream fin("student.txt");

        if (!fin || fin.peek() == ifstream::traits_type::eof()) {
            return;
        }

        string str;
        Student curr;
        bool ok = false;
        int ctn = 0;

        while (getline(fin, str)) {
            if (str == "\n" || str == "") {
                s.pb(curr);
                ok = false;
                continue;
            }

            if (!ok) {
                string t = "";
                int cnt = 0;

                for (int i = 0; i < sz(str); ++i) {
                    if (str[i] == ',' || str[i] == '\n') {
                        if (cnt == 0) {
                            curr.n = t;
                        } else if (cnt == 1) {
                            curr.p = t;
                        } else if (cnt == 2) {
                            curr.id = t;
                        } else {
                            curr.cls = t;
                        }

                        cnt++;
                        i++;
                        t = "";
                    } else {
                        t += str[i];
                    }
                }

                if (t != "") {
                    curr.cls = t;
                }

                ok = true;
            } else {
                string t = "";
                int cnt = 0;
                Nota nt;

                for (int i = 0; i < sz(str); ++i) {
                    if (str[i] == ',' || str[i] == '\n') {
                        if (cnt == 0) {
                            nt.val = stoi(t);
                        } else {
                            nt.idd = t;
                        }

                        cnt++;
                        i++;
                        t = "";
                    } else {
                        t += str[i];
                    }
                }

                if (cnt == 0) {
                    if (curr.note.empty()) {
                        curr.note.resize(stoi(t));
                    } else {
                        curr.mg = stod(t);
                    }
                } else {
                    if (t != "") {
                        nt.idd = t;
                    }

                    curr.note[ctn++] = nt;
                }
            }
        }
    }

    {
        ifstream fin("discipline.txt");

        if (!fin || fin.peek() == ifstream::traits_type::eof()) {
            return;
        }

        string str;
        Disciplina curnt;

        while (getline(fin, str)) {
            string t = "";
            int cnt = 0;

            for (int i = 0; i < sz(str); ++i) {
                if (str[i] == ',' || str[i] == '\n') {
                    if (cnt == 0) {
                        curnt.id = t;
                    } else if (cnt == 1) {
                        curnt.nd = t;
                    } else {
                        curnt.cr = stoi(t);
                    }

                    cnt++;
                    i++;
                    t = "";
                } else {
                    t += str[i];
                }
            }

            d.pb(curnt);
        }
    }
}

signed main() {
    ///FAST
    int selectat = 0;
    vector<string> opts = {"1. Studenti", "2. Discipline", "3. Rapoarte", "4. Salvare si iesire"};
    extract_saved_data();

    while (true) {
        clearScreen();
        setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        setCursorPos(1, 1);
        cout << "==== SISTEM DE GESTIONARE STUDENTI ====";
        setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        setCursorPos(3, 3);
        cout << "Folositi tastele sageata sus/jos pentru navigare si ENTER pentru selectare";

        for (int i = 0; i < sz(opts); ++i) {
            if (i == selectat) {
                setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                setCursorPos(1, 5 + i);
                cout << ">";
            } else {
                setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }

            setCursorPos(4, 5 + i);
            cout << opts[i] << "\n";
        }

        int key = getKey();

        if (key == -1 && selectat) {
            selectat--;
        } else if (key == 1 && selectat + 1 < sz(opts)) {
            selectat++;
        } else if (key == 13) {
            switch (selectat) {
                case 0:
                    Meniu1();
                    break;
                case 1:
                    Meniu2();
                    break;
                case 2:
                    Meniu3();
                    break;
                case 3:
                    save();
            }
        }
    }
}
