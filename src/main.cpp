#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>
#include <cstdlib>

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

    bool make_move(char player, int row, int col) { // retorna true se a escrita foi executada, false caso contrario
        // Implementar a lógica para realizar uma jogada no tabuleiro
        // Utilizar mutex para controle de acesso
        // Utilizar variável de condição para alternância de turnos

    std::unique_lock<std::mutex> lock(board_mutex); 

        if( row>=3 || row<0 || col>=3 || col<0) {
            std::cout << "essa jogada nao eh valida";
            return false;
        }

       
       
        
        while (current_player != player) {  //bloqueia o jogador ate que seja sua vez
        turn_cv.wait(lock);
        }

     
        if(player == 'X' && board[row][col] == '-'){  
            board[row][col]= 'X'; // secao critica, escrevendo em recurso compartilhado
            current_player = 'O';
            turn_cv.notify(lock);
           
            return true;
        }

       
        else if(player == 'O' && board[row][col] == '-') {
            //wait
            board[row][col] = 'O'; // secao critica, escrevendo em recurso compartilhado 
            current_player = 'X';
            turn_cv.notify();
           
            return true;
        }

    
            
        return false;
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

        if(is_game_over()){
            if ( check_win('X') || check_win('O') ){
                return false;}   // nesse caso ha um vencedor
            else{
                return true;}} // ha empate

        return false;} // nesse caso o jogo nao acabou


    bool is_game_over() {
        // Retornar true se o jogo terminou

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

        if(is_game_over() && (!check_draw()) ){
            return winner; }
        else{
            return 'D';} 
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
        if(strategy == "sequencial"){
            play_sequential();
    }
        else if(strategy == "aleatorio"){
            play_random();
        }

private:
    void play_sequential() {
        // Implementar a estratégia sequencial de jogadas

        while(!is_game_over()) {
        
        int escreveu = 0;
         for (int i = 0; i < 3; i=i+1) { 
            for (int j = 0; j < 3; j=j+1) {
                if(game.make_move(symbol,i,j)){   //retorna true se conseguiu escrever no board
                    escreveu = 1;
                    break;
                    }}
            if(escreveu == 1){
                break;
            }}
        }}

    void play_random() {
        // Implementar a estratégia aleatória de jogadas

            while(is_game_over()){
                while(true){
                // gera uma posicao aleatoria entre 0 e 2
                    int linha_aleatoria = std::rand() % 3;
                    int coluna_aleatoria = std::rand() % 3;
                    if(game.make_move(symbol,linha_aleatoria, coluna_aleatoria)){
                        break;
                    }
                
                }
        }}


int main() {
    // Inicializar o jogo e os jogadores

    TicTacToe tabuleiro;

    Player p1(tabuleiro, 'X', "aleatorio");
    Player p2(tabuleiro, 'O', "aleatorio");
    

    // Criar as threads para os jogadores

    std::thread jogador1(&Player::play, &p1);
    std::thread jogador2(&Player::play, &p2);
    

    // Aguardar o término das threads

    jogador1.join();
    jogador2.join();

    // Exibir o resultado final do jogo

    tabuleiro.display_board();

    return 0;
}
