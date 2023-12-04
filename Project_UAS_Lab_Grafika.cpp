// Project_UAS_Lab_Grafika.cpp : This file contains the 'main' function. Program execution begins and ends there.
// ==============================================================================================================
// Kelompok Ciwi - ciwi :
// 1. Margareth Serepine Simanjuntak - 221401022
// 2. Dhea Tania Salsabilah Harahap - 221401092
// 3. Ivanny Putri Marianto - 221401101
// 
// Dengan Asisten Laboratorium : Bang Andrew Benedictus Jamesie
// ==============================================================================================================
// Project Ujian Akhir Semester Lab. Grafika Komputer:
// Buatlah sebuah program grafis dengan menerapkan konsep dasar 3D, pewarnaan, 
// dan fungsi - fungsi callback pada OpenGL yang bertemakan bebas dan terdapat beberapa
// objek lengkap sesuai dengan yang ada di dunia nyata.Konfigurasinya adalah sebagai berikut :
// a) Menggunakan fungsi gluLookAt() dan fungsi keyboard, sehingga objek dapat dilihat dari berbagai sisi.
// b) Menerapkan minimal satu transformasi pada salah satu atau lebih objek.

#include <glut.h>
#include <math.h>

//Deklarasi fungsi 
float X1 = 0;
float Y1 = 0;
float X2 = 0;
float Y2 = 0;

float jamRotation = 0.0f;

bool mouseDown = false;

//Deklarasi pengaturan agar Gambar 3d yang kita buat saat diputar atau di geser tidak kemana mana
void ukur(int lebar, int tinggi) {
    if (tinggi == 0) tinggi = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, lebar / tinggi, 5, 700);
    glTranslatef(0, 0, -400);// jarak object 
    glMatrixMode(GL_MODELVIEW);
}

void myinit(void) {
    glClearColor(0.7, 0.9, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glPointSize(10.0);
    glLineWidth(7.0f);
}

void idle()
{
    if (!mouseDown)
    {
        X1 += 0.3;
        Y1 += 0.4;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;
        X2 = x - Y1;
        Y2 = -y + X1;
    }
    else
        mouseDown = false;
}

void mouseMotion(int x, int y)
{
    if (mouseDown)
    {
        Y1 = x - X2;
        X1 = y + Y2;
        glutPostRedisplay();
    }
}

void tembok() {
    // Tembok Bagian Atas
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.6);   // Warna abu-abu tua di bagian atas kiri
    glVertex3f(-120, -40, -100);
    glColor3f(0.7, 0.7, 0.7);   // Warna abu-abu muda di bagian atas kanan
    glVertex3f(120, -40, -100);
    glColor3f(0.5, 0.5, 0.5);   // Warna abu-abu muda di bagian bawah kiri
    glVertex3f(120, 100, -100);
    glColor3f(0.7, 0.7, 0.7);   // Warna abu-abu tua di bagian bawah kanan
    glVertex3f(-120, 100, -100);
    glEnd();

    // Tembok Kiri
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);   // Warna abu-abu untuk tembok kiri
    glVertex3f(-120, -40, -100);
    glVertex3f(-120, 100, -100);
    glVertex3f(-120, 100, 100);
    glVertex3f(-120, -40, 100);
    glEnd();

    // Tembok Kanan
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);   // Warna abu-abu untuk tembok kanan
    glVertex3f(120, -40, -100);
    glVertex3f(120, 100, -100);
    glVertex3f(120, 100, 100);
    glVertex3f(120, -40, 100);
    glEnd();
}

void lantai() {
    // Lantai Catur
    int size = 20;  // Ukuran kotak catur
    for (int i = -120; i < 120; i += size) {
        for (int j = -100; j < 100; j += size) {
            if ((i / size + j / size) % 2 == 0) {
                glColor3f(0.5, 0.5, 0.5);  // Warna abu-abu tua
            }
            else {
                glColor3f(0.9, 0.9, 0.9);;  // Warna abu-abu muda
            }
            glBegin(GL_POLYGON);
            glVertex3f(i, -40, j);
            glVertex3f(i + size, -40, j);
            glVertex3f(i + size, -40, j + size);
            glVertex3f(i, -40, j + size);
            glEnd();
        }
    }
}

