#include <iostream>
#include <iomanip>

// Definição da estrutura do produto
typedef struct {
    std::string name;
    float price;
    int qtd;
} Product;

//Inicializado o vetor
Product product[12];

//declarando a variavel que irá armazenar a quantidade total de lucro obtida.
double gain;

// Função para exibir os produtos disponíveis para o usuário
void displayProducts() {
    std::cout << "Produtos disponíveis:\n";
    std::cout << "---------------------\n";
    for (int i = 0; i < 12; i++) {
        if(product[i].qtd > 0) {
            std::cout << i+1 << " | " << product[i].name << " | R$" << std::fixed << std::setprecision(2) << product[i].price << std::endl;
        }
    }
    std::cout << "0 | Encerrar\n";
    std::cout << "---------------------\n";
}

// Função que exibe o inventário no modo administrador;
void displayInventory() {

    std::cout << "Produtos disponíveis:\n";
    std::cout << "---------------------\n";
    for (int i = 0; i < 12; i++) {
        std::cout << i+1 << " | " << product[i].name << " | R$" << std::fixed << std::setprecision(2) << product[i].price << " | " << product[i].qtd<< std::endl;
    }
    std::cout << "---------------------\n";
}

//Função para realizar a compra do produto
void buyProduct  (int command){

    //definindo variavel que guarda a quantia depositada e a que armazena o troco;
    double payment;
    double change;
    int qtd;

    std::cout << "Por favor insira a quantidade do produto desejada : \n";
    std::cin >> qtd;
    std::cout << "Por favor insira a quantia inserida como pagamento (digite 0 para cancelar): \n";
    std::cin >> payment;


    //verifica se a compra foi cancelada ou não.
    if (payment != 0){
        //verifica se a quantidade solicitada está disponível
        if(product[command-1].qtd >= qtd) {
            //verifica se o pagamento foi o suficente.
            if (payment < product[command-1].price*qtd) {
                std::cout << "A quantia inserida nao eh o suficiente para realizar a compra, por favor tente novamente. \n";
            } else {
                //realiza a compra e calcula o troco
                product[command-1].qtd = product[command-1].qtd - qtd;
                gain = gain + product[command-1].price*qtd;
                change = payment - product[command-1].price*qtd;

                std::cout << "Muito obrigado por sua compra, seu troco foi de R$" << change << "\n";
            }
        } else {
            std::cout << "A quantidade solicitada deste produto nao esta diponível. Atualmente so temos " << product[command-1].qtd << " unidades desse produto. \n";
            std::cout << "Desculpe-nos pelo inconveniente, por favor tente novamente. \n";
        }
    }
}

void admMode(double initialCash){
    //Definindo variável que vai receber os comandos
    int command = -1;

    //Definindo a váriável que vai receber o código do protudo a ser reabastecido.
    int productCode;

    //Definindo a váriavel que vai armazenar a quantiade de itens a seres reabastecidos.
    int tempQtd;

    //Definindo variavel que vai receber o cash atual da máquina
    double currentCash;

    //Calculando quanto ainda tem de cash em produtos
    for (int i = 0; i < 12; i++) {
        currentCash = currentCash + (product[i].price*product[i].qtd);
    }



    //iniciando laço de comandos do modo administrador
    while(command != 0) {
        std::cout << "1 - Listar Inventario \n";
        std::cout << "2 - Repor Inventario \n";
        std::cout << "3 - Cash Report \n";
        std::cout << "0 - Voltar \n";

        std::cin >> command;

        //verificando se o laço foi cancelado
        if (command != 0) {
            if(command == 1) {
                displayInventory();

            } else if(command == 2) {
                std::cout << "Insira o codigo do produto a ser abastecido.\n";
                std::cin >> productCode;

                std::cout << "Insira a quantidade a ser abastecida.\n";
                std::cin >> tempQtd;

                if (tempQtd + product[productCode-1].qtd <= 20) {
                    product[productCode-1].qtd = product[productCode-1].qtd + tempQtd;

                    std::cout << product[productCode-1].name << " reabastecido com sucesso.\n";
                } else {
                    std::cout << product[productCode-1].name << " reabastecido com sucesso, porem " << tempQtd + product[productCode-1].qtd - 20 << " itens ficaram sobressalentes por exceder a capacidade da maquina.\n";
                    product[productCode-1].qtd = 20;
                }


            } else if(command == 3) {
                std::cout << "O cash inicial do dia foi de R$" << initialCash << "\n";
                std::cout << "O cash atual ainda disponivel para venda eh de R$" << currentCash << "\n";
                std::cout << "O lucro ate o atual momento eh de R$" << gain << "\n";
            } else {
                std::cout << "O comando inserido nao existe, por favor tente novamente \n";
            }
        } else {
            std::cout << "Saindo do modo administrador, por favor aguarde... \n";
        }
    }
};

int main() {
    //Poderiamos sim fazemos uma máquina de venda infinita, mas elas não existem, então fizemos uma com 12 slots;

    //Definindo a configuração inicial do Vetor, que em uma empresa, viria do banco de dados;
    //Por favor, se vier a mecher aki, mantenha os nomes dos produtos de 0 a 8, com 14 caractéres, e os de 9 a 11 com 13 caracteres, a formatação da tabela agradece.
    product[0] = {"Ruffles       ", 10.50f, 10};
    product[1] = {"Doritos       ", 12.30f, 10};
    product[2] = {"Lays          ", 09.00f, 10};
    product[3] = {"Cheetos       ", 06.60f, 10};
    product[4] = {"Hersheys      ", 07.50f, 10};
    product[5] = {"Diamante_Negro", 06.50f, 10};
    product[6] = {"Laka          ", 06.50f, 10};
    product[7] = {"Milka         ", 15.50f, 10};
    product[8] = {"Coca_Cola     ", 06.50f, 10};
    product[9] = {"Sprite       ", 05.50f, 10};
    product[10] = {"Pepsi        ", 06.50f, 10};
    product[11] = {"Fanta_Laranja", 05.50f, 10};

    //definindo variavel que armazena o valor total dos produtos armazenados;
    double initialCash;

    // somando o cash inicial;
    for (int i = 0; i < 12; i++) {
        initialCash = initialCash + (product[i].price*product[i].qtd);
    }

    //Definindo variável que vai receber os comandos
    int command = -1;

    // definindo o codigo a ser usado para entrar no modo admin
    int admPassword;
    admPassword = 1313;

    //Chamando função para exibir os produtos;
    while(command != 0) {
        displayProducts();

        std::cin >> command;

        //verificando a continuidade do laço
        if (command != 0){
            //verificando se o código existe
            if(command != 1313 && command > 12 && command < 0) {
                std::cout << "O comando inserido nao existe, por favor tente novamente \n";
            } else {
                //verificando codigo para possivel inicialização do modo de Administrador.
                if (command == admPassword){
                    std::cout << "Entrando no modo adminitrador, por favor aguarde...\n";
                    admMode(initialCash);
                } else {
                    buyProduct(command);
                }
            }

        }



    }
    std::cout << "Obrigado pela preferencia, volte sempre!\n";
return 0;
}