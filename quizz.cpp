#include <iostream>
#include <ctime>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

void hasil();
void rules();
void random_question();
void cek_jawaban(char jawaban, char JawabanBenar);
void saveResultsToFile();

struct Question {
    string soal;
    string opsi_a;
    string opsi_b;
    string opsi_c;
    string opsi_d;
    char jawaban;
    bool availability;
};

Question questions[10];
string player;
bool pay_half_skip = true;
bool skip = true;
long cash = 0;
long question_value = 100;
int consective = 0;
int jawaban_benar = 0;
int jawaban_salah = 0;
int question_no = 1;

int main()
{
    system("cls");
    questions[0] = {"Huruf ke-empat dari abjad adalah... " ,
    "a",
    "b",
    "c",
    "D",
    'a', true };
    
    questions[1] = {"Saat dibalik aku akan berkurang tiga " ,
    "6",
    "7",
    "8",
    "9",
    'd', true };
    
    questions[2] = {"Kenapa Motor berhenti di lampu merah? " ,
    "Lampu sedang berwarna Merah",
    "Karena di rem",
    "Motornya mogok",
    "Takut Ketilang",
    'b', true };

    questions[3] = {"Binatang apa yang jago berenang? " ,
    "ikan",
    "hiu",
    "bebek",
    "lumba-lumba",
    'c', true };

    questions[4] = {"Olahraga apa yang paling berat?" ,
    "Angkat Beban",
    "Maraton",
    "Badminton",
    "Catur",
    'd', true };

    questions[5] = {"Apa yang senang di dapati, tetapi susah dibuang?" ,
    "Kekasih",
    "Sampah",
    "Masalah",
    "Tiket bioskop",
    'c', true };

    questions[6] = {"Buah-buah apa yang tidak punya otak?" ,
    "Pisang",
    "Semangka",
    "Cucumis melo",
    "Semua benar",
    'd', true };
   
    questions[7] = {"Apa yang selau menjadi korban pemerasan?" ,
    "Rakyat",
    "Baju",
    "Sapi",
    "kain",
    'c', true };

    questions[8] = {"Tau gak angin warnanya apa?" ,
    "merah",
    "putih",
    "bening",
    "coklat",
    'a', true };

    questions[9] = {"Kapan unesa didirikan?" ,
    "19 Desember 1967",
    "19 Desember 1964",
    "18 Desember 1964",
    "19 November 1964",
    'b', true };

    std::cout << "=====================================================" << std::endl;
    std::cout << "================== WELCOME TO THE ===================" << std::endl;
    std::cout << "================== J2n GAME SHOW ====================" << std::endl;
    std::cout << "=====================================================" << std::endl;
    cout << "Ketik Jenengmu!: ";
    getline(cin, player);
    system("cls");
    rules();

    while (true) {
        if (question_no > 10)
            break;
        random_question();
    }
    hasil();
    saveResultsToFile();
    return 0;
}

void random_question() {
    srand(time(0));
    while (true) {
        system("cls");
        int number = rand() % 10;
        if (questions[number].availability) {
            questions[number].availability = false;
            cout << "=====================================================" << endl;
            cout << "================== J2n GAME SHOW ====================" << endl;
            cout << endl;
            cout << "Soal: " << question_no << " untuk " << question_value << "koin" << "\t\t\t\tBalance =" << cash << "koin" << endl;
            cout << "Nyawa:" ;
            if(pay_half_skip)
                cout << "\th=>PAY HALF dan SKIP";
            if(skip)
                cout << "\tl=>LEAVE QUESTION" ;
            cout << endl << endl;
            cout << "=====================================================" << endl;
            cout << "================== PILIH OPSIMU =====================" << endl;
            cout << questions[number].soal << endl << endl;
            cout << "a) " << questions[number].opsi_a 
                    << "\t\tb)" << questions[number].opsi_b << endl << endl;
            cout << "c) " << questions[number].opsi_c 
                    << "\t\td)" << questions[number].opsi_d << endl << endl;
            char answer = _getche();
            answer = tolower(answer);
            cout << endl;
            question_no++;
            cek_jawaban(answer, questions[number].jawaban);
            break;
        }
    }
}

