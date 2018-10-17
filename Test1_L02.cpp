#include <cmath>
#include <iostream>

using namespace std;

#define EPSILON 1E-10

struct Point {
    double x;
    double y;
    string name;
    Point *next;
    Point()
    {
        this->x = 0;
        this->y = 0;
        this->name = "";
        this->next = nullptr;
    }
    Point(Point *p)
    {
        this->x = p->x;
        this->y = p->y;
        this->name = p->name;
        this->next = nullptr;
    }
    Point(double x, double y, string name)
    {
        this->x = x;
        this->y = y;
        this->name = name;
        this->next = nullptr;
    }
};

void appendPoint(Point *&pHead, Point *newPoint)
{
    if (pHead == nullptr) {
        pHead = newPoint;
        return;
    }
    Point *temp = pHead;
    while (temp->next != nullptr)
        temp = temp->next;
    temp->next = newPoint;
}

double distancePointToLine(Point *point, double a, double b, double c)
{
    if (point == nullptr)
        return -1;
    return abs(a * point->x + b * point->y + c) / sqrt(a * a + b * b);
}

Point *listPoint(Point *pHead, double a, double b, double c, double H)
{
    Point *newList = nullptr;
    Point *temp = pHead;
    while (temp != nullptr) {
        if (distancePointToLine(temp, a, b, c) >= H) {
            Point *newPoint = new Point(temp);
            appendPoint(newList, newPoint);
        }
        temp = temp->next;
    }
    return newList;
}

double distanceBetweenTwoPoint(Point *point1, Point *point2)
{
    if (point1 == nullptr || point2 == nullptr)
        return -1;
    return sqrt(pow(point1->x - point2->x, 2) + pow(point1->y - point2->y, 2));
}

void printLineFromTwoPoint(Point *point1, Point *point2)
{
    if (point1 == nullptr || point2 == nullptr) {
        cout << "Diem 1 hoac diem 2 chua xac dinh!" << endl;
        return;
    }
    if (distanceBetweenTwoPoint(point1, point2) < EPSILON) {
        cout << "Hai diem da cho trung nhau!" << endl;
        return;
    }
    double a = (point1->y - point2->y);
    double b = (point2->x - point1->x);
    double c = a * (-point1->x) + b * (-point1->y);
    cout << a << " * x + " << b << " * y + " << c << " = 0" << endl;
}

void printAllLineFromPointList(Point *pHead)
{
    if (pHead == nullptr)
        return;
    Point *temp = pHead->next;
    while (temp != nullptr) {
        printLineFromTwoPoint(pHead, temp);
        temp = temp->next;
    }
    printAllLineFromPointList(pHead->next);
}

void prependPoint(Point *&pHead, Point *&newPoint)
{
    newPoint->next = pHead;
    pHead = newPoint;
}

Point *findPreMinPoint(Point *pHead, double a, double b, double c)
{
    if (pHead == nullptr)
        return nullptr;
    Point *preMinPoint = nullptr;
    double minLenght = distancePointToLine(pHead, a, b, c);
    Point *temp = pHead;
    while (temp->next != nullptr) {
        double distance = distancePointToLine(temp->next, a, b, c);
        if (distance < minLenght) {
            minLenght = distance;
            preMinPoint = temp;
        }
        temp = temp->next;
    }
    return preMinPoint;
}

void sortDecreaseDistanceToLine(Point *&pHead, double a, double b, double c)
{
    if (pHead == nullptr)
        return;
    if (pHead->next == nullptr)
        return;
    Point *sortedList = nullptr;
    while (pHead != nullptr) {
        Point *temp = nullptr;
        Point *preMinPoint = findPreMinPoint(pHead, a, b, c);
        if (preMinPoint == nullptr) {
            temp = pHead;
            pHead = pHead->next;
        } else {
            temp = preMinPoint->next;
            preMinPoint->next = temp->next;
        }
        prependPoint(sortedList, temp);
    }
    pHead = sortedList;
}

double sumAllDistanceToLine(Point *pHead, double a, double b, double c)
{
    if (pHead == nullptr)
        return 0;
    return distancePointToLine(pHead, a, b, c) + sumAllDistanceToLine(pHead->next, a, b, c);
}

bool isCyclicQuadrilateral(Point *a, Point *b, Point *c, Point *d)
{
    double ab = distanceBetweenTwoPoint(a, b);
    double ac = distanceBetweenTwoPoint(a, c);
    double ad = distanceBetweenTwoPoint(a, d);
    double bc = distanceBetweenTwoPoint(b, c);
    double bd = distanceBetweenTwoPoint(b, d);
    double cd = distanceBetweenTwoPoint(c, d);
    if (ab < EPSILON || ac < EPSILON || ad < EPSILON || bc < EPSILON || bd < EPSILON || cd < EPSILON)
        return false;
    double cosA = (ab * ab + ad * ad - bd * bd) / (2 * ab * ad);
    double cosC = (bc * bc + cd * cd - bd * bd) / (2 * bc * cd);
    if (abs(cosA + cosC) > EPSILON || abs(abs(cosA) - 1) < EPSILON || abs(abs(cosC) - 1) < EPSILON)
        return false;
    return true;
}

