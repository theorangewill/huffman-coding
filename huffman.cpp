#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Esta classe armazena o codigo binario de cada caminho, que sera colocado na hashmap
class Codigo{
public:
    Codigo(int x);

    int cod;
    Codigo *prox;
    Codigo *ant;
};

//Esta classe e as celulas da lista encadeada que armazena a frequencia das letras no texto
class Lista_Celula{
public:
    Lista_Celula(char x);

    char letra;
    int freq;
    Lista_Celula *prox;
    Lista_Celula *ant;
};

//Esta classe e a cabeca da lista encadeada que armazena a frequencia das letras no texto
class Lista{
public:
    Lista();

    Lista_Celula *inicio;
    Lista_Celula *fim;
};

//Esta classe sao os nos da arvore de huffman
class Celula_Huff{
public:
    Celula_Huff(char x, int y);
    Celula_Huff(int y);

    char letra;
    int peso;
    int indice;
    int folha;
    Celula_Huff *dir;
    Celula_Huff *esq;
    Celula_Huff *pai;
};

//Esta classe e a cabeca da arvore de huffman
class Huffman{
public:
    Huffman(int n);
    Huffman();
    void construir(Lista lista, int *c);

    Celula_Huff **vetor;
    Celula_Huff *raiz;
};

//Esta classe e as celulas que representam os caminhos na arvore huffman
class Celula_Hash{
public:
    Celula_Hash(int x);

    Celula_Hash *prox;
    Celula_Hash *ant;
    int cod;
    //Se o valor de indice eh 0, essa celula pode ser descartada, pos nao sera mais necessaria
    //(isso ocorre quando, ao percorrer a arvore na construcao dos caminhos, o programa volta para o pai
    //ou seja, quando vai para uma folha)
    //Se o valor de indice eh 1, essa celula sera usada em outro caminho
    int indice;
    //Esse indice eh respecivo a Celula_Huff que esta relacionada
    int indicehuff;
    char letra;
    //Sera necessario saber de qual celula da huffman a celula da hash foi criada
    Celula_Huff *huff;
};

//Esta classe e o vetor da hashmap, com ponteiros para o Codigo, representando o caminho
//na arvore huffman, dependendo de sua letra
class Vetor_Hash{
public:
    Vetor_Hash();

    char letra;
    Codigo *v;
    int ocupado;
};

//Esta classe e a cabeca da hashmap
class Hash{
public:
    void cria_hash(Lista lst, Huffman h, int c);
    void insere_hash(Codigo *inicio, char l);
    Hash(int n);
    int  key(char x, int i, int c);
    void copiar_lista();
    void imprimirhash();
    int  *procurar_hash(char x);

    //Para a construcao da hashmap, sera necessario ponteiros
    //para Celulas_Hash, indicando o inicio da lista e o fim
    Celula_Hash *fim;
    Celula_Hash *comeco;
    //Pra a contrucao da hashmap, sera necessario ponteiro para a Celula_Huff
    //para indicar em qual celula da arvore huffman o programa esta avaliando
    Celula_Huff *atual;
    int tam;
    Vetor_Hash *vetor;
};

//Esta classe armazena o percurso pre-ordem na arvore huffman
class Pre_ordem{
public:
    Pre_ordem(int n);
    ~Pre_ordem();
    void percorrer(Celula_Huff *h);

    int i;
    int j;
    int *v;
    char *c;
};

//Destrutor da classe Pre_ordem, liberando memoria pros dos vetores alocados
Pre_ordem::~Pre_ordem()
{
    free(v);
    free(c);
}

//Construtor da classe Pre_ordem, alocando memoria
//necessaria para o vetor do caminho pre-ordem e pro vetor das letras
Pre_ordem::Pre_ordem(int n)
{
    v = (int *) malloc((2*n-1)*sizeof(int));
    c = (char *) malloc((n)*sizeof(char));
    i = 0;
    j = 0;
}

//Construtor da classe Codigo, com o codigo respectivo
Codigo::Codigo(int x)
{
    ant = NULL;
    prox = NULL;
    cod = x;
}

