#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"
struct BigInteger {
    struct node *head;
    int len;
};

struct node {
    struct node *next;
    int data;
};

struct node *createnode(struct node **head, int data) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
    if (*head == NULL) {
        *head = newnode;
    } else {
        struct node *cur = *head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newnode;
    }
    return newnode;
}
struct node *reverse(struct node **head) {
    struct node *prev = NULL, *current = *head, *next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
    return *head;
}
struct BigInteger initialize(char *s) {
    struct BigInteger a;
    struct node *newnode = NULL;
    int i, len = 0;
    for (i = 0; s[i] != '\0'; i++) {
        int digit = s[i] - '0';
        len++;
        createnode(&newnode, digit);
    }
    a.head = newnode;
    a.len = len;
    return a;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct node *bigA = reverse(&a.head);
    struct node *bigB = reverse(&b.head);
    struct node *result = NULL;
    int sum = 0, carry = 0;
    while (bigA || bigB) {
        sum = 0;
        if (bigA) {
            sum = sum + bigA->data;
        }
        if (bigB) {
            sum = sum + bigB->data;
        }
        sum = sum + carry;
        carry = sum / 10;
        sum = sum % 10;
        createnode(&result, sum);
        if (bigA) {
            bigA = bigA->next;
        }
        if (bigB) {
            bigB = bigB->next;
        }
    }
    if (carry)
        result = createnode(&result, carry);
    result = reverse(&result);
    struct BigInteger su;
    su.head = result;
    return su;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b) 
{
    struct node *bigA = reverse(&a.head);
    struct node *bigB = reverse(&b.head);
    struct node *res = NULL;
    int bor = 0;

    while (bigA || bigB) {
        int numA = bigA ? bigA->data : 0;
        int numB = bigB ? bigB->data : 0;
        int diff = numA - numB - bor;

        if (diff < 0) {
            diff += 10;
            bor = 1;
        } else {
            bor = 0;
        }

        createnode(&res, diff);

        if (bigA) {
            bigA = bigA->next;
        }
        if (bigB) {
            bigB = bigB->next;
        }
    }
    while (res && res->data == 0) {
        struct node *temp = res;
        res = res->next;
        free(temp);
    }
    if (!res) {
        struct BigInteger zero;
        zero.head = createnode(&zero.head, 0);
        zero.len = 1;
        return zero;
    }

    res = reverse(&res);

    struct BigInteger su;
    su.head = res;
    return su;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b) {
    struct node *bigA = a.head;
    struct node *bigB = b.head;
    struct node *result = NULL;
    struct node *res = NULL;
    struct node *itr = bigA;
    struct node *ptr = bigB;
    long n1 = 0, n2 = 0, n3;
    while (itr) {
        n1 = n1 * 10 + itr->data;
        itr = itr->next;
    }
    while (ptr) {
        n2 = n2 * 10 + ptr->data;
        ptr = ptr->next;
    }
    n3 = n1 * n2;
    while (n3 > 0) {
        createnode(&result, n3 % 10);
        n3 = n3 / 10;
    }
    result = reverse(&result);
    struct BigInteger su;
    su.head= result;
    return su;
}


struct BigInteger div1(struct BigInteger a, struct BigInteger b) {
    struct node *bigA = a.head;
    struct node *bigB = b.head;
    struct node *res = NULL;
    int n1 = 0, n2 = 0, n3;
    struct node *itr = bigA;
    struct node *ptr = bigB;
    while (itr) {
        n1 = n1 * 10 + itr->data;
        itr = itr->next;
    }
    while (ptr) {
        n2 = n2 * 10 + ptr->data;
        ptr = ptr->next;
    }
    n3 = n1 / n2;
    while (n3 > 0) {
        createnode(&res, n3 % 10);
        n3 = n3 / 10;
    }
    struct node *result = reverse(&res);
    struct BigInteger c;
    c.head = result;
    return c;
}

//struct BigInteger mod(struct BigInteger a, struct BigInteger b) {
  //  struct BigInteger quotient = div1(a, b); // Calculate the quotient
    //struct BigInteger product = mul(quotient, b); // Multiply quotient by b
    //struct BigInteger result = sub(a, product); // Subtract product from a to get the modulus
    //if (result.l == NULL) {
      //  result.l = createnode(&(result.l), 0);
    //}

    //return result;
//}


void display(struct BigInteger a) {
    struct node *itr = a.head;
    while (itr) {
        printf("%d", itr->data);
        itr = itr->next;
        a.len++;
    }
}