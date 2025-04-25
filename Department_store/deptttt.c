#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "store.txt"

struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
};

void addProduct();
void viewProducts();
void searchProduct();
void updateProduct();
void deleteProduct();

int main() {
    int choice;
    while (1) {
        printf("\n Departmental Store Management \n");
        printf("1: Add Product\n");
        printf("2: View Products\n");
        printf("3: Search Product\n");
        printf("4: Update Product\n");
        printf("5: Delete Product\n");
        printf("6: Exit\n");
        printf("Enter your choice = ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: exit(0);
            default: printf("Wrong choice\n");
        }
    }
    return 0;
}

void addProduct() {
    struct Product p;
    FILE *fp = fopen(FILE_NAME, "a");
    if (!fp) {
        printf("Something wrong with file entry\n");
        return;
    }
    printf("Enter Product ID = ");
    scanf("%d", &p.id);
    printf("Enter Product Name = ");
    scanf("%s", p.name);

    do {
        printf("Enter Price = ");
        scanf("%f", &p.price);
        if (p.price < 0)
            printf("Price cannot be negative. Please re-enter.\n");
    } while (p.price < 0);

    do {
        printf("Enter Quantity = ");
        scanf("%d", &p.quantity);
        if (p.quantity < 0)
            printf("Quantity cannot be negative. Please re-enter.\n");
    } while (p.quantity < 0);

    fprintf(fp, "%d %s %.2f %d\n", p.id, p.name, p.price, p.quantity);
    fclose(fp);

    printf("Product added successfully!\n");
}

void viewProducts() {
    struct Product p;
    FILE *fp = fopen(FILE_NAME, "r");

    if (!fp) {
        printf("Something wrong with file entry\n");
        return;
    }

    printf("ID\tName\t\tPrice\tQuantity\n");
    printf("----------------------------------------\n");

    int found = 0;
    while (fscanf(fp, "%d %s %f %d", &p.id, p.name, &p.price, &p.quantity) == 4) {
        printf("%d\t%-10s\t%.2f\t%d\n", p.id, p.name, p.price, p.quantity);
        found = 1;
    }

    if (!found) {
        printf("No products available.\n");
    }

    fclose(fp);
}

void searchProduct() {
    struct Product p;
    int id, found = 0;
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("Something wrong with file entry\n");
        return;
    }

    printf("Enter Product ID to search = ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %f %d", &p.id, p.name, &p.price, &p.quantity) == 4) {
        if (p.id == id) {
            printf("Product Found!\n");
            printf("ID = %d\nName = %s\nPrice = %.2f\nQuantity = %d\n", 
                   p.id, p.name, p.price, p.quantity);
            found = 1;
            break;
        }
    }

    fclose(fp);
    if (!found) {
        printf("Product not found!\n");
    }
}

void updateProduct() {
    struct Product p;
    int id, found = 0;
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Something wrong with file entry\n");
        return;
    }

    printf("Enter Product ID to update = ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %f %d", &p.id, p.name, &p.price, &p.quantity) == 4) {
        if (p.id == id) {
            printf("Enter New Product Name = ");
            scanf("%s", p.name);

            do {
                printf("Enter New Price = ");
                scanf("%f", &p.price);
                if (p.price < 0)
                    printf("Price cannot be negative. Please re-enter.\n");
            } while (p.price < 0);

            do {
                printf("Enter New Quantity = ");
                scanf("%d", &p.quantity);
                if (p.quantity < 0)
                    printf("Quantity cannot be negative. Please re-enter.\n");
            } while (p.quantity < 0);

            found = 1;
        }
        fprintf(temp, "%d %s %.2f %d\n", p.id, p.name, p.price, p.quantity);
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Product updated successfully!\n");
    else
        printf("Product not found!\n");
}

void deleteProduct() {
    struct Product p;
    int id, found = 0;
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Something wrong with file entry\n");
        return;
    }

    printf("Enter Product ID to delete = ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %f %d", &p.id, p.name, &p.price, &p.quantity) == 4) {
        if (p.id == id) {
            found = 1;
            continue;
        }
        fprintf(temp, "%d %s %.2f %d\n", p.id, p.name, p.price, p.quantity);
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Product deleted successfully!\n");
    else
        printf("Product not found!\n");
}