//Construtor da classe Celula_Hash, iniciando com o codigo recebido
Celula_Hash::Celula_Hash(int x)
{
    prox = NULL;
    ant = NULL;
    cod = x;
    letra = '\0';
    huff = NULL;
    indice = 0;
    indicehuff = 0;
}

//Construtor da classe Huffman, alocando memoria pro minheap
Huffman::Huffman(int n)
{
    raiz = NULL;
    vetor = (Celula_Huff **) malloc(n* sizeof(Celula_Huff *));
}

//Construtor da classe Hash, alocando memoria pro vetor
Hash::Hash(int n)
{
    vetor = (Vetor_Hash *) malloc(n* sizeof(Vetor_Hash));
    fim = NULL;
    comeco = NULL;
    atual = NULL;
    tam = n;
}

//Construtor da classe Vetor_Hash, iniciando sem nenhuma letra
Vetor_Hash::Vetor_Hash()
{
    letra = '\0';
    v = NULL;
    ocupado = 0;
}

//Construtor da classe Celula_Huff quando se trata de um no folha, entao possui letra
Celula_Huff::Celula_Huff(char x, int y)
{
    letra = x;
    peso = y;
    folha = 1;
    indice = 0;
    dir = NULL;
    esq = NULL;
    pai = NULL;
}

//Construtor da classe Celula_Huff quando se trata de um no nao folha, que nao possui letra
Celula_Huff::Celula_Huff(int y)
{
    letra = '\0';
    peso = y;
    folha = 0;
    indice = 0;
    dir = NULL;
    esq = NULL;
    pai = NULL;
}

//Construtor da classe Lista, anulando o inicio e o fim da lista
Lista::Lista()
{
    inicio = NULL;
    fim = NULL;
}

//Construtor da classe Lista_Celula, iniciando a frequencia como 1 e recebendo uma letra
Lista_Celula::Lista_Celula(char x)
{
    prox = NULL;
    ant = NULL;
    letra = x;
    freq = 1;
}

//Declaracao de funcoes
Lista frequencia(char *texto, int *c, int tam);
void insere_folha(int n, Celula_Huff **vetor, Celula_Huff *p);
void insere_no(int *n, Celula_Huff **vetor, Celula_Huff *p);
Celula_Huff *minima(Celula_Huff **vetor, int *n);
Celula_Hash *recursivo(Celula_Huff *z, int x);
void insere_hash(Celula_Hash inicio, Hash table, char l);
void compactar(Huffman h, Hash table, FILE *ph, int tam, char *s);

//Esta funcao libera a memoria alocada para a arvore de huffman (todos os nos)
void liberar_huff(Celula_Huff *h)
{
    if(h != NULL){
        liberar_huff(h->esq);
        liberar_huff(h->dir);
        delete(h);
    }
}

//Esta funcao libera a memoria alocada para a hashmap (o vetor da hash e as listas de cada celula do vetor)
void liberar_hash(Hash table)
{
    Vetor_Hash *p;
    Codigo *t, *h;
    int i;

    for(i = 0; i<table.tam; i++){
        p = table.vetor;
        t = p[i].v;
        while(t != NULL){
            h = t;
            t = t->prox;
            delete(h);
        }
    }
    free(p);
}

//Esta funcao libera a memoria alocada para a lista encadeada das frequencias das letras
void liberar_lista(Lista l)
{
    Lista_Celula *p, *q;

    p = l.inicio;

    while(p!=NULL){
        q = p;
        p = p->prox;
        delete(q);
    }

    l.inicio = NULL;
    l.fim = NULL;
}

