#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

// source: https://azrael.digipen.edu/~mmead/www/mg/getopt/index.html

int main(int argc, char *argv[])
{
    printf("Hello world!\n");

    // demo_short_options(argc, argv);
    // demo_long_options(argc, argv);
    generate_demo_cmd();
    // demo_token();

    return 0;
}

void demo_token(void)
{
    // char string[50] = "Hello world";
    char *string = "Hello world";
    // Extract the first token
    char * token = strtok(string, " ");
    printf( " %s\n", token ); //printing the token
}

void generate_demo_cmd(void)
{
    char str[64];
    char *tokens[50];  // Array to store tokens
    int num_tokens = 0;
    const char* cmd = "run --uart 9600 --spi PORTB --i2c RTC --reboot";

    int len = strlen(cmd);

    strncpy(str, cmd, strlen(cmd));

    printf("Command string: %s", str);
    // fgets(str, 100, stdin);  // Use fgets for more safety

    // Remove trailing newline, if any
    // str[strcspn(str, "\n")] = '\0';

    // Split the string into tokens using strtok
    char *token = strtok(str, " ");
    while (token != NULL)
    {
        tokens[num_tokens++] = token;
        token = strtok(NULL, " ");
    }

    printf("\n");

    demo_long_options(num_tokens, tokens);

    /*
    printf("Number of tokens: %d\n", numTokens);
    printf("Tokens:\n");
    for (int i = 0; i < numTokens; i++)
    {
        printf("%s\n", tokens[i]);
    }
    */
}

void proces_command(char *cmd) {
    char str[64];
    char *tokens[24];  // Array to store tokens
    int num_tokens = 0;
    int len = strlen(cmd);

    // copy the command into buffer
    strncpy(str, cmd, strlen(cmd));

    // Remove trailing newline, if any
    str[strcspn(str, "\n")] = '\0';

    // Split the string into tokens using strtok
    char *token = strtok(str, " ");
    while (token != NULL)
    {
        tokens[num_tokens++] = token;
        token = strtok(NULL, " ");
    }

    printf("\n");

    demo_long_options(num_tokens, tokens);
}

int demo_short_options(int argc, char *argv[])
{
    int opt;

    while ((opt = getopt(argc, argv, "u:s:i:")) != -1)
    {
        switch (opt)
        {
        case 'u':
            printf("Option uart was provided: %s\n", optarg);
            break;
        case 's':
            printf("Option spi was provided: %s\n", optarg);
            break;
        case 'i':
            printf("Option i2c was provided: %s\n", optarg);
            break;
        }
    }
}

int demo_long_options(int argc, char *argv[])
{
    int c;

    while (1)
    {
        int option_index = 0;
        static struct option long_options[] =
        {
            {"uart",    required_argument, NULL,  0 },
            {"spi",     required_argument, NULL,  0 },
            {"i2c",     required_argument, NULL,  0 },
            {"cpu",     optional_argument, NULL,  0 },
            {"verbose", no_argument,       NULL,  'v' },
            {"reboot",  no_argument,       NULL,  0 },
            {NULL,      0,                 NULL,  0 }
        };

        c = getopt_long(argc, argv, "u::s:i:cvr", long_options, &option_index);
        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            printf("long option %s", long_options[option_index].name);
            if (optarg)
                printf(" with arg %s", optarg);
            printf("\n");
            break;

        case 1:
            printf("regular argument '%s'\n", optarg); /* non-option arg */
            break;

        case 'u':
            printf("option u with value '%s'\n", optarg);
            break;

        case 's':
            printf("option s with value '%s'\n", optarg);
            break;

        case 'i':
            printf("option i with value '%s'\n", optarg);
            break;

        case 'c':
            printf("option c with value '%s'\n", optarg ? optarg : "NULL");
            break;

        case 'v':
            printf("option v with value '%s'\n", optarg ? optarg : "NULL");
            break;

        case 'r':
            printf("option r with value '%s'\n", optarg ? optarg : "NULL");
            break;

        case '?':
            printf("Unknown option %c\n", optopt);
            break;

        case ':':
            printf("Missing option for %c\n", optopt);
            break;

        default:
            printf("?? getopt returned character code %c ??\n", c);
        }
    }
}

