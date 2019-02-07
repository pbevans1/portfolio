typedef struct _vector {
    int size;
    int capacity;
    int *contents;
} vector;

vector* newVector();
void pushToVec(vector*, int);
int popFromVec(vector*);
vector* destroyVec(vector*);
void test_vector();