int main(int argc,char *argv[])
{
    char *s;
    int c = 0, d, tam;
    long unsigned int n = 1;
    Lista l;
    FILE *pt, *ph;

    //Caso a opcao seja para compactar
    if(strcmp(argv[1],"c") == 0){
        //pt recebe o arquivo para ler
        pt = fopen(argv[2],"r");
        //ph recebe o arquivo de escrita
        ph = fopen(argv[3],"w");

        //Se for possivel manusear tais arquivos
        if(pt!= NULL && ph != NULL){
            //Aloca memoria pra armazenar o texto
            s= (char *) malloc (n + 1);
            //s recebe o texto no arquivo em pt, colocando um '\n' no final
            //tam recebe o tamanho do texto
            tam = getline(&s, &n, pt);

            //Calcula a frequencia das letras no texto e cria uma lista encadeada
            l = frequencia(s, &c, tam);

            Huffman h(c);
            d = c;
            //Cria a arvore huffman
            h.construir(l,&d);


            Hash table(c);
            //Cria a hashmap
            table.cria_hash(l, h, c);

            //Compacta o arquivo
            compactar(h,table,ph,tam,s);

            //Libera a memoria alocada
            liberar_huff(h.raiz);
            liberar_hash(table);
            liberar_lista(l);
            free(h.vetor);
            free(s);
            //Fecha os arquivos
            fclose(pt);
            fclose(ph);
        }
    }
    return 0;
}

//Esta funcao compacta um arquivo de texto em um arquivo .huff
void compactar(Huffman h, Hash table, FILE *ph, int tam, char *s)
{
    //O valor de k possui o numero de letras no texto
    unsigned char k;
    k = (char)table.tam;
    fputc(k,ph);

    //O valor de t possui o tamanho do texto
    unsigned int t;
    t = tam-1;
    fwrite(&t,sizeof(int),1,ph);

    Pre_ordem ordem(table.tam);
    //Percorre a arvore de huffman em pre-ordem e armazena o caminho e as letras em vetores
    ordem.percorrer(h.raiz);
    int i;
    //Escreve no arquivo as letras do texto
    for(i=0;i<table.tam; i++){
        fputc(ordem.c[i],ph);
    }

    unsigned char caminho;
    int n, j = 0;
    n = 2*table.tam-1;
    i=0;
    caminho = 0;
    //Enquante nao sobra um byte do vetor
    while(n > 8){
        //Caminho recebe o primeiro valor do caminho pre-ordem
        caminho = ordem.v[i];
        //Armazeno em caminho o vetor do caminho pre-ordem em tamanho de byte
        while(i < 7+j){
            i++;
            caminho = caminho << 1;
            caminho = caminho | ordem.v[i];
        }
        //Ja foi lido um byte
        n = n-8;
        //Escreve o caminho no arquivo
        fputc(caminho,ph);
        //Ja foi lido um byte
        j+=8;
        i++;
    }
    //Zera o caminho
    caminho = 0;
    //Se ainda tiver bits no caminho, termina de armazenar o caminho
    if(n != 0){
        j = n;
        caminho = ordem.v[i];
        while(j > 1){
            i++;
            caminho = caminho << 1;
            caminho = caminho | ordem.v[i];
            j--;
        }
    }

    n = 8-n;

    int *vetor;
    j=0;
    i=0;
    //Se o byte em construcao nao foi totalmente preenchido,
    //Termina-se de preencher compactando o arquivo ja
    if(n != 0){
        //Procura na hash o caminho da letra no texto
        vetor = table.procurar_hash(s[j]);

        //Se nao for o fim do texto e numero de bits a serem
        //lidos sao maiores q o tamanho do caminho
        while(n>vetor[0] && s[j] != '\n'){
            //Enquanto for menor q o tamanho do caminho, armazeno o caminho
            while(i < vetor[0]){
                i++;
                caminho = caminho << 1;
                caminho = caminho | vetor[i];
                n--;
            }
            j++;
            free(vetor);
            //Procuro a proxima letra
            vetor = table.procurar_hash(s[j]);
            i = 0;
        }
        //Se o caminho eh maior q a qunatidade de bits faltando ppra concluir um byte
        while(n != 0 && s[j] != '\n'){
            i++;
            caminho = caminho << 1;
            caminho = caminho | vetor[i];
            n--;
        }
        fputc(caminho,ph);
    }

    //Armazena o texto no arquivo
    unsigned int texto;
    //Caso a letra anterior terminou de ser lida, pega proxima letra
    if(i >= vetor[0] || i == 0){
        j++;
        free(vetor);
        vetor = table.procurar_hash(s[j]);
        i = 0;
    }
    n = 0;
    //Enquanto nao chega o final do texto
    while(s[j] != '\n'){
        //Armazeno o caminho
        while(i < vetor[0] && n < 8){
            i++;
            texto = texto << 1;
            texto = texto | vetor[i];
            n++;
        }
        //Se concluiu um byte, insere no arquivo
        if(n == 8){
            fputc(texto,ph);
            texto = 0;
            n = 0;
        }
        //Se terminou o caminho, pega outro caminho
        if(i >= vetor[0]){
            i = 0;
            j++;
            free(vetor);
            vetor = table.procurar_hash(s[j]);
        }
    }
    //Desloca o ultimo byte do arquivo para alinhar os bits para direita
    n = 8 - n;
    texto = texto << n;

    if(vetor != NULL)
        free(vetor);
    fputc(texto,ph);
}

