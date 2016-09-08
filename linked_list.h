
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept> 

//! Classe LinkedList para uma Lista.
/*! 
*   Na classe LinkedList, � implementado o funcionamento de uma lista
*   atrav�s de Nodes que referenciam o pr�ximo valor na lista e o dado na mesma.
*/

namespace structures {

template<typename T>
class LinkedList {
public:

//! Construtor.
/*!
*   Construtor que inicializa o elemento head que ser� usado como cabe�a para a lista.
*/
    LinkedList() {
        size_ = 0;
        head = new Node(0u);
    }
    
//! Destrutor.
/*!
*   Deleta todos os elementos da lista.
*   \sa clear()
*/
    ~LinkedList() {
        clear();    
    }

//! Fun��o repons�vel por limpar a lista.
/*!
*   Faz com que a lista seja limpa.
*   \sa empty(), pop_front()
*/
    void clear() {
        while(!empty()){
            pop_front();
        }
    }

//! Fun��o repons�vel por adicionar um elemento ao final da lista.
/*!
*   Adiciona um elemento ao final da lista.
*   \param data dado a ser adicionado no final da lista. 
*   \sa insert(), size()
*/
    void push_back(const T& data) {
        insert(data, size());
    }

//! Fun��o repons�vel por adicionar um elemento no inicio da lista.
/*!
*   Adiciona um elemento no inicio da lista.
*   \param data dado a ser adicionado no inicio da lista. 
    \sa empty()
*/
    void push_front(const T& data) {
        Node *novo = new Node(data);
        
        if(novo == NULL)
            throw std::out_of_range("listaCheia");
        else{
            if(!empty())
                novo->next(head->next());
            head->next(novo);
            size_++;
        }
    }

//! Fun��o repons�vel por adicionar um elemento em uma posicao da lista.
/*!
*   Adiciona um elemento na posicao solicitada.
*   \param data dado a ser adicionado na lista. 
*   \param index posicao na qual sera adicionado
*   \sa push_front(), size()
*/
    void insert(const T& data, std::size_t index) {
        auto *novo = new Node(data);
        Node *anterior;
        
        if (novo == NULL)
            throw std::out_of_range("listaCheia");
        else{
            if(index > size() || index < 0)
                throw std::out_of_range("posicaoInvalida");
            else{
                if(index == 0)
                    push_front(data);
                else{
                    anterior = head->next();
                    for(int i = 0; i < index -1; i++){
                        anterior = anterior->next();  
                    }
                    if (index != size())
                        novo->next(anterior->next());
                    anterior->next(novo);
                    size_++;
                }
            }
        }
    }

//! Fun��o repons�vel por adicionar um elemento em ordem na lista.
/*!
*   Adiciona um elemento em ordem na lista.
*   \param data dado a ser adicionado na lista. 
*   \sa insert(), push_front(), empty()
*/
    void insert_sorted(const T& data) {
        Node *atual;
        int posicao;
        
        if(empty())
            push_front(data);
        else{
          atual = head->next();  
          posicao = 0;
          while(atual->next() != NULL  && data > atual->data()){
              atual = atual->next();
              posicao++;
          }
          
            if(data > atual->data())
                insert(data, posicao+1);
            else
                insert(data, posicao);
        }
        
    }

//! Fun��o respons�vel por devolver o elemento na posicao index.
/*!
*   Devolve o elemento na posicao solicitada, e caso a mesma nao esteja correta lanca uma excecao. 
*   \param index posicao a qual sera usada para retornar o elemento.
*   \return o elemento correspondente a posicao.
*   \sa empty(), size()
*/
    T& at(std::size_t index) {
        Node *dado = head->next();
        if (empty())
            throw std::out_of_range("listaVazia");
        else{
            if(index > size() || index < 0)
                throw std::out_of_range("posicaoInvalida");
            else{
                for(int i = 0; i < index; i++){
                    dado = dado->next();
                }
                return dado->data();
            }
        }
    }

//! Fun��o repons�vel por retornar e retirar um elemento de uma posicao.
/*!
*   Retira um elemento da posicao que lhe foi solicitada e o retorna.
*   \param index posicao na qual o elemento se encontra.
*   \return o dado retirado.
*   \sa pop_front(), size()
*/
    T pop(std::size_t index) {
        Node* anterior;
        Node* eliminar;
        T volta;

        if(index > size()-1 || index < 0)
            throw std::out_of_range("posicaoInvalida");
        else{
            if(index == 0)
                return pop_front();
            else{
                anterior = head->next();
                for(int i = 0; i < index -1; i++){
                    anterior = anterior->next();  
                }
                eliminar = anterior->next();
                volta = eliminar->data();
                if (index+1 != size())
                    anterior->next(eliminar->next());
                size_--;
                free(eliminar);
                
                return volta;
            }
        }
    }

//! Fun��o repons�vel por retornar e retirar o ultimo elemento da lista.
/*!
*   Retira o ultimo elemento da lista.
*   \return o dado encontrado na ultima posicao da lista.
*   \sa pop(), size(), empty()
*/
    T pop_back() {
        if (empty())
            throw std::out_of_range("listaVazia");
        else
            return pop(size()-1);
    }

//! Fun��o repons�vel por retornar e retirar o primeiro elemento da lista.
/*!
*   Retira o primeiro elemento da lista.
*   \return o dado encontrado na primeira posicao da lista.
*   \sa empty(), size()
*/
    T pop_front() {
        Node *saiu;
        T volta;
        if(empty())
            throw std::out_of_range("listaVazia");
        else{
            saiu = head->next();
            volta = saiu->data();
            if(size() != 1)
                head->next(saiu->next());
            size_--;
            free(saiu);
            
            return volta;
        } 
    }

//! Fun��o repons�vel por remover um dado da lista.
/*!
*   Remove um dado da lista.
*   \param data dado a ser removido.
*   \sa empty(), contains(), pop(), find()
*/
    void remove(const T& data) {
        if(empty())
            throw std::out_of_range("listaVazia");
        else{
            if(contains(data)){
                pop(find(data));  
            }else{
                throw std::out_of_range("dataNotFound");
            }
        } 
    }

//! Fun��o respons�vel por verificar se a lista est� vazia.
/*!
*   Retorna true se a lista estiver vazia.
*   \return uma vari�vel booleana.
*/
    bool empty() const {
        return size_ == 0;
    }

//! Fun��o respons�vel por verificar se um elemento existe no vetor.
/*!
*   Retorna true se o elemento realmente se encontra no vetor.
*   \param data elemento a ser procurado na lista.
*   \return uma vari�vel booleana.
*   \sa size()
*/   
    bool contains(const T& data) const {
        auto *dado = head;
        
        for(int i = 0; i < size(); i++){
            dado = dado->next();
            if(data == dado->data()){
                return true;
            }
        }
        return false;
    }

//! Fun��o respons�vel por retornar a posicao de um elemento no vetor.
/*!
*   Retorna a posicao atual de um elemento no vetor.
*   \param data elemento o qual se deseja saber a posicao.
*   \return um inteiro.
*   \sa size()
*/    
    std::size_t find(const T& data) const {
        auto *dado = head;
        
        for(int i = 0; i < size(); i++){
            dado = dado->next();
            if(data == dado->data())
                return i;
        }
        return size();
        
    }

//! Fun��o repons�vel por retornar a quantidade de dados.
/*!
*   Retorna a quantidade de dados que se encontram na lista.
*   \return um valor.
*/
    std::size_t size() const {
        return size_;
    }
    

    
public:
    class Node {
    public:
        Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }
    private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}

#endif
