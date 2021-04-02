#include "ChunkList.h"


template<class T>
ChunkList<T>::ChunkList() {
    head = nullptr;
    tail = nullptr;
    iterNode = nullptr;
    arrPos = 0;
    listLen = 0;
    numChunks = 0;
}

template<class T>
ChunkList<T>::ChunkList(T *arr, int arrLen) {
    if (arrLen > ARRAY_SIZE){
        throw InvalidArrayLength();
    }
}

template<class T>
ChunkList<T>::~ChunkList() {

}

template<class T>
void ChunkList<T>::Append(T value) {
    if(head == nullptr && tail == nullptr){
        Node* newNode = new Node;
        newNode->values[0] = value;
        newNode->len = 1;
        head = newNode;
        tail = newNode;
        tail->next = nullptr;
        numChunks = numChunks + 1;
    }
    else if(tail->len < ARRAY_SIZE){
        tail->values[tail->len] = value;
        tail->len ++;
    }
    else if(tail->len == ARRAY_SIZE){
        Node* newNode = new Node;
        newNode->values[0] = value;
        newNode->len = 1;
        tail->next = newNode;
        tail = newNode;
        tail->next = nullptr;
        numChunks = numChunks + 1;
    }
    listLen = listLen + 1;
}

template<class T>
void ChunkList<T>::Remove(T value) {
    Node* curr = new Node;
    curr = head;
    if(curr == nullptr){
        throw EmptyList();
    }
    while(curr != nullptr){
        for(int i=0; i<numChunks; i++) {
            for(int j=0; j<curr->len; j++){
                if(curr->values[j] == value){
                    if(curr->len == 1){
                        if(head->values[0] == value){
                            Node* tmp = head;
                            head = head->next;
                            delete tmp;
                            listLen --;
                            numChunks --;
                            return;
                        }
                            //remove last node
                        else if(curr->next == nullptr){
                            delete curr;
                            numChunks = numChunks - 1;
                            listLen = listLen - 1;
                            return;
                        }
                        else{
                            //remove middle node
                            Node* del = curr->next;
                            *curr = *curr->next;
                            if(curr->next == nullptr){
                                curr = nullptr;
                                tail = curr;
                            }
                            else{
                                curr->next = curr->next->next;
                            }
                            delete del;
                            numChunks = numChunks - 1;
                            listLen = listLen - 1;
                            return;
                        }
                    }
                    else{
                        for(int k=j; k<curr->len-1; k++){
                            curr->values[k] = curr->values[k+1];
                        }
                        curr->len = curr->len - 1;
                        listLen = listLen - 1;
                        return;
                    }
                }
            }
            curr = curr->next;
        }
    }
}

template<class T>
int ChunkList<T>::GetLength() {
    return listLen;
}

template<class T>
double ChunkList<T>::LoadFactor() {
    double LoadFactor = double(listLen)/double(numChunks*ARRAY_SIZE);
    return LoadFactor;
}

template<class T>
bool ChunkList<T>::Contains(T value) {
    Node* curr = head;
    while(curr != nullptr){
        for(int i=0; i<numChunks; i++) {
            for (int j = 0; j < curr->len; j++) {
                if (curr->values[j] == value) {
                    return true;
                }
            }
            curr = curr->next;
        }
    }
    return false;
}

template<class T>
T ChunkList<T>::GetIndex(int i) {
    Node* curr = new Node;
    curr = head;
    if(curr == nullptr){
        throw EmptyList();
    }
    while(curr->next != nullptr){
        if(i<curr->len){
            return curr->values[i];
        }
        else if(i == curr->len && curr->len == 1){
            i = i - curr->len;
            curr = curr->next;
            return curr->values[i];
        }
        else if(i == curr->len && curr->len > 1){
            return curr->values[i-1];
        }
        else{
            i = i - curr->len;
            curr = curr->next;
        }
    }
    throw IndexOutOfBounds();
}

template<class T>
void ChunkList<T>::ResetIterator() {
    iterNode = head;
}

template<class T>
T ChunkList<T>::GetNextItem() {
    if(iterNode == nullptr){
        iterNode = head;
    }
    if(iterNode == tail && arrPos == ARRAY_SIZE-1){
        ResetIterator();
    }
    if(arrPos == ARRAY_SIZE-1){
        iterNode = iterNode->next;
        arrPos = 0;
    }
    return iterNode->values[arrPos++];
}

template<class T>
bool ChunkList<T>::IsEmpty() {
    return false;
}


