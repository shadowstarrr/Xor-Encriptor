#include <stdio.h>
#include <string.h>

void xorCipher(char *msg, char *key) {
    int msgLen = strlen(msg);
    int keyLen = strlen(key);

    for (int i = 0; i < msgLen; i++) {
        msg[i] ^= key[i % keyLen];
    }
}

void hexToBytes(const char *hexStr, char *out) {
    int i = 0;
    unsigned int val;
    const char *p = hexStr;

    while (sscanf(p, "%2x", &val) == 1) {
        out[i++] = (char)val;
        p += 2;
        while (*p == ' ' || *p == '\n') p++;
    }
    out[i] = '\0';
}

int main() {
    char message[256];
    char key[256];
    char hexInput[1024];
    int option;

    while (1) {
        printf("[Encriptor] To exit use Ctrl + C\n");
        printf("1 - Encrypt Message\n");
        printf("2 - Decrypt Message (from hex)\n> ");

        if (scanf("%d", &option) != 1) {
            printf("Opção inválida!\n");
            while(getchar() != '\n');
            continue;
        }
        getchar();

        if (option == 1) {
            printf("Qual a mensagem?\n> ");
            fgets(message, sizeof(message), stdin);

            printf("Qual a chave?\n> ");
            fgets(key, sizeof(key), stdin);

            xorCipher(message, key);

            printf("Encriptografado (hex): ");
            for (int i = 0; i < (int)strlen(message); i++) {
                printf("%02X ", (unsigned char)message[i]);
            }
            printf("\n\n");

        } else if (option == 2) {
            printf("Digite a mensagem criptografada (hex):\n> ");
            fgets(hexInput, sizeof(hexInput), stdin);

            printf("Qual a chave?\n> ");
            fgets(key, sizeof(key), stdin);

            hexToBytes(hexInput, message);
            xorCipher(message, key);

            printf("Mensagem descriptografada: %s\n\n", message);
        } else {
            printf("Opção inválida!\n\n");
        }
    }
}