//Esta funcao procura um valor na hashmap e retorna um vetor com o codigo binario da letra requirida
int *Hash::procurar_hash(char x)
{
    int k, s = 0, *v, i;
    Codigo *p;

    //Vetor inicia com uma posicao
    v = (int *) malloc(1*sizeof(int));
    //O primeiro valor recebe o numero de codigos que o caminho para essa letra possui
    v[0] = 0;
    do{
        //Calcula a key para a hashmap
        k = key(x, s, tam);
        //Se a letra for igual
        if(vetor[k].letra == x){
            //Copia os codigos do caminho para o vetor, realocando a memoria do vetor a cada incremento
            for(p=vetor[k].v, i=1; p!=NULL; p = p->prox, i++){
                v = (int *) realloc(v, (i+1)*sizeof(int));
                v[i] = p->cod;
            }
            s = tam;
        }
        else
        //Se nao calcula nova key
            s++;
    }while(s != tam);
    //O primeiro valor recebe o numero de codigos que o caminho possui
    v[0] = i-1;

    return v;
}

//Esta funcao percorre a arvore de huffman e constroi um vetor com o caminho pre-ordem
//Caso o no na arvore nao for folha, recebe valor 0, se eh folha, recebe 1
//Tambem constroi um vetor para armazenas as letras conforme sao encontradas na arvore
void Pre_ordem::percorrer(Celula_Huff *h)
{
    if(h != NULL){
        if(h->folha == 1){
            v[i] = 1;
            c[j] = h->letra;
            j++;
        }
        else
            v[i] = 0;
        i++;
        percorrer(h->esq);
        percorrer(h->dir);
    }
}

//Esta funcao calcula e retorna uma key para a hashmap
int Hash::key(char x, int i, int c)
{
    int y;
    y = (int)x;
    return  ((y%10)+i)%c;
}