void jamDinding() {
    // Jam Dinding
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(0.3, 0.3, 0.3);

    // Hitung koordinat tengah jam
    float centerX = 0.0;
    float centerY = 50.0;
    float centerZ = -99.0; // Tambahkan komponen z

    for (int i = 0; i < 12; ++i) {
        // Hitung koordinat titik pada lingkaran jam
        float angle = i * (2.0 * 3.14159265358979323846 / 12);
        float radius = 20.0; // Sesuaikan dengan radius yang diinginkan
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        float z = centerZ; // Tetapkan komponen z sesuai keinginan

        glVertex3f(x, y, z);
    }

    glEnd();
    glPointSize(1.0);
}

void jarumJam() {
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); // Warna merah untuk jarum jam

    // Tentukan panjang dan lebar jarum jam
    float panjangJarum = 10.0;
    float lebarJarum = 2.0;

    // Posisi dan rotasi jarum jam
    glTranslatef(0.0, 50.0, -99.0); // Sesuaikan posisi jarum jam sesuai keinginan
    glRotatef(jamRotation, 0.0, 0.0, 10.0);

    // Gambar jarum jam sebagai segiempat
    glBegin(GL_QUADS);
    glVertex3f(-lebarJarum / 2, 0, 0);
    glVertex3f(lebarJarum / 2, 0, 0);
    glVertex3f(lebarJarum / 2, panjangJarum, 0);
    glVertex3f(-lebarJarum / 2, panjangJarum, 0);
    glEnd();

    glPopMatrix();
}

void jendela() {
    //Jendela Kiri
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-90, 30, -99.9);  // Kiri Bawah
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-50, 30, -99.9);  // Kanan Bawah
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(-50, 70, -99.9);  // Kanan Atas
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(-90, 70, -99.9);  // Kiri Atas
    glEnd();

    //Outline Jendela Kiri
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);  // Warna biru untuk jendela
    glVertex3f(-89, 29, -99.9);  // Kiri Bawah
    glVertex3f(-49, 29, -99.9);  // Kanan Bawah
    glVertex3f(-49, 69, -99.9);  // Kanan Atas
    glVertex3f(-89, 69, -100);  // Kiri Atas
    glEnd();

    //Jendela Kiri Belakabg
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-90, 30, -100.1);  // Kiri Bawah
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-50, 30, -100.1);  // Kanan Bawah
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(-50, 70, -100.1);  // Kanan Atas
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(-90, 70, -100.1);  // Kiri Atas
    glEnd();

    //Outline Jendela Kiri Belakang
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);  // Warna biru untuk jendela
    glVertex3f(-89, 29, -100.1);  // Kiri Bawah
    glVertex3f(-49, 29, -100.1);  // Kanan Bawah
    glVertex3f(-49, 69, -100.1);  // Kanan Atas
    glVertex3f(-89, 69, -100);  // Kiri Atas
    glEnd();

    //Jendela Kanan
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(50, 30, -99.9);  // Kiri Bawah
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(90, 30, -99.9);  // Kanan Bawah
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(90, 70, -99.9);  // Kanan Atas
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(50, 70, -99.9);  // Kiri Atas
    glEnd();

    //Outline Jendela Kanan
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(49, 29, -99.9);  // Kiri Bawah
    glVertex3f(89, 29, -99.9);  // Kanan Bawah
    glVertex3f(89, 69, -99.9);  // Kanan Atas
    glVertex3f(49, 69, -100);  // Kiri Atas
    glEnd();

    //Jendela Kanan Belakang
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(50, 30, -100.1);  // Kiri Bawah
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(90, 30, -100.1);  // Kanan Bawah
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(90, 70, -100.1);  // Kanan Atas
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(50, 70, -100.1);  // Kiri Atas
    glEnd();

    //Outline Jendela Kanan Belakang
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(49, 29, -100.1);  // Kiri Bawah
    glVertex3f(89, 29, -100.1);  // Kanan Bawah
    glVertex3f(89, 69, -100.1);  // Kanan Atas
    glVertex3f(49, 69, -100);  // Kiri Atas
    glEnd();
}

