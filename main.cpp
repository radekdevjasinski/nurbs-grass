#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <cmath>
#include <vector>
#include <random>

// Struktura reprezentuj¹ca krzyw¹ NURBS
struct NURBSCurve {
    GLfloat controlPoints[4][3]; // Punkty kontrolne krzywej (x, y, z)
    GLfloat knotVector[8];       // Wektor wêz³ów krzywej
    float range;                  // Zakres ruchu punktu kontrolnego
    float initialX;               // Pocz¹tkowa pozycja punktu kontrolnego

    // Konstruktor inicjalizuj¹cy krzyw¹ NURBS
    NURBSCurve(GLfloat points[4][3], GLfloat knots[8], float rang) {
        std::copy(&points[0][0], &points[0][0] + 4 * 3, &controlPoints[0][0]);
        std::copy(&knots[0], &knots[0] + 8, &knotVector[0]);
        range = rang;
        initialX = controlPoints[3][0];
    }

    // Metoda do rysowania krzywej NURBS
    void draw() const {
        glLineWidth(3.0f);         // Ustawienie szerokoœci linii
        glColor3f(0.0f, 1.0f, 0.0f); // Ustawienie koloru (zielony)

        glEnable(GL_MAP1_VERTEX_3); // W³¹czenie mapowania na krzyw¹ NURBS
        glMap1f(GL_MAP1_VERTEX_3, 0.0f, 1.0f, 3, 4, &controlPoints[0][0]); // Ustawienie danych krzywej

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= 50; ++i) {
            glEvalCoord1f((GLfloat)i / 50.0f); 
        }
        glEnd();

        glDisable(GL_MAP1_VERTEX_3); // Wy³¹czenie mapowania na krzyw¹ NURBS

        //drawControlPoints(); // Rysowanie punktów kontrolnych (wy³¹czone)
    }

    // Metoda do rysowania punktów kontrolnych
    void drawControlPoints() const {
        glColor3f(1.0f, 0.0f, 0.0f); // Ustawienie koloru na czerwony
        glPointSize(6.0f);          // Ustawienie rozmiaru punktu kontrolnego

        glBegin(GL_POINTS); // Rozpoczêcie rysowania punktów
        for (int i = 0; i < 4; ++i) {
            glVertex3fv(&controlPoints[i][0]); // Rysowanie punktu kontrolnego
        }
        glEnd(); // Zakoñczenie rysowania
    }

    // Metoda do aktualizacji pozycji punktów kontrolnych na podstawie czasu
    void update(float time) {
        // Aktualizacja pozycji punktu kontrolnego wzd³u¿ osi X na podstawie funkcji sinus
        controlPoints[3][0] = initialX + std::sin(time) * range;
    }
};

std::vector<NURBSCurve> curves; // Kontener na wszystkie krzywe NURBS

// Funkcja inicjalizuj¹ca wszystkie krzywe NURBS
void initCurves() {
    // Krzywa 1
    GLfloat controlPoints1[4][3] = {
        { 0.0f, -6.0f, 0.0f },
        { 0.0f, 3.0f, 0.0f },
        { 0.0f, 9.0f, 0.0f },
        { 0.0f, 5.0f, 0.0f },
    };
    GLfloat knotVector1[8] = { 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.0f, 2.0f, 2.0f };
    curves.push_back(NURBSCurve(controlPoints1, knotVector1, 1)); // Dodanie krzywej do kontenera

    // Krzywa 2
    GLfloat controlPoints2[4][3] = {
        { 0.0f, -6.0f, 0.0f },
        { 0.5f, 1.0f, 0.0f },
        { 0.5f, 5.0f, 0.0f },
        { 0.5f, 3.2f, 0.0f },
    };
    GLfloat knotVector2[8] = { 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.0f, 2.0f, 2.0f };
    curves.push_back(NURBSCurve(controlPoints2, knotVector2, 1.2f));

    // Krzywa 3
    GLfloat controlPoints3[4][3] = {
        { 0.0f, -6.0f, 0.0f },
        { -0.5f, 2.0f, 0.0f },
        { -0.5f, 6.0f, 0.0f },
        { -0.5f, 4.2f, 0.0f },
    };
    GLfloat knotVector3[8] = { 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.0f, 2.0f, 2.0f };
    curves.push_back(NURBSCurve(controlPoints3, knotVector3, 1.2f));

    // Krzywa 4
    GLfloat controlPoints4[4][3] = {
        { 0.0f, -6.0f, 0.0f },
        { -1.0f, 1.0f, 0.0f },
        { -1.0f, 4.0f, 0.0f },
        { -1.0f, 2.0f, 0.0f },
    };
    GLfloat knotVector4[8] = { 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.0f, 2.0f, 2.0f };
    curves.push_back(NURBSCurve(controlPoints4, knotVector4, 1.4f));

    // Krzywa 5
    GLfloat controlPoints5[4][3] = {
        { 0.0f, -6.0f, 0.0f },
        { 1.0f, 0.5f, 0.0f },
        { 1.0f, 1.0f, 0.0f },
        { 1.0f, 0.3f, 0.0f },
    };
    GLfloat knotVector5[8] = { 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.0f, 2.0f, 2.0f };
    curves.push_back(NURBSCurve(controlPoints5, knotVector5, 1.4f));

    // Krzywa 6
    GLfloat controlPoints6[4][3] = {
        { 0.0f, -
    6.0f, 0.0f },
        { 1.5f, -3.0f, 0.0f },
        { 1.5f, 0.0f, 0.0f },
        { 1.5f, -4.0f, 0.0f },
    };
    GLfloat knotVector6[8] = { 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.0f, 2.0f, 6.0f };
    curves.push_back(NURBSCurve(controlPoints6, knotVector6, 2.0f));

    // Krzywa 7
    GLfloat controlPoints7[4][3] = {
        { 0.0f, -6.0f, 0.0f },
        { -1.5f, -2.0f, 0.0f },
        { -1.5f, 1.0f, 0.0f },
        { -1.5f, -3.0f, 0.0f },
    };
    GLfloat knotVector7[8] = { 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.0f, 2.0f, 6.0f };
    curves.push_back(NURBSCurve(controlPoints7, knotVector7, 2.0f));
}

