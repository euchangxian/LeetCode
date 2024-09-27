struct PolyNode {
  int coefficient, power;
  PolyNode *next;
  PolyNode() : coefficient(0), power(0), next(nullptr){};
  PolyNode(int x, int y) : coefficient(x), power(y), next(nullptr){};
  PolyNode(int x, int y, PolyNode *next)
      : coefficient(x), power(y), next(next){};
};