//Esta funcao cria a hashmap para o codigo de cada letra no texto
void Hash::cria_hash(Lista lst, Huffman h, int c)
{
    Celula_Huff *w;
    Celula_Hash *p, *x, *q;
    int c1, s, k;
    Lista_Celula *l;

    //Inserimos as letras do texto no vetor da hash
    for(l = lst.inicio; l != NULL; l = l->prox){
        s = 0;
        do{
            //Calculamos a key da letra para colocar na hash
            k = key(l->letra, s, c);
            //Se nao estiver ocupado
            if(vetor[k].ocupado == 0){
                //O indice do vetor vai receber a letra
                vetor[k].letra = l->letra;
                vetor[k].ocupado = 1;
                s = c;
            }
            //Se estiver ocupado, vai calcular uma nova key
            else
                s++;
        }while (s != c);
    }

    p = NULL;
    x = NULL;
    //Atual armazena o ultimo no na arvore huffman que passou
    atual = h.raiz;
    c1 = c;

    while(atual != NULL){
        //Percorremos o caminho a esquerda do no atual
        x = recursivo(atual,0);
        //Se for a primeira vez, o comeco vai ser no x
        if(c1 == c){
            comeco = x;
        }
        //Se o no for uma folha, o fim vai receber os respectivos valores de quando eh uma folha
        if(x == NULL && fim != NULL){
            fim->indice = 0;
            fim->letra = atual->letra;
            fim->huff = atual->pai;
            fim->indicehuff = fim->huff->indice;
        }
        //Se x tiver um caminho de pelo menos duas celulas
        if(x != NULL && x->prox != NULL){
            //Encadeamos o caminho, se o caminho de x nao foi percorrido
            if(comeco != NULL && fim != NULL && x->prox->indicehuff == 0){
                fim->prox = x;
            }
        }
        //Se x tiver um caminho de uma celula
        else if(x != NULL){
            //Encadeamos o caminho, se o caminho de x nao foi percorrido
            if(comeco != NULL && fim != NULL && x->indicehuff == 0){
                fim->prox = x;
                x->ant = fim;
            }
        }

        //Se fim nao esta armazenando nada, caminhamos a lista para armazenar o ultimo
        if(fim == NULL){
            for(fim = comeco; fim->prox != NULL; fim= fim->prox)
                ;
        }

        //Atual recebe a celula em que o fim esta
        atual = fim->huff;

        //Copia a lista construida e insere na hash
        copiar_lista();

        //Se o caminho da esquerda e da direita de atual ja foram percorridas
        if(atual->esq->indice == 1 && atual->dir->indice == 1){
            //Concluimos a pesquisa no atual
            atual->indice = 1;
            //Se atual nao eh raiz
            if(atual != h.raiz){
                //Achamos o proximo filho direito, deletando as celulas conforme sobe na arvore
                w = atual->pai->dir;
                while(atual == w){
                    atual = atual->pai;
                    atual->indice = 1;
                    if(atual->pai != NULL)
                        w = atual->pai->dir;
                    else
                        atual = NULL;
                    if(atual != NULL){
                        q = fim;
                        fim = fim->ant;
                        if(fim != NULL)
                            fim->prox = NULL;
                        if(comeco == fim)
                            comeco = NULL;
                        delete(q);
                    }
                }
            }
            //Se eh raiz
            else
                atual = NULL;
            //Se atual nao era raiz, sube e deleta a ultima celula
            //q sera alterada da esquerda para ser para direita
            if(atual != NULL){
                atual = atual->pai;
                q = fim;
                if(comeco == fim)
                    comeco = NULL;
                fim = fim->ant;
                if(fim != NULL){
                    fim->prox = NULL;
                }
                delete(q);
            }
            //Se atual era raiz, entao deletara a ultima celula do caminho e fim e comeco serao nulos
            else{
                delete(fim);
                fim = NULL;
                comeco = NULL;
            }
        }
        //Se nao terminou de percorrer toda a arvore
        if(atual != NULL){
            //Cria uma celula pra direita
            p = new Celula_Hash(1);
            //Tem indice 1, pois pode ter caminho pra esquerda e pra direita
            p->indice = 1;
            p->huff = atual;
            p->indicehuff = p->huff->indice;
            atual = atual->dir;
            if(fim != NULL)
                fim->prox = p;
            if(comeco == NULL)
                comeco = p;
            p->ant = fim;
            fim = p;
        }
        //Decrementa a quantidade de letras a serem lidas
        c1--;
    }
}