void lemari3D() {
    // Lemari 3D
    glColor3f(0.5, 0.3, 0.1);
    glBegin(GL_QUADS);
    // Depan
    glVertex3f(-120, -40, -60);
    glVertex3f(-80, -40, -60);
    glVertex3f(-80, 60, -60);
    glVertex3f(-120, 60, -60);

    // Belakang
    glVertex3f(-120, -40, -99.9);
    glVertex3f(-80, -40, -99.9);
    glVertex3f(-80, 60, -99.9);
    glVertex3f(-120, 60, -99.9);

    // Samping Kiri
    glVertex3f(-119.9, -40, -60);
    glVertex3f(-119.9, 60, -60);
    glVertex3f(-119.9, 60, -99.9);
    glVertex3f(-119.9, -40, -99.9);

    // Samping Kanan
    glColor3f(0.4, 0.2, 0.1);
    glVertex3f(-80, -40, -60);
    glVertex3f(-80, 60, -60);
    glVertex3f(-80, 60, -99.9);
    glVertex3f(-80, -40, -99.9);

    // Atas
    glColor3f(0.6, 0.3, 0.1);
    glVertex3f(-120, 60, -60);
    glVertex3f(-80, 60, -60);
    glVertex3f(-80, 60, -99.9);
    glVertex3f(-120, 60, -99.9);

    // Pintu Kiri
    glColor3f(0.8, 0.6, 0.4); 
    glBegin(GL_QUADS);
    glVertex3f(-115, -35, -59.9);
    glVertex3f(-101, -35, -59.9);
    glVertex3f(-101, 55, -59.9);
    glVertex3f(-115, 55, -59.9);
    glEnd();

    // Pintu Kanan
    glColor3f(0.8, 0.6, 0.4); 
    glBegin(GL_QUADS);
    glVertex3f(-99, -35, -59.9);
    glVertex3f(-85, -35, -59.9);
    glVertex3f(-85, 55, -59.9);
    glVertex3f(-99, 55, -59.9);
    glEnd();
}

void tempatTidur() {
    // Tempat Tidur
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.9);
    glVertex3f(50, -20, 50);
    glVertex3f(119, -20, 50);
    glColor3f(0.5, 0.7, 0.9);
    glVertex3f(119, -20, -99);
    glVertex3f(50, -20, -99);
    //Depan
    glColor3f(0.4, 0.4, 0.8);
    glVertex3f(50, -20, 50);
    glVertex3f(119, -20, 50);
    glVertex3f(119, -40, 50);
    glVertex3f(50, -40, 50);
    // Belakang
    glVertex3f(50, -20, -99);
    glVertex3f(119, -20, -99);
    glVertex3f(119, -40, -99);
    glVertex3f(50, -40, -99);
    // Kiri
    glVertex3f(50, -20, 50);
    glVertex3f(50, -20, -99);
    glVertex3f(50, -40, -99);
    glVertex3f(50, -40, 50);
    // Atas
    glVertex3f(50, -20, 50);
    glVertex3f(119, -20, 50);
    glVertex3f(119, -20, -99);
    glVertex3f(50, -20, -99);
    // Bawah
    glVertex3f(50, -39, 50);
    glVertex3f(119, -39, 50);
    glVertex3f(119, -39, -99);
    glVertex3f(50, -39, -99);
    glEnd();
}

void bantal() {
    // Bantal 
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.5, 0.7);
    glVertex3f(65, -10, -60);
    glColor3f(1.0, 0.8, 0.9);
    glVertex3f(103, -10, -60);
    glVertex3f(103, -10, -90);
    glColor3f(1.0, 0.5, 0.7);
    glVertex3f(65, -10, -90);
    // Depan
    glColor3f(0.8, 0.5, 0.7);
    glVertex3f(65, -10, -60);
    glVertex3f(103, -10, -60);
    glVertex3f(103, -20, -60);
    glVertex3f(65, -20, -60);
    // Belakang
    glColor3f(0.8, 0.5, 0.7);
    glVertex3f(65, -10, -90);
    glVertex3f(103, -10, -90);
    glVertex3f(103, -20, -90);
    glVertex3f(65, -20, -90);
    // Kiri
    glColor3f(0.8, 0.5, 0.7);
    glVertex3f(65, -10, -60);
    glVertex3f(65, -10, -90);
    glVertex3f(65, -20, -90);
    glVertex3f(65, -20, -60);
    // Kanan
    glColor3f(0.8, 0.5, 0.7);
    glVertex3f(103, -10, -60);
    glVertex3f(103, -10, -90);
    glVertex3f(103, -20, -90);
    glVertex3f(103, -20, -60);
    // Atas
    glColor3f(1.0, 0.5, 0.7);
    glVertex3f(65, -10, -60);
    glVertex3f(103, -10, -60);
    glVertex3f(103, -10, -90);
    glVertex3f(65, -10, -90);
    // Bawah
    glColor3f(1.0, 0.5, 0.7);
    glVertex3f(65, -20, -60);
    glVertex3f(103, -20, -60);
    glColor3f(1.0, 0.8, 0.9);
    glVertex3f(103, -20, -90);
    glVertex3f(65, -20, -90);
    glEnd();
}