// Funkcja inicjalizuj¹ca ustawienia OpenGL
void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Ustawienie koloru t³a na bia³y
    glMatrixMode(GL_PROJECTION); // Ustawienie trybu macierzy projekcji
    glLoadIdentity();            // Zresetowanie macierzy

    gluPerspective(125.0, 640.0 / 480.0, 0.1, 100.0); // Ustawienie perspektywy
    glMatrixMode(GL_MODELVIEW);  // Ustawienie trybu macierzy modelu
    glLoadIdentity();            // Zresetowanie macierzy
    glTranslatef(0.0f, 0.0f, -5.0f); // Przesuniêcie wzd³u¿ osi Z

    glEnable(GL_DEPTH_TEST); // W³¹czenie testu g³êbokoœci
}

// Funkcja rysuj¹ca t³o
void drawSquares() {
    // Rysowanie zielonego kwadratu
    glColor3f(0.0f, 1.0f, 0.0f); 
    glBegin(GL_QUADS);         
    glVertex3f(-100.0f, -6.0f, 0.0f);
    glVertex3f(100.0f, -6.0f, 0.0f);
    glVertex3f(100.0f, -100.0f, 0.0f);
    glVertex3f(-100.0f, -100.0f, 0.0f);
    glEnd();

    // Rysowanie niebieskiego kwadratu
    glColor3f(0.0f, 0.5f, 1.0f); 
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, -100.0f, 0.0f);
    glVertex3f(100.0f, -100.0f, 0.0f);
    glVertex3f(100.0f, 100.0f, 0.0f);
    glVertex3f(-100.0f, 100.0f, 0.0f);
    glEnd(); 
}

// G³ówna funkcja programu
int main(void) {
    GLFWwindow* window; // WskaŸnik na okno GLFW

    if (!glfwInit()) // Inicjalizacja biblioteki GLFW
        return -1;

    // Tworzenie okna GLFW
    window = glfwCreateWindow(640, 480, "NURBS Curves", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Ustawienie okna jako bie¿¹cego kontekstu OpenGL
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // W³¹czenie synchronizacji pionowej

    initOpenGL(); // Inicjalizacja ustawieñ OpenGL
    initCurves(); // Inicjalizacja krzywych NURBS

    float startTime = glfwGetTime(); // Pocz¹tkowy czas aplikacji

    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime(); // Aktualny czas aplikacji
        float deltaTime = currentTime - startTime; // Obliczenie czasu delta

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Wyczyszczenie buforów

        // Aktualizacja i rysowanie ka¿dej krzywej NURBS
        for (auto& curve : curves) {
            curve.update(deltaTime); // Aktualizacja pozycji punktów kontrolnych
            curve.draw();            // Rysowanie krzywej NURBS
        }

        //drawSquares(); // Rysowanie t³a

        glfwSwapBuffers(window); // Zamiana buforów
        glfwPollEvents();        // Przetwarzanie zdarzeñ
    }

    glfwTerminate(); // Zakoñczenie GLFW
    return 0;
}
