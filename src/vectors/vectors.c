#include <vectors/vectors.h>

char_vector_t newCharVector() {
     char_vector_t vector;

     vector.data = NULL;
     vector.size = 0;
     vector.capacity = 0;

     return vector;
}

void charVectorPush(char_vector_t vector, char val) {
     if (vector.size == 0) {
          vector.data = malloc(sizeof(char));
     }
}
char charVectorPop(char_vector_t vector);
void charVectorPopAt(char_vector_t vector, size_t index);
char charVectorPeek(char_vector_t vector, size_t index);