void guling() {
    // Guling 1
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.5, 0.7);
    glVertex3f(57, -15, -50);
    glVertex3f(69, -15, -50);
    glVertex3f(69, -15, 30);
    glVertex3f(57, -15, 30);

    glColor3f(0.8, 0.5, 0.7);
    glVertex3f(57, -15, -50);
    glVertex3f(69, -15, -50);
    glVertex3f(69, -25, -50);
    glVertex3f(57, -25, -50);

    glVertex3f(57, -15, 30);
    glVertex3f(69, -15, 30);
    glVertex3f(69, -25, 30);
    glVertex3f(57, -25, 30);

    glVertex3f(57, -15, -50);
    glVertex3f(57, -15, 30);
    glVertex3f(57, -25, 30);
    glVertex3f(57, -25, -50);

    glVertex3f(69, -15, -50);
    glVertex3f(69, -15, 30);
    glVertex3f(69, -25, 30);
    glVertex3f(69, -25, -50);

    glVertex3f(57, -15, -50);
    glVertex3f(69, -15, -50);
    glVertex3f(69, -15, 30);
    glVertex3f(57, -15, 30);
    glEnd();

    // Guling 2
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.5, 0.7); 
    glVertex3f(100, -15, -50);
    glVertex3f(112, -15, -50);
    glVertex3f(112, -15, 30);
    glVertex3f(100, -15, 30);

    glColor3f(0.8, 0.5, 0.7); 
    glVertex3f(100, -15, -50);
    glVertex3f(112, -15, -50);
    glVertex3f(112, -25, -50);
    glVertex3f(100, -25, -50);

    glVertex3f(100, -15, 30);
    glVertex3f(112, -15, 30);
    glVertex3f(112, -25, 30);
    glVertex3f(100, -25, 30);

    glVertex3f(100, -15, -50);
    glVertex3f(100, -15, 30);
    glVertex3f(100, -25, 30);
    glVertex3f(100, -25, -50);

    glVertex3f(112, -15, -50);
    glVertex3f(112, -15, 30);
    glVertex3f(112, -25, 30);
    glVertex3f(112, -25, -50);

    glVertex3f(100, -15, -50);
    glVertex3f(112, -15, -50);
    glVertex3f(112, -15, 30);
    glVertex3f(100, -15, 30);
    glEnd();
}