bool checkAndPrintCyclicQuadrilateral(Point *a, Point *b, Point *c, Point *d)
{
    bool check = isCyclicQuadrilateral(a, b, c, d);
    if (check) {
        cout << a->name << " " << b->name << " " << c->name << " " << d->name << endl;
        return true;
    }
    return false;
}

void printAllCyclicQuadrilateral(Point *pHead)
{
    Point *a = pHead;
    while (a != nullptr) {
        Point *b = a->next;
        while (b != nullptr) {
            Point *c = b->next;
            while (c != nullptr) {
                Point *d = c->next;
                while (d != nullptr) {
                    if (checkAndPrintCyclicQuadrilateral(a, b, c, d)) {
                    } else if (checkAndPrintCyclicQuadrilateral(a, b, d, c)) {
                    } else if (checkAndPrintCyclicQuadrilateral(a, c, b, d)) {
                    } else if (checkAndPrintCyclicQuadrilateral(a, c, d, b)) {
                    } else if (checkAndPrintCyclicQuadrilateral(a, d, b, c)) {
                    } else if (checkAndPrintCyclicQuadrilateral(a, d, c, b)) {
                    } else if (checkAndPrintCyclicQuadrilateral(b, a, c, d)) {
                    } else if (checkAndPrintCyclicQuadrilateral(b, a, d, c)) {
                    } else if (checkAndPrintCyclicQuadrilateral(b, c, a, d)) {
                    } else if (checkAndPrintCyclicQuadrilateral(b, c, d, a)) {
                    } else if (checkAndPrintCyclicQuadrilateral(b, d, a, c)) {
                    } else if (checkAndPrintCyclicQuadrilateral(b, d, c, a)) {
                    } else if (checkAndPrintCyclicQuadrilateral(c, a, b, d)) {
                    } else if (checkAndPrintCyclicQuadrilateral(c, a, d, b)) {
                    } else if (checkAndPrintCyclicQuadrilateral(c, b, a, d)) {
                    } else if (checkAndPrintCyclicQuadrilateral(c, b, d, a)) {
                    } else if (checkAndPrintCyclicQuadrilateral(c, d, a, b)) {
                    } else if (checkAndPrintCyclicQuadrilateral(c, d, b, a)) {
                    } else if (checkAndPrintCyclicQuadrilateral(d, a, b, c)) {
                    } else if (checkAndPrintCyclicQuadrilateral(d, a, c, b)) {
                    } else if (checkAndPrintCyclicQuadrilateral(d, b, a, c)) {
                    } else if (checkAndPrintCyclicQuadrilateral(d, b, c, a)) {
                    } else if (checkAndPrintCyclicQuadrilateral(d, c, a, b)) {
                    } else if (checkAndPrintCyclicQuadrilateral(d, c, b, a)) {
                    }
                    d = d->next;
                }
                c = c->next;
            }
            b = b->next;
        }
        a = a->next;
    }
}

void printAllPointInList(Point *pHead)
{
    Point *temp = pHead;
    while (temp != nullptr) {
        cout << temp->name << " " << temp->x << " " << temp->y << endl;
        temp = temp->next;
    }
}

void clearPointList(Point *&pHead)
{
    while (pHead != nullptr) {
        Point *temp = pHead;
        pHead = pHead->next;
        delete temp;
    }
}

int main()
{
    Point *pHead = nullptr;
    double x[] = {
        2, 4, 6, 2, 4, 6, 2, 4, 6
    };
    double y[] = {
        1, 1, 1, 3, 3, 3, 5, 5, 5
    };
    string name[] = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I"
    };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            Point *newPoint = new Point(x[i * 3 + j], y[i * 3 + j], name[i * 3 + j]);
            cout << distancePointToLine(newPoint, 1, 0, 0) << endl;
            prependPoint(pHead, newPoint);
        }
    }
    printAllPointInList(pHead);
    clearPointList(pHead);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            Point *newPoint = new Point(x[i * 3 + j], y[i * 3 + j], name[i * 3 + j]);
            cout << distancePointToLine(newPoint, 0, 1, 0) << endl;
            appendPoint(pHead, newPoint);
        }
    }
    printAllPointInList(pHead);
    sortDecreaseDistanceToLine(pHead, 1, -1, 0);
    printAllPointInList(pHead);
    printAllLineFromPointList(pHead);
    printAllCyclicQuadrilateral(pHead);
    return 0;
}
