// Menu das opções de impressão
void menu2(arvore *arvoreDoArq, int teste2) {
  int opcaoDeImprimir;
  while (teste2 == 0) {

    printf("\nEscolha o jeito que quer imprimir a árvore:\n"
           "\n1 - pré ordem;"
           "\n2 - em ordem;"
           "\n3 - pós ordem;"
           "\n4 - em largura.\n\n");
    scanf("%d", &opcaoDeImprimir);

    switch (opcaoDeImprimir) {

    case (1):
      printf("\n\nImprimindo a árvore em forma de pré ordem:\n\n");
      preOrdem(arvoreDoArq);
      teste2 = 1;

      break;

    case (2):
      printf("\n\nImprimindo a árvore em forma de em ordem:\n\n");
      emOrdem(arvoreDoArq);
      teste2 = 1;

      break;

    case (3):
      printf("\n\nImprimindo a árvore em forma de pós ordem:\n\n");
      posOrdem(arvoreDoArq);
      teste2 = 1;

      break;

    case (4):
      printf("\n\nImprimindo a árvore em largura:\n\n");
      int h = altura(arvoreDoArq);
      printf("[");
      largura(arvoreDoArq, h, 0);
      printf("]\n\n\n");
      teste2 = 1;
      break;

    default:
      printf("\n\nOpção inválida");
    }
  }
}

// Menu das opções gerais
void menu(arvore *arvoreDoArq) {
  FILE *arq = fopen("arvore.txt", "r");
  int opcao;
  char continua[5] = "sim";
  int teste = 0;
  int hMudou = 0;

  while (strcmp(continua, "sim") == 0 || strcmp(continua, "Sim") == 0 ||
         strcmp(continua, "SIM") == 0 || strcmp(continua, "s") == 0 ||
         strcmp(continua, "S") == 0) {

    int teste2 = 0;

    printf("\nEscolha a opção que deseja executar:\n"
           "\n1 - Ler uma árvore de um arquivo fornecido pelo usuário;"
           "\n2 - Imprimir a árvore;"
           "\n3 - Verficar se um elemento x existe na árvore;"
           "\n4 - Imprimir o nível de um nó x;"
           "\n5 - Imprimir as folhas menores que um valor x;"
           "\n6 - Inserir um nó x na árvore;"
           "\n7 - Remover um nó x da árvore;"
           "\n8 - Sair.\n");

    scanf("%d", &opcao);
    printf("\n");

    switch (opcao) {
    case (1):
      printf("");
      arvoreDoArq = lerAVL(arq);
      printf("A árvore foi lida do arquivo!!\n");

      if (arvoreDoArq != NULL) {
        teste = 1;
      } else {
        teste = 0;
      }
      fclose(arq);

      break;

    case (2):
      menu2(arvoreDoArq, teste2);
      break;
    case (3):
      printf("Verificando se elemento existe na árvore:\n\n");

      int x;
      printf("Insira o elemento (int) que quer verificar se existe "
             "na árvore: \n");
      scanf("%d", &x);
      puts("\n");

      if (existeABB(arvoreDoArq, x) == 1)
        printf("O elemento %d EXISTE na árvore!!", x);
      else
        printf("O elemento %d NÃO existe na árvore!!", x);

      break;

    case (4):
      printf("\n\nImprimindo o nível de um nó x:\n\n");
      int n = 0;
      printf("Digite o número (int) para procurar ele na árvore e "
             "imprimir seu nível: ");
      scanf("%d", &n);
      printf("O nível do nó %d é: ", n);
      printf("[");
      nivelDoNoABB(arvoreDoArq, n, 0);
      printf("]");

      break;

    case (5):
      printf("\n\nImprimindo folhas menores que um valor x:\n\n");
      int f = 0;
      printf("Digite o valor que você quer usar para fazer essa "
             "comparação: ");
      scanf("%d", &f);
      imprimirNosFolhaMenores(arvoreDoArq, f);

      break;

    case (6):
      printf("\n\nInserindo um elemento x na árvore:\n\n");
      int y = 0;
      printf("Digite o valor inteiro que deseja adicionar na árvore: ");
      scanf("%d", &y);
      arvoreDoArq = Inserir(arvoreDoArq, y, &hMudou);

      break;

    case (7):
      printf("\n\nRemovendo um elemento x na árvore:\n\n");
      int z = 0;
      printf("Digite o valor inteiro que deseja retirar na árvore: ");
      scanf("%d", &z);
      arvoreDoArq = Remover(arvoreDoArq, z, &hMudou);

      break;

    case (8):
      if (teste == 1) {
        freearvore(arvoreDoArq);
        printf("\n\nÁrvore liberada da memória!");
      }

      printf("\n\nObrigado por utilizar nosso programa!");
      strcpy(continua, "nao");

      break;

    default:
      printf("Opção inválida");
    }

    if (opcao != 8) {
      printf("\n\nDeseja continuar?\n\n");
      scanf("%s", continua);
      puts("\n");
    }
  }

  if (opcao != 8) {
    printf("\n\nObrigado por utilizar nosso programa!");
  }
}