void meja() {
    //ALAS MEJA
    glBegin(GL_POLYGON);//ATAS
    glColor3f(1.0, 0.6, 0.6);
    glVertex3f(-50, 15, 40);
    glVertex3f(20, 15, 40);
    glVertex3f(20, 15, -10);
    glVertex3f(-50, 15, -10);
    glEnd();
    glBegin(GL_POLYGON);//BAWAH
    glColor3f(1.0, 0.6, 0.6);
    glVertex3f(-50, 10, 40);
    glVertex3f(20, 10, 40);
    glVertex3f(20, 10, -10);
    glVertex3f(-50, 10, -10);
    glEnd();
    glBegin(GL_POLYGON);//SAMPING KANAN
    glColor3f(0.9, 0.5, 0.5);
    glVertex3f(20, 10, 40);
    glVertex3f(20, 15, 40);
    glVertex3f(20, 15, -10);
    glVertex3f(20, 10, -10);
    glEnd();
    glBegin(GL_POLYGON);//SAMPING KIRI
    glColor3f(0.9, 0.5, 0.5);
    glVertex3f(-50, 10, 40);
    glVertex3f(-50, 15, 40);
    glVertex3f(-50, 15, -10);
    glVertex3f(-50, 10, -10);
    glEnd();
    glBegin(GL_POLYGON);//DEPAN
    glColor3f(0.8, 0.4, 0.4);
    glVertex3f(-50, 10, 40);
    glVertex3f(-50, 15, 40);
    glVertex3f(20, 15, 40);
    glVertex3f(20, 10, 40);
    glEnd();
    glBegin(GL_POLYGON);//BELAKANG
    glColor3f(0.8, 0.4, 0.4);
    glVertex3f(-50, 10, -10);
    glVertex3f(-50, 15, -10);
    glVertex3f(20, 15, -10);
    glVertex3f(20, 10, -10);
    glEnd();

    //KAKI MEJA 1
    glBegin(GL_POLYGON);//DEPAN
    glColor3f(0.8, 0.4, 0.4);
    glVertex3f(-50, 10, 40);
    glVertex3f(-40, 10, 40);
    glVertex3f(-40, -40, 40);
    glVertex3f(-50, -40, 40);
    glEnd();
    glBegin(GL_POLYGON);//BELAKANG
    glColor3f(0.8, 0.4, 0.4);
    glVertex3f(-50, 10, 30);
    glVertex3f(-40, 10, 30);
    glVertex3f(-40, -40, 30);
    glVertex3f(-50, -40, 30);
    glEnd();
    glBegin(GL_POLYGON);//KIRI
    glColor3f(0.9, 0.5, 0.5);
    glVertex3f(-50, 10, 30);
    glVertex3f(-50, -40, 30);
    glVertex3f(-50, -40, 40);
    glVertex3f(-50, 10, 40);
    glEnd();
    glBegin(GL_POLYGON);//KANAN
    glColor3f(0.9, 0.5, 0.5);
    glVertex3f(-40, 10, 30);
    glVertex3f(-40, -40, 30);
    glVertex3f(-40, -40, 40);
    glVertex3f(-40, 10, 40);
    glEnd();

    //KAKI MEJA 2
    glBegin(GL_POLYGON);//DEPAN
    glColor3f(0.8, 0.4, 0.4);
    glVertex3f(10, 10, 40);
    glVertex3f(20, 10, 40);
    glVertex3f(20, -40, 40);
    glVertex3f(10, -40, 40);
    glEnd();
    glBegin(GL_POLYGON);//BELAKANG
    glColor3f(0.8, 0.4, 0.4);
    glVertex3f(10, 10, 30);
    glVertex3f(20, 10, 30);
    glVertex3f(20, -40, 30);
    glVertex3f(10, -40, 30);
    glEnd();
    glBegin(GL_POLYGON);//KIRI
    glColor3f(0.9, 0.5, 0.5);
    glVertex3f(10, 10, 30);
    glVertex3f(10, -40, 30);
    glVertex3f(10, -40, 40);
    glVertex3f(10, 10, 40);
    glEnd();
    glBegin(GL_POLYGON);//KANAN
    glColor3f(0.9, 0.5, 0.5);
    glVertex3f(20, 10, 30);
    glVertex3f(20, -40, 30);
    glVertex3f(20, -40, 40);
    glVertex3f(20, 10, 40);
    glEnd();

    //KAKI MEJA 3
    glBegin(GL_POLYGON);//DEPAN
    glColor3f(0.8, 0.4, 0.4);
    glVertex3f(-50, 10, 0);
    glVertex3f(-40, 10, 0);
    glVertex3f(-40, -40, 0);
    glVertex3f(-50, -40, 0);
    glEnd();
    glBegin(GL_POLYGON);//BELAKANG
    glColor3f(0.8, 0.4, 0.4);
    glVertex3f(-50, 10, -10);
    glVertex3f(-40, 10, -10);
    glVertex3f(-40, -40, -10);
    glVertex3f(-50, -40, -10);
    glEnd();
    glBegin(GL_POLYGON);//KIRI
    glColor3f(0.9, 0.5, 0.5);
    glVertex3f(-50, 10, 0);
    glVertex3f(-50, -40, 0);
    glVertex3f(-50, -40, -10);
    glVertex3f(-50, 10, -10);
    glEnd();
    glBegin(GL_POLYGON);//KANAN
    glColor3f(0.9, 0.5, 0.5);
    glVertex3f(-40, 10, 0);
    glVertex3f(-40, -40, 0);
    glVertex3f(-40, -40, -10);
    glVertex3f(-40, 10, -10);
    glEnd();

    //KAKI MEJA 4
    glBegin(GL_POLYGON);//DEPAN
    glColor3f(0.8, 0.4, 0.4);
    glVertex3f(20, 10, 0);
    glVertex3f(10, 10, 0);
    glVertex3f(10, -40, 0);
    glVertex3f(20, -40, 0);
    glEnd();
    glBegin(GL_POLYGON);//BELAKANG
    glColor3f(0.8, 0.4, 0.4);
    glVertex3f(20, 10, -10);
    glVertex3f(10, 10, -10);
    glVertex3f(10, -40, -10);
    glVertex3f(20, -40, -10);
    glEnd();
    glBegin(GL_POLYGON);//KIRI
    glColor3f(0.9, 0.5, 0.5);
    glVertex3f(20, 10, 0);
    glVertex3f(20, -40, 0);
    glVertex3f(20, -40, -10);
    glVertex3f(20, 10, -10);
    glEnd();
    glBegin(GL_POLYGON);//KANAN
    glColor3f(0.9, 0.5, 0.5);
    glVertex3f(10, 10, 0);
    glVertex3f(10, -40, 0);
    glVertex3f(10, -40, -10);
    glVertex3f(10, 10, -10);
    glEnd();
}