//Esta funcao faz a copia de uma lista
//Especificamente: copia uma lista de Celula_Hash para uma lista do tipo Codigo
void Hash::copiar_lista()
{
    Celula_Hash *p, *q;
    Codigo *c, *inicio, *ante;
    char l;

    c = NULL;
    inicio = NULL;
    ante = NULL;
    q = NULL;

    //Percorre a lista de Celulas_Hash
    for(p = comeco; p != NULL; p = p->prox){
        //Cria uma nova celula do tipo Codigo
        c = new Codigo(p->cod);
        //Se for a primeira celula, temos o inicio da lista
        if(ante == NULL){
            inicio = c;
        }
        //Se nao encadeamos a lista
        else{
            c->ant = ante;
            ante->prox = c;
        }
        //Salva ate em qual Celula_Hash temos o indice 1
        //Para saber em qual caminho temos q retornar
        if(p->indice == 1){
            fim = p;
        }
        p->ant = q;
        ante = c;
        q = p;
    }

    l = q->letra;
    atual = q->huff;

    if(q!=NULL && q->ant!=NULL)
        q->ant->prox = NULL;

    //Se for a ultima letra a ser inserida
    if(q == comeco && q == fim){
        comeco = NULL;
        fim = NULL;
    }

    //Libera na memoria a ultima celula, que nao sera mais necessaria
    delete(q);

    //Insere a lista copiada
    insere_hash(inicio, l);
}

//Esta funcao insere uma lista encadeada na hash
void Hash::insere_hash(Codigo *inicio, char l)
{
    int k, s = 0;


    do{
        //Procura a key para inserir na hash
        k = key(l, s, tam);
        //Se a letra na hash for igual a letra do caminho
        if(vetor[k].letra == l){
            vetor[k].v = inicio;
            s = tam;
        }
        //Se nao, tentamos uma nova key
        else
            s++;
    }while(s != tam);
}

//Esta funcao cria celula da hash para o percurso a esquerda do no z da huffman
//Retorna uma lista encadeada de celulas da hash com o percurso a esquerda do no z
Celula_Hash *recursivo(Celula_Huff *z, int x)
{
    Celula_Hash *y;
    //Se z eh uma folha, nao ha percurso a esquerda
    if(z->folha == 1){
        //No ja foi visitado
        z->indice = 1;
        return NULL;
    }
    //Se z nao eh uma folha, entao ha percurso a esquerda
    else{
        y = new Celula_Hash(x);
        //Para cada caminho a esquerda tem codigo 0
        y->prox = recursivo(z->esq, 0);
        //Se y eh a ultima celula hash da lista
        if(y->prox == NULL){
            //Esse indice pertence apenas a essa letra
            y->indice = 0;
            //A ultima celula recebe a letra correspondente do caminho
            y->letra = z->esq->letra;
            //A celula recebe o valor do no huff q ela saiu
            y->huff = z;
            y->indicehuff = y->huff->indice;
        }
        //Se y nao eh a ultima celula hash da lista
        else{
            //Esse indice vai ser utilizado pra outro caminho
            y->indice = 1;
            //A celula recebe o valor do no huff q ela saiu
            y->huff = z;
            y->indicehuff = y->huff->indice;
        }
    }
    return y;
}

//Esta funcao percorre o texto calculando a frequencia de cada letra
//Retorna uma uma lista duplamente encadeada ordenada armazenando as letras e suas frequencias
Lista frequencia(char *texto, int *c, int tam)
{
    int i, enc = 0;
    Lista l;
    Lista_Celula *q;
    Lista_Celula *p = new Lista_Celula(texto[0]);

    (*c)++;
    l.inicio = p;
    l.fim = p;

    //Percorre o texto
    for(i=1; i<tam-1; i++){
        p = l.inicio;
        //Percorre a lista ate o fim
        while(p != NULL){
            //Se a letra na celula da lista for igual a letra no texto
            if(p->letra == texto[i]){
                //Aumenta a frequencia
                p->freq++;
                enc = 1;
                q = p;
                p = NULL;
            }
            else
                p=p->prox;
        }
        //Se a letra nao foi encontrada
        if(enc != 1){
            //Cria uma nova celula com a nova letra encontrada
            p = new Lista_Celula(texto[i]);
            q = l.fim;
            q->prox = p;
            p->ant = q;
            l.fim = p;
            (*c)++;
        }
        //Se a letra foi encontrada
        else{
            p = q;
            q = p->ant;
            //Ordena a lista
            while(q != NULL){
                if(q->freq < p->freq){
                    if(q->ant != NULL)
                        q->ant->prox = p;
                    if(p->prox != NULL)
                        p->prox->ant = q;
                    p->ant = q->ant;
                    q->prox = p->prox;
                    p->prox = q;
                    q->ant = p;
                    if(p == l.fim)
                        l.fim = q;
                    if(q == l.inicio)
                        l.inicio = p;
                    q = p->ant;
                }
                else{
                    q = NULL;
                }
            }
        }
        enc = 0;
    }
    return l;
}

