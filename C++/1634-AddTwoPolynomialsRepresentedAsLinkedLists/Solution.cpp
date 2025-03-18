#ifdef LOCAL
struct PolyNode {
  int coefficient, power;
  PolyNode* next;
  PolyNode() : coefficient(0), power(0), next(nullptr) {};
  PolyNode(int x, int y) : coefficient(x), power(y), next(nullptr) {};
  PolyNode(int x, int y, PolyNode* next)
      : coefficient(x), power(y), next(next) {};
};
#endif  // LOCAL

class Solution {
 public:
  PolyNode* addPoly(PolyNode* poly1, PolyNode* poly2) {
    if (!poly1) {
      return poly2;
    }

    if (!poly2) {
      return poly1;
    }

    if (poly1->power == poly2->power) {
      poly1->coefficient += poly2->coefficient;
      poly1->next = addPoly(poly1->next, poly2->next);
      if (poly1->coefficient == 0) {
        return poly1->next;
      }

      return poly1;
    }

    if (poly1->power > poly2->power) {
      poly1->next = addPoly(poly1->next, poly2);
      return poly1;
    }

    poly2->next = addPoly(poly1, poly2->next);
    return poly2;
  }
};
