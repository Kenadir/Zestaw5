#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

const char PIXEL_EMPTY = ' ';
const char PIXEL_FILLED = '#';

class Canvas {
private:
    int width;
    int height;
    vector<vector<char>> pixels;

public:
    Canvas(int width, int height) : width(width), height(height) {
        pixels.resize(height, vector<char>(width, PIXEL_EMPTY));
    }

    void setPixel(int x, int y, char ch) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y][x] = ch;
        }
    }

    void printToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << "|" << string(width, '=') << "|\n";
            for (int y = 0; y < height; y++) {
                file << "|";
                for (int x = 0; x < width; x++) {
                    file << pixels[y][x];
                }
                file << "|\n";
            }
            file << "|" << string(width, '=') << "|\n";
            file.close();
        }
    }

    void clear() {
        for (auto& row : pixels) {
            fill(row.begin(), row.end(), PIXEL_EMPTY);
        }
    }
};

class Figure {
protected:
    int centerX;
    int centerY;
    int dimensions;
    char symbol;

public:
    Figure(int centerX, int centerY, int dimensions, char symbol) : centerX(centerX), centerY(centerY), dimensions(dimensions), symbol(symbol) {}

    virtual void draw(Canvas& canvas) = 0;
};

class Rectangle : public Figure {
public:
    Rectangle(int centerX, int centerY, int width, int height, char symbol) : Figure(centerX, centerY, std::max(width, height), symbol) {}

    void draw(Canvas& canvas) override {
        int startX = centerX - dimensions / 2;
        int startY = centerY - dimensions / 2;

        for (int y = 0; y < dimensions; ++y) {
            for (int x = 0; x < dimensions; ++x) {
                canvas.setPixel(startX + x, startY + y, symbol);
            }
        }
    }
};

class Circle : public Figure {
public:
    Circle(int centerX, int centerY, int radius, char symbol) : Figure(centerX, centerY, radius, symbol) {}

    void draw(Canvas& canvas) override {
        int startX = centerX - dimensions;
        int startY = centerY - dimensions;

        for (int y = 0; y <= dimensions * 2; ++y) {
            for (int x = 0; x <= dimensions * 2; ++x) {
                int dx = x - dimensions;
                int dy = y - dimensions;
                if (dx * dx + dy * dy <= dimensions * dimensions) {
                    canvas.setPixel(startX + x, startY + y, symbol);
                }
            }
        }
    }
};

vector<string> splitString(const string& str, char delimiter) {
    vector<std::string> tokens;
    istringstream iss(str);
    string token;
    while (getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<Figure*> parseConfigFile(const string& filename, Canvas& canvas) {
    vector<Figure*> figures;

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        int lineNumber = 0;
        while (getline(file, line)) {
            if (!line.empty()) {
                try {
                    vector<string> tokens = splitString(line, ' ');

                    if (tokens[0] == "Canvas") {
                        int width = stoi(tokens[1]);
                        int height = stoi(tokens[2]);
                        canvas = Canvas(width, height);
                    } else if (tokens[0] == "EmptySymbol") {
                        char emptySymbol = tokens[1][0];
                        emptySymbol = PIXEL_EMPTY;
                    } else if (tokens[0] == "Figure") {
                        string figureType = tokens[1];
                        int centerX = stoi(tokens[2]);
                        int centerY = stoi(tokens[3]);
                        int dimensions = stoi(tokens[4]);
                        char symbol = tokens[5][0];

                        Figure* figure = nullptr;
                        if (figureType == "Rectangle") {
                            int x = stoi(tokens[2]);
                            int y = stoi(tokens[3]);
                            int width = stoi(tokens[4]);
                            int height = stoi(tokens[5]);
                            char symbol = tokens[6][0];
                            figures.push_back(new Rectangle(x, y, width, height, symbol));
                        } else if (figureType == "Circle") {
                            figure = new Circle(centerX, centerY, dimensions, symbol);
                        }

                        if (figure != nullptr) {
                            figures.push_back(figure);
                        }
                    }
                } catch (const exception& e) {
                    cerr << "Błąd w wierszu " << lineNumber << ": " << line << endl;
                    cerr << "Wyjątek: " << e.what() << endl;
                }
            }
            lineNumber++;
        }

        file.close();
    }

    return figures;
}

void drawFiguresOnCanvas(const vector<Figure*>& figures, Canvas& canvas) {
    for (Figure* figure : figures) {
        figure->draw(canvas);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./ascii_art <config_file>" << endl;
        return 1;
    }

    string configFilename = argv[1];

    Canvas canvas(0, 0);
    vector<Figure*> figures = parseConfigFile(configFilename, canvas);

    drawFiguresOnCanvas(figures, canvas);
    canvas.printToFile("output.txt");

    for (Figure* figure : figures) {
        delete figure;
    }

    return 0;
}