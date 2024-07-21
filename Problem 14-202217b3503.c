
#include <stdio.h>

#define MAX_NODE 15

// Tree representation (1-based index for simplicity)
char tree[] = {'\0', 'D', 'A', 'F', 'E', 'B', 'R', 'T', 'G', 'Q', '\0', '\0', 'V', '\0', 'J', 'L'};

// Get the left child index
int get_left_child(int index) {
    int left_index = 2 * index;
    if (left_index <= MAX_NODE && tree[left_index] != '\0') {
        return left_index;
    }
    return -1;
}

// Get the right child index
int get_right_child(int index) {
    int right_index = 2 * index + 1;
    if (right_index <= MAX_NODE && tree[right_index] != '\0') {
        return right_index;
    }
    return -1;
}

// Pre-order traversal: Root - Left - Right
void preorder(int index) {
    if (index > 0 && tree[index] != '\0') {
        printf(" %c ", tree[index]);
        preorder(get_left_child(index));
        preorder(get_right_child(index));
    }
}

// Post-order traversal: Left - Right - Root
void postorder(int index) {
    if (index > 0 && tree[index] != '\0') {
        postorder(get_left_child(index));
        postorder(get_right_child(index));
        printf(" %c ", tree[index]);
    }
}

// In-order traversal: Left - Root - Right
void inorder(int index) {
    if (index > 0 && tree[index] != '\0') {
        inorder(get_left_child(index));
        printf(" %c ", tree[index]);
        inorder(get_right_child(index));
    }
}

int main() {
    printf("Preorder:\n");
    preorder(1);
    printf("\nPostorder:\n");
    postorder(1);
    printf("\nInorder:\n");
    inorder(1);
    printf("\n");
    return 0;
}