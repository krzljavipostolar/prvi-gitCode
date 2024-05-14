#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    int brUcenika;
    cout << "Unesite broj ucenika: ";
    cin >> brUcenika;
    cin.ignore();

    string ime_prezime[100];
    double prosjek[100];

    for (int i = 0; i < brUcenika; i++)
    {
        cout << "Unesite prosjek " << i + 1 << ". ucenika: ";
        cin >> prosjek[i];
        cin.ignore();
        cout << "Unesite ime i prezime " << i + 1 << ". ucenika: ";
        getline(cin, ime_prezime[i]);
    }

    for (int i = 0; i < brUcenika - 1; i++)
    {
        for (int j = i + 1; j < brUcenika; j++)
        {
            if (prosjek[i] < prosjek[j])
            {
                swap(prosjek[i], prosjek[j]);
                swap(ime_prezime[i], ime_prezime[j]);
            }
        }
    }

    fstream datotekaOut("ucenici.bin", ios::binary | ios::out);
    for (int i = 0; i < brUcenika; i++)
    {
        datotekaOut.write((char *)&prosjek[i], sizeof(double));
        int len = ime_prezime[i].size();
        datotekaOut.write((char *)&len, sizeof(int));
        datotekaOut.write((char *)&ime_prezime[i], sizeof(string));
    }
    datotekaOut.close();

    fstream datotekaIn("ucenici.bin", ios::binary | ios::in);
    for (int i = 0; i < brUcenika; i++)
    {
        string ime_prezime;
        double prosjek;
        datotekaIn.read((char *)&prosjek, sizeof(double));
        int len;
        datotekaIn.read((char *)&len, sizeof(int));
        char *buffer = new char[len + 1];
        datotekaIn.read(buffer, len);
        buffer[len] = '\0';
        ime_prezime = buffer;
        delete[] buffer;
        cout << ime_prezime << " " << prosjek << endl;
    }
    datotekaIn.close();
    return 0;
}