void kursi() {
    //ALAS KURSI
    glBegin(GL_POLYGON);//ATAS
    glColor3f(0.6, 0.6, 1.0);
    glVertex3f(-30, -10, -20);
    glVertex3f(0, -10, -20);
    glVertex3f(0, -10, -50);
    glVertex3f(-30, -10, -50);
    glEnd();
    glBegin(GL_POLYGON);//BAWAH
    glColor3f(0.6, 0.6, 1.0);
    glVertex3f(-30, -15, -20);
    glVertex3f(0, -15, -20);
    glVertex3f(0, -15, -50);
    glVertex3f(-30, -15, -50);
    glEnd();
    glBegin(GL_POLYGON);//SAMPING KANAN
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(0, -10, -20);
    glVertex3f(0, -15, -20);
    glVertex3f(0, -15, -50);
    glVertex3f(0, -10, -50);
    glEnd();
    glBegin(GL_POLYGON);//SAMPING KIRI
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-30, -10, -20);
    glVertex3f(-30, -15, -20);
    glVertex3f(-30, -15, -50);
    glVertex3f(-30, -10, -50);
    glEnd();
    glBegin(GL_POLYGON);//DEPAN
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(-30, -10, -20);
    glVertex3f(-30, -15, -20);
    glVertex3f(0, -15, -20);
    glVertex3f(0, -10, -20);
    glEnd();
    glBegin(GL_POLYGON);//BELAKANG
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(-30, -10, -50);
    glVertex3f(-30, -15, -50);
    glVertex3f(0, -15, -50);
    glVertex3f(0, -10, -50);
    glEnd();

    //KAKI KURSI KIRI DEPAN
    glBegin(GL_POLYGON);//DEPAN
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(-30, -10, -20);
    glVertex3f(-25, -10, -20);
    glVertex3f(-25, -40, -20);
    glVertex3f(-30, -40, -20);
    glEnd();
    glBegin(GL_POLYGON);//BELAKANG
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(-30, -10, -30);
    glVertex3f(-25, -10, -30);
    glVertex3f(-25, -40, -30);
    glVertex3f(-30, -40, -30);
    glEnd();
    glBegin(GL_POLYGON);//KIRI
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-30, -10, -30);
    glVertex3f(-30, -40, -30);
    glVertex3f(-30, -40, -20);
    glVertex3f(-30, -10, -20);
    glEnd();
    glBegin(GL_POLYGON);//KANAN
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-25, -10, -30);
    glVertex3f(-25, -40, -30);
    glVertex3f(-25, -40, -20);
    glVertex3f(-25, -10, -20);
    glEnd();

    //KAKI KURSI KIRI BELAKANG
    glBegin(GL_POLYGON);//ALAS ATAS
    glColor3f(0.6, 0.6, 1.0);
    glVertex3f(-25, 30, -50);
    glVertex3f(-30, 30, -50);
    glVertex3f(-30, 30, -40);
    glVertex3f(-25, 30, -40);
    glEnd();
    glBegin(GL_POLYGON);//DEPAN
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(-25, 30, -40);
    glVertex3f(-30, 30, -40);
    glVertex3f(-30, -40, -40);
    glVertex3f(-25, -40, -40);
    glEnd();
    glBegin(GL_POLYGON);//BELAKANG
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(-25, 30, -50);
    glVertex3f(-30, 30, -50);
    glVertex3f(-30, -40, -50);
    glVertex3f(-25, -40, -50);
    glEnd();
    glBegin(GL_POLYGON);//KIRI
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-25, 30, -50);
    glVertex3f(-25, -40, -50);
    glVertex3f(-25, -40, -40);
    glVertex3f(-25, 30, -40);
    glEnd();
    glBegin(GL_POLYGON);//KANAN
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-30, 30, -50);
    glVertex3f(-30, -40, -50);
    glVertex3f(-30, -40, -40);
    glVertex3f(-30, 30, -40);
    glEnd();

    //KAKI KURSI KANAN DEPAN
    glBegin(GL_POLYGON);//DEPAN
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(0, -10, -20);
    glVertex3f(-5, -10, -20);
    glVertex3f(-5, -40, -20);
    glVertex3f(0, -40, -20);
    glEnd();
    glBegin(GL_POLYGON);//BELAKANG
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(0, -10, -30);
    glVertex3f(-5, -10, -30);
    glVertex3f(-5, -40, -30);
    glVertex3f(0, -40, -30);
    glEnd();
    glBegin(GL_POLYGON);//KIRI
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(0, -10, -30);
    glVertex3f(0, -40, -30);
    glVertex3f(0, -40, -20);
    glVertex3f(0, -10, -20);
    glEnd();
    glBegin(GL_POLYGON);//KANAN
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-5, -10, -30);
    glVertex3f(-5, -40, -30);
    glVertex3f(-5, -40, -20);
    glVertex3f(-5, -10, -20);
    glEnd();

    //KAKI KURSI KANAN BELAKANG
    glBegin(GL_POLYGON);//ALAS ATAS
    glColor3f(0.6, 0.6, 1.0);
    glVertex3f(-5, 30, -50);
    glVertex3f(0, 30, -50);
    glVertex3f(0, 30, -40);
    glVertex3f(-5, 30, -40);
    glEnd();
    glBegin(GL_POLYGON);//DEPAN
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(-5, 30, -40);
    glVertex3f(0, 30, -40);
    glVertex3f(0, -40, -40);
    glVertex3f(-5, -40, -40);
    glEnd();
    glBegin(GL_POLYGON);//BELAKANG
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(-5, 30, -50);
    glVertex3f(0, 30, -50);
    glVertex3f(0, -40, -50);
    glVertex3f(-5, -40, -50);
    glEnd();
    glBegin(GL_POLYGON);//KIRI
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-5, 30, -50);
    glVertex3f(-5, -40, -50);
    glVertex3f(-5, -40, -40);
    glVertex3f(-5, 30, -40);
    glEnd();
    glBegin(GL_POLYGON);//KANAN
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(0, 30, -50);
    glVertex3f(0, -40, -50);
    glVertex3f(0, -40, -40);
    glVertex3f(0, 30, -40);
    glEnd();

    //SENDERAN KURSI
    glBegin(GL_POLYGON);//DEPAN
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(-30, 30, -40);
    glVertex3f(-30, 10, -40);
    glVertex3f(0, 10, -40);
    glVertex3f(0, 30, -40);
    glEnd();
    glBegin(GL_POLYGON);//BELAKANG
    glColor3f(0.4, 0.4, 1.0);
    glVertex3f(-30, 30, -45);
    glVertex3f(-30, 10, -45);
    glVertex3f(0, 10, -45);
    glVertex3f(0, 30, -45);
    glEnd();
    glBegin(GL_POLYGON);//ATAS
    glColor3f(0.6, 0.6, 1.0);
    glVertex3f(-30, 30, -40);
    glVertex3f(-30, 30, -45);
    glVertex3f(0, 30, -45);
    glVertex3f(0, 30, -40);
    glEnd();
    glBegin(GL_POLYGON);//BAWAH
    glColor3f(0.6, 0.6, 1.0);
    glVertex3f(-30, 10, -40);
    glVertex3f(-30, 10, -45);
    glVertex3f(0, 10, -45);
    glVertex3f(0, 10, -40);
    glEnd();
}

void tampilan(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
    glRotatef(X1, 1, 0, 0);
    glRotatef(Y1, 0, 1, 0);
    glPushMatrix();

    tembok();

    jarumJam();
    jamRotation -= 0.01;

    lantai();

    jamDinding();

    lemari3D();

    tempatTidur();

    bantal();

    guling();
    
    jendela();

    meja();

    kursi();

    glPushMatrix();
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(240, 80);
    glutInitWindowSize(750, 600);
    glutCreateWindow("Project_UAS_Lab");

    myinit();
    glutDisplayFunc(tampilan);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutReshapeFunc(ukur);
    glutMainLoop();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
