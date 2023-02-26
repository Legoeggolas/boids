#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include <array>
#include <memory>
#include <utility>

#include "raylib/raylib-cpp.hpp"

using Vec2 = raylib::Vector2;

template <typename T>
class QTreeNode {
   public:
    std::pair<Vec2, Vec2> bounds;
    std::vector<T> points;

    std::array<std::unique_ptr<QTreeNode>, 4> children;

    QTreeNode(std::pair<Vec2, Vec2> _bounds) {
        bounds = bounds;
    }

    bool contains(Vec2 const &point) {
        if (point.x < bounds.first.x || point.x > bounds.second.x) {
            return false;
        }

        if (point.y < bounds.first.y || point.y > bounds.second.y) {
            return false;
        }

        return true;
    }

    void divide() {
        float length = abs(bounds.first.x - bounds.second.x);
        float width = abs(bounds.first.y - bounds.second.y);

        QTreeNode quadOne = new QTreeNode(std::make_pair(Vec2{bounds.first.x + length / 2, bounds.first.y},
                                                         Vec2{bounds.second.x, bounds.second.y - width / 2}));
        QTreeNode quadTwo = new QTreeNode(std::make_pair(bounds.first,
                                                         Vec2{bounds.second.x - length / 2, bounds.second.y - width / 2}));
        QTreeNode quadThree = new QTreeNode(std::make_pair(Vec2{bounds.first.x, bounds.first.y + width / 2},
                                                           Vec2{bounds.second.x - length / 2}, bounds.second.y));
        QTreeNode quadFour = new QTreeNode(std::make_pair(Vec2{bounds.first.x + length / 2, bounds.first.y + width / 2},
                                                          bounds.second));

        children = {std::unique_ptr<QTreeNode>(quadOne),
                    std::unique_ptr<QTreeNode>(quadTwo),
                    std::unique_ptr<QTreeNode>(quadThree),
                    std::unique_ptr<QTreeNode>(quadFour)};

        while (!points.empty()) {
            auto curr = points.back();

            for (auto &quad : children) {
                if (quad->contains(curr->position)) {
                    quad.insert(curr);
                    break;
                }
            }

            points.pop_back();
        }
    }

    void insert(std::shared_ptr<T> object) {
        Vec2 pos = T->position;

        if (children[0] == nullptr) {
            points.push_back(object);

            if (points.size() >= 4) {
                divide();
            }
            return;
        }

        for (auto child : children) {
            if (child.contains(object->position)) {
                child.insert(object);
                break;
            }
        }
    }

    std::vector<std::unique_ptr<T>> query(std::pair<Vec2, Vec2> const &queryBounds) {
    }
};

#endif