//Esta funcao constroi a huffman a partir de uma minheap
void Huffman::construir(Lista lista, int *c)
{
    Lista_Celula *q;
    Celula_Huff *z, *x, *y;
    int n;

    q = lista.fim;

    //Insere na minheap as letras e suas frequencias
    //Essa insercao e so para as folhas da huffman
    for(n=0; q!=NULL; n++){
        z = new Celula_Huff(q->letra, q->freq);
        insere_folha(n,vetor,z);
        q = q->ant;
    }

    //Insere os nos na min heap ate estar apenas uma celula da minheap preenchida
    while((*c)>1){
        //Extrai a minima
        x = minima(vetor,c);
        delete(vetor[n-1]);
        n--;
        //Extrai a minima
        y = minima(vetor,c);
        z = new Celula_Huff(x->peso + y->peso);
        //O novo no recebe as duas minimas extraidas como filhos
        z->dir = y;
        y->pai = z;
        z->esq = x;
        x->pai = z;
        //Insere o novo no na minheap
        insere_no(c,vetor,z);
    }
    //Assim q sobrar apenas uma celula na minheap, ela sera a raiz ca arvore huffman
    raiz = minima(vetor,c);
    delete(vetor[n-1]);
}

//Esta funcao retorna o pai do indice i
int pai(int i)
{
    if(i==0)
        return 0;
    else
        return (i-1)/2;
}

//Esta funcao retorna o filho esquerdo do indice i
int esquerdo(int i)
{
    return 2*(i+1)-1;
}

//Esta funcao retorna o filho direito do indice i
int direito(int i)
{
    return 2*(i+1);
}

//Esta funcao sobe o valor do indice i na minheap
//ate a min heap estar com suas propriedades corretas
void sobe(Celula_Huff **vetor, int i)
{
    int dad;
    Celula_Huff *aux;

    dad = pai(i);

    while(vetor[dad]->peso > vetor[i]->peso){
        aux = vetor[dad];
        vetor[dad] = vetor[i];
        vetor[i] = aux;

        i = dad;
        dad = pai(i);
    }
}

//Esta funcao insere uma folha da arvore huffman na minheap
void insere_folha(int n, Celula_Huff **vetor, Celula_Huff *z)
{
    vetor[n] = z;
}

//Esta funcao insere um no da arvore huffman na minheap
void insere_no(int *n, Celula_Huff **vetor, Celula_Huff *z)
{
    vetor[*n] = z;
    *n = *n+1;
    sobe(vetor, *n-1);
}

//Esta funcao desce o valor do indice i da minheap
//ate a minheap estar com suas propriedades corretas
void desce(int n, Celula_Huff **vetor, int i)
{
    int e, d, menor;
    Celula_Huff *aux;

    e = esquerdo(i);
    d = direito(i);
    if (e < n && vetor[e]->peso < vetor[i]->peso)
        menor = e;
    else
        menor = i;
    if (d < n && vetor[d]->peso < vetor[menor]->peso)
        menor = d;
    if (menor != i) {
        aux = vetor[menor];
        vetor[menor] = vetor[i];
        vetor[i] = aux;
        desce(n, vetor, menor);
    }
}

//Esta funcao extrai e retorna a celula huffman de valor minimo da min-heap
Celula_Huff *minima(Celula_Huff **vetor, int *n)
{
    Celula_Huff *menor;

    menor = vetor[0];
    vetor[0] = vetor[*n-1];
    vetor[*n-1] = NULL;
    *n = *n-1;
    desce(*n, vetor, 0);
    return menor;
}

