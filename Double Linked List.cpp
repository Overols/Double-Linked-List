#include <stdio.h>
#include <stdlib.h>

// struktur untuk node dari double linked list
struct node {
    int x; // value
    struct node *next;
    struct node *previous;
} *head, *tail, *current;

// untuk deklarasi fungsi
void delete_front();
void delete_back();

// function untuk membuat node baru
struct node* createNode(int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode -> x = value;
    newNode -> next = NULL;
    newNode -> previous = NULL;
    return newNode;
}

// function untuk menambahkan node di depan
void push_front(int value) {
    struct node* newNode = createNode(value);
    
    if (head == NULL) { // periksa apakah data kosong
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }
}

// function untuk menambahkan node di belakang
void push_back(int value) {
    struct node* newNode = createNode(value);
    
    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail -> next = newNode;
        newNode -> previous = tail;
        tail = newNode;
    }
}

// function untuk menambahkan node di tengah setelah kunci tertentu
void push_mid(int value, int searchKey) {
    struct node* newNode = createNode(value);
    
    if (head == NULL) {
        head = tail = newNode;
    } else {
        current = head;
        while (current != NULL) {
            if (current -> x == searchKey) {
                if (current == tail) {
                    push_back(value);
                } else {
                    newNode -> next = current->next;
                    newNode -> previous = current;
                    current -> next -> previous = newNode; // menghubungkan node berikut ke node baru
                    current -> next = newNode;
                }
                return;
            }
            current = current -> next;
        }
        printf("Data %d not found\n", searchKey);
        free(newNode); 
    }
}

// function untuk menghapus node di tengah berdasarkan kunci tertentu
void delete_mid(int searchKey) {
    if (head == NULL) {
        printf("No data to delete\n");
        return;
    }

    current = head;
    while (current != NULL) {
        if (current -> x == searchKey) {
            if (current == head) {
                delete_front(); // jika node yang dihapus adalah head
            } else if (current == tail) {
                delete_back(); // jika node yang dihapus adalah tail
            } else {
                current -> previous -> next = current->next; // menghubungkan node sebelumnya ke node berikutnya
                current -> next -> previous = current->previous; // menghubungkan node berikutnya ke node sebelumnya
                free(current);
            }
            return;
        }
        current = current->next;
    }
    printf("Data %d not found for deletion\n", searchKey);
}

// function untuk menghapus semua node
void clearData() {
    while (head != NULL) {
        current = head;
        head = head->next;
        free(current);
    }
    tail = NULL; 
}

// function untuk mencetak list
void printList() {
    if (head == NULL) {
        printf("There is no data\n");
        return;
    }
    
    current = head;
    while (current != NULL) {
        printf("%d ", current -> x);
        current = current -> next;
    }
    printf("\n");
}

// function untuk menghapus node depan
void delete_front() {
    if (head == NULL) {
        printf("No data\n");
    } else {
        struct node* del = head;
        head = head -> next;
        if (head != NULL) {
            head -> previous = NULL;
        } else {
            tail = NULL; // Jika list kosong
        }
        free(del);
    }
}

// function untuk menghapus node belakang
void delete_back() {
    if (head == NULL) {
        printf("No data\n");
    } else {
        struct node* del = tail;
        if (head == tail) {
            head = tail = NULL; // Jika hanya ada satu node
        } else {
            tail = tail -> previous;
            tail -> next = NULL; // mengupdate next dari tail yang baru
        }
        free(del);
    }
}

int main() {
    push_front(10);
    push_back(20);
    push_front(5);
    push_back(30);
    push_mid(15, 10);

    // mencetak list
    printf("List setelah penambahan data: ");
    printList();
    getchar();

    // menghapus node tengah dan mencetak list
    delete_mid(15);
    printf("List setelah menghapus node tengah: ");
    printList();
    getchar();

    // menghapus node depan dan mencetak list
    delete_front();
    printf("List setelah menghapus node depan: ");
    printList();
    getchar();

    // menghapus node belakang dan mencetak list
    delete_back();
    printf("List setelah menghapus node belakang: ");
    printList();
    getchar();

    // menghapus semua node
    clearData();
    printf("List setelah menghapus semua data: ");
    printList();
    getchar();

    return 0;
}