void cek_jawaban(char answer, char JawabanBenar) 
{
    if (answer == JawabanBenar) 
    {
        cout << " Selamat...! Jawabannya kamu benar" << endl;
        cout << " Kamu dapat " << question_value << "koin" << endl;
        cout << " Tekan apapun untuk lanjut..." << endl;
        _getch();
        jawaban_benar ++;
        consective ++;
        cash = cash + question_value;
    }

    else if((answer == 'h') && (pay_half_skip))
    {
        cout << " Kamu pilih 'PAY HALF dan SKIP'" << endl;
        cout << " Kamu kehilangan " << question_value/4 << "koin" << endl;
        cout << " Tekan apapun untuk lanjut..." << endl;
        _getch();
        cash = cash - (question_value/4);
        pay_half_skip = false;
    } 

    else if((answer == 'l') && (skip))
    {
        cout << " Kamu pilih 'LEAVE QUESTION'" << endl;
        cout << " Kamu kehilangan 0 koin" << endl;
        cout << " Tekan apapun untuk lanjut..." << endl;
        _getch();
        skip = false;
    } 

    else 
    {
        cout << " Maaf...! Jawaban anda salah." << endl;
        cout << " Kamu kehilangan "<< question_value/2 << "koin"  << endl;
        cout << " Tekan apapun untuk lanjut..." << endl;
        _getch();
        jawaban_salah ++;
        consective = 0;
        cash = cash - (question_value/2);
    }

    question_value = question_value*2;
    if (consective == 3)
    {
        pay_half_skip = true;
    }
    if (consective == 5)
    {
        skip = true;
    }
}

void hasil() 
{
    double percentage;
    percentage = jawaban_benar*10;
    system("cls");

    cout << "=====================================================" << endl;
    cout << "====================== HASIL ========================" << endl;
    cout << "=====================================================" << endl;
    cout << "Nama Pemain: \t\t\t" << player << endl << endl;
    cout << "Jawaban Yang Benar: \t\t\t" << jawaban_benar << endl << endl;
    cout << "Jawaban Yang salah: \t\t\t" << jawaban_salah << endl << endl;
    cout << "Rata-rata: \t\t\t" << percentage << "%" << endl << endl;

    if (cash >= 0)
        cout << "Poin Yang Didapatkan: \t\t\tkoin" << cash << endl << endl;
    else
        cout << "Poin Yang Hangus: \t\t\tkoin" << cash << endl << endl;

    cout << "=====================================================" << endl;
    cout << "=============== THANKS FOR PLAYING ^-^ ==============" << endl;
    cout << "=====================================================" << endl;
    cout << "=====================================================" << endl;
    cout << "============== PRESS ANY KEY TO CONTINUE ============" << endl;
    cout << "=====================================================" << endl;
    _getch();

    saveResultsToFile();

}

void rules()
{
    cout << "=====================================================" << endl;
    cout << "====================== PERATURAN ====================" << endl;
    cout << "=====================================================" << endl;
    cout << " 01. Ada 10 soal di program ini." << endl << endl;
    cout << " 02. Hanya ada 2 kesempatan di setiap stage" << endl << endl;
    cout << " 03. Pay HALF dan SKIP artinya kamu harus bayar 1/4% dari soal yang sedang berlangsung" << endl << endl;
    cout << " 04. Leave Question artinya kamu bisa meninggalkan pertanyaan tanpa adanya deduksi" << endl << endl;
    cout << " 05. Jika kamu benar 3 beruntun Pay HALF dan SKIP akan diselamatkan" << endl << endl;
    cout << " 06. Jika kamu benar 5 beruntun Leave Questio akan diselamatkan" << endl << endl;
    cout << " 07. Setelah semua pertanyaan, jumlah pertanyaan akan didouble" << endl << endl;
    cout << " 08. Jika jawaban salah, 1/2 dari nilai pertanyaan akan mengurangi balance koin anda" << endl << endl;
    cout << " 09. Tekan H untuk Pay HALF dan SKIP" << endl << endl;
    cout << " 10. Tekan L untuk Leave Question" << endl << endl;
    cout << " 11. Tekan A / B / C / D untuk menjawab pertanyaan" << endl << endl;
    cout << " ===================================================== " << endl;
    cout << " ============= PRESS ANY KEY TO CONTINUE ============= " << endl;
    cout << " ===================================================== " << endl;
    _getch();
}

void saveResultsToFile() 
{
    ofstream outputFile("hasil.txt");

    if (outputFile.is_open()) {
        outputFile << "=====================================================" << endl;
        outputFile << "====================== HASIL ========================" << endl;
        outputFile << "=====================================================" << endl;
        outputFile << "Nama Pemain: \t\t\t" << player << endl << endl;
        outputFile << "Jawaban Yang Benar: \t\t\t" << jawaban_benar << endl << endl;
        outputFile << "Jawaban Yang salah: \t\t\t" << jawaban_salah << endl << endl;
        double percentage = jawaban_benar * 10;
        outputFile << "Rata-rata: \t\t\t" << percentage << "%" << endl << endl;

        if (cash >= 0)
            outputFile << "Poin Yang Didapatkan: \t\t\tkoin" << cash << endl << endl;
        else
            outputFile << "Poin Yang Hangus: \t\t\tkoin" << cash << endl << endl;

        outputFile << "=====================================================" << endl;
        outputFile << "=============== THANKS FOR PLAYING ^-^ ==============" << endl;
        outputFile << "=====================================================" << endl;
        outputFile << "=====================================================" << endl;
        outputFile << "============== END OF RESULTS ============" << endl;

        outputFile.close();
    }
}