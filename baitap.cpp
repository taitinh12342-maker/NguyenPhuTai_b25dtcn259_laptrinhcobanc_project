#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
typedef struct TransactionStruct {
    char transId[20];
    char productId[10];
    char type[5];
    char date[15];
} Transaction;

typedef struct ProductStruct {
    char productId[20]; 
    char name[50];
    char unit[20];
    int qty;
    int status;
} Product;

Product listProduct[MAX];
int n_product = 0;
Transaction listTransaction[MAX];
int n_transaction=0;

int productExisted(char productId[]);
void addProduct();
void updateProduct();
void managementProduct();
void searchProduct();
void listmaterialsProduct();
void sortProduct();
void In_OutTransaction(Product listProduct[], int n_product);
void History_Transaction();


int main(){
	char choiceStr[20];
	int choice;
	while(1){
	system("cls");
	printf("+------------- MENU -----------------+");
	printf("\n| 1.Them ma hang moi                 |");
	printf("\n+------------------------------------+");
	printf("\n| 2.Cap nhap thong tin               |");
	printf("\n+------------------------------------+");
	printf("\n| 3.Quan ly trang thai               |");
	printf("\n+------------------------------------+");
	printf("\n| 4.Tra cuu                          |");
	printf("\n+------------------------------------+");
	printf("\n| 5.Danh sach                        |");
	printf("\n+------------------------------------+");
	printf("\n| 6.Sap xep danh sach                |");
	printf("\n+------------------------------------+");
	printf("\n| 7.Giao dich xuat/nhap hang hoa     |");
	printf("\n+------------------------------------+");
	printf("\n| 8.Lich su xuat/nhap                |\n");
	printf("+------------------------------------+");
	printf("\nmoi ban chon:");
        fflush(stdin);
        fgets(choiceStr, sizeof(choiceStr), stdin);
        choice = atoi(choiceStr);
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
            	 managementProduct();
                break;
            case 4:
                 searchProduct();
                break;
            case 5:
                 listmaterialsProduct();
                break;
            case 6:
            	sortProduct();
                break;
            case 7:
            	 In_OutTransaction(listProduct, n_product);
                break;
            case 8:
            	History_Transaction();
                break;
            default:
                printf("Lua chon khong hop le!\nVui long nhap lai!\n");
                system("pause");
        }
    }
}

void addProduct() {
    if (n_product >= MAX) {
        printf("\nDanh sach san pham da day!\n");
        system("pause");
        return;
    }

    Product p;
    fflush(stdin);

    do {
        printf("\nNhap ma hang hoa: ");
        fgets(p.productId, sizeof(p.productId), stdin);
        p.productId[strcspn(p.productId, "\n")] = '\0';

        if (strlen(p.productId) == 0) {
            printf(" Ma hang khong duoc rong!\n");
        } else if (productExisted(p.productId)) {
            printf(" Ma hang da ton tai!\n");
        }

    } while (strlen(p.productId) == 0 || productExisted(p.productId));

    do {
        printf("Nhap ten hang hoa: ");
        fgets(p.name, sizeof(p.name), stdin);
        p.name[strcspn(p.name, "\n")] = '\0';

        if (strlen(p.name) == 0) {
            printf(" Ten hang hoa khong duoc rong!\n");
        }

    } while (strlen(p.name) == 0);
  do {
        printf("Nhap don vi (cai/kg/hop): ");
        fgets(p.unit, sizeof(p.unit), stdin);
        p.unit[strcspn(p.unit, "\n")] = '\0';

        if(!(strcmp(p.unit, "cai") == 0 || strcmp(p.unit, "kg") == 0  ||strcmp(p.unit, "hop") == 0)) {

            printf("Don vi khong hop le! \nChi chap nhan: cai, kg, hop.\n");
        }
    } while(!(strcmp(p.unit, "cai") == 0 || strcmp(p.unit, "kg") == 0  || strcmp(p.unit, "hop") == 0));


    char qtyStr[20];
int isNumber;

do {
    printf("Nhap so luong ton kho: ");
    fflush(stdin);
    fgets(qtyStr, sizeof(qtyStr), stdin);
    qtyStr[strcspn(qtyStr, "\n")] = '\0';

    isNumber = 1;
    for (int i = 0; i < strlen(qtyStr); i++) {
        if (qtyStr[i] < '0' || qtyStr[i] > '9') {
            isNumber = 0;
            break;
        }
    }

    if (!isNumber || strlen(qtyStr) == 0) {
        printf("Chi duoc nhap so nguyen (=> 0)!\n");
        continue;
    }

    p.qty = atoi(qtyStr);

} while (!isNumber || p.qty < 0);

    p.status = 1;
    listProduct[n_product++] = p;
    printf("\n Them thanh cong!\n");
    system("pause");
}
int productExisted(char productId[]) {
    for (int i = 0; i < n_product; i++) {
        if (strcmp(listProduct[i].productId, productId) == 0) {
            return 1;
        }
    }
    return 0;
}





