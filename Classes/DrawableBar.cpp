#include "DrawableBar.h"
#include <array>

DrawableBar::DrawableBar() {
    bar = new Bar();
}

Bar*
DrawableBar::getBar() {
    return bar;
}

DrawNode*
DrawableBar::getDrawNode() {
    return drawNode;
}

void
DrawableBar::createDrawNode() {

    drawNode = DrawNode::create();
    Position position = bar->getPosition();
    drawNode->setPosition(position.x, position.y);

    std::array<Point, 4> vertexes = {
        Point(0, 0),
        Point(bar->getWidth(), 0),
        Point(bar->getWidth(), bar->getHeight()),
        Point(0, bar->getHeight()),
    };
    float weight = 1.0f;
    drawNode->drawPolygon(vertexes.data(), vertexes.size(), Color4F::GREEN, weight, Color4F::GREEN);
}

