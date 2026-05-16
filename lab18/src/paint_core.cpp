#include "paint_core.hpp"
#include <algorithm>   // std::min, std::max, std::transform, std::fill
#include <cmath>       // std::abs
#include <stack>       // std::stack

extern std::stack<Canvas> undoStack;

// ========== Вспомогательная функция сохранения (уже готова) ==========
void saveToUndo(const Canvas& canvas) {
    undoStack.push(canvas);
}

// ========== 1. Очистка холста (оценка 3) ==========
void clearCanvas(Canvas& canvas) {
    for (auto& row : canvas) {
        std::fill(row.begin(), row.end(), sf::Color::White);
    }
}

// ========== 2. Рисование пикселя (оценка 3) ==========
void drawPixel(Canvas& canvas, int x, int y, const sf::Color& color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = color;
    }
}

// ========== 3. Круглая кисть (оценка 3) ==========
void drawBrush(Canvas& canvas, int x, int y, const sf::Color& color, int radius) {
    for (int dy = -radius; dy <= radius; ++dy) {
        for (int dx = -radius; dx <= radius; ++dx) {
            if (dx * dx + dy * dy <= radius * radius) {
                drawPixel(canvas, x + dx, y + dy, color);
            }
        }
    }
}

// ========== 4. Прямоугольник (оценка 3) ==========
void drawRectangle(Canvas& canvas, int x1, int y1, int x2, int y2, const sf::Color& color) {
    saveToUndo(canvas);   // уже есть, не удалять
    int left   = std::min(x1, x2);
    int right  = std::max(x1, x2);
    int top    = std::min(y1, y2);
    int bottom = std::max(y1, y2);
    for (int y = top; y <= bottom; ++y) {
        for (int x = left; x <= right; ++x){
            drawPixel(canvas, x, y, color);
        }
    }
}

// ========== 5. Линия (Брезенхем) (оценка 4) ==========
void drawLine(Canvas& canvas, int x1, int y1, int x2, int y2, const sf::Color& color) {
    saveToUndo(canvas);
    
    int A, B, sign;
    A = y2 - y1;
    B = x1 - x2;
    
    if (std::abs(A) > std::abs(B))
        sign = 1;
    else
        sign = -1;
    
    int signa, signb;
    if (A < 0)
        signa = -1;
    else
        signa = 1;
    
    if (B < 0)
        signb = -1;
    else
        signb = 1;
    
    int f = 0;
    drawPixel(canvas, x1, y1, color);
    
    int x = x1, y = y1;
    
    if (sign == -1) {
        do {
            f += A * signa;
            if (f > 0) {
                f -= B * signb;
                y += signa;
            }
            x -= signb;
            drawPixel(canvas, x, y, color);
        } while (x != x2 || y != y2);
    }
    else {
        do {
            f += B * signb;
            if (f > 0) {
                f -= A * signa;
                x -= signb;
            }
            y += signa;
            drawPixel(canvas, x, y, color);
        } while (x != x2 || y != y2);
    }   
}

// ========== 6. Undo (оценка 4) ==========
void undo(Canvas& canvas) {
    if (!undoStack.empty()) {
        canvas = undoStack.top();
        undoStack.pop();
    }
}

// ========== 7. Оттенки серого (оценка 5) ==========
void applyGrayscale(Canvas& canvas) {
    saveToUndo(canvas);
    for (auto& row : canvas) {
        std::transform(row.begin(), row.end(), row.begin(),
            [](const sf::Color& c) {
                sf::Uint8 gray = static_cast<sf::Uint8>((c.r + c.g + c.b) / 3);
                return sf::Color(gray, gray, gray, c.a);
            }
        );
    }

}

// ========== 8. Негатив (оценка 5) ==========
void applyNegative(Canvas& canvas) {
    saveToUndo(canvas);
    for (auto& row : canvas) {
        std::transform(row.begin(), row.end(), row.begin(),
            [](const sf::Color& c) {
                return sf::Color(255 - c.r, 255 - c.g, 255 - c.b, c.a);
            }
        );
    }
}

// ========== 9. Размытие (оценка 5) ==========
void applyBlur(Canvas& canvas) {
    saveToUndo(canvas);
    Canvas original = canvas;
    for (int y = 1; y < HEIGHT - 1; ++y) {
        for (int x = 1; x < WIDTH - 1; ++x) {
            int sumR = 0, sumG = 0, sumB = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    const sf::Color& p = original[y + dy][x + dx];
                    sumR += p.r;
                    sumG += p.g;
                    sumB += p.b;
                }
            }
            canvas[y][x] = sf::Color(
                static_cast<sf::Uint8>(sumR / 9),
                static_cast<sf::Uint8>(sumG / 9),
                static_cast<sf::Uint8>(sumB / 9),
                original[y][x].a
            );
        }
    }
}

// ========== Вспомогательная отрисовка (уже готова) ==========
void renderToWindow(sf::RenderWindow& window, const Canvas& canvas) {
    static sf::Image image;
    static sf::Texture texture;
    static sf::Sprite sprite;
    
    image.create(WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; ++y)
        for (int x = 0; x < WIDTH; ++x)
            image.setPixel(x, y, canvas[y][x]);
    
    texture.loadFromImage(image);
    texture.setSmooth(false);
    sprite.setTexture(texture);
    sprite.setScale(PIXEL_SIZE, PIXEL_SIZE);
    window.draw(sprite);
}