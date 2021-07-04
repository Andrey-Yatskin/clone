#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

const float g = 9.8;

typedef struct paramsOfBall {
    float Sy, Vy, Sx, Vx, t;
} params;

typedef struct list {
    paramsOfBall inf;
    struct list* next;
} List;

typedef struct TestStruct {
    params res;
    float Vy;
    float Vx;
    float Sx;
    float Sy;
    float timeBTW;
} tests;

typedef struct Image {
    int mx;
    int my;
    int* points;
} image;

params initOfStruct() {
    params temp;
    temp.Sy = 0;
    cout << "Введте Vy" << endl;
    cin >> temp.Vy;
    temp.Sx = 0;
    cout << "Введте Vx" << endl;
    cin >> temp.Vx;
    return temp;
}

List* AddElemToList(List* beg, params tmp) {
    if (beg == NULL) {
        beg = new List;
        beg -> inf = tmp;
        beg -> inf.t = 0;
        beg -> next = NULL;
        return beg;
    }
    List* temp = beg;
    while (temp -> next != NULL) {
        temp = temp -> next;
    }
    temp -> next = new List;
    temp = temp -> next;
    temp -> inf = tmp;
    temp -> next = NULL;
    return beg;
}

void PrintOfInfStruct(params tmp) {
    cout << "Time: " << tmp.t << endl;
    cout << "Sy = " << tmp.Sy << endl;
    cout << "Vy = " << tmp.Vy << endl;
    cout << "Sx = " << tmp.Sx << endl;
    cout << "Vx = " << tmp.Vx << endl;
}

void PrintList(List* begin) {
    while (begin) {
        PrintOfInfStruct(begin -> inf);
        begin = begin -> next;
    }
}

params CalculatingParams(List* beg, double btwTime) {
    params temp;
    
    while (beg -> next != NULL) {
        beg = beg -> next;
    }
    
    temp.t = beg -> inf.t + btwTime;
    
    if (temp.t < 2 * beg -> inf.Vy / g) {
        temp.Sx = beg -> inf.Vx * temp.t;
        temp.Sy = beg -> inf.Vy * temp.t - g * temp.t * temp.t / 2;
        temp.Vy = beg -> inf.Vy - g * temp.t;
        temp.Vx = beg -> inf.Vx;
    } else {
        temp.Sx = 2 * beg -> inf.Vx * temp.t / g;
        temp.Sy = 0;
        temp.Vx = 0;
        temp.Vy = 0;
    }
    
    if (temp.Sy < 0)
        temp.Sy = 0;
    
    return temp;
}


List* MainCalculating(List* beg) {
    if (beg == NULL) {
        return beg;
    }
    List* temp = beg;
    double btwTime = 0;
    
    while (btwTime <= 0) {
        cout << "Введите интервал времени: " << endl;
        cin >> btwTime;
    }
    
    while (CalculatingParams(temp, btwTime).Sy != 0) {
        beg = AddElemToList(beg, CalculatingParams(temp, btwTime));
        temp = temp -> next;
    }
    beg = AddElemToList(beg, CalculatingParams(temp, btwTime));
    PrintList(beg);
    return beg;
}

List* ClnMem(List* beg) {
    List* temp = beg;
    while (beg -> next) {
        beg = beg -> next;
        delete temp;
        temp = beg;
    }
    delete beg;
    beg = NULL;
    return beg;
}

bool comprasionOfParams(params p1, params p2) {
    if ((p1.Sx == p2.Sx) && (p1.Sy == p2.Sy) && (p1.Vx == p2.Vx) && (p1.Vy == p2.Vy) && (p1.t == p2.t)) {
        return true;
    }
    return false;
}

bool TestCalculating(tests test) {
    List* someList = NULL;
    params temp;
    temp.Vy = test.Vy;
    temp.Vx = test.Vx;
    temp.Sy = test.Sy;
    temp.Sx = test.Sx;
    someList = AddElemToList(someList, temp);
    
    if (comprasionOfParams(CalculatingParams(someList, test.timeBTW),test.res)) {
        return true;
    }
    
    return false;
}

void RunTesting() {
    tests* arrToTests = new tests[1];
    
    arrToTests[0].Vx = 10;
    arrToTests[0].Vy = 5;
    arrToTests[0].Sx = 0;
    arrToTests[0].Sy = 0;
    arrToTests[0].timeBTW = 1;
    
    arrToTests[0].res.Sx = (float)10;
    arrToTests[0].res.Vy = (float)-4.8;
    arrToTests[0].res.Vx = (float)10;
    arrToTests[0].res.Sy = (float)0.1;
    arrToTests[0].res.t = (float)1;
    
    if (TestCalculating(arrToTests[0])) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

}

Image* CreateImage(Image* img, int x, int y ) {
    img = new Image;
    img -> mx = x;
    img -> my = y;
    img -> points = new int[x * y];
    return img;
}

Image* SetPointImage(Image* img, int x, int y, int color) {
    img -> points[(y * img -> mx + x)] = color;
    return img;
}

int GetPointImage(Image* img, int x, int y) {
    return img->points[y * img->mx + x];
}

void ShowImage(Image* img)
{
    for (int i = 0; i < img -> my; i++)
    {
        for (int j = 0; j < img -> mx; j++)
        {
            cout << img->points[i * img -> mx + j] << " ";
        }
        cout << endl;
    }
}

void SaveImage(Image* img, const string fname)
{
    fstream file;
    file.open(fname, fstream::out);
    file << "P1" << endl;
    file << img -> mx << " " << img -> my << endl;

    for (int i = 0; i < img -> my; i++)
    {
        for (int j = 0; j < img -> mx; j++)
        {
            file << img -> points[i * img -> mx + j] << " ";
        }
        file << endl;
    }
    file.close();
}

void ListToImg(List* beg, Image* im)
{
    const int tSize = 1000;
    const double sSize = 12.5;

    List* temp = beg;
    while (temp -> next != NULL)
    {
        SetPointImage(im, tSize * temp -> inf.t, (im -> my - 1) - sSize * temp -> inf.Sx * temp -> inf.Sy, 1);
        temp = temp -> next;
    }

    SaveImage(im, "1.jpg");
}

int main() {
    Image* Img = new Image;
    Img = CreateImage(Img, 400, 300);
    List* beg = NULL;
    beg = AddElemToList(beg, initOfStruct());
    beg = MainCalculating(beg);
    ListToImg(beg, Img);
    return 0;
}