void updateProduct() {
    if (n_product == 0) {
        printf("\nKhong co san pham de cap nhat!\n");
        system("pause");
        return;
    }

    char id[20];
    fflush(stdin);

    printf("\nNhap ma san pham can cap nhat: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = -1;

    for (int i = 0; i < n_product; i++) {
        if (strcmp(listProduct[i].productId, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\n Khong tim thay san pham!\n");
        system("pause");
        return;
    }

    Product *p = &listProduct[index];
    printf("\n======= THONG TIN HIEN TAI =======\n");
    printf("Ma san pham (khong duoc sua): %s\n", p->productId);
    printf("Ten: %s\n", p->name);
    printf("Don vi: %s\n", p->unit);
    printf("So luong: %d\n", p->qty);
    printf("\n======= NHAP THONG TIN MOI =======\n");
    char newName[50];
    do {
        printf("Nhap ten moi: ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = '\0';

        if (strlen(newName) == 0) {
            printf("Ten khong duoc de rong!\n");
        }

    } while (strlen(newName) == 0);
    strcpy(p->name, newName);

    char newUnit[20];
    do {
        printf("Nhap don vi moi (cai / kg / hop): ");
        fgets(newUnit, sizeof(newUnit), stdin);
        newUnit[strcspn(newUnit, "\n")] = '\0';

        if (strlen(newUnit) == 0) {
            printf("Don vi khong duoc rong!\n");
            continue;
        }

        if (!(strcmp(newUnit, "cai") == 0 ||
              strcmp(newUnit, "kg") == 0  ||
              strcmp(newUnit, "hop") == 0)) 
        {
            printf("Don vi KHONG hop le!\n   Chi chap nhan: cai, kg, hop.\n");
        }

    } while (!(strcmp(newUnit, "cai") == 0 ||
               strcmp(newUnit, "kg") == 0  ||
               strcmp(newUnit, "hop") == 0));

    strcpy(p->unit, newUnit);
    
    
    char qtyStr[20];
    int newQty;
    int isNumber;

    do {
        printf("Nhap so luong moi (>= 0): ");
        fgets(qtyStr, sizeof(qtyStr), stdin);
        qtyStr[strcspn(qtyStr, "\n")] = '\0';

        if (strlen(qtyStr) == 0) {
            printf("? Khong duoc de trong!\n");
            continue;
        }
        isNumber = 1;
        for (int i = 0; i < strlen(qtyStr); i++) {
            if (qtyStr[i] < '0' || qtyStr[i] > '9') {
                isNumber = 0;
                break;
            }
        }

        if (!isNumber) {
            printf("Chi duoc nhap so >= 0!\n");
            continue;
        }

        newQty = atoi(qtyStr);

        if (newQty < 0) {
            printf("So luong phai >= 0!\n");
        }

    } while (!isNumber || newQty < 0);

    p->qty = newQty;

    printf("\n Cap nhat thanh cong!\n");
    system("pause");
}




void managementProduct() {
    if (n_product == 0) {
        printf("\nDanh sach rong! Khong co san pham de doi trang thai.\n");
        system("pause");
        return;
    }

    char id[20];
    fflush(stdin);

    printf("\nNhap ma vat tu can doi trang thai: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = -1;
    for (int i = 0; i < n_product; i++) {
        if (strcmp(listProduct[i].productId, id) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\n Ma vat tu khong ton tai!\n");
        system("pause");
        return;
    }

    listProduct[index].status = 0;

  printf("\n Doi trang thai thanh cong! Ma hang: %s\n", listProduct[index].productId);

    system("pause");
}
void searchProduct() {
    char key[50];
    int found = 0;

retry:
    fflush(stdin);
    printf("\nNhap ma hang hoa hoac ten can tra cuu: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    if (strlen(key) == 0) {
        printf("\n!Khong duoc de trong. Nhap lai!\n");
        goto retry;
    }

    printf("\n========== KET QUA TRA CUU ==========\n");

    for (int i = 0; i < n_product; i++) {

        if (strcmp(listProduct[i].productId, key) == 0 ||strcmp(listProduct[i].name, key) == 0) {
            found = 1;

            printf("\nMa san pham: %s", listProduct[i].productId);
            printf("\nTen san pham: %s", listProduct[i].name);
            printf("\nDon vi: %s", listProduct[i].unit);
            printf("\nSo luong: %d", listProduct[i].qty);
            if (listProduct[i].status == 1) {
 		        printf("\nTrang thai: Hoat dong");
			}   else {
  		             printf("\nTrang thai: Da het han");
               }

        }
    }

    if (!found) {
        printf("\n! Khong tim thay san pham!\n");
    }

    printf("\n");
    system("pause");
}





void listmaterialsProduct() {
    if (n_product == 0) {
        printf("\nDanh sach san pham trong!\n");
        return;
    }
    int page = 1;
    int itemPerPage = 10;
    int index = 0;
    char c;

    do {
        index = (page - 1) * itemPerPage;
        printf("\nTrang %d:\n", page);

        for (int j = 0; j < 83; j++) printf("-");
        printf("\n| %15s | %20s | %10s | %10s | %12s |\n",
               "Ma san pham", "Ten san pham", "Don vi", "So luong", "Trang thai");
        for (int j = 0; j < 83; j++) printf("-");

        for (int i = index; i < index + itemPerPage && i < n_product; i++) {
            printf("\n| %15s | %20s | %10s | %10d | %12s |\n",
                   listProduct[i].productId,
                   listProduct[i].name,
                   listProduct[i].unit,
                   listProduct[i].qty,
                   listProduct[i].status == 1 ? "Con su dung" : "Da het han");
            for (int j = 0; j < 83; j++) printf("-");
        }
        do {
            printf("\nBan muon chuyen trang? (y/n): ");
            scanf(" %c", &c);
            if (c!='y' && c!='Y' && c!='n' && c!='N') {
                printf("\nLua chon khong hop le!");
            }
        } while (c!='y' && c!='Y' && c!='n' && c!='N');

        if (c=='y' || c=='Y') {
            printf("\nNhap so trang (1-%d): ", (n_product + itemPerPage - 1) / itemPerPage);
            scanf("%d", &page);
            if (page < 1 || page > (n_product + itemPerPage - 1) / itemPerPage) {
                printf("\nTrang nay khong hop le. Quay ve trang 1\n");
                page = 1;
            }
        }

    } while (c=='y' || c=='Y');
}


void sortProduct() {
    if (n_product == 0) {
        printf("\nDanh sach rong! Khong the sap xep.\n");
        system("pause");
        return;
    }

    char choiceStr[10];
    int choice;

    printf("\nBAN MUON CHON LOAI SAP XEP?\n");
    printf("1. Sap xep theo Ten (A-Z)\n");
    printf("2. Sap xep theo So luong (Tang dan)\n");
    printf("Moi chon: ");

    fflush(stdin);
    fgets(choiceStr, sizeof(choiceStr), stdin);
    choice = atoi(choiceStr);

    Product temp;

    switch (choice) {
        case 1:  
            for (int i = 0; i < n_product - 1; i++) {
                for (int j = i + 1; j < n_product; j++) {
                    if (strcmp(listProduct[i].name, listProduct[j].name) > 0) {
                        temp = listProduct[i];
                        listProduct[i] = listProduct[j];
                        listProduct[j] = temp;
                    }
                }
            }
            printf("\nSap xep theo ten thanh cong!\n");
            break;

        case 2:
            for (int i = 0; i < n_product - 1; i++) {
                for (int j = i + 1; j < n_product; j++) {
                    if (listProduct[i].qty > listProduct[j].qty) {
                        temp = listProduct[i];
                        listProduct[i] = listProduct[j];
                        listProduct[j] = temp;
                    }
                }
            }
            printf("\nSap xep theo so luong thanh cong!\n");
            break;

        default:
            printf("\nLua chon khong hop le!\n");
            system("pause");
            return;
    }

    printf("\n========= DANH SACH SAU KHI SAP XEP =========\n");
    listmaterialsProduct();
}


void In_OutTransaction(Product listProduct[], int n_product){
    char id[20];
    int found = -1;
    char type[20];
    char quantity[30];
    int Qty;
    char date[20];

    fflush(stdin);

    do {
        printf("\nNhap ma vat tu: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = '\0';
        if (strlen(id) == 0){
            printf("\nKhong de trong");
        } else if (productExisted(id) == 0){
            printf("\nMa vat tu %s khong ton tai", id);
        }
    } while(strlen(id) == 0 || productExisted(id) == 0);

    for (int i = 0; i < n_product; i++){
        if (strcmp(listProduct[i].productId, id) == 0){
            found = i;
            break;
        }
    }
    do {
        printf("\nNhap loai giao dich (Xuat/Nhap): ");
        fgets(type, sizeof(type), stdin);
        type[strcspn(type, "\n")] = '\0';
        if (strcmp(type, "Xuat") != 0 && strcmp(type, "Nhap") != 0){
            printf("\nDu lieu khong hop le");
        }
    } while(strcmp(type, "Xuat") != 0 && strcmp(type, "Nhap") != 0);

    do {
        printf("\nNhap so luong: ");
        fgets(quantity, sizeof(quantity), stdin);
        quantity[strcspn(quantity, "\n")] = '\0';
        Qty = atoi(quantity);

        if (Qty <= 0){
            printf("\nSo luong nhap phai > 0\n");
        } else if(strcmp(type, "Xuat") == 0 && Qty > listProduct[found].qty){
            printf("\nSo luong xuat hang hoa ma %s vuot qua so luong hien co\n", id);
            Qty = -1;
        }
    } while(Qty <= 0);

    do {
        printf("\nNhap ngay thang nam giao dich(DD/MM/YYYY): ");
        fgets(date, sizeof(date), stdin);
        date[strcspn(date, "\n")] = '\0';
        if (strlen(date) == 0){
            printf("\nKhong de trong");
        }
    } while(strlen(date) == 0);

    if (strcmp(type, "Nhap") == 0){
        listProduct[found].qty += Qty;
    } else if (strcmp(type, "Xuat") == 0){
        listProduct[found].qty -= Qty;   
    }

    Transaction t;
    sprintf(t.transId, "T%03d", n_transaction + 1);
    strcpy(t.productId, id);
    strcpy(t.type, type);
    strcpy(t.date, date);

    listTransaction[n_transaction] = t;
    n_transaction++;

    if(strcmp(type, "Xuat") == 0){
        printf("\nXuat hang hoa ma %s thanh cong\n", id);
    } else if (strcmp(type, "Nhap") == 0){
        printf("\nNhap hang hoa ma %s thanh cong\n", id);
    }

    printf("\nNhan Enter de tiep tuc...");	
    while(getchar() != '\n');
    getchar();
}


void History_Transaction(){
	if (n_transaction == 0){
		printf("\nChua co giao dich nao");
		fflush(stdin);
		getchar();
		return;
	}
	for (int i = 0; i < 56; i++){
		printf("-");
	}
	printf("\n|                  LICH SU GIAO DICH                   |");
	printf("\n");
	for (int i = 0; i < 56; i++){
		printf("-");
	}
	printf("\n|  %12s  |   %9s   |   %4s   |   %4s   |", "Ma giao dich", "Ma vat tu","Loai","Ngay");
	printf("\n");
	for (int i = 0; i < 56; i++){
		printf("-");
	}
	for (int i = 0; i < n_transaction; i++){
		printf("\n|%16s|%15s|%10s|%10s|", listTransaction[i].transId, listTransaction[i].productId, listTransaction[i].type, listTransaction[i].date);
	}
	printf("\n");
	for (int i = 0; i < 56; i++){
		printf("-");
	}
	fflush(stdin);
	getchar();
}


