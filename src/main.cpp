#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>

// Classe TicTacToe
class TicTacToe {
private:
    std::array<std::array<char, 3>, 3> board; // Tabuleiro do jogo
    std::mutex board_mutex; // Mutex para controle de acesso ao tabuleiro
    std::condition_variable turn_cv; // Variável de condição para alternância de turnos
    char current_player; // Jogador atual ('X' ou 'O')
    bool game_over; // Estado do jogo
    char winner; // Vencedor do jogo

public:
    TicTacToe() {
        // Inicializar o tabuleiro e as variáveis do jogo
        current_player = 'X';
        game_over = false;
        winner = 'n';

        for (int i = 0; i < 3; ++i) { // iniciando o tabuleiro
            for (int j = 0; j < 3; ++j) {
                board[i][j] = '-';
            }
        }
    
    }

    void display_board() {
        // Exibir o tabuleiro no console
            // Loop duplo para imprimir cada elemento do tabuleiro
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << board[i][j] << ' ';
            }
        std::cout << '\n'; // nova linha
        }
    }

    bool make_move(char player, int row, int col) {
        // Implementar a lógica para realizar uma jogada no tabuleiro
        // Utilizar mutex para controle de acesso
        // Utilizar variável de condição para alternância de turnos

        if( row>=3 || col>=3) {
            cout << "essa jogada nao eh valida";
            return false;
        }

        if(player == 'X'){  
            board_mutex.lock();
            board[row][col] = 'X'; // secao critica, escrevendo em recurso compartilhado 
            board_mutex.unlock();
        }
        else if(player == 'O') {
            board_mutex.lock();
            board[row][col] = 'O'; // secao critica, escrevendo em recurso compartilhado 
            board_mutex.unlock();
        }
        
        
    }

    bool check_win(char player) {
        // Verificar se o jogador atual venceu o jogo

    if(player == 'X'){
        if( board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {
            winner = 'X';
            return true;}
        else if(board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X'){
            winner = 'X';
            return true;}
        else if(board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X'){
            winner = 'X';
            return true;}
        else if(board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X'){
            winner = 'X';
            return true;}
        else if(board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X'){
            winner = 'X';
            return true;}
        else if(board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X'){
            winner = 'X';
            return true;}
        else if(board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X'){
            winner = 'X';
            return true;}
        return false;}

        

    if(player == 'O'){
        if( board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') {
            winner = 'O';;
            return true;}
        else if(board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O'){
            winner = 'O';
            return true;}
        else if(board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O'){
            winner = 'O';
            return true;}
        else if(board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O'){
            winner = 'O';
            return true;}
        else if(board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O'){
            winner = 'O';
            return true;}
        else if(board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O'){
            winner = 'O';
            return true;}
        else if(board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O'){
            winner = 'O';
            return true;}
        return false;}
        
        return false; // retorna false se um jogador nao 'X' ou 'O' for avaliado
    }

    bool check_draw() {
        // Verificar se houve um empate, retorna false se nao ha empate, retorna true se ha empate

        if ( check_win('X') || check_win('O') ){
            return false;}   // nesse caso ha um vencedor
        else{
            return true; // ha empate
        }
    }



    bool is_game_over() {
        // Retornar se o jogo terminou

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j){ 
                if (board[i][j] == '-') {
                return false;                 
                }
            }
        }

        return true;
    }

    char get_winner() {
        // Retornar o vencedor do jogo ('X', 'O', ou 'D' para empate)

        if(is_game_over()){
        return winner;   
    }
        else{
            return 'Q';}
    }

// Classe Player
class Player {
private:
    TicTacToe& game; // Referência para o jogo
    char symbol; // Símbolo do jogador ('X' ou 'O')
    std::string strategy; // Estratégia do jogador

public:
    Player(TicTacToe& g, char s, std::string strat) 
        : game(g), symbol(s), strategy(strat) {}

    void play() {
        // Executar jogadas de acordo com a estratégia escolhida
    }

private:
    void play_sequential() {
        // Implementar a estratégia sequencial de jogadas
    }

    void play_random() {
        // Implementar a estratégia aleatória de jogadas
    }
};

// Função principal

// avaliar isso  --- TicTacToe board;  //  tabuleiro compartilhado entre as threads

int main() {
    // Inicializar o jogo e os jogadores

    // Criar as threads para os jogadores

    // Aguardar o término das threads

    // Exibir o resultado final do jogo

    return 0;